/**************************************************************************
 * @ ����ģʽ
 * @ brief
     1��Ϊ�����ṩһ�ִ������������
     2����װ��ģʽ����ֻ�ǽ���װ��ģʽ(Decorator.h)���еĻ���(cDecorator)������(cDecoratorA/B)�ϲ���
     3������Ҫ��ͬ�Ĵ����࣬�Ǿ�ͬ��װ��ģʽ��һģһ����

     4��Զ�̴���Ϊ�����ڲ�ͬ�ռ��ṩ�ֲ�������Զ�̴���WebService
     5������������������ܴ�Ķ���ʱ���Ż�����
                  �����ͼƬ��Դʱ���ô洢����ʵͼƬ·��/�ߴ���������δ�򿪵�ͼ��
     6����ȫ����������ʵ�������ʱ��Ȩ��
     7������ָ������������ʵ����ʱ��������һЩ����
 * @ author zhoumf
 * @ date 2014-10-31
 ************************************************************************/
#pragma once


/************************************************************************/
// ���� ����
class iProxy{
public:
	virtual ~iProxy() {} // ���������������������ǣ�
    virtual void DoSomething() = 0; // Ҫ���ƵĽӿ�
};

/************************************************************************/
// ���๦�ܣ�ƽ����չ
class cProxy : public iProxy{ // ������ ���Ƶ������ԡ��������󡱵ķ���
public:
    cProxy(iProxy* pObj) : m_pObj(pObj) {}

    void DoSomething()
    {
        cout << "I'm the Proxy! Control access the RealObject..." << endl;

		this->Before(); // Ԥ����

        if (m_pObj) m_pObj->DoSomething();

		this->After(); // �ƺ���
    }
private:
	void Before() {}
	void After() {}
	iProxy* const m_pObj; //  ��ָֹ��䶯��������;ָ������һ����
};

/************************************************************************/
// ʾ��
class cObj_Proxy : public iProxy{ // Ҫ�������
public:
    void DoSomething() {cout << "I'm the RealObject!" << endl;}
};

void test_Proxy(){
	cout << "��������������������������������ģʽ����������������������������" << endl;
	cObj_Proxy obj;
	cProxy proxy(&obj);
    proxy.DoSomething();
}