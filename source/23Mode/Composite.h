/**************************************************************************
 * @ ���ģʽ
 * @ brief
     1�����ڵݹ���״��Ͻṹ
	 2�����ṩ���ӽڵ�����ݽṹ����(vector��array��list��map)
	 3��ȥ��cComposite��ĵݹ鹦�ܺ󣬾��ǹ۲���ģʽ(Observer.h)��
	 4���۲��߱���Ҳ��һȺ�ӹ۲���
 * @ author zhoumf
 * @ date 2014-11-14
 ************************************************************************/
#pragma once


/************************************************************************/
// ���� ����
class iComponent{
public:
	virtual ~iComponent() {}
	virtual void Operate() = 0;
};

/************************************************************************/
// ���๦�ܣ�ƽ����չ
class cLeafA : public iComponent{ // Ҷ�ڵ�(�������)
public:
	void Operate() override { cout << "Ҷ�ڵ㣺cLeafA" << endl; }
};
class cLeafB : public iComponent{
public:
	void Operate() override { cout << "Ҷ�ڵ㣺cLeafB" << endl; }
};

class cComposite : public iComponent{ // ��Ͻڵ�(��������ӽڵ�)�����ڵݹ�
public:
	void Add(iComponent* p) { m_list.push_back(p); }
	void Remove(iComponent* p){
		list<iComponent*>::const_iterator it = m_list.begin();
		for (; m_list.end() != it; ++it)
		{
			if (*it == p) { m_list.erase(it); return; }
		}
	}
	void Operate() override {
		cout << "���ڵ㣺cComposite" << endl;
		for (auto v : m_list) v->Operate();
	}
private:
	list<iComponent*> m_list;
};

/************************************************************************/
// ʾ��
void test_Composite(){
	cout << "�������������������������������ģʽ����������������������������" << endl;
	cLeafA leafA;
	cLeafB leafB;
	cComposite groupA;
	groupA.Add(&leafA);
	groupA.Add(&leafB);

	cComposite group;
	group.Add(&leafA);
	group.Add(&groupA);
	group.Operate();
}