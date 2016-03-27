/**************************************************************************
 * @ 解释器模式
 * @ brief
     1、为简单语言定义一个文法，如何在该语言中表示一个句子、如何解释句子
     2、代码以加减运算为例
	 3、优点：每条文法规则彼此独立，易于改变/扩展文法
	 4、缺陷：效率低，涉及大量递归/循环，调试困难
 * @ author zhoumf
 * @ date 2014-11-12
 ************************************************************************/
#pragma once


class iInterpreter;
class cContext_Interpret{
public:
	void SetValue(string key, int val) { _mapValue[key] = val; }
	int GetValue(string key) { return _mapValue[key]; }
	int Calc();
public:
	vector<string> _vecStr;		// 公式
	map<string, int> _mapValue; // 参数
	std::stack<iInterpreter*> _stack;
};

/************************************************************************/
// 抽象 基类
class iInterpreter{
public:
	virtual ~iInterpreter() { cout << "Delete Interpreter" << endl; }
	virtual int Interpret(cContext_Interpret& context) = 0;
};

/************************************************************************/
// 子类功能，平行扩展
class cTerminal : public iInterpreter{ // 通常只一个
/*终结符：1、语言中用到的基本元素，不能再被分解，语法中的最小逻辑单元
		  2、如a + b中的a、b只需赋值，无需做任何处理，所有元素都对应一个具体业务参数
		  3、实现与文法中的元素相关联的解释操作，通常一个解释器模式中只有一个终结符表达式*/
public:
	cTerminal(string key) : _key(key) {}
	int Interpret(cContext_Interpret& context) { return context.GetValue(_key); }
private:
	string _key;
};

class cNonterminal : public iInterpreter{ // 通常有多个
/*非终结符：1、文法中的每条规则对应于一个非终结表达式
			2、非终结表达式根据逻辑的复杂程度而增加，原则上每个文法规则都对应一个非终结符表达式
			3、如a + b中的运算符，需要我们编写算法进行处理，每个运算符都要对应处理单元
			4、每个规则需要分别实现解释操作，如加法要加法解析器、减法要减法解析器*/
public:
	cNonterminal(iInterpreter* p) : _p(p) {}
	int Interpret(cContext_Interpret& context){
		int ret = _p->Interpret(context);
		delete _p;
		return ret;
	}
private:
	iInterpreter* _p;
};
class cNonterminal_Add : public iInterpreter{
public:
	cNonterminal_Add(iInterpreter* left, iInterpreter* right) : _left(left), _right(right) {}
	int Interpret(cContext_Interpret& context){
		int ret = _left->Interpret(context) + _right->Interpret(context);
		delete _left; delete _right;
		return ret;
	}
private:
	iInterpreter* _left;
	iInterpreter* _right;
};
class cNonterminal_Sub : public iInterpreter{
public:
	cNonterminal_Sub(iInterpreter* left, iInterpreter* right) : _left(left), _right(right) {}
	int Interpret(cContext_Interpret& context){
		int ret = _left->Interpret(context) - _right->Interpret(context);
		delete _left; delete _right;
		return ret;
	}
private:
	iInterpreter* _left;
	iInterpreter* _right;
};

/************************************************************************/
// 管理方式，松耦合
int cContext_Interpret::Calc()
{
	iInterpreter *left(NULL), *right(NULL);
	vector<string>::iterator it = _vecStr.begin();
	for (; it != _vecStr.end(); ++it)
	{
		const string& str = *it;
		if (str == "+")
		{
			if (_stack.empty()) continue;
			left = _stack.top(); _stack.pop();
			right = new cTerminal(*(++it));
			_stack.push(new cNonterminal_Add(left, right));
		}
		else if (str == "-")
		{
			if (_stack.empty()) continue;
			left = _stack.top(); _stack.pop();
			right = new cTerminal(*(++it));
			_stack.push(new cNonterminal_Sub(left, right));
		}
		else
		{
			_stack.push(new cTerminal(str));
		}
	}

	if (_stack.empty()) return 0;
	left = _stack.top(); _stack.pop();
	int nRet = left->Interpret(*this);
	delete left; // 最后一个用完要delete
	return nRet;
}

/************************************************************************/
// 示例
void test_Interpreter(){
	cout << "——————————————解释器模式——————————————" << endl;
	cContext_Interpret context;

	string arr[] = { "a", "+", "b", "-", "c" };
	vector<string>& vec = context._vecStr;
	map<string, int>& map = context._mapValue;
	vec.insert(vec.end(), arr, arr + 5);
	map["a"] = 3; map["b"] = 2; map["c"] = 1;

	cout << "a + b - c = " << context.Calc() << endl;
}