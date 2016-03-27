/**************************************************************************
 * @ 访问者模式
 * @ brief
     1、在不破坏类的前提下，为类添加新操作
     2、将更新(变更)封装到一个类中（Visitor），并由待更改类（Obj_Visit）提供一个接收接口
	 3、访问者模式适用于数据结构相对稳定的系统
	 4、把数据结构、对数据结构的操作解耦
 * @ author zhoumf
 * @ date 2014-11-8
 ************************************************************************/
#pragma once


/************************************************************************/
// 抽象 基类
class iObj_Visit;
class iVisitor{ // 封装新内容的类
public:
	virtual ~iVisitor() {}
	virtual void Visit(iObj_Visit* pObj) = 0;
};

class iObj_Visit{ // 待更改类
public:
	virtual ~iObj_Visit() {}
	virtual void Accept(iVisitor* p) { p->Visit(this); } // 接收Visitor的访问
};

/************************************************************************/
// 子类功能，平行扩展
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
// 示例
void test_Visitor(){
	cout << "——————————————访问者模式——————————————" << endl;
	cVisitorA visitorA;
	cVisitorB visitorB;

	cObj_VisitA objA;
	objA.Accept(&visitorA);
	objA.Accept(&visitorB);

	cObj_VisitB objB;
	objB.Accept(&visitorA);
	objB.Accept(&visitorB);
}