/**************************************************************************
 * @ 享元模式
 * @ brief
     1、共享，支持大量细粒度的对象
	 2、程序设计中，有时需要生成大量细粒度的类实例(对象)来表示数据
		若这些对象除个别参数外都相同，就可以把这些个别参数移到类实例的外面，函数调用时才传进来
	 3、即Flyweight执行时所需的数据有内部的也有外部的
	    内部数据存储于Flyweight对象中
		外部数据由客户端自己管理，调用相应函数时才传递
 * @ author zhoumf
 * @ date 2014-11-16
 ************************************************************************/
#pragma once


/************************************************************************/
class cBook{ // 包含细粒度对象的类
public:
	void SetPublisher(string strPublisher) { m_strPublisher = strPublisher; }
	void SetWriter(string strWriter)       { m_strWriter = strWriter; }
	void SetName(string strName)	       { m_strName = strName; }
	void SetPrice(int nPrice)              { m_nPrice = nPrice; }

	void PrintInfo()
	{
		cout << "Book Name : "		<< m_strName		<< endl;
		cout << "Book Publisher : " << m_strPublisher	<< endl;
		cout << "Book Writer : "	<< m_strWriter		<< endl;
		cout << "Book Price : "		<< m_nPrice			<< endl;
	}
private:
	string m_strPublisher; // 出版商
	string m_strWriter;	   // 作者
	string m_strName;	   // 书名
	int    m_nPrice;	   // 价格
};

class cPublisherFlyweight{ // 出版商 共享类
public:
	cPublisherFlyweight(string strPublisher) { m_strPublisher = strPublisher; }
	string GetPublisher() { return m_strPublisher; }
private:
	string m_strPublisher;
};
class cPublisherMgr{ // 共享管理
public:
	~cPublisherMgr()
	{
		for (auto& pair : m_mapPublisher) 
		{
			delete pair.second;
		}
	}
	cPublisherFlyweight* CreatePublisher(string strKey)
	{
		cPublisherFlyweight* pPublisherFlyWeight = NULL;
		auto it = m_mapPublisher.find(strKey);
		if (it != m_mapPublisher.end()){
			pPublisherFlyWeight = it->second;
			//cout << "Already existed this publisher : " << pPublisherFlyWeight->GetPublisher() << endl;
		}else{
			pPublisherFlyWeight = new cPublisherFlyweight(strKey);
			m_mapPublisher.insert(make_pair(strKey, pPublisherFlyWeight));
			//cout << "New a publisher : " << pPublisherFlyWeight->GetPublisher() << endl;
		}
		return pPublisherFlyWeight;
	}
private:
	map<string, cPublisherFlyweight*> m_mapPublisher;
};

class cWriterFlyweight{ // 作者 共享类
public:
	cWriterFlyweight(string strWriter) { m_strWriter = strWriter; }
	string GetWriter() { return m_strWriter; }
private:
	string m_strWriter;
};
class cWriterMgr{
public:
	~cWriterMgr()
	{
		for (auto& pair : m_mapWriter)
		{
			delete pair.second;
		}
	}
	cWriterFlyweight* CreateWriter(string strKey)
	{
		cWriterFlyweight* pWriterFlyWeight = NULL;
		auto it = m_mapWriter.find(strKey);
		if (it != m_mapWriter.end()){
			pWriterFlyWeight = (*it).second;
			//cout << "Already existed this writer : " << pWriterFlyWeight->GetWriter() << endl;
		}else{
			pWriterFlyWeight = new cWriterFlyweight(strKey);
			m_mapWriter.insert(make_pair(strKey, pWriterFlyWeight));
			//cout << "New a writer : " << pWriterFlyWeight->GetWriter() << endl;
		}
		return pWriterFlyWeight;
	}
private:
	map<string, cWriterFlyweight*> m_mapWriter;
};

/************************************************************************/
// 示例
void test_Flyweight(){
	cout << "——————————————享元模式——————————————" << endl;
	cPublisherMgr PMgr;
	cWriterMgr    WMgr;
	cBook book1, book2;

	book1.SetPrice(50);
	book1.SetName("《深入浅出MFC》");
	book1.SetPublisher((PMgr.CreatePublisher("电子工业出版社")->GetPublisher()));
	book1.SetWriter((WMgr.CreateWriter("侯捷")->GetWriter()));
	book1.PrintInfo();
	cout << endl;

	book1.SetPrice(50);
	book1.SetName("《STL源码剖析》");
	book1.SetPublisher((PMgr.CreatePublisher("电子工业出版社")->GetPublisher()));
	book1.SetWriter((WMgr.CreateWriter("侯捷")->GetWriter()));
	book1.PrintInfo();
}