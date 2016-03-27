/**************************************************************************
 * @ 中介者模式
 * @ brief
     1、中介对象——封装一系列对象的交互关系
     2、当一个对象发消息时，不直接访问目的对象，而是把消息发给中介者，由它转发
	 3、拆散发送者、接收者之间的紧密关系，可各自独立改变发送/接收方式、消息传递路径
	 4、Mediator将多对多的通信简化为一(Mediator)对多(Colleague)通信
	 5、加入中介层次可额外调控交互关系
 * @ author zhoumf
 * @ date 2014-11-4
 ************************************************************************/
#pragma once


/************************************************************************/
// 系列交互对象基类
class cMediator;
class iColleague{
public:
	virtual ~iColleague() {}
	void SetMediator(cMediator* p) { m_pMediator = p; }
protected:
	cMediator* m_pMediator; 
	/*问题：1、这样写会令Colleague、Mediator互相持有对方的指针（循环引用）
			2、若用智能指针重构系统，会出现内存泄露问题
			3、出现类互相引用，属不良设计（互相依赖，耦合太高）*/
	/*优化：1、将m_pMediator作为接口参数，使类之间的关系限定于接口
			2、具体情况允许的话，可将中介者Mediator设计为单例，需要时调用
			3、若要保存对象指针，将指针的初始化写在构造函数中，如此若出现类互相引用（包括多个类引用成环）编译报错
			   iColleague(cMediator* p) { m_pMediator = p; }*/
};

/************************************************************************/
// 中介者：管理各个对象的消息请求，松耦合
class cColleagueA;
class cColleagueB;
class cMediator{ // 中介者，需要知道所有的交互对象
public:
	cMediator(cColleagueA* pA, cColleagueB* pB) : m_pColleagueA(pA), m_pColleagueB(pB)
	{
		((iColleague*)m_pColleagueA)->SetMediator(this); // 为了编译通过才强转的
		((iColleague*)m_pColleagueB)->SetMediator(this);
		//m_pColleagueA->SetMediator(this);
		//m_pColleagueB->SetMediator(this);
	}
	void ACallB() { cout << "A ask B to do something" << endl; m_pColleagueB; }
	void BCallA() { cout << "B ask A to do something" << endl; m_pColleagueA; }
private:
	cColleagueA* const m_pColleagueA; // 防止中途改变所指对象
	cColleagueB* const m_pColleagueB;
};

/************************************************************************/
// 子类功能，平行扩展
class cColleagueA : public iColleague{
public:
	void CallB() { cout << "A do something then call B" << endl; m_pMediator->ACallB(); }
};
class cColleagueB : public iColleague{
public:
	void CallA() { cout << "B do something then call A" << endl; m_pMediator->BCallA(); }
};

/************************************************************************/
// 示例
void test_Mediator(){
	cout << "——————————————中介者模式——————————————" << endl;
	cColleagueA objA;
	cColleagueB objB;
	cMediator mediator(&objA, &objB);

	objA.CallB();
	objB.CallA();
}


/************************************************************************/
// 优化方案，无需iColleague类
class cColleagueA_better;
class cColleagueB_better;
class cMediator_better{ // 中介者，需要知道所有的交互对象
public:
	cMediator_better(cColleagueA_better* pA, cColleagueB_better* pB) : m_pColleagueA(pA), m_pColleagueB(pB){}
	void ACallB() { cout << "A ask B to do something" << endl; m_pColleagueB; }
	void BCallA() { cout << "B ask A to do something" << endl; m_pColleagueA; }
private:
	cColleagueA_better* const m_pColleagueA; // 防止中途改变所指对象
	cColleagueB_better* const m_pColleagueB;
};

class cColleagueA_better{
public:
	void CallB(cMediator_better& mediator) { cout << "A do something then call B" << endl; mediator.ACallB(); }
};
class cColleagueB_better{
public:
	void CallA(cMediator_better& mediator) { cout << "B do something then call A" << endl; mediator.BCallA(); }
};