/**************************************************************************
 * @ 工厂模式
 * @ brief
     1、统一处理子类实例化，优化代码结构
     2、若工厂是 new 对象，用完一定要 delete
     3、（可嵌套智能指针，要防止循环引用）
	 4、抽象工厂模式：再抽象一层iFactory生成各个cFactory子类，统一管理
 * @ author zhoumf
 * @ date 2014-09-19
 ************************************************************************/
#pragma once
#include <functional>
#include "..\tool\My_unique_ptr.h"

/************************************************************************/
// 抽象 基类
class iOperation{
public:
    /*没有参数或所有的参数都有默认值的构造函数称为默认构造函数
    如果类中没有声明构造函数，编译器将自动产生一个默认无参数构造函数
    如果存在一个构造函数声明,那么编译器不会产生默认构造函数*/
    iOperation(double a = 0, double b = 0) {_numA = a; _numB = b;}

	virtual ~iOperation() { cout << "Delete Operation" << endl; } // 基类虚析构函数（易忘记）
	virtual void DoSomething() = 0;

protected:
    double _numA;
    double _numB;
};

/************************************************************************/
// 子类功能，平行扩展
class cOperationA : public iOperation{
public:
	void DoSomething() override { cout << "Use A Operation" << endl; }

	//标识符override : 此虚函数应当重写基类中的虚函数
	//void DoSomething(int) override { cout << "Use A Operation" << endl; } //会编译报错
	//标识符final : 派生类虚函数不应当重写基类虚函数
	//void DoSomething() final { cout << "Use A Operation" << endl; } // 变成重载函数了
};
class cOperationB : public iOperation{
public:
	void DoSomething() { cout << "Use B Operation" << endl; }
};

/************************************************************************/
// 管理方式，松耦合
enum class EnumOperation{ // 强类型枚举，不会将枚举常量暴露到外层作用域，也不会隐式转换为整形
    Operation_A,
    Operation_B,
};
class cFactory{ // 枚举工厂：具体的实例化
public:
    static iOperation* NewObject(EnumOperation eType){
        switch (eType){
		case EnumOperation::Operation_A:      return new cOperationA();
		case EnumOperation::Operation_B:      return new cOperationB();
        default : return NULL;
        }
    }
};

/************************************************************************/
// 示例
void test_Factory(){
	cout << "——————————————工厂模式——————————————" << endl;
	if (iOperation* pObj = cFactory::NewObject(EnumOperation::Operation_A))
    {
        pObj->DoSomething();

        delete pObj; // 记得用完要delete
    }
}

/************************************************************************/
// 类名工厂，模仿Java反射机制（可以全局化创建所有对象，引入内存池统一管理，提高效率）
const char* const OBJ_NAME[] = { // 理论上这个可由编译器生成
	"cOperationA",
	"cOperationB",
};
template<class T> iOperation* new_obj() { return new T; }
typedef iOperation* (*New_Fun)(); // 函数指针
New_Fun const ARR_FUN[] = { // 指针本身不能改变(防止指向别的函数)
	new_obj<cOperationA>,
	new_obj<cOperationB>,
};
STATIC_ASSERT_ARRAY_ARRAY(OBJ_NAME, ARR_FUN);

/*匿名函数：
		1、Lambda表达式，'[]'里可填'='或'&'：以什么方式“捕获（闭包）”数据(传值、引用)		[a,&b]a值、b引用
		2、'[]'不填则试图在Lambda内使用任何外部变量都是错误的
		3、'()'中是参数列表，无参数时可省略													[ capture ] { body }
		4、'->'后是返回值类型，可省略，由return自动推断										[ capture ] ( params ) { body }
		5、如果一个闭包含有局部变量的引用，在超出创建它的作用域之外的被使用，这种行为是未定义的!*/
std::function<iOperation*()> const ARR_NEW[] = {
	[]()->iOperation* { return new cOperationA; },
	[]()->iOperation* { return new cOperationB; },
};
static_assert( sizeof(OBJ_NAME)/sizeof(OBJ_NAME[0])==sizeof(ARR_NEW)/sizeof(ARR_NEW[0]), "Length isn't equal");

template<class _Ty>
class cNewObjByName{ // 类名工厂
public:
	static cNewObjByName& Instance(){ static cNewObjByName T; return T; }

	typedef My_unique_ptr<_Ty> unique_ptr; // 嵌套智能指针
	unique_ptr NewObjByName(string name)
	{
		//auto类型占位符，通知编译器去根据初始化代码推断所声明变量的真实类型
		auto it = mapNewFun.find(name); //NewFunMap::iterator it = mapNewFun.find(name);
		if (mapNewFun.end() != it) return (it->second)();
		assert(!"类名错误！");
		return NULL;
	}
private:
	cNewObjByName(){ // 构造函数，初始化<类名，函数指针>表
		for (int i = 0; i < sizeof(OBJ_NAME)/sizeof(OBJ_NAME[0]); ++i){
			if (!mapNewFun.insert(make_pair(OBJ_NAME[i], ARR_FUN[i])).second)
				assert(!"类名重复！"); // 插入失败
		}
	}
	typedef _Ty* (*New_Fun)(); // 函数指针
	typedef std::map<string, New_Fun> NewFunMap;
	NewFunMap mapNewFun;
};

/************************************************************************/
// 示例
void test_Reflect(){
	cout << "——————————————反射机制——————————————" << endl;
	if (cNewObjByName<iOperation>::unique_ptr pObj = cNewObjByName<iOperation>::Instance().NewObjByName("cOperationB"))
	{
		pObj->DoSomething();
	}
}

/************************************************************************/
// 那个蹲着的同学，你有没有发现VS2013容器的insert()形参是value_type&& _Val，而VS2005是const value_type& _Val
// 这两货有啥差别？
/* Move语义：
		1、vector<int> getVec() { vector<int> vec; return vec; } //产生两次复制()
		   在函数返回时，因local变量要被回收，所以需要copy构造一个临时对象返回给外界
		   返回这个临时对象后，又需要一次copy赋值操作来赋值给外界接收者
		2、C++11中一个值是否临时的，可用右值引用来检测，右值引用使用&&语法，可以是const/非const
		   见下面的示例
		3、move语义可以使临时对象避免拷贝，并保证临时对象中资源的安全性
		  （貌似——那部分资源一定要是全局性的static、global、new）
		4、定义move构造/赋值函数，与const&构造/赋值函数互相重载
		   move函数做浅拷贝，并把原始指针置为NULL，让临时对象析构不释放内存
*/
class cMove{
public:
	cMove(int n) { _p = new int(n); }
	~cMove() { delete _p; }

	cMove(cMove&& other)
		: _p(other._p)
	{
		cout << "Move 构造被调用" << endl;
		other._p = NULL;
	}

	cMove(const cMove& other)
		: _p(new int)
	{
		cout << "普通构造被调用" << endl;
		memcpy(_p, other._p, sizeof(int));
	}
private:
	int* _p;
};
string Set(string& val) { return val; }				  // 不能匹配右值引用/常量，优先于const &
string Set(const string& val) { return val; }		  // 可匹配全部
string Set(string&& val) { return val = "右值引用"; } // 只能匹配右值引用(临时匿名变量)，优先于const &

void test_Move(){
	cout << "——————————————Move语义——————————————" << endl;
	string str("渣渣");
	cout << Set(str) << endl;
	cout << Set("渣渣") << endl; // 输入常量，返回了其它东西哟！（改了临时变量的值）

	auto fun = []{ cMove obj(10);  return obj; };
	fun();				// 调一次move构造函数
	cMove obj1(fun());	// 也调一次！！！？？？难道编译器帮忙做了优化,直接把临时变量当成了obj( ⊙ o ⊙ )！
						// 因为有对象显式接收fun()，所以不必再创建临时对象做返回值
	cMove obj2 = fun(); // 还是只调一次！！！（不必operator=  自动生成拷贝构造函数、赋值操作符）
}