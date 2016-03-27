/**************************************************************************
 * @ ����¼ģʽ
 * @ brief
     1�����ƻ���װ�ԣ����񲢱���һ��������ڴ�״̬�������ø�״̬ʵʩ�ָ�����
	 2������ģʽ(Command.h)�У����ñ���¼��ά������������״̬
 * @ author zhoumf
 * @ date 2014-11-13
 ************************************************************************/
#pragma once


typedef string STATE;
/************************************************************************/
// �����ࣺ��¼״̬
class cMemento{
public:
	cMemento() { _state.clear(); }
	const STATE& GetState() { return _state; } // ���� const STATE& ��һ��ֵ����
	void SetState(const STATE& state) { _state = state; }
private:
	STATE _state;
};

/************************************************************************/
// Ҫ�������ݵ���
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
	void RestoreToMemento(cMemento*& pMemento){ //ָ�����ã�����pMementoҲ���ΪNULL
		if (NULL == pMemento) return;
		_state = pMemento->GetState();
		delete pMemento; pMemento = NULL;
		cout << "Restore to Memento" << endl;
	}
private:
	STATE _state;
};

/************************************************************************/
// ʾ��
void test_Memento(){
	cout << "��������������������������������¼ģʽ����������������������������" << endl;
	cObj_Memento obj;
	obj.SetState("State 1");
	cout << "State of the Object : " << obj.GetState() << endl;

	cMemento* pMemento = obj.CreateMemento();

	obj.SetState("State 2");
	cout << "State of the Object : " << obj.GetState() << endl;

	obj.RestoreToMemento(pMemento); //������ɺ�pMemento��ΪNULL
	cout << "State of the Object : " << obj.GetState() << endl;
}