/**************************************************************************
 * @ ��Ԫģʽ
 * @ brief
     1������֧�ִ���ϸ���ȵĶ���
	 2����������У���ʱ��Ҫ���ɴ���ϸ���ȵ���ʵ��(����)����ʾ����
		����Щ�������������ⶼ��ͬ���Ϳ��԰���Щ��������Ƶ���ʵ�������棬��������ʱ�Ŵ�����
	 3����Flyweightִ��ʱ������������ڲ���Ҳ���ⲿ��
	    �ڲ����ݴ洢��Flyweight������
		�ⲿ�����ɿͻ����Լ�����������Ӧ����ʱ�Ŵ���
 * @ author zhoumf
 * @ date 2014-11-16
 ************************************************************************/
#pragma once


/************************************************************************/
class cBook{ // ����ϸ���ȶ������
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
	string m_strPublisher; // ������
	string m_strWriter;	   // ����
	string m_strName;	   // ����
	int    m_nPrice;	   // �۸�
};

class cPublisherFlyweight{ // ������ ������
public:
	cPublisherFlyweight(string strPublisher) { m_strPublisher = strPublisher; }
	string GetPublisher() { return m_strPublisher; }
private:
	string m_strPublisher;
};
class cPublisherMgr{ // �������
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

class cWriterFlyweight{ // ���� ������
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
// ʾ��
void test_Flyweight(){
	cout << "������������������������������Ԫģʽ����������������������������" << endl;
	cPublisherMgr PMgr;
	cWriterMgr    WMgr;
	cBook book1, book2;

	book1.SetPrice(50);
	book1.SetName("������ǳ��MFC��");
	book1.SetPublisher((PMgr.CreatePublisher("���ӹ�ҵ������")->GetPublisher()));
	book1.SetWriter((WMgr.CreateWriter("���")->GetWriter()));
	book1.PrintInfo();
	cout << endl;

	book1.SetPrice(50);
	book1.SetName("��STLԴ��������");
	book1.SetPublisher((PMgr.CreatePublisher("���ӹ�ҵ������")->GetPublisher()));
	book1.SetWriter((WMgr.CreateWriter("���")->GetWriter()));
	book1.PrintInfo();
}