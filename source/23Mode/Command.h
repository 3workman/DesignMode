/**************************************************************************
 * @ 命令模式
 * @ brief
     1、将请求封装到Command类中，并将请求的接收者存放到Receiver类中
     2、实现了调用操作的对象、操作的具体实现者之间的解耦
	 3、可嵌入一个命令队列（如消息队列）
	 4、命令模式、备忘录模式(Memento.h)结合，可实现撤销/重做

	 5、命令模式打断了请求——接收的直接关联
	 6、命令管理器(cManageCommand)才真正激活处理，本质上是一种回调
 * @ author zhoumf
 * @ date 2014-11-13
 ************************************************************************/
#pragma once


class cReceiver{ // 若操作实现复杂，接收者可抽象为多个类，从cReceiver到iReceiver的重构也容易
public:
	void ActionA() { cout << "cReceiver : ActionA" << endl; } // 不同接口应对不同请求
	void ActionB() { cout << "cReceiver : ActionB" << endl; }
};
/************************************************************************/
// 抽象 基类
class iReceiver{
public:
	virtual ~iReceiver() {}
	virtual void DoSomething() = 0; // 统一的处理请求接口，子类实现不同功能
};

class iCommand{ // 类中尽量不保存Receiver对象，让关联限定在接口中
public:
	virtual ~iCommand() {}
	virtual void Call(cReceiver* p) = 0; // 简单情况，可将接收者统一到一个类里
	virtual void Call(iReceiver* p) = 0; // 复杂情况，抽象出一个接收者类集，一个接收者处理一种请求
};

/************************************************************************/
// 子类功能，平行扩展
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
// 管理方式：统一的请求调用
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
// 示例
void test_Command(){
	cout << "——————————————命令模式——————————————" << endl;
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
// 命令模式 + 工厂模式 + 单例 : 重构P18消息处理系统
// 原系统结构如下：
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
struct stMsg // 消息基础结构体
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
	int HandleMessage(const stMsg& msg) // 统一处理消息的接口
	{
		if (NULL == m_aOnMsg[msg.type]) return 0;
		return m_aOnMsg[msg.type](msg);
	}
private:
	typedef int(*OnMsg) (const stMsg& msg);
	OnMsg m_aOnMsg[Msg_Num];

	// 消息处理函数，自己强转成想要的数据
	static int OnDo_1(const stMsg& msg){ return 1; }
	static int OnDo_2(const stMsg& msg){ return 1; }
	static int OnDo_3(const stMsg& msg){ return 1; }
};

/************************************************************************/
// 重构：比之函数指针，封装消息请求的各CommandMsg子类能携带额外数据
/* 优化：1、项目中的消息按来源分为几大类别——主逻辑消息、数据库消息、网络消息、自发送消息
		 2、enum MsgQueueEnum{MsgQueue_Main, MsgQueue_Database, MsgQueue_Net, MsgQueue_Self, MsgQueue_Num};
		 3、可以先用命令模式将大类别分开，各个类别中用函数指针数组
		 4、真正的响应函数中就不必关心不同来源消息串杂的问题了（项目里的有些响应函数还要预先判断消息来源）*/
class iCommandMsg{ // 封装消息请求
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
	// 消息处理函数，自己强转成想要的数据
	static int OnDo_2(const stMsg& msg){ return 1; }
};
class cCommandMsg_DB : public iCommandMsg{
public:
	void RegistMsgFun() override
	{
		m_aOnMsg[Msg_Three] = OnDo_3;
	}
private:
	// 消息处理函数，自己强转成想要的数据
	static int OnDo_3(const stMsg& msg){ return 1; }
};
class cCommandMsg_Net : public iCommandMsg{
public:
	void RegistMsgFun() override
	{
		m_aOnMsg[Msg_One] = OnDo_1;
	}
private:
	// 消息处理函数，自己强转成想要的数据
	static int OnDo_1(const stMsg& msg){ return 1; }
};

class cFactoryCommand{ // 枚举工厂：具体的实例化
public:
	static cFactoryCommand& Instance(){ static cFactoryCommand T; return T; }
	int HandleMessage(const stMsg& msg) // 可将cHandleMsg单例化
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
		case MsgFromEnum::Msg_Self:   return new cCommandMsg_Self; // 这些消息命令类都可以单例化
		case MsgFromEnum::Msg_DB:     return new cCommandMsg_DB;
		case MsgFromEnum::Msg_Net:    return new cCommandMsg_Net;
		default: return NULL;
		}
	}
};