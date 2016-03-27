/**************************************************************************
 * @ 策略模式
 * @ brief
     1、定义算法家族，分别封装起来，让它们之间可以互相替换
     2、此模式让算法的变化，不会影响到使用算法的客户
     3、算法子类还可携带额外数据
 * @ author zhoumf
 * @ date 2014-10-27
 ************************************************************************/
#pragma once


/************************************************************************/
// 抽象 基类
class iStrategy{
public:
	virtual ~iStrategy() {} // 基类虚析构函数（易忘记）
    virtual void DoSomething() = 0;
};

/************************************************************************/
// 子类功能，平行扩展
class cStrategyA : public iStrategy{
public:
    cStrategyA(int data = 0) {m_data = data;}
    int m_data; // 子类携带的额外数据

    void DoSomething() {cout << "Use A Strategy" << endl;}
};
class cStrategyB : public iStrategy{
public:
    void DoSomething() {cout << "Use B Strategy" << endl;}
};

/************************************************************************/
// 管理方式，松耦合
enum EnumStrategyType{
    Strategy_A,
    Strategy_B,
};
class cContext_Strategy{ // 环境对象，控制策略调用
public:
    void SetStrategy(iStrategy* pStrategy) {m_pStrategy = pStrategy;} // 注册要使用的策略

    void Function() { if (m_pStrategy) m_pStrategy->DoSomething();} // 包装一个统一接口

    static iStrategy* NewObject(EnumStrategyType eType){ //嵌套工厂
        switch (eType){
        case Strategy_A :       return new cStrategyA();
        case Strategy_B :       return new cStrategyB();
        default : return NULL;
        }
    }
private:
    iStrategy* m_pStrategy = NULL;
	/*优化：1、尽量不要保存对象指针
			2、将指针作为接口参数，使类之间的关系限定于接口*/
};

/************************************************************************/
// 示例
void test_Strategy(){
	cout << "——————————————策略模式——————————————" << endl;
    cContext_Strategy context; // 先定义环境变量

    // 方式一：策略模式
    cStrategyA objStrategyA(10); // 初始化额外数据
    cStrategyB objStrategyB;
    context.SetStrategy(&objStrategyA);
    context.Function();

    // 方式二：嵌套工厂
    if (iStrategy* pObj = cContext_Strategy::NewObject(Strategy_A))
    {
        context.SetStrategy(pObj);
        context.Function();

        delete pObj; // 记得用完要delete
    }

	// 方式三：Context类中保存函数指针/函数对象
}

/************************************************************************/
// 优化方案
class cContext_Strategy_better{ // 环境对象，控制策略调用
public:
	void NewObject_Do(EnumStrategyType eType){ //嵌套工厂
		iStrategy* p = NULL;
		switch (eType){
		case Strategy_A:	p = new cStrategyA(); break;
		case Strategy_B:    p = new cStrategyB(); break;
		default: break;
		}
		if (p) p->DoSomething();
		delete p;
	}
};