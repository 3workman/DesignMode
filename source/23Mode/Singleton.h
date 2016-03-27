/**************************************************************************
 * @ ����ģʽ
 * @ brief
     1������һ��Ψһ�Ķ���
	 2�����͹���ģʽ(Factory.h)һ��ʹ��
 * @ author zhoumf
 * @ date 2014-11-13
 ************************************************************************/
#pragma once


/************************************************************************/
// ָ��ʽ��ɶ�ŵ㣿��ָ����ʽ�ĵ�����ѡ���ͷ�ʱ���� һ���õ�����ʽ
class cSingleton{
protected: // ����޷��Լ���������
	cSingleton() {}
public:
	static cSingleton& Instance(){ static cSingleton T; return T; }
	static cSingleton* GetSingleton(){
		if (NULL == _Instance)
		{
			_Instance = new cSingleton;
			atexit(cSingleton::Delete); // ����������Ϊ�������ʱ����Ӧ����
		}
		return _Instance;
	}
	static void Delete(void) { delete _Instance; }
private:
	static cSingleton* _Instance;
public:
	void DoSomething() {}
};
cSingleton* cSingleton::_Instance = NULL;

/************************************************************************/
// ʾ��
void test_Singleton()
{
	cSingleton::Instance().DoSomething();
	cSingleton::GetSingleton()->DoSomething();
}