#ifndef __LIST_H__
#define __LIST_H__
#include <cstring>
#include <iostream>

template <typename Elem>
class Node
{
private:
	Elem data;
	Node<Elem>* prev;
	Node<Elem>* next;

public:
	Node(Elem data, Node<Elem>* prev = nullptr, Node<Elem>* next = nullptr)
	{
		this->data = data;
		this->prev = prev;
		this->next = next;
	}
	Node() : Node(data) { memset(&data, 0, sizeof(Elem)); }
	void setData(Elem data) 
	{ 
		this->data = data; 
	}
	void setPrev(Node<Elem>* prev)
	{
		//prev�� nullptr�� �ƴ� ���
		if (prev != nullptr)
		{
			//prev->next�� �����ϴ� ���
			//prev->next�� prev�� ���� ����
			if (prev->next != nullptr)
				prev->next->prev = nullptr;

			//prev�� next�� this�� ����
			prev->next = this;
		}

		//this->prev�� ����� ���
		//this->prev�� next�� ���� ����
		if (this->prev != nullptr)
			this->prev->next = nullptr;

		this->prev = prev;
	}
	void setNext(Node<Elem>* next)
	{
		//next�� nullptr�� �ƴ� ���
		if (next != nullptr) 
		{
			//next->prev�� �����ϴ� ���
			//next->prev�� next�� ���� ����
			if (next->prev != nullptr)
				next->prev->next = nullptr;

			//next�� prev�� this�� ����
			next->prev = this;
		}

		//this->next�� ����� ���
		//this->next�� prev�� ���� ����
		if (this->next != nullptr)
			this->next->prev = nullptr;

		this->next = next;
	}

	Elem getData() { return data; }
	Node<Elem>* getPrev() { return prev; }
	Node<Elem>* getNext() { return next; }

	static Node<Elem>* newInstance(Elem data, Node<Elem>* prev = nullptr, Node<Elem>* next = nullptr)
	{
		return new Node<Elem>(data, prev, next);
	}
	static Node<Elem>* newInstance() { return new Node<Elem>; }
	static void destroyInstance(Node<Elem>* node)
	{
		if (node != nullptr)
			delete node;
	}

	//Node ���
	friend std::ostream& operator<<(std::ostream& os, Node<Elem>& node)
	{
		using std::cout;
		using std::endl;

		cout << "[NodeInfo]" << endl;

		cout << "prevData-> ";
		if (node.getPrev() == nullptr)
			cout << "(nullptr)";
		else
			cout << node.getPrev()->getData();
		cout << endl;

		cout << "thisData:  " << node.getData() << endl;

		cout << "nextData-> ";
		if (node.getNext() == nullptr)
			cout << "(nullptr)";
		else
			cout << node.getNext()->getData();
		cout << endl;

		return os;
	}
};

template <typename Elem>
class List
{
private:
	Node<Elem>* head;
	Node<Elem>* tail;
	Node<Elem>* iter;
	unsigned int m_size;
	bool (*comp)(const Elem& d1, const Elem& d2); //���� ����
	bool isRecentAccessNextDirect;

public:
	List(bool (*sortRule)(const Elem& d1, const Elem& d2) = nullptr)
	{
		//head�� tail�� ���� ������ ���� ��带 ����Ų��
		head = Node<Elem>::newInstance();
		tail = Node<Elem>::newInstance(); 
		iter = head;

		head->setNext(tail);
		m_size = 0;
		comp = sortRule;
		isRecentAccessNextDirect = true;
	}
	~List()
	{
		//������ ��� ����
		setIterFirst();
		while (isNextDataExist()) {
			getNextData();
			removeAccessedData();
		}

		//���̳�� ����
		Node<Elem>::destroyInstance(head);
		Node<Elem>::destroyInstance(tail);
	}

	void printIterNode()
	{
		std::cout << *iter << std::endl;
	}

	unsigned int size() { return m_size; }
	bool isEmpty() { return m_size == 0; }

	//data �߰�
	List<Elem>& insert(Elem data)
	{
		//���� ���� ���� ��� �ڿ� ������ �߰�
		if (comp == nullptr)
			return addLast(data);
		else
		{
			setIterFirst();
			while (isNextDataExist())
			{
				if (comp(data, getNextData()) )
			}
			// temp
			addLast(data);
			return *this;
		}
	}
	List<Elem>& addLast(Elem data)
	{
		//���ı��� ���õ� ��� ���� ����
		if (comp != nullptr)
			return insert(data);

		Node<Elem>* newNode = Node<Elem>::newInstance(data);
		newNode->setPrev(tail->getPrev());
		newNode->setNext(tail);
		m_size++;
		return *this;
	}
	List<Elem>& addFirst(Elem data)
	{
		//���ı��� ���õ� ��� ���� ����
		if (comp != nullptr)
			return insert(data);

		Node<Elem>* newNode = Node<Elem>::newInstance(data);
		newNode->setNext(head->getNext());
		newNode->setPrev(head);
		m_size++;
		return *this;
	}
	Elem getAccessedData()
	{
		return iter->getData();
	}
	Elem removeAccessedData()
	{
		//accessedData�� ���� ���
		if (iter == head || iter == tail) 
			return iter->getData();

		//delTarget ����
		Node<Elem>* delTarget = iter;
		Elem removedData = iter->getData();
		
		//�ֱ� ������ �������� ���� ������ ���
		if (isRecentAccessNextDirect)
		{ 
			//iter�� ��ĭ �������� �ű�� iter�� next�� delTarget�� next�� ����
			iter = iter->getPrev();
			iter->setNext(delTarget->getNext()); 
			//���� delTarget�� prev�� next�� ��� nullptr�� ��
		}
		else //���� ������ ���
		{
			//iter�� ��ĭ ���ķ� �ű�� iter�� prev�� delTarget�� prev�� ����
			iter = iter->getNext();
			iter->setPrev(delTarget->getPrev());
			//���� delTarget�� prev�� next�� ��� nullptr�� ��
		}
		Node<Elem>::destroyInstance(delTarget);
		m_size--;

		return removedData;
	}

	void setIterFirst()		{ iter = head; }
	void setIterLast()		{ iter = tail; }
	bool isNextDataExist() { return iter->getNext() != tail && iter != tail; }
	bool isPrevDataExist() { return iter->getPrev() != head && iter != head; }
	Elem getNextData()		
	{
		isRecentAccessNextDirect = true;
		if (iter != tail)
			iter = iter->getNext();

		return iter->getData(); 
	}
	Elem getPrevData()		
	{
		isRecentAccessNextDirect = false;
		if (iter != head)
			iter = iter->getPrev();

		return iter->getData();
	}
};

#endif
