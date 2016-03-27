/**************************************************************************
 * @ ������ģʽ
 * @ brief
     1������һ���ۺ϶�������ͳһ��װ
 * @ author zhoumf
 * @ date 2014-11-13
 ************************************************************************/
#pragma once


/************************************************************************/
// ��װ����
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
	size_t _endpos = 0;		// β�α�
	size_t _capacity = 64;  // ����
	_Ty* _arr;
};

/************************************************************************/
// ʾ��
void test_Iterator(){
	cout << "����������������������������������ģʽ����������������������������" << endl;
	cIterator<string> obj;
	obj.Insert("����");
	obj.Insert("����");
	obj.Insert("AD�ո��˶���");
	cIterator<string>::iterator it = obj.Begin();
	for (; it != obj.End(); ++it)
	{
		cout << *it << endl;
	}
}