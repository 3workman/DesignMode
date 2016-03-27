/**************************************************************************
 * @ 适配器模式
 * @ brief
     1、将一个类(第三方库)的接口转化为客户希望的接口
     2、分为类模式（继承方式复用第三方接口）、对象模式（组合方式实现对第三方的复用）
	 3、很像装饰模式(Decorator.h)，为类的接口添加额外功能
 * @ author zhoumf
 * @ date 2014-11-9
 ************************************************************************/
#pragma once


class cObj_Adapter{ // 第三方类
public:
	void OldPort() {}
};

/************************************************************************/
// 抽象 基类
class iAdapter{
public:
	virtual ~iAdapter() {}
	virtual void NewPort() = 0; // 新接口
};

/************************************************************************/
// 子类功能，平行扩展
class cAdapter : public iAdapter{
public:
	cAdapter(cObj_Adapter* p) : _pObj(p) {}
	void NewPort() { cout << "NewPot do something to change OldPort" << endl; _pObj->OldPort(); } // 转化第三方类的接口
private:
	cObj_Adapter* _pObj;
};

/************************************************************************/
// 示例
void test_Adapter(){
	cout << "——————————————适配器模式——————————————" << endl;
	cObj_Adapter obj;
	cAdapter adapter(&obj);
	adapter.NewPort();
}