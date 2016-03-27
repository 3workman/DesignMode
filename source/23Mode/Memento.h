/**************************************************************************
 * @ 备忘录模式
 * @ brief
     1、不破坏封装性，捕获并保存一个对象的内存状态，可利用该状态实施恢复操作
	 2、命令模式(Command.h)中，常用备忘录来维护撤销操作的状态
 * @ author zhoumf
 * @ date 2014-11-13
 ************************************************************************/
#pragma once


typedef string STATE;
/************************************************************************/
// 备忘类：记录状态
class cMemento{
public:
	cMemento() { _state.clear(); }
	const STATE& GetState() { return _state; } // 返回 const STATE& 少一次值拷贝
	void SetState(const STATE& state) { _state = state; }
private:
	STATE _state;
};

/************************************************************************/
// 要备忘数据的类
class cObj_Memento{
public:
	const STATE& GetState() { return _state; }
	void SetState(const STATE& state) { _state = state; }

	cMemento* CreateMemento(){
		if (cMemento* pMemento = new cMemento())
		{
			pMemento->SetState(_state);
			cout << "Create the Memento" << endl;
			return pMemento;
		}
		return NULL;
	}
	void RestoreToMemento(cMemento*& pMemento){ //指针引用，外层的pMemento也会变为NULL
		if (NULL == pMemento) return;
		_state = pMemento->GetState();
		delete pMemento; pMemento = NULL;
		cout << "Restore to Memento" << endl;
	}
private:
	STATE _state;
};

/************************************************************************/
// 示例
void test_Memento(){
	cout << "——————————————备忘录模式——————————————" << endl;
	cObj_Memento obj;
	obj.SetState("State 1");
	cout << "State of the Object : " << obj.GetState() << endl;

	cMemento* pMemento = obj.CreateMemento();

	obj.SetState("State 2");
	cout << "State of the Object : " << obj.GetState() << endl;

	obj.RestoreToMemento(pMemento); //调用完成后，pMemento变为NULL
	cout << "State of the Object : " << obj.GetState() << endl;
}