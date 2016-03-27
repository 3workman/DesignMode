/**************************************************************************
 * @ װ��ģʽ
 * @ brief
     1��������̬������������Ӷ��⹦�ܣ���������������
     2����ֻ�������ļ����ӿڣ��̳л�Я������׸������
	 3��ʹ�ü̳�ʵ�ֹ�����չ����Щ�����Ǳ���ʱ��ȷ���ˣ��Ǿ�̬��
     4��Decorator�ɶ�̬���أ��¼���Ķ�������Ϊ������һЩ�ض�����µ�������Ϊ����
     5��������֤װ����˴˶�����ע�⡪��װ��˳�򡪡�
 * @ author zhoumf
 * @ date 2014-10-29
 ************************************************************************/
#pragma once


/************************************************************************/
// ���� ����
class iDecorator{
public:
	virtual ~iDecorator() {} // ���������������������ǣ�
    virtual void DoSomething() = 0; // Ҫ��չ���ܵĺ���
};

class cDecorator : public iDecorator{ // װ�λ��࣬�洢Ҫװ�εĶ��󣬰ѹ����Ĳ��������
public:
	cDecorator(iDecorator* pObj) : m_pObj(pObj) {}

    void DoSomething() { if (m_pObj) m_pObj->DoSomething();} // ����Ҫ��չ���ܵĺ���

protected:
	iDecorator* const m_pObj; // ��ָֹ��䶯��������;ָ������һ����
};

/************************************************************************/
// ���๦�ܣ�ƽ����չ
class cDecoratorA : public cDecorator{
public:
    cDecoratorA(iDecorator* pObj) : cDecorator(pObj) {}
    void DoSomething()
    {
        cout << "Use A Decorator" << endl; // ��ӹ���

        cDecorator::DoSomething();  // ���Ļص�
    }
};

class cDecoratorB : public cDecorator{
public:
    cDecoratorB(iDecorator* pObj) : cDecorator(pObj) {}
    void DoSomething()
    {
        cout << "Use B Decorator" << endl;

        cDecorator::DoSomething();
    }
};

/************************************************************************/
// ����ʽ�������

// ��Ƕ�׹������Ա�ģʽ���ԣ��������˸��Ӷȣ���û��ݶ��٣�һ�㲻��

/************************************************************************/
// ʾ��
class cObj_Decorate : public iDecorator{ // Ҫװ�ε���
public:
	void DoSomething() { cout << "None Decorator" << endl; }

	/* ��ȥ��iDecorator�࣬�̳�����cDecorator��ʼ
	   cObj_Decorate���ز���̳У�cDecorator��ֱ�ӱ���cObjָ��
	   ������cDecoratorҪ����cObj_Decorateͷ�ļ�
	   ����iDecorator���࣬�ɽ���cDecorator��cObj_Decorate
	*/
};

void test_Decorator(){
	cout << "����������������������������װ��ģʽ����������������������������" << endl;
	// cDecoratorA objDecoratorA(&cObj_Decorate());
	// cObj_Decorate�����ڽ��ں������ô���cDecorator�ڱ����ָ���ΪҰָ��
	// ��cDecorator���캯������Ϊ�����βΣ����벻ͨ������������ڽ�������ʧЧ��

	cObj_Decorate obj;
	cDecoratorA objDecoratorA(&obj);
    objDecoratorA.DoSomething();
}