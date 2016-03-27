/**************************************************************************
 * @ 迭代器模式
 * @ brief
     1、遍历一个聚合对象，用类统一封装
 * @ author zhoumf
 * @ date 2014-11-13
 ************************************************************************/
#pragma once


/************************************************************************/
// 封装遍历
template <typename _Ty>
class cIterator{
public:
	cIterator() { _arr = new _Ty[_capacity]; }
	~cIterator(){ delete[] _arr; }
	typedef _Ty* iterator;
	size_t Size() { return _endpos; }
	iterator Begin() { return &_arr[0]; }
	iterator End() { return &_arr[_endpos]; }
	iterator Insert(const _Ty& val)
	{
		if (_endpos >= _capacity) Double();
		return &(_arr[_endpos++] = val);
	}
private:
	void Double()
	{
		_Ty* temp = new _Ty[_capacity *= 2];
		memcpy(temp, _arr, _capacity/2 * sizeof(_Ty));
		delete[] _arr;
		_arr = temp;
	}
	size_t _endpos = 0;		// 尾游标
	size_t _capacity = 64;  // 容量
	_Ty* _arr;
};

/************************************************************************/
// 示例
void test_Iterator(){
	cout << "——————————————迭代器模式——————————————" << endl;
	cIterator<string> obj;
	obj.Insert("阿呆");
	obj.Insert("渣渣");
	obj.Insert("AD收腹运动机");
	cIterator<string>::iterator it = obj.Begin();
	for (; it != obj.End(); ++it)
	{
		cout << *it << endl;
	}
}