/**************************************************************************
 * @ ְ����ģʽ
 * @ brief
     1��ʹ��������л��ᴦ�����󣬽�������ķ����ߡ�������֮������
     2������Щ��������һ������ָ����̴����ߣ�����������������ֱ����һ����������Ϊֹ
	 3���ɽ���̴�������չ�ɺ�̱���GUI����ܹ�
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
// ���� ����
class iHandler{
public:
	iHandler(iHandler* p) : m_pNext(p) {}
	void SetNextHandler(iHandler* p) { m_pNext = p; }
	virtual ~iHandler() {}
	virtual bool CanHandle(const stEvent& event) = 0; // �������Ҫ���ж��Ƿ��ܴ��������
	virtual void HandleRequest(const stEvent& event)  // Ĭ�Ͻ������ߵĴ����߼�
	{
		if (m_pNext)
			m_pNext->HandleRequest(event);
		else
			cout << "Error : No handler deal with this request" << endl; // �����һ��Ĭ�ϴ��������������
	}
private:
	iHandler* m_pNext; // ��̴�����󣨿����ɺ�̱�
};

/************************************************************************/
// ���๦�ܣ�ƽ����չ
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
// ����ʽ�������
class cManageHandler{
public:
	static cManageHandler& Instance(){ static cManageHandler T; return T; }
	void HandleEvent(iHandler* p, const stEvent& event) // ��װһ��ͳһ�ӿ�
	{
		p->HandleRequest(event);
	}
};

/************************************************************************/
// ʾ��
void test_ChainOfResponsibility(){
	cout << "����������������������������ְ����ģʽ����������������������������" << endl;
	cHandlerA objA(NULL);
	cHandlerB objB(&objA);

	stEvent enent;
	enent.type = stEvent::Event_A;
	cManageHandler::Instance().HandleEvent(&objB, enent);

	enent.type = stEvent::Event_C;
	cManageHandler::Instance().HandleEvent(&objB, enent);
}