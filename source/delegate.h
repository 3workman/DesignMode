/**************************************************************************
 * @ �¼�ί��
 * @ brief
	 1��ί�пɿ����ǶԺ����ӿڵĳ���
	 2��һ��ί�ж���ɴ��ض�����������з������λ���
	 3��ί�ж��������صķ�����������ͬһ���࣬�����߱���ͬ�Ĳ���������ֵ���ͼ���
	 4������δ�����ķǾ�̬��Ա����������MessageMap.h�еĳ�Ա����ָ���÷�
	 5���Ա�Observer.h�۲���ģʽ
 * @ author zhoumf
 * @ date 2016-3-6
 ************************************************************************/
#pragma once

class iDelegate{}; //ֻ��Ϊ������c++���Աָ����ʽ����~
template<typename TReturn, typename TParam>
class cDelegate{
public:
	typedef TReturn(iDelegate::*Ptr_Fun)(TParam); // ����ָ��

	cDelegate() {}
	void Add(iDelegate* p, Ptr_Fun fun) { m_vecFun.push_back(stFun(p, fun)); }
	void Cut(iDelegate* p, Ptr_Fun fun)
	{
		auto it = m_vecFun.begin();
		for (; it != m_vecFun.end(); ++it){
			if (v.pObj == p && v.pFun == fun){
				m_vecFun.erase(it);
				break;
			}
		}
	}
	void operator()(TParam param)
	{
		for (stFun& v : m_vecFun) v(param); // ������'&'
	}

private:
	struct stFun{
		iDelegate* pObj;   // ����Ǹ����������ˣ���ָ�벻��Ұ�ˣ�������who Add who Cut��
		Ptr_Fun pFun;
		stFun(iDelegate* p, Ptr_Fun fun) : pObj(p), pFun(fun) {}
		TReturn operator()(TParam param) { return (pObj->*pFun)(param); }
	};
	vector<stFun> m_vecFun;
};

/************************************************************************/
// ʾ��
// Ҫ���صķ���
class cDelegateObjA : public iDelegate{
public:
	void Fun_1(int data)
	{
		cout << "�¼�ί�У�A�������" << data << endl;
	}
};
class cDelegateObjB : public iDelegate{
public:
	void Fun_2(int data)
	{
		cout << "�¼�ί�У�B�������" << data << endl;
	}
};
void test_Delegate(){
	cout << "�����������������������������¼�ί�� Delegate����������������������������" << endl;
	cDelegateObjA objA;
	cDelegateObjB objB;

	typedef cDelegate<void, int> Delegate;
	Delegate entrust;
	entrust.Add(&objA, static_cast<Delegate::Ptr_Fun>(&cDelegateObjA::Fun_1)); // ֱ��ǿת������Ϊstring���ͣ��Կɱ���ͨ��������ʱ崻�/(��o��)/~~
	entrust.Add(&objB, (Delegate::Ptr_Fun)&cDelegateObjB::Fun_2); // ��ʲô�취�������뱨���أ��� static_cast
	entrust(10);
}