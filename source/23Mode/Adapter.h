/**************************************************************************
 * @ ������ģʽ
 * @ brief
     1����һ����(��������)�Ľӿ�ת��Ϊ�ͻ�ϣ���Ľӿ�
     2����Ϊ��ģʽ���̳з�ʽ���õ������ӿڣ�������ģʽ����Ϸ�ʽʵ�ֶԵ������ĸ��ã�
	 3������װ��ģʽ(Decorator.h)��Ϊ��Ľӿ���Ӷ��⹦��
 * @ author zhoumf
 * @ date 2014-11-9
 ************************************************************************/
#pragma once


class cObj_Adapter{ // ��������
public:
	void OldPort() {}
};

/************************************************************************/
// ���� ����
class iAdapter{
public:
	virtual ~iAdapter() {}
	virtual void NewPort() = 0; // �½ӿ�
};

/************************************************************************/
// ���๦�ܣ�ƽ����չ
class cAdapter : public iAdapter{
public:
	cAdapter(cObj_Adapter* p) : _pObj(p) {}
	void NewPort() { cout << "NewPot do something to change OldPort" << endl; _pObj->OldPort(); } // ת����������Ľӿ�
private:
	cObj_Adapter* _pObj;
};

/************************************************************************/
// ʾ��
void test_Adapter(){
	cout << "����������������������������������ģʽ����������������������������" << endl;
	cObj_Adapter obj;
	cAdapter adapter(&obj);
	adapter.NewPort();
}