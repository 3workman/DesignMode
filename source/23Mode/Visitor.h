/**************************************************************************
 * @ ������ģʽ
 * @ brief
     1���ڲ��ƻ����ǰ���£�Ϊ������²���
     2��������(���)��װ��һ�����У�Visitor�������ɴ������ࣨObj_Visit���ṩһ�����սӿ�
	 3��������ģʽ���������ݽṹ����ȶ���ϵͳ
	 4�������ݽṹ�������ݽṹ�Ĳ�������
 * @ author zhoumf
 * @ date 2014-11-8
 ************************************************************************/
#pragma once


/************************************************************************/
// ���� ����
class iObj_Visit;
class iVisitor{ // ��װ�����ݵ���
public:
	virtual ~iVisitor() {}
	virtual void Visit(iObj_Visit* pObj) = 0;
};

class iObj_Visit{ // ��������
public:
	virtual ~iObj_Visit() {}
	virtual void Accept(iVisitor* p) { p->Visit(this); } // ����Visitor�ķ���
};

/************************************************************************/
// ���๦�ܣ�ƽ����չ
class cVisitorA : public iVisitor{
public:
	void Visit(iObj_Visit* pObj) { cout << "A Visitor do something" << endl; pObj; }
};
class cVisitorB : public iVisitor{
public:
	void Visit(iObj_Visit* pObj) { cout << "B Visitor do something" << endl; pObj; }
};

class cObj_VisitA : public iObj_Visit{

};
class cObj_VisitB : public iObj_Visit{

};

/************************************************************************/
// ʾ��
void test_Visitor(){
	cout << "����������������������������������ģʽ����������������������������" << endl;
	cVisitorA visitorA;
	cVisitorB visitorB;

	cObj_VisitA objA;
	objA.Accept(&visitorA);
	objA.Accept(&visitorB);

	cObj_VisitB objB;
	objB.Accept(&visitorA);
	objB.Accept(&visitorB);
}