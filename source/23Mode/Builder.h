/**************************************************************************
 * @ 建造者模式
 * @ brief
     1、将对象的构建与细节表示分离，抽象统一的构建过程（避免遗漏步骤）
     2、用于创建复杂对象，这些对象内部部件间的——建造顺序稳定，但构建内容有变动——
	 3、若建造顺序有互相依赖性（后一步需要前一步的结果），就将建造接口protected
 * @ author zhoumf
 * @ date 2014-11-3
 ************************************************************************/
#pragma once


class cObj_Builder{ // 要创建的产品
public:
	void Show() { cout << "成功创建产品！" << endl; }
};

/************************************************************************/
// 抽象 基类
class iBuilder{ // 抽象统一的构建过程
public:
	iBuilder() : m_pObj(new cObj_Builder) {}

	virtual ~iBuilder() { delete m_pObj; } // 基类虚析构函数（易忘记）

    virtual void BuildStep1() = 0;
    virtual void BuildStep2() = 0;

	cObj_Builder* GetResult() { return m_pObj; }

protected:
    cObj_Builder* const m_pObj; // 防止指针变动，建造中途指向了另一产品
};

/************************************************************************/
// 子类功能，平行扩展
class cBuilderA : public iBuilder{
public:
	void BuildStep1() { m_pObj; cout << "cBuilderA do step1" << endl; }
	void BuildStep2() { m_pObj; cout << "cBuilderA do step2" << endl; }
};
class cBuilderB : public iBuilder{
public:
	void BuildStep1() { m_pObj; cout << "cBuilderB do step1" << endl; }
	void BuildStep2() { m_pObj; cout << "cBuilderB do step2" << endl; }
};

/************************************************************************/
// 管理方式：统一的建造过程调用
class cManageBuilder{
public:
	void UnifyBuild(iBuilder& builder)
    {
        builder.BuildStep1();
        builder.BuildStep2();
    }
};

/************************************************************************/
// 示例
void test_Builder(){
	cout << "——————————————建造者模式——————————————" << endl;
	cManageBuilder manage;

	cBuilderA builderA;
	manage.UnifyBuild(builderA);

    builderA.GetResult()->Show();
}