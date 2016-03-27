/************************************************************************
* @ �Զ����auto_ptr
* @ brief
	1����new����ָ������ʱ�Զ��ͷ��ڴ�(ptr��������ʱ�ͷ�)
	2����ָ֤��ֻ��Ψһ�����ߣ������ƶ����������ߣ������Ḵ��
	3����粻Ҫ����ʵֵָ�룬ptr�������������ָ��ʧЧ
* @ author zhoumf
* @ date 2014-11-7
************************************************************************/
#pragma once

template<class _Ty>
class My_unique_ptr{
public:
	My_unique_ptr(_Ty* p) : _ptr(p){}

	~My_unique_ptr() { delete _ptr; } // delete NULL;�ǰ�ȫ��

	// ���ƣ������ʵֵ����Ȩת�ƣ������ٶ�ʹ��
	My_unique_ptr(const My_unique_ptr& right) {
		iObserver* temp = right._ptr; // ��ֹ������������Ҫ�����ʱ����
		const_cast<_Ty*>(right._ptr) = NULL;
		_ptr = temp;
	}
	My_unique_ptr& operator = (const My_unique_ptr& right){
		_Ty* temp = right._ptr; // ��ֹ������������Ҫ�����ʱ����
		const_cast<_Ty*>(right._ptr) = NULL;
		_ptr = temp;
		return *this;
	}
	operator bool() { return _ptr != NULL; } // ת����������ʹ������ֱ���п�
	bool operator ==(const My_unique_ptr& right) const { return right._ptr == _ptr; }
	_Ty* operator->() { return _ptr; }   // �������ֵ���ָ��
	//_Ty& operator*() { return *_ptr; } // ��������л��ᱣ��ʵֵָ��
	//_Ty* get() { return _ptr; } // ����籣����ʵֵָ�룬auto_ptr��ǰ������������
private:
	_Ty* _ptr; // ��ʵֵָ��ı䶯�޶�������

	/*�Ż���
			1����ʵֵָ�����м������ü���
			2��void AddUseNum() { ++m_useNum; }
			3��virtual ~_Ty() { "�˴���ֹ��������" } // delete�������ȵ������������ٵ�operator delete
			4��void operator delete(void* p, size_t) { if (--(((_Ty*)p)->m_useNum) == 0) delete p; "�ͷ��ڴ����������"}
			5��operator delete���delete�����ٵ���������(ָ��pΪvoid�͵�Ե��ô��)
			6����������ָ�롪���û�Ҫ�Լ���AddUseNum()*/
	/*ע�⣺
			1����operator delete���Ͳ�Ҫ������������������
			2����Ϊ�������������ã�����һ���ͷ��ڴ棨��ý�����������Ϊ�գ�
			3��������Ҫ������delete�����operator delete�����delete��*/
	/*ѭ�����ã�
			1��������жԷ���ָ�롢��������óɻ�
			2�������໥�����ã���������ƣ��������������̫�ߣ�
			3���ɽ��������ָ����Ϊ�ӿڲ�����ʹ��֮��Ĺ�ϵ�޶��ڽӿ�
			4����Ҫ�������ָ�룬��ָ��ĳ�ʼ��д�ڹ��캯���У����������ѭ�����û���뱨��
			   _Ty(MyClass* p) { m_pClass = p; }*/
};