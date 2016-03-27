/**************************************************************************
 * @ 单例模式
 * @ brief
     1、创建一个唯一的对象
	 2、常和工厂模式(Factory.h)一起使用
 * @ author zhoumf
 * @ date 2014-11-13
 ************************************************************************/
#pragma once


/************************************************************************/
// 指针式有啥优点？（指针形式的单例能选择释放时机） 一般用的引用式
class cSingleton{
protected: // 外界无法自己创建对象
	cSingleton() {}
public:
	static cSingleton& Instance(){ static cSingleton T; return T; }
	static cSingleton* GetSingleton(){
		if (NULL == _Instance)
		{
			_Instance = new cSingleton;
			atexit(cSingleton::Delete); // 将函数设置为程序结束时的响应函数
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
// 示例
void test_Singleton()
{
	cSingleton::Instance().DoSomething();
	cSingleton::GetSingleton()->DoSomething();
}