/************************************************************************
* @ 自定义的auto_ptr
* @ brief
	1、让new出的指针析构时自动释放内存(ptr对象析构时释放)
	2、保证指针只有唯一所有者，可以移动到新所有者，但不会复制
	3、外界不要保存实值指针，ptr对象消亡后，外界指针失效
* @ author zhoumf
* @ date 2014-11-7
************************************************************************/
#pragma once

template<class _Ty>
class My_unique_ptr{
public:
	My_unique_ptr(_Ty* p) : _ptr(p){}

	~My_unique_ptr() { delete _ptr; } // delete NULL;是安全的

	// 复制：对象的实值所有权转移，不可再度使用
	My_unique_ptr(const My_unique_ptr& right) {
		iObserver* temp = right._ptr; // 防止自身拷贝，所以要这个临时变量
		const_cast<_Ty*>(right._ptr) = NULL;
		_ptr = temp;
	}
	My_unique_ptr& operator = (const My_unique_ptr& right){
		_Ty* temp = right._ptr; // 防止自身拷贝，所以要这个临时变量
		const_cast<_Ty*>(right._ptr) = NULL;
		_ptr = temp;
		return *this;
	}
	operator bool() { return _ptr != NULL; } // 转换操作符：使对象能直接判空
	bool operator ==(const My_unique_ptr& right) const { return right._ptr == _ptr; }
	_Ty* operator->() { return _ptr; }   // 令对象表现得像指针
	//_Ty& operator*() { return *_ptr; } // 会让外界有机会保存实值指针
	//_Ty* get() { return _ptr; } // 若外界保存了实值指针，auto_ptr提前析构就有问题
private:
	_Ty* _ptr; // 将实值指针的变动限定在类内

	/*优化：
			1、在实值指针类中加入引用计数
			2、void AddUseNum() { ++m_useNum; }
			3、virtual ~_Ty() { "此处禁止清理数据" } // delete操作：先调析构函数，再调operator delete
			4、void operator delete(void* p, size_t) { if (--(((_Ty*)p)->m_useNum) == 0) delete p; "释放内存后清理数据"}
			5、operator delete里的delete不会再调析构函数(指针p为void型的缘故么？)
			6、差于智能指针——用户要自己调AddUseNum()*/
	/*注意：
			1、有operator delete，就不要在析构函数里清数据
			2、因为析构函数被调用，对象不一定释放内存（最好将析构函数设为空）
			3、清数据要在真正delete对象后（operator delete里调用delete后）*/
	/*循环引用：
			1、互相持有对方的指针、多个类引用成环
			2、出现类互相引用，属不良设计（互相依赖，耦合太高）
			3、可将其它类的指针作为接口参数，使类之间的关系限定于接口
			4、若要保存对象指针，将指针的初始化写在构造函数中，如此若出现循环引用会编译报错
			   _Ty(MyClass* p) { m_pClass = p; }*/
};