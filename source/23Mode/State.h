/**************************************************************************
 * @ ״̬ģʽ
 * @ brief
     1��״̬�߼�(״̬�л�)������ʵ�ֽ���
     2��������֤��״̬֮����໥������������˳���ϵ
	 3���ǳ������ģʽ(Strategy.h)����������˶Թ������ĵ��ã��������������л�״̬
	 4����cManageState��Ƕ��iState������ʵ��״̬����
 * @ author zhoumf
 * @ date 2014-11-14
 ************************************************************************/
#pragma once


/************************************************************************/
// ���� ����
class cManageState;
class iState{
public:
	virtual ~iState() {}
	virtual void ChangeState(cManageState* pMgr, iState* p) = 0;
	virtual void DoSomething() = 0;
};

/************************************************************************/
// ����ʽ�������
class cManageState{
public:
	void ChangeState(iState* p) { _pState = p; _pState->DoSomething(); }
private:
	iState* _pState = NULL; // ������Ҫһֱ֪����ǰ״̬�����Բű������ָ��
};

/************************************************************************/
// ���๦�ܣ�ƽ����չ
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
// ʾ��
void test_State(){
	cout << "����������������������������״̬ģʽ����������������������������" << endl;
	cManageState manage;
	cStateA objA;
	cStateB objB;
	manage.ChangeState(&objA);
	objA.ChangeState(&manage, &objB);
}