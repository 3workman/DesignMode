/**************************************************************************
 * @ 状态模式
 * @ brief
     1、状态逻辑(状态切换)、动作实现解耦
     2、尽量保证各状态之间的相互独立，不夹杂顺序关系
	 3、非常像策略模式(Strategy.h)，仅子类多了对管理器的调用，让子类能自主切换状态
	 4、将cManageState内嵌至iState，就能实现状态机了
 * @ author zhoumf
 * @ date 2014-11-14
 ************************************************************************/
#pragma once


/************************************************************************/
// 抽象 基类
class cManageState;
class iState{
public:
	virtual ~iState() {}
	virtual void ChangeState(cManageState* pMgr, iState* p) = 0;
	virtual void DoSomething() = 0;
};

/************************************************************************/
// 管理方式，松耦合
class cManageState{
public:
	void ChangeState(iState* p) { _pState = p; _pState->DoSomething(); }
private:
	iState* _pState = NULL; // 管理器要一直知道当前状态，所以才保存对象指针
};

/************************************************************************/
// 子类功能，平行扩展
class cStateA : public iState{
public:
	void ChangeState(cManageState* pMgr, iState* p) { pMgr->ChangeState(p); }
	void DoSomething() { cout << "StateA" << endl; }
};
class cStateB : public iState{
public:
	void ChangeState(cManageState* pMgr, iState* p) { pMgr->ChangeState(p); }
	void DoSomething() { cout << "StateB" << endl; }
};

/************************************************************************/
// 示例
void test_State(){
	cout << "——————————————状态模式——————————————" << endl;
	cManageState manage;
	cStateA objA;
	cStateB objB;
	manage.ChangeState(&objA);
	objA.ChangeState(&manage, &objB);
}