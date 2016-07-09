/**************************************************************************
 * @ �۲���ģʽ
 * @ brief
     1�������������һ�����󣬱���������״̬�ı�ʱ�������������Զ���֪ͨ
     2���۲���ģʽ���Լ������󡢱�֪ͨ��������
	 3��ת��ֱ������Ϊ��������������ϵ��Subject��̬�趨
	 4��Subject��Observer����Զ������á��޸�
	 5���Ա�delegate.hί�л���
 * @ author zhoumf
 * @ date 2014-11-4
 ************************************************************************/
#pragma once


/************************************************************************/
// ���� ����
class iSubject;
class iObserver{
public:
	//cObj_Observer* m_pObj; // ��m_pObj��ΪUpdate()�Ĳ������������
	virtual void Update(const int& data) = 0;

	// new����Observer�����ж��Subject����ͬһObserver��Ӧдһ�׻��ջ���
	void AddUseNum() { ++m_useNum; }
	//void Release() { if (--m_useNum == 0) delete this; }

	/*ע�⣺1��operator delete�󣬲�Ҫ������������������
			2����Ϊ�������������ã�����һ���ͷ��ڴ�
			3��������Ҫ������delete����� */
	virtual ~iObserver() { --m_useNum; }  // ��delete�������ȵ������������ٵ�operator delete��
	void operator delete(void* p, size_t) // �̳в����size_t�ββ����٣��ҡ�����������������������ָ�����С
	{
		if (((iObserver*)p)->m_useNum == 0)
		{
			delete p; // ���غ������delete�����ٵ�����������
					  // �����ͷ��ڴ棬��������������ԭ�����������ɵ����飩
			cout << "Delete Observer" << endl;
		}
	}
private:
	size_t m_useNum{0}; // ���캯����ʼ���������ڲ���ʼ��
};

class iSubject{ // Ҫ�۲�Ķ���
public:
	virtual ~iSubject() {} // ���������������������ǣ�

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
		//����C���͵����顢��ʼ���б��Լ��κ������˷ǳ�Աbegin()��end()������
		for (auto& v : m_list) v->Update(data); // ��ü���'&'
		//ListPtr::iterator it = m_list.begin();
		//for (; it != m_list.end(); ++it){ (*it)->Update(data); }
	}
private:
	typedef list< My_unique_ptr<iObserver> > ListPtr;
	ListPtr m_list;
};

/************************************************************************/
// ���๦�ܣ�ƽ����չ
class cObserverA : public iObserver{
public:
	void Update(const int& data) override { cout << "Update A Observer" << endl; }
};

class cObserverB : public iObserver{
public:
	void Update(const int& data) override { cout << "Update B Observer" << endl; }
};

/************************************************************************/
// ʾ��
void test_Observer(){
	cout << "�����������������������������۲���ģʽ����������������������������" << endl;
	iSubject obj;

	// ���ù���ͳһ new cObserver
	for (int i = 0; i < 1; ++i)
	{
		obj.Attach(new cObserverA);
	}
	obj.Notify(50);
}

/*���㣺1������֪ͨ��(iSubject)��������۲���(iObserver)
		2������۲��߲�һ������ʵ�֣�����Ŀ������Ҫ��һ���ѷ�װ�õ�����Ϊ�۲���
		3������۲��ߣ���һ����Update()���������ã��ӿ�����ͳһ��*/
/************************************************************************/
/*�¼�ί�У�
		1��ί�пɿ����ǶԺ����ӿڵĳ���
		2��һ��ί�ж���ɴ��ض�����������з������λ���
		3��ί�ж��������صķ�����������ͬһ���࣬�����߱���ͬ�Ĳ���������ֵ���ͼ���
		4������δ�����ķǾ�̬��Ա����������MessageMap.h�еĳ�Ա����ָ���÷�*/

template<typename TReturn, typename TParam>
class cEntrust{
private:
	typedef TReturn (*Ptr_Fun)(void*, TParam); // ����ָ��
	struct stFun{
		void* pObj;   // Ϊʹstatic�����ܷ��ʳ�Ա��������void*ͳһ���ն��󣬸����ط����Լ�ǿת������Ǹ����������ˣ���ָ�벻��Ұ�ˣ�������
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
		for (stFun& v : m_vecFun) v(param); // ������'&'
	}
};

/************************************************************************/
// ʾ��
// Ҫ���صķ���
class cObserverC{
public:
	LPCSTR name{ "ObserverC" };
	static void Fun_1(void* p, int data)
	{
		cObserverC* pObj = (cObserverC*)p; // ����ǿת
		cout << "�¼�ί�У�" << pObj->name << "�������" << data << endl;
	}
};
class cObserverD{
public:
	LPCSTR name{ "ObserverD" };
	static void Fun_2(void* p, int data)
	{
		cObserverD* pObj = (cObserverD*)p; // ����ǿת
		cout << "�¼�ί�У�" << pObj->name << "�������" << data << endl;
	}
};
void test_Entrust(){
	cout << "�����������������������������¼�ί�� Entrust����������������������������" << endl;
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