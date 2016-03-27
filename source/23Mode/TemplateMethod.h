/**************************************************************************
 * @ 模板方法模式
 * @ brief
     1、在某一层次一致，但其个别步骤在更详细的实现上不同
     2、定义算法骨架，将一些细节实现放到子类——把不变行为搬到父类（避免代码重复）
	 3、类似建造者模式(Builder.h)，只是将“统一的建造过程调用cManageBuilder::UnifyBuild”移至类中TemplateMethod()
 * @ author zhoumf
 * @ date 2014-11-3
 ************************************************************************/
#pragma once


/************************************************************************/
// 抽象 基类
class iTemplate{
public:
	virtual ~iTemplate() {} // 基类虚析构函数（易忘记）

    void TemplateMethod() // 统一的逻辑框架
    {
        DoSomething_1(); // do step1
        DoSomething_2(); // do step2
    }
protected:
    virtual void DoSomething_1() = 0; // 子类中细节实现
    virtual void DoSomething_2() = 0;
};

/************************************************************************/
// 子类功能，平行扩展
class cMethodA : public iTemplate{
protected:
    void DoSomething_1() override {cout << "Use A Method, Now do step1" << endl;}
	void DoSomething_2() override { cout << "Use A Method, Now do step2" << endl; }
};
class cMethodB : public iTemplate{
protected:
	void DoSomething_1() override { cout << "Use B Method, Now do step1" << endl; }
	void DoSomething_2() override { cout << "Use B Method, Now do step2" << endl; }
};

/************************************************************************/
// 管理方式，松耦合

/************************************************************************/
// 示例
void test_Template(){
	cout << "——————————————模板方法模式——————————————" << endl;
    cMethodA methodA;
    methodA.TemplateMethod();

    cMethodB methodB;
    methodB.TemplateMethod();
}