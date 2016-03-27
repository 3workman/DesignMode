/**************************************************************************
 * @ �н���ģʽ
 * @ brief
     1���н���󡪡���װһϵ�ж���Ľ�����ϵ
     2����һ��������Ϣʱ����ֱ�ӷ���Ŀ�Ķ��󣬶��ǰ���Ϣ�����н��ߣ�����ת��
	 3����ɢ�����ߡ�������֮��Ľ��ܹ�ϵ���ɸ��Զ����ı䷢��/���շ�ʽ����Ϣ����·��
	 4��Mediator����Զ��ͨ�ż�Ϊһ(Mediator)�Զ�(Colleague)ͨ��
	 5�������н��οɶ�����ؽ�����ϵ
 * @ author zhoumf
 * @ date 2014-11-4
 ************************************************************************/
#pragma once


/************************************************************************/
// ϵ�н����������
class cMediator;
class iColleague{
public:
	virtual ~iColleague() {}
	void SetMediator(cMediator* p) { m_pMediator = p; }
protected:
	cMediator* m_pMediator; 
	/*���⣺1������д����Colleague��Mediator������жԷ���ָ�루ѭ�����ã�
			2����������ָ���ع�ϵͳ��������ڴ�й¶����
			3�������໥�����ã���������ƣ��������������̫�ߣ�*/
	/*�Ż���1����m_pMediator��Ϊ�ӿڲ�����ʹ��֮��Ĺ�ϵ�޶��ڽӿ�
			2�������������Ļ����ɽ��н���Mediator���Ϊ��������Ҫʱ����
			3����Ҫ�������ָ�룬��ָ��ĳ�ʼ��д�ڹ��캯���У�����������໥�����ã�������������óɻ������뱨��
			   iColleague(cMediator* p) { m_pMediator = p; }*/
};

/************************************************************************/
// �н��ߣ���������������Ϣ���������
class cColleagueA;
class cColleagueB;
class cMediator{ // �н��ߣ���Ҫ֪�����еĽ�������
public:
	cMediator(cColleagueA* pA, cColleagueB* pB) : m_pColleagueA(pA), m_pColleagueB(pB)
	{
		((iColleague*)m_pColleagueA)->SetMediator(this); // Ϊ�˱���ͨ����ǿת��
		((iColleague*)m_pColleagueB)->SetMediator(this);
		//m_pColleagueA->SetMediator(this);
		//m_pColleagueB->SetMediator(this);
	}
	void ACallB() { cout << "A ask B to do something" << endl; m_pColleagueB; }
	void BCallA() { cout << "B ask A to do something" << endl; m_pColleagueA; }
private:
	cColleagueA* const m_pColleagueA; // ��ֹ��;�ı���ָ����
	cColleagueB* const m_pColleagueB;
};

/************************************************************************/
// ���๦�ܣ�ƽ����չ
class cColleagueA : public iColleague{
public:
	void CallB() { cout << "A do something then call B" << endl; m_pMediator->ACallB(); }
};
class cColleagueB : public iColleague{
public:
	void CallA() { cout << "B do something then call A" << endl; m_pMediator->BCallA(); }
};

/************************************************************************/
// ʾ��
void test_Mediator(){
	cout << "�����������������������������н���ģʽ����������������������������" << endl;
	cColleagueA objA;
	cColleagueB objB;
	cMediator mediator(&objA, &objB);

	objA.CallB();
	objB.CallA();
}


/************************************************************************/
// �Ż�����������iColleague��
class cColleagueA_better;
class cColleagueB_better;
class cMediator_better{ // �н��ߣ���Ҫ֪�����еĽ�������
public:
	cMediator_better(cColleagueA_better* pA, cColleagueB_better* pB) : m_pColleagueA(pA), m_pColleagueB(pB){}
	void ACallB() { cout << "A ask B to do something" << endl; m_pColleagueB; }
	void BCallA() { cout << "B ask A to do something" << endl; m_pColleagueA; }
private:
	cColleagueA_better* const m_pColleagueA; // ��ֹ��;�ı���ָ����
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