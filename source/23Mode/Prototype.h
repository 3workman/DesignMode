/**************************************************************************
 * @ 原型模式
 * @ brief
     1、原型实例，指定创建对象种类，通过拷贝原型创建新对象
     2、从一个对象再创建另一个对象（可定制），无需知道创建细节

     3、如果——构造函数执行时间很长，多次调用太低效了——

     4、在初始化信息不发生变化的情况下，克隆是最好的办法，既隐藏了对象创建细节，又提升性能
     5、不必重新初始化对象，而是动态获取对象运行时状态
 * @ author zhoumf
 * @ date 2014-10-29
 ************************************************************************/
#pragma once


/************************************************************************/
// 抽象 基类
class iPrototype{
public:
	virtual ~iPrototype() {}
    virtual iPrototype* Clone() const = 0;
};

/************************************************************************/
// 子类功能，平行扩展
class cObj_Prototype : public iPrototype{
public:
    cObj_Prototype() {}
	cObj_Prototype(const cObj_Prototype& copy){ // 注意深浅拷贝
		cout << "You can control the copy and get dynamic state" << endl;
	}

    // 调拷贝构造函数，避免再构造函数初始化
    // 克隆，获取对象运行时状态
    iPrototype* Clone() const{ return new cObj_Prototype(*this);}
    // new指针给外面用，很危险(=@__@=)呐，换智能指针？
};

/************************************************************************/
// 管理方式，松耦合

/************************************************************************/
// 示例
void test_Prototype(){
	cout << "——————————————原型模式——————————————" << endl;
    cObj_Prototype obj;

    cObj_Prototype* pClone = dynamic_cast<cObj_Prototype*>(obj.Clone());

    delete pClone;
}