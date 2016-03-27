/**************************************************************************
 * @ ����ģʽ
 * @ brief
     1���������װ��Command���У���������Ľ����ߴ�ŵ�Receiver����
     2��ʵ���˵��ò����Ķ��󡢲����ľ���ʵ����֮��Ľ���
	 3����Ƕ��һ��������У�����Ϣ���У�
	 4������ģʽ������¼ģʽ(Memento.h)��ϣ���ʵ�ֳ���/����

	 5������ģʽ��������󡪡����յ�ֱ�ӹ���
	 6�����������(cManageCommand)�������������������һ�ֻص�
 * @ author zhoumf
 * @ date 2014-11-13
 ************************************************************************/
#pragma once


class cReceiver{ // ������ʵ�ָ��ӣ������߿ɳ���Ϊ����࣬��cReceiver��iReceiver���ع�Ҳ����
public:
	void ActionA() { cout << "cReceiver : ActionA" << endl; } // ��ͬ�ӿ�Ӧ�Բ�ͬ����
	void ActionB() { cout << "cReceiver : ActionB" << endl; }
};
/************************************************************************/
// ���� ����
class iReceiver{
public:
	virtual ~iReceiver() {}
	virtual void DoSomething() = 0; // ͳһ�Ĵ�������ӿڣ�����ʵ�ֲ�ͬ����
};

class iCommand{ // ���о���������Receiver�����ù����޶��ڽӿ���
public:
	virtual ~iCommand() {}
	virtual void Call(cReceiver* p) = 0; // ��������ɽ�������ͳһ��һ������
	virtual void Call(iReceiver* p) = 0; // ��������������һ���������༯��һ�������ߴ���һ������
};

/************************************************************************/
// ���๦�ܣ�ƽ����չ
class cCommandA : public iCommand{
public:
	void Call(cReceiver* p) { p->ActionA(); }
	void Call(iReceiver* p) { p->DoSomething(); }
};
class cCommandB : public iCommand{
public:
	void Call(cReceiver* p) { p->ActionB(); }
	void Call(iReceiver* p) { p->DoSomething(); }
};

class cReceiverA : public iReceiver{
public:
	virtual void DoSomething() { cout << "cReceiverA : DoSomething" << endl; }
};
class cReceiverB : public iReceiver{
public:
	virtual void DoSomething() { cout << "cReceiverB : DoSomething" << endl; }
};

/************************************************************************/
// ����ʽ��ͳһ���������
class cManageCommand{
public:
	void UnifyCommand(iCommand* pCommand, cReceiver* pReceiver)
	{
		pCommand->Call(pReceiver);
	}
	void UnifyCommand(iCommand* pCommand, iReceiver* pReceiver)
	{
		pCommand->Call(pReceiver);
	}
};

/************************************************************************/
// ʾ��
void test_Command(){
	cout << "��������������������������������ģʽ����������������������������" << endl;
	cManageCommand manage;

	cCommandA commandA;
	cCommandB commandB;

	cReceiver receive;
	manage.UnifyCommand(&commandA, &receive);
	manage.UnifyCommand(&commandB, &receive);

	cReceiverA receiveA;
	cReceiverB receiveB;
	manage.UnifyCommand(&commandA, &receiveA);
	manage.UnifyCommand(&commandB, &receiveB);
}

/************************************************************************/
// ����ģʽ + ����ģʽ + ���� : �ع�P18��Ϣ����ϵͳ
// ԭϵͳ�ṹ���£�
enum class MsgFromEnum{
	Msg_Self,
	Msg_Net,
	Msg_DB,
	Msg_Num
};
enum MsgTypeEnum{
	Msg_One,
	Msg_Two,
	Msg_Three,
	Msg_Num
};
struct stMsg // ��Ϣ�����ṹ��
{
	stMsg(MsgTypeEnum e) : type(e){}
	MsgTypeEnum type;
	MsgFromEnum eFrom;
};
class cWorldServer{
protected:
	cWorldServer()
	{
		memset(m_aOnMsg, 0, sizeof(m_aOnMsg));
		m_aOnMsg[Msg_One] = OnDo_1;
		m_aOnMsg[Msg_Two] = OnDo_2;
		m_aOnMsg[Msg_Three] = OnDo_3;
	}
public:
	static cWorldServer& Instance(){ static cWorldServer T; return T; }
	int HandleMessage(const stMsg& msg) // ͳһ������Ϣ�Ľӿ�
	{
		if (NULL == m_aOnMsg[msg.type]) return 0;
		return m_aOnMsg[msg.type](msg);
	}
private:
	typedef int(*OnMsg) (const stMsg& msg);
	OnMsg m_aOnMsg[Msg_Num];

	// ��Ϣ���������Լ�ǿת����Ҫ������
	static int OnDo_1(const stMsg& msg){ return 1; }
	static int OnDo_2(const stMsg& msg){ return 1; }
	static int OnDo_3(const stMsg& msg){ return 1; }
};

/************************************************************************/
// �ع�����֮����ָ�룬��װ��Ϣ����ĸ�CommandMsg������Я����������
/* �Ż���1����Ŀ�е���Ϣ����Դ��Ϊ������𡪡����߼���Ϣ�����ݿ���Ϣ��������Ϣ���Է�����Ϣ
		 2��enum MsgQueueEnum{MsgQueue_Main, MsgQueue_Database, MsgQueue_Net, MsgQueue_Self, MsgQueue_Num};
		 3��������������ģʽ�������ֿ�������������ú���ָ������
		 4����������Ӧ�����оͲ��ع��Ĳ�ͬ��Դ��Ϣ���ӵ������ˣ���Ŀ�����Щ��Ӧ������ҪԤ���ж���Ϣ��Դ��*/
class iCommandMsg{ // ��װ��Ϣ����
public:
	iCommandMsg() { memset(m_aOnMsg, 0, sizeof(m_aOnMsg)); }
	virtual ~iCommandMsg() {}
	int Call(const stMsg& msg)
	{
		if (NULL == m_aOnMsg[msg.type]) return 0;
		return m_aOnMsg[msg.type](msg);
	}
	virtual void RegistMsgFun() = 0;
protected:
	typedef int(*OnMsg) (const stMsg& msg);
	OnMsg m_aOnMsg[Msg_Num];
};
class cCommandMsg_Self : public iCommandMsg{
public:
	void RegistMsgFun() override
	{
		m_aOnMsg[Msg_Two] = OnDo_2;
	}
private:
	// ��Ϣ���������Լ�ǿת����Ҫ������
	static int OnDo_2(const stMsg& msg){ return 1; }
};
class cCommandMsg_DB : public iCommandMsg{
public:
	void RegistMsgFun() override
	{
		m_aOnMsg[Msg_Three] = OnDo_3;
	}
private:
	// ��Ϣ���������Լ�ǿת����Ҫ������
	static int OnDo_3(const stMsg& msg){ return 1; }
};
class cCommandMsg_Net : public iCommandMsg{
public:
	void RegistMsgFun() override
	{
		m_aOnMsg[Msg_One] = OnDo_1;
	}
private:
	// ��Ϣ���������Լ�ǿת����Ҫ������
	static int OnDo_1(const stMsg& msg){ return 1; }
};

class cFactoryCommand{ // ö�ٹ����������ʵ����
public:
	static cFactoryCommand& Instance(){ static cFactoryCommand T; return T; }
	int HandleMessage(const stMsg& msg) // �ɽ�cHandleMsg������
	{
		if (iCommandMsg* pCommand = NewObject(msg.eFrom))
		{
			int nRet = pCommand->Call(msg);
			delete pCommand;
			return nRet;
		}
		return 0;
	}
private:
	iCommandMsg* NewObject(MsgFromEnum eFrom){
		switch (eFrom){
		case MsgFromEnum::Msg_Self:   return new cCommandMsg_Self; // ��Щ��Ϣ�����඼���Ե�����
		case MsgFromEnum::Msg_DB:     return new cCommandMsg_DB;
		case MsgFromEnum::Msg_Net:    return new cCommandMsg_Net;
		default: return NULL;
		}
	}
};