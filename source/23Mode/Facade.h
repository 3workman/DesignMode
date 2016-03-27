/**************************************************************************
 * @ 外观模式
 * @ brief
     1、整合“底层类集”的一组接口，外观的上层接口使底层系统更易使用
     2、避免复杂底层、上层业务的直接耦合

     3、首先，设计上有意识将不同的两个层分离，
        在数据访问层和业务层、业务层和表示层的层与层之间建立外观，
        这样可以为复杂的子系统提供简单接口，降低耦合
     4、其次，开发阶段，子系统往往因不断重构而越发复杂，
        给外部调用它们的用户带来使用上的困难，
        外观可以提供一个简单接口，减少它们之间的依赖
     5、第三，维护一个大系统时，可能这个系统已经非常难维护/扩展了，但新需求必须依赖它
        外观类可为遗留代码提供较清晰的接口，让新系统与Facade对象交互
        Facade对象与遗留代码交互所有复杂工作
 * @ author zhoumf
 * @ date 2014-11-3
 ************************************************************************/
#pragma once


/************************************************************************/
// 抽象 基类

/************************************************************************/
// 底层类集
class cSubSystemA{
public:
    void FunctionA(){cout << "FunctionA"<< endl;}
};
class cSubSystemB{
public:
    void FunctionB(){cout << "FunctionB"<< endl;}
};
class cSubSystemC{
public:
    void FunctionC(){cout << "FunctionC"<< endl;}
};

/************************************************************************/
// 管理方式：外观类
class cFacade{
public:
    void MethodA()
    {
        m_subA.FunctionA();
        m_subB.FunctionB();
    }
    void MethodB()
    {
        m_subB.FunctionB();
        m_subC.FunctionC();
    }
private:
    cSubSystemA m_subA;
    cSubSystemB m_subB;
    cSubSystemC m_subC;
};

/************************************************************************/
// 示例
void test_Facade(){
	cout << "——————————————外观模式——————————————" << endl;
    cFacade facade;
    facade.MethodA();
    facade.MethodB();
}