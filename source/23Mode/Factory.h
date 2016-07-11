/**************************************************************************
 * @ ����ģʽ
 * @ brief
     1��ͳһ��������ʵ�������Ż�����ṹ
     2���������� new ��������һ��Ҫ delete
     3������Ƕ������ָ�룬Ҫ��ֹѭ�����ã�
	 4�����󹤳�ģʽ���ٳ���һ��iFactory���ɸ���cFactory���࣬ͳһ����
 * @ author zhoumf
 * @ date 2014-09-19
 ************************************************************************/
#pragma once
#include <functional>
#include "..\tool\My_unique_ptr.h"

/************************************************************************/
// ���� ����
class iOperation{
public:
    /*û�в��������еĲ�������Ĭ��ֵ�Ĺ��캯����ΪĬ�Ϲ��캯��
    �������û���������캯�������������Զ�����һ��Ĭ���޲������캯��
    �������һ�����캯������,��ô�������������Ĭ�Ϲ��캯��*/
    iOperation(double a = 0, double b = 0) {_numA = a; _numB = b;}

	virtual ~iOperation() { cout << "Delete Operation" << endl; } // ���������������������ǣ�
	virtual void DoSomething() = 0;

protected:
    double _numA;
    double _numB;
};

/************************************************************************/
// ���๦�ܣ�ƽ����չ
class cOperationA : public iOperation{
public:
	void DoSomething() override { cout << "Use A Operation" << endl; }

	//��ʶ��override : ���麯��Ӧ����д�����е��麯��
	//void DoSomething(int) override { cout << "Use A Operation" << endl; } //����뱨��
	//��ʶ��final : �������麯����Ӧ����д�����麯��
	//void DoSomething() final { cout << "Use A Operation" << endl; } // ������غ�����
};
class cOperationB : public iOperation{
public:
	void DoSomething() { cout << "Use B Operation" << endl; }
};

/************************************************************************/
// ����ʽ�������
enum class EnumOperation{ // ǿ����ö�٣����Ὣö�ٳ�����¶�����������Ҳ������ʽת��Ϊ����
    Operation_A,
    Operation_B,
};
class cFactory{ // ö�ٹ����������ʵ����
public:
    static iOperation* NewObject(EnumOperation eType){
        switch (eType){
		case EnumOperation::Operation_A:      return new cOperationA();
		case EnumOperation::Operation_B:      return new cOperationB();
        default : return NULL;
        }
    }
};

/************************************************************************/
// ʾ��
void test_Factory(){
	cout << "��������������������������������ģʽ����������������������������" << endl;
	if (iOperation* pObj = cFactory::NewObject(EnumOperation::Operation_A))
    {
        pObj->DoSomething();

        delete pObj; // �ǵ�����Ҫdelete
    }
}

/************************************************************************/
// ����������ģ��Java������ƣ�����ȫ�ֻ��������ж��������ڴ��ͳһ�������Ч�ʣ�
const char* const OBJ_NAME[] = { // ������������ɱ���������
	"cOperationA",
	"cOperationB",
};
template<class T> iOperation* new_obj() { return new T; }
typedef iOperation* (*New_Fun)(); // ����ָ��
New_Fun const ARR_FUN[] = { // ָ�뱾���ܸı�(��ָֹ���ĺ���)
	new_obj<cOperationA>,
	new_obj<cOperationB>,
};
STATIC_ASSERT_ARRAY_ARRAY(OBJ_NAME, ARR_FUN);

/*����������
		1��Lambda���ʽ��'[]'�����'='��'&'����ʲô��ʽ�����񣨱հ���������(��ֵ������)		[a,&b]aֵ��b����
		2��'[]'��������ͼ��Lambda��ʹ���κ��ⲿ�������Ǵ����
		3��'()'���ǲ����б��޲���ʱ��ʡ��													[ capture ] { body }
		4��'->'���Ƿ���ֵ���ͣ���ʡ�ԣ���return�Զ��ƶ�										[ capture ] ( params ) { body }
		5�����һ���հ����оֲ����������ã��ڳ�����������������֮��ı�ʹ�ã�������Ϊ��δ�����!*/
std::function<iOperation*()> const ARR_NEW[] = {
	[]()->iOperation* { return new cOperationA; },
	[]()->iOperation* { return new cOperationB; },
};
static_assert( sizeof(OBJ_NAME)/sizeof(OBJ_NAME[0])==sizeof(ARR_NEW)/sizeof(ARR_NEW[0]), "Length isn't equal");

template<class _Ty>
class cNewObjByName{ // ��������
public:
	static cNewObjByName& Instance(){ static cNewObjByName T; return T; }

	typedef My_unique_ptr<_Ty> unique_ptr; // Ƕ������ָ��
	unique_ptr NewObjByName(string name)
	{
		//auto����ռλ����֪ͨ������ȥ���ݳ�ʼ�������ƶ���������������ʵ����
		auto it = mapNewFun.find(name); //NewFunMap::iterator it = mapNewFun.find(name);
		if (mapNewFun.end() != it) return (it->second)();
		assert(!"��������");
		return NULL;
	}
private:
	cNewObjByName(){ // ���캯������ʼ��<����������ָ��>��
		for (int i = 0; i < sizeof(OBJ_NAME)/sizeof(OBJ_NAME[0]); ++i){
			if (!mapNewFun.insert(make_pair(OBJ_NAME[i], ARR_FUN[i])).second)
				assert(!"�����ظ���"); // ����ʧ��
		}
	}
	typedef _Ty* (*New_Fun)(); // ����ָ��
	typedef std::map<string, New_Fun> NewFunMap;
	NewFunMap mapNewFun;
};

/************************************************************************/
// ʾ��
void test_Reflect(){
	cout << "����������������������������������ơ���������������������������" << endl;
	if (cNewObjByName<iOperation>::unique_ptr pObj = cNewObjByName<iOperation>::Instance().NewObjByName("cOperationB"))
	{
		pObj->DoSomething();
	}
}

/************************************************************************/
// �Ǹ����ŵ�ͬѧ������û�з���VS2013������insert()�β���value_type&& _Val����VS2005��const value_type& _Val
// ��������ɶ���
/* Move���壺
		1��vector<int> getVec() { vector<int> vec; return vec; } //�������θ���()
		   �ں�������ʱ����local����Ҫ�����գ�������Ҫcopy����һ����ʱ���󷵻ظ����
		   ���������ʱ���������Ҫһ��copy��ֵ��������ֵ����������
		2��C++11��һ��ֵ�Ƿ���ʱ�ģ�������ֵ��������⣬��ֵ����ʹ��&&�﷨��������const/��const
		   �������ʾ��
		3��move�������ʹ��ʱ������⿽��������֤��ʱ��������Դ�İ�ȫ��
		  ��ò�ơ����ǲ�����Դһ��Ҫ��ȫ���Ե�static��global��new��
		4������move����/��ֵ��������const&����/��ֵ������������
		   move������ǳ����������ԭʼָ����ΪNULL������ʱ�����������ͷ��ڴ�
*/
class cMove{
public:
	cMove(int n) { _p = new int(n); }
	~cMove() { delete _p; }

	cMove(cMove&& other)
		: _p(other._p)
	{
		cout << "Move ���챻����" << endl;
		other._p = NULL;
	}

	cMove(const cMove& other)
		: _p(new int)
	{
		cout << "��ͨ���챻����" << endl;
		memcpy(_p, other._p, sizeof(int));
	}
private:
	int* _p;
};
string Set(string& val) { return val; }				  // ����ƥ����ֵ����/������������const &
string Set(const string& val) { return val; }		  // ��ƥ��ȫ��
string Set(string&& val) { return val = "��ֵ����"; } // ֻ��ƥ����ֵ����(��ʱ��������)��������const &

void test_Move(){
	cout << "����������������������������Move���塪��������������������������" << endl;
	string str("����");
	cout << Set(str) << endl;
	cout << Set("����") << endl; // ���볣������������������Ӵ����������ʱ������ֵ��

	auto fun = []{ cMove obj(10);  return obj; };
	fun();				// ��һ��move���캯��
	cMove obj1(fun());	// Ҳ��һ�Σ������������ѵ���������æ�����Ż�,ֱ�Ӱ���ʱ����������obj( �� o �� )��
						// ��Ϊ�ж�����ʽ����fun()�����Բ����ٴ�����ʱ����������ֵ
	cMove obj2 = fun(); // ����ֻ��һ�Σ�����������operator=  �Զ����ɿ������캯������ֵ��������
}