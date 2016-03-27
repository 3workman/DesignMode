/**************************************************************************
 * @ ����ģʽ
 * @ brief
     1�������㷨���壬�ֱ��װ������������֮����Ի����滻
     2����ģʽ���㷨�ı仯������Ӱ�쵽ʹ���㷨�Ŀͻ�
     3���㷨���໹��Я����������
 * @ author zhoumf
 * @ date 2014-10-27
 ************************************************************************/
#pragma once


/************************************************************************/
// ���� ����
class iStrategy{
public:
	virtual ~iStrategy() {} // ���������������������ǣ�
    virtual void DoSomething() = 0;
};

/************************************************************************/
// ���๦�ܣ�ƽ����չ
class cStrategyA : public iStrategy{
public:
    cStrategyA(int data = 0) {m_data = data;}
    int m_data; // ����Я���Ķ�������

    void DoSomething() {cout << "Use A Strategy" << endl;}
};
class cStrategyB : public iStrategy{
public:
    void DoSomething() {cout << "Use B Strategy" << endl;}
};

/************************************************************************/
// ����ʽ�������
enum EnumStrategyType{
    Strategy_A,
    Strategy_B,
};
class cContext_Strategy{ // �������󣬿��Ʋ��Ե���
public:
    void SetStrategy(iStrategy* pStrategy) {m_pStrategy = pStrategy;} // ע��Ҫʹ�õĲ���

    void Function() { if (m_pStrategy) m_pStrategy->DoSomething();} // ��װһ��ͳһ�ӿ�

    static iStrategy* NewObject(EnumStrategyType eType){ //Ƕ�׹���
        switch (eType){
        case Strategy_A :       return new cStrategyA();
        case Strategy_B :       return new cStrategyB();
        default : return NULL;
        }
    }
private:
    iStrategy* m_pStrategy = NULL;
	/*�Ż���1��������Ҫ�������ָ��
			2����ָ����Ϊ�ӿڲ�����ʹ��֮��Ĺ�ϵ�޶��ڽӿ�*/
};

/************************************************************************/
// ʾ��
void test_Strategy(){
	cout << "��������������������������������ģʽ����������������������������" << endl;
    cContext_Strategy context; // �ȶ��廷������

    // ��ʽһ������ģʽ
    cStrategyA objStrategyA(10); // ��ʼ����������
    cStrategyB objStrategyB;
    context.SetStrategy(&objStrategyA);
    context.Function();

    // ��ʽ����Ƕ�׹���
    if (iStrategy* pObj = cContext_Strategy::NewObject(Strategy_A))
    {
        context.SetStrategy(pObj);
        context.Function();

        delete pObj; // �ǵ�����Ҫdelete
    }

	// ��ʽ����Context���б��溯��ָ��/��������
}

/************************************************************************/
// �Ż�����
class cContext_Strategy_better{ // �������󣬿��Ʋ��Ե���
public:
	void NewObject_Do(EnumStrategyType eType){ //Ƕ�׹���
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