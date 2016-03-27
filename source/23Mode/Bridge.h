/**************************************************************************
 * @ �Ž�ģʽ
 * @ brief
     1��ϵͳ����Ϊ���󲿷֡�ʵ�ֲ��֣��������ֿɶ����޸�
     2��ʵ����ָ����������/������ͨ��������ϣ���������ָ��/ֱ�ӱ������ʵ������
	 3����Ҫ��Ƕȷ���ʵ�ֶ���ʱ�������ü̳л����������������������ʹ�úϳ�/�ۺ�
	 4���ۺϣ���ӵ�й�ϵ��A���԰���B����B����A��һ���֣�A����Bָ�룩
	 5���ϳɣ�ǿӵ�й�ϵ���ϸ�Ĳ���/����Ĺ�ϵ��������������һ�£�A��Ƕ��B����
 * @ author zhoumf
 * @ date 2014-11-16
 ************************************************************************/
#pragma once


class cDrawLib1{ // ����ʵ�ֲ�������⣨���ڼ̳�ϵͳ�У�
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
// ���󲿷֡�������ϵͳ�и��̳���֮��Ĺ�ϵ(iDraw��iShapeָ��)������ֻ����ʵ��������
class iDraw{
public: // �����ⲿ��⣬��װ�ⲿ��(ת���ӿ�)����Լ���ϵͳʹ��
	virtual ~iDraw() {}
	virtual void OperateA() = 0;
	virtual void OperateB() = 0;
};

class iShape{ // ���ʹ���߻���
public:
	iShape(iDraw* p) : m_pLib(p) {}
	virtual ~iShape() {}
	virtual void DrawShape() = 0;
protected:
	iDraw* m_pLib;
};

/************************************************************************/
// ʵ�ֲ��֡���ϵͳ�еĸ������࣬���ػ�������ϵ���ܸ��Զ���ʵ��
class cDraw1 : public iDraw{
public: // ���������ⲿ�������࣬���Զ���ʵ�����ӵĶ��󣨶�Ƕȷ���ʵ�ֶ���
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

class cCircle : public iShape{ // �û�ֻ�����Լ�Ҫ�Ľӿ�
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
// ʾ��
void test_Bridge(){
	cout << "�����������������������������Ž�ģʽ����������������������������" << endl;
	cDraw1 draw1;
	cDraw2 draw2;

	cCircle circle(&draw1);
	cRect rect(&draw2);
	circle.DrawShape();
	rect.DrawShape();
}