/**************************************************************************
 * @ ������ģʽ
 * @ brief
     1��Ϊ�����Զ���һ���ķ�������ڸ������б�ʾһ�����ӡ���ν��;���
     2�������ԼӼ�����Ϊ��
	 3���ŵ㣺ÿ���ķ�����˴˶��������ڸı�/��չ�ķ�
	 4��ȱ�ݣ�Ч�ʵͣ��漰�����ݹ�/ѭ������������
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
	vector<string> _vecStr;		// ��ʽ
	map<string, int> _mapValue; // ����
	std::stack<iInterpreter*> _stack;
};

/************************************************************************/
// ���� ����
class iInterpreter{
public:
	virtual ~iInterpreter() { cout << "Delete Interpreter" << endl; }
	virtual int Interpret(cContext_Interpret& context) = 0;
};

/************************************************************************/
// ���๦�ܣ�ƽ����չ
class cTerminal : public iInterpreter{ // ͨ��ֻһ��
/*�ս����1���������õ��Ļ���Ԫ�أ������ٱ��ֽ⣬�﷨�е���С�߼���Ԫ
		  2����a + b�е�a��bֻ�踳ֵ���������κδ�������Ԫ�ض���Ӧһ������ҵ�����
		  3��ʵ�����ķ��е�Ԫ��������Ľ��Ͳ�����ͨ��һ��������ģʽ��ֻ��һ���ս�����ʽ*/
public:
	cTerminal(string key) : _key(key) {}
	int Interpret(cContext_Interpret& context) { return context.GetValue(_key); }
private:
	string _key;
};

class cNonterminal : public iInterpreter{ // ͨ���ж��
/*���ս����1���ķ��е�ÿ�������Ӧ��һ�����ս���ʽ
			2�����ս���ʽ�����߼��ĸ��ӳ̶ȶ����ӣ�ԭ����ÿ���ķ����򶼶�Ӧһ�����ս�����ʽ
			3����a + b�е����������Ҫ���Ǳ�д�㷨���д���ÿ���������Ҫ��Ӧ����Ԫ
			4��ÿ��������Ҫ�ֱ�ʵ�ֽ��Ͳ�������ӷ�Ҫ�ӷ�������������Ҫ����������*/
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
// ����ʽ�������
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
	delete left; // ���һ������Ҫdelete
	return nRet;
}

/************************************************************************/
// ʾ��
void test_Interpreter(){
	cout << "����������������������������������ģʽ����������������������������" << endl;
	cContext_Interpret context;

	string arr[] = { "a", "+", "b", "-", "c" };
	vector<string>& vec = context._vecStr;
	map<string, int>& map = context._mapValue;
	vec.insert(vec.end(), arr, arr + 5);
	map["a"] = 3; map["b"] = 2; map["c"] = 1;

	cout << "a + b - c = " << context.Calc() << endl;
}