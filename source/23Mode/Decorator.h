/**************************************************************************
 * @ 装饰模式
 * @ brief
     1、——动态——给对象添加额外功能，比生成子类更灵活
     2、若只想更改类的几个接口，继承会携带父类赘余数据
	 3、使用继承实现功能拓展，这些功能是编译时就确定了，是静态的
     4、Decorator可动态加载：新加入的东西仅仅为了满足一些特定情况下的特殊行为需求
     5、尽量保证装饰类彼此独立，注意——装饰顺序——
 * @ author zhoumf
 * @ date 2014-10-29
 ************************************************************************/
#pragma once


/************************************************************************/
// 抽象 基类
class iDecorator{
public:
	virtual ~iDecorator() {} // 基类虚析构函数（易忘记）
    virtual void DoSomething() = 0; // 要扩展功能的函数
};

class cDecorator : public iDecorator{ // 装饰基类，存储要装饰的对象，把公共的操作抽出来
public:
	cDecorator(iDecorator* pObj) : m_pObj(pObj) {}

    void DoSomething() { if (m_pObj) m_pObj->DoSomething();} // 调用要扩展功能的函数

protected:
	iDecorator* const m_pObj; // 防止指针变动，调用中途指向了另一对象
};

/************************************************************************/
// 子类功能，平行扩展
class cDecoratorA : public cDecorator{
public:
    cDecoratorA(iDecorator* pObj) : cDecorator(pObj) {}
    void DoSomething()
    {
        cout << "Use A Decorator" << endl; // 添加功能

        cDecorator::DoSomething();  // 最后的回调
    }
};

class cDecoratorB : public cDecorator{
public:
    cDecoratorB(iDecorator* pObj) : cDecorator(pObj) {}
    void DoSomething()
    {
        cout << "Use B Decorator" << endl;

        cDecorator::DoSomething();
    }
};

/************************************************************************/
// 管理方式，松耦合

// 可嵌套工厂：对本模式而言，既增加了复杂度，又没便捷多少，一般不用

/************************************************************************/
// 示例
class cObj_Decorate : public iDecorator{ // 要装饰的类
public:
	void DoSomething() { cout << "None Decorator" << endl; }

	/* 可去除iDecorator类，继承树从cDecorator开始
	   cObj_Decorate不必参与继承，cDecorator类直接保存cObj指针
	   坏处：cDecorator要包含cObj_Decorate头文件
	   加入iDecorator基类，可解耦cDecorator、cObj_Decorate
	*/
};

void test_Decorator(){
	cout << "——————————————装饰模式——————————————" << endl;
	// cDecoratorA objDecoratorA(&cObj_Decorate());
	// cObj_Decorate生成期仅在函数调用处，cDecorator内保存的指针变为野指针
	// 【cDecorator构造函数声明为引用形参，编译不通过，因出生存期结束引用失效】

	cObj_Decorate obj;
	cDecoratorA objDecoratorA(&obj);
    objDecoratorA.DoSomething();
}