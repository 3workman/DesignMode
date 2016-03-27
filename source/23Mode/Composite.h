/**************************************************************************
 * @ 组合模式
 * @ brief
     1、用于递归树状组合结构
	 2、须提供对子节点的数据结构管理(vector、array、list、map)
	 3、去除cComposite类的递归功能后，就是观察者模式(Observer.h)了
	 4、观察者本身也有一群子观察者
 * @ author zhoumf
 * @ date 2014-11-14
 ************************************************************************/
#pragma once


/************************************************************************/
// 抽象 基类
class iComponent{
public:
	virtual ~iComponent() {}
	virtual void Operate() = 0;
};

/************************************************************************/
// 子类功能，平行扩展
class cLeafA : public iComponent{ // 叶节点(基本组件)
public:
	void Operate() override { cout << "叶节点：cLeafA" << endl; }
};
class cLeafB : public iComponent{
public:
	void Operate() override { cout << "叶节点：cLeafB" << endl; }
};

class cComposite : public iComponent{ // 组合节点(包含多个子节点)，用于递归
public:
	void Add(iComponent* p) { m_list.push_back(p); }
	void Remove(iComponent* p){
		list<iComponent*>::const_iterator it = m_list.begin();
		for (; m_list.end() != it; ++it)
		{
			if (*it == p) { m_list.erase(it); return; }
		}
	}
	void Operate() override {
		cout << "根节点：cComposite" << endl;
		for (auto v : m_list) v->Operate();
	}
private:
	list<iComponent*> m_list;
};

/************************************************************************/
// 示例
void test_Composite(){
	cout << "——————————————组合模式——————————————" << endl;
	cLeafA leafA;
	cLeafB leafB;
	cComposite groupA;
	groupA.Add(&leafA);
	groupA.Add(&leafB);

	cComposite group;
	group.Add(&leafA);
	group.Add(&groupA);
	group.Operate();
}