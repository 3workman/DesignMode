/**************************************************************************
 * @ 桥接模式
 * @ brief
     1、系统被分为抽象部分、实现部分，两个部分可独立修改
     2、实现是指——抽象类/派生类通过对象组合（持有它类指针/直接保存对象）实现需求
	 3、需要多角度分类实现对象时，单纯用继承会造成类数量激增——优先使用合成/聚合
	 4、聚合：弱拥有关系，A可以包含B，但B不是A的一部分（A持有B指针）
	 5、合成：强拥有关系，严格的部分/整体的关系，二者生命周期一致（A内嵌了B对象）
 * @ author zhoumf
 * @ date 2014-11-16
 ************************************************************************/
#pragma once


class cDrawLib1{ // 用以实现操作的类库（不在继承系统中）
public:
	void DrawCircle(){ cout << "Draw Circle use LIB 1" << endl; }
	void DrawRect(){ cout << "Draw Rect use LIB 1" << endl; }
	void DrawTriangle(){ cout << "Draw Triangle use LIB 1" << endl; }
};
class cDrawLib2{
public:
	void DrawCircle(){ cout << "Draw Circle use LIB 2" << endl; }
	void DrawRect(){ cout << "Draw Rect use LIB 2" << endl; }
	void DrawTriangle(){ cout << "Draw Triangle use LIB 2" << endl; }
};
/************************************************************************/
// 抽象部分——决定系统中各继承树之间的关系(iDraw、iShape指定)，子类只负责实例化即可
class iDraw{
public: // 链接外部类库，包装外部库(转化接口)后给自己的系统使用
	virtual ~iDraw() {}
	virtual void OperateA() = 0;
	virtual void OperateB() = 0;
};

class iShape{ // 库的使用者基类
public:
	iShape(iDraw* p) : m_pLib(p) {}
	virtual ~iShape() {}
	virtual void DrawShape() = 0;
protected:
	iDraw* m_pLib;
};

/************************************************************************/
// 实现部分——系统中的各个子类，不必互相有联系，能各自独立实现
class cDraw1 : public iDraw{
public: // 负责链接外部类库的子类，可自定义实际链接的对象（多角度分类实现对象）
	void OperateA() { m_lib.DrawCircle(); }
	void OperateB() { m_lib.DrawRect(); }
private:
	cDrawLib1 m_lib;
};
class cDraw2 : public iDraw{
public:
	void OperateA() { m_lib.DrawTriangle(); }
	void OperateB() { m_lib.DrawRect(); }
private:
	cDrawLib2 m_lib;
};

class cCircle : public iShape{ // 用户只关心自己要的接口
public:
	cCircle(iDraw* p) : iShape(p) {}
	void DrawShape() { m_pLib->OperateA(); }
};
class cRect : public iShape{
public:
	cRect(iDraw* p) : iShape(p) {}
	void DrawShape() { m_pLib->OperateB(); }
};

/************************************************************************/
// 示例
void test_Bridge(){
	cout << "——————————————桥接模式——————————————" << endl;
	cDraw1 draw1;
	cDraw2 draw2;

	cCircle circle(&draw1);
	cRect rect(&draw2);
	circle.DrawShape();
	rect.DrawShape();
}