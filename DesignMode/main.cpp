// main.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#define _MY_Test
#include "..\source\23Mode\Factory.h"
#include "..\source\23Mode\Strategy.h"
#include "..\source\23Mode\Decorator.h"
#include "..\source\23Mode\Proxy.h"
#include "..\source\23Mode\Prototype.h"
#include "..\source\23Mode\TemplateMethod.h"
#include "..\source\23Mode\Facade.h"
#include "..\source\23Mode\Builder.h"
#include "..\source\23Mode\Observer.h"
#include "..\source\23Mode\Mediator.h"
#include "..\source\23Mode\Visitor.h"
#include "..\source\23Mode\Adapter.h"
#include "..\source\23Mode\Interpreter.h"
#include "..\source\23Mode\Iterator.h"
#include "..\source\23Mode\Memento.h"
#include "..\source\23Mode\State.h"
#include "..\source\23Mode\Composite.h"
#include "..\source\23Mode\Singleton.h"
#include "..\source\23Mode\Bridge.h"
#include "..\source\23Mode\Command.h"
#include "..\source\23Mode\Flyweight.h"
#include "..\source\23Mode\ChainOfResponsibility.h"
#include "..\source\delegate.h"
#undef _MY_Test


int _tmain(int argc, _TCHAR* argv[]){
/************************************************************************/
    test_Factory();     // ����
	test_Reflect();		// ����
    test_Strategy();    // ����
	test_State();       // ״̬
	test_Decorator();   // װ��
    test_Proxy();       // ����
    test_Facade();      // ���
	test_Observer();    // �۲���
	test_Entrust();		// �¼�ί��
	test_Delegate();	// �¼�ί��
	test_Composite();   // ���
	test_Mediator();    // �н���
	test_Memento();     // ����¼
	test_Command();     // ����
	test_Bridge();      // �Ž�
	test_Flyweight();   // ��Ԫ
	test_ChainOfResponsibility();   // ְ����
/************************************************************************/

    test_Prototype();   // ԭ��
	test_Builder();     // ������
	test_Template();    // ģ�巽��
	test_Visitor();     // ������
	test_Adapter();     // ������
	test_Interpreter(); // ������
	test_Iterator();    // ������
	test_Singleton();   // ����

	test_Move();		// Move����
	
	cout << "��������������������������������ͨ������������������������������" << endl;
	system("pause");
	return 0;
}