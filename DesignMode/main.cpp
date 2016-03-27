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
    test_Factory();     // 工厂
	test_Reflect();		// 反射
    test_Strategy();    // 策略
	test_State();       // 状态
	test_Decorator();   // 装饰
    test_Proxy();       // 代理
    test_Facade();      // 外观
	test_Observer();    // 观察者
	test_Entrust();		// 事件委托
	test_Delegate();	// 事件委托
	test_Composite();   // 组合
	test_Mediator();    // 中介者
	test_Memento();     // 备忘录
	test_Command();     // 命令
	test_Bridge();      // 桥接
	test_Flyweight();   // 享元
	test_ChainOfResponsibility();   // 职责链
/************************************************************************/

    test_Prototype();   // 原型
	test_Builder();     // 建造者
	test_Template();    // 模板方法
	test_Visitor();     // 访问者
	test_Adapter();     // 适配器
	test_Interpreter(); // 解释器
	test_Iterator();    // 迭代器
	test_Singleton();   // 单例

	test_Move();		// Move语义
	
	cout << "——————————————测试通过——————————————" << endl;
	system("pause");
	return 0;
}