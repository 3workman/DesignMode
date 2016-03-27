/**************************************************************************
 * @ 职责链模式
 * @ brief
     1、使多个对象都有机会处理请求，降低请求的发送者、接收者之间的耦合
     2、将这些对象连成一条链（指定后继处理者），并沿链传递请求，直到有一个对象处理它为止
	 3、可将后继处理者扩展成后继表——GUI引擎架构
 * @ author zhoumf
 * @ date 2014-11-15
 ************************************************************************/
#pragma once


struct stEvent
{
	stEvent() { memset(this, 0, sizeof(*this)); }
	enum EnumEvent{
		Event_A,
		Event_B,
		Event_C,
	};
	EnumEvent type;
	int data;
};
/************************************************************************/
// 抽象 基类
class iHandler{
public:
	iHandler(iHandler* p) : m_pNext(p) {}
	void SetNextHandler(iHandler* p) { m_pNext = p; }
	virtual ~iHandler() {}
	virtual bool CanHandle(const stEvent& event) = 0; // 具体对象要先判断是否能处理该请求
	virtual void HandleRequest(const stEvent& event)  // 默认交予后继者的处理逻辑
	{
		if (m_pNext)
			m_pNext->HandleRequest(event);
		else
			cout << "Error : No handler deal with this request" << endl; // 可设计一个默认处理所有请求的类
	}
private:
	iHandler* m_pNext; // 后继处理对象（可做成后继表）
};

/************************************************************************/
// 子类功能，平行扩展
class cHandlerA : public iHandler{
public:
	cHandlerA(iHandler* p) : iHandler(p) {}
	bool CanHandle(const stEvent& event) { return event.type == stEvent::Event_A; }
	void HandleRequest(const stEvent& event)
	{
		if (CanHandle(event))
			cout << "HandlerA deal with this request" << endl;
		else
			iHandler::HandleRequest(event);
	}
};
class cHandlerB : public iHandler{
public:
	cHandlerB(iHandler* p) : iHandler(p) {}
	bool CanHandle(const stEvent& event) { return event.type == stEvent::Event_B; }
	void HandleRequest(const stEvent& event)
	{
		if (CanHandle(event))
			cout << "HandlerB deal with this request" << endl;
		else
			iHandler::HandleRequest(event);
	}
};

/************************************************************************/
// 管理方式，松耦合
class cManageHandler{
public:
	static cManageHandler& Instance(){ static cManageHandler T; return T; }
	void HandleEvent(iHandler* p, const stEvent& event) // 包装一个统一接口
	{
		p->HandleRequest(event);
	}
};

/************************************************************************/
// 示例
void test_ChainOfResponsibility(){
	cout << "——————————————职责链模式——————————————" << endl;
	cHandlerA objA(NULL);
	cHandlerB objB(&objA);

	stEvent enent;
	enent.type = stEvent::Event_A;
	cManageHandler::Instance().HandleEvent(&objB, enent);

	enent.type = stEvent::Event_C;
	cManageHandler::Instance().HandleEvent(&objB, enent);
}