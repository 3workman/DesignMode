/**************************************************************************
 * @ ģ�巽��ģʽ
 * @ brief
     1����ĳһ���һ�£�����������ڸ���ϸ��ʵ���ϲ�ͬ
     2�������㷨�Ǽܣ���һЩϸ��ʵ�ַŵ����ࡪ���Ѳ�����Ϊ�ᵽ���ࣨ��������ظ���
	 3�����ƽ�����ģʽ(Builder.h)��ֻ�ǽ���ͳһ�Ľ�����̵���cManageBuilder::UnifyBuild����������TemplateMethod()
 * @ author zhoumf
 * @ date 2014-11-3
 ************************************************************************/
#pragma once


/************************************************************************/
// ���� ����
class iTemplate{
public:
	virtual ~iTemplate() {} // ���������������������ǣ�

    void TemplateMethod() // ͳһ���߼����
    {
        DoSomething_1(); // do step1
        DoSomething_2(); // do step2
    }
protected:
    virtual void DoSomething_1() = 0; // ������ϸ��ʵ��
    virtual void DoSomething_2() = 0;
};

/************************************************************************/
// ���๦�ܣ�ƽ����չ
class cMethodA : public iTemplate{
protected:
    void DoSomething_1() override {cout << "Use A Method, Now do step1" << endl;}
	void DoSomething_2() override { cout << "Use A Method, Now do step2" << endl; }
};
class cMethodB : public iTemplate{
protected:
	void DoSomething_1() override { cout << "Use B Method, Now do step1" << endl; }
	void DoSomething_2() override { cout << "Use B Method, Now do step2" << endl; }
};

/************************************************************************/
// ����ʽ�������

/************************************************************************/
// ʾ��
void test_Template(){
	cout << "����������������������������ģ�巽��ģʽ����������������������������" << endl;
    cMethodA methodA;
    methodA.TemplateMethod();

    cMethodB methodB;
    methodB.TemplateMethod();
}