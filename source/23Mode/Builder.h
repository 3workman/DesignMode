/**************************************************************************
 * @ ������ģʽ
 * @ brief
     1��������Ĺ�����ϸ�ڱ�ʾ���룬����ͳһ�Ĺ������̣�������©���裩
     2�����ڴ������Ӷ�����Щ�����ڲ�������ġ�������˳���ȶ��������������б䶯����
	 3��������˳���л��������ԣ���һ����Ҫǰһ���Ľ�������ͽ�����ӿ�protected
 * @ author zhoumf
 * @ date 2014-11-3
 ************************************************************************/
#pragma once


class cObj_Builder{ // Ҫ�����Ĳ�Ʒ
public:
	void Show() { cout << "�ɹ�������Ʒ��" << endl; }
};

/************************************************************************/
// ���� ����
class iBuilder{ // ����ͳһ�Ĺ�������
public:
	iBuilder() : m_pObj(new cObj_Builder) {}

	virtual ~iBuilder() { delete m_pObj; } // ���������������������ǣ�

    virtual void BuildStep1() = 0;
    virtual void BuildStep2() = 0;

	cObj_Builder* GetResult() { return m_pObj; }

protected:
    cObj_Builder* const m_pObj; // ��ָֹ��䶯��������;ָ������һ��Ʒ
};

/************************************************************************/
// ���๦�ܣ�ƽ����չ
class cBuilderA : public iBuilder{
public:
	void BuildStep1() { m_pObj; cout << "cBuilderA do step1" << endl; }
	void BuildStep2() { m_pObj; cout << "cBuilderA do step2" << endl; }
};
class cBuilderB : public iBuilder{
public:
	void BuildStep1() { m_pObj; cout << "cBuilderB do step1" << endl; }
	void BuildStep2() { m_pObj; cout << "cBuilderB do step2" << endl; }
};

/************************************************************************/
// ����ʽ��ͳһ�Ľ�����̵���
class cManageBuilder{
public:
	void UnifyBuild(iBuilder& builder)
    {
        builder.BuildStep1();
        builder.BuildStep2();
    }
};

/************************************************************************/
// ʾ��
void test_Builder(){
	cout << "����������������������������������ģʽ����������������������������" << endl;
	cManageBuilder manage;

	cBuilderA builderA;
	manage.UnifyBuild(builderA);

    builderA.GetResult()->Show();
}