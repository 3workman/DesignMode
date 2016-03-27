/**************************************************************************
 * @ 代理模式
 * @ brief
     1、为对象提供一种代理，控制其访问
     2、跟装饰模式很像，只是将“装饰模式(Decorator.h)”中的基类(cDecorator)、子类(cDecoratorA/B)合并了
     3、若需要不同的代理类，那就同“装饰模式”一模一样了

     4、远程代理：为对象在不同空间提供局部代表，如远程代理WebService
     5、虚拟代理：创建开销很大的对象时，优化性能
                  如加载图片资源时，用存储了真实图片路径/尺寸的虚拟代理（未打开的图框）
     6、安全代理：控制真实对象访问时的权限
     7、智能指引：当调用真实对象时，代理做一些事情
 * @ author zhoumf
 * @ date 2014-10-31
 ************************************************************************/
#pragma once


/************************************************************************/
// 抽象 基类
class iProxy{
public:
	virtual ~iProxy() {} // 基类虚析构函数（易忘记）
    virtual void DoSomething() = 0; // 要控制的接口
};

/************************************************************************/
// 子类功能，平行扩展
class cProxy : public iProxy{ // 代理类 控制第三方对“真正对象”的访问
public:
    cProxy(iProxy* pObj) : m_pObj(pObj) {}

    void DoSomething()
    {
        cout << "I'm the Proxy! Control access the RealObject..." << endl;

		this->Before(); // 预处理

        if (m_pObj) m_pObj->DoSomething();

		this->After(); // 善后处理
    }
private:
	void Before() {}
	void After() {}
	iProxy* const m_pObj; //  防止指针变动，调用中途指向了另一对象
};

/************************************************************************/
// 示例
class cObj_Proxy : public iProxy{ // 要代理的类
public:
    void DoSomething() {cout << "I'm the RealObject!" << endl;}
};

void test_Proxy(){
	cout << "——————————————代理模式——————————————" << endl;
	cObj_Proxy obj;
	cProxy proxy(&obj);
    proxy.DoSomething();
}