/**************************************************************************
 * @ 观察者模式
 * @ brief
     1、多个对象依赖一个对象，被依赖对象状态改变时，所有依赖者自动被通知
     2、观察者模式可以减弱对象、被通知对象的耦合
	 3、转化直接依赖为间接依赖，具体关系由Subject动态设定
	 4、Subject、Observer可相对独立复用、修改
	 5、对比delegate.h委托机制
 * @ author zhoumf
 * @ date 2014-11-4
 ************************************************************************/
#pragma once


/************************************************************************/
// 抽象 基类
class iSubject;
class iObserver{
public:
	//cObj_Observer* m_pObj; // 将m_pObj作为Update()的参数，降低耦合
	virtual void Update(const int& data) = 0;

	// new出的Observer，若有多个Subject引用同一Observer，应写一套回收机制
	void AddUseNum() { ++m_useNum; }
	//void Release() { if (--m_useNum == 0) delete this; }

	/*注意：1、operator delete后，不要在析构函数里清数据
			2、因为析构函数被调用，对象不一定释放内存
			3、清数据要在真正delete对象后 */
	virtual ~iObserver() { --m_useNum; }  // 【delete操作：先调析构函数，再调operator delete】
	void operator delete(void* p, size_t) // 继承层次中size_t形参不可少，且——虚析构函数——决定所指对象大小
	{
		if (((iObserver*)p)->m_useNum == 0)
		{
			delete p; // 重载后，里面的delete不会再调析构函数了
					  // 真正释放内存，这里做数据清理（原本析构函数干的事情）
			cout << "Delete Observer" << endl;
		}
	}
private:
	size_t m_useNum{0}; // 构造函数初始化覆盖类内部初始化
};

class iSubject{ // 要观察的对象
public:
	virtual ~iSubject() {} // 基类虚析构函数（易忘记）

	void Attach(iObserver* pObserver)
	{
		if (NULL == pObserver) return;
		m_list.push_back(pObserver);
		pObserver->AddUseNum();
	}
	void Detach(iObserver* pObserver)
	{
		if (NULL == pObserver) return;
		ListPtr::iterator it = m_list.begin();
		for (; it != m_list.end(); ++it){
			if ((*it) == pObserver){
				m_list.erase(it);
				break;
			}
		}
	}
	void Notify(const int& data)
	{
		//遍历C类型的数组、初始化列表以及任何重载了非成员begin()和end()的类型
		for (auto& v : m_list) v->Update(data); // 最好加上'&'
		//ListPtr::iterator it = m_list.begin();
		//for (; it != m_list.end(); ++it){ (*it)->Update(data); }
	}
private:
	typedef list< My_unique_ptr<iObserver> > ListPtr;
	ListPtr m_list;
};

/************************************************************************/
// 子类功能，平行扩展
class cObserverA : public iObserver{
public:
	void Update(const int& data) override { cout << "Update A Observer" << endl; }
};

class cObserverB : public iObserver{
public:
	void Update(const int& data) override { cout << "Update B Observer" << endl; }
};

/************************************************************************/
// 示例
void test_Observer(){
	cout << "——————————————观察者模式——————————————" << endl;
	iSubject obj;

	// 可用工厂统一 new cObserver
	for (int i = 0; i < 1; ++i)
	{
		obj.Attach(new cObserverA);
	}
	obj.Notify(50);
}

/*不足：1、抽象通知者(iSubject)依赖抽象观察者(iObserver)
		2、抽象观察者不一定方便实现，如项目迭代中要将一个已封装好的类做为观察者
		3、具体观察者，不一定是Update()方法被调用（接口难以统一）*/
/************************************************************************/
/*事件委托：
		1、委托可看作是对函数接口的抽象
		2、一个委托对象可搭载多个方法，所有方法依次唤起
		3、委托对象所搭载的方法不必来自同一个类，方法具备相同的参数表、返回值类型即可
		4、【如何搭载类的非静态成员函数？】见MessageMap.h中的成员函数指针用法*/

template<typename TReturn, typename TParam>
class cEntrust{
private:
	typedef TReturn (*Ptr_Fun)(void*, TParam); // 函数指针
	struct stFun{
		void* pObj;   // 为使static函数能访问成员变量，用void*统一接收对象，各搭载方法自己强转（如果那个对象析构了，此指针不就野了！！！）
		Ptr_Fun pFun;
		stFun(void* p, Ptr_Fun fun) : pObj(p), pFun(fun) {}
		TReturn operator()(TParam param) { return pFun(pObj, param); }
	};
	vector<stFun> m_vecFun;
public:
	cEntrust() {}
	void Add(void* p, Ptr_Fun fun) { m_vecFun.push_back(stFun(p, fun)); }
	cEntrust& operator+=(const cEntrust& obj){
		//vector<stFun>::const_iterator it = obj.vecFun.begin();
		for (auto it = obj.m_vecFun.begin(); obj.m_vecFun.end() != it; ++it)
		{
			m_vecFun.push_back(*it);
		}
		return *this;
	}
	void operator()(TParam param)
	{
		for (stFun& v : m_vecFun) v(param); // 别忘了'&'
	}
};

/************************************************************************/
// 示例
// 要搭载的方法
class cObserverC{
public:
	LPCSTR name{ "ObserverC" };
	static void Fun_1(void* p, int data)
	{
		cObserverC* pObj = (cObserverC*)p; // 各自强转
		cout << "事件委托（" << pObj->name << "）输出：" << data << endl;
	}
};
class cObserverD{
public:
	LPCSTR name{ "ObserverD" };
	static void Fun_2(void* p, int data)
	{
		cObserverD* pObj = (cObserverD*)p; // 各自强转
		cout << "事件委托（" << pObj->name << "）输出：" << data << endl;
	}
};
void test_Entrust(){
	cout << "——————————————事件委托 Entrust——————————————" << endl;
	cObserverC objC;
	cObserverD objD;

	typedef cEntrust<void, int> Entrust;
	Entrust entrust;

	Entrust temp;
	temp.Add(&objD, cObserverD::Fun_2);

	entrust.Add(&objC, cObserverC::Fun_1);
	entrust.Add(&objD, cObserverD::Fun_2);
	entrust += temp;
	entrust(10);
}