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
public:
	List()
	{
		//head�� tail�� ���� ��带 ����Ű���� ����
		head = tail = iter = Node<Elem>::newInstance();

		m_size = 0;
	}
	~List()
	{
		//���̳�带 ���� ������ ��� ����
		while (head != tail)
		{
			Node<Elem>* delTarget = tail;
			//tail�� ��ĭ �������� �ű�鼭 tail�� next ���� ����
			tail = tail->getPrev();
			tail->setNext(nullptr);
			//������ tail�� ����Ų ��� ����
			Node<Elem>::destroyInstance(delTarget);
		} 
		//���̳�� ����
		Node<Elem>::destroyInstance(head);
	}

	void printIterNode()
	{
		std::cout << *iter << std::endl;
	}

	unsigned int size() { return m_size; }
	bool isEmpty() { return m_size == 0; }

	//data �߰�
	List<Elem>& add_last(Elem data)
	{
		Node<Elem>* newNode = Node<Elem>::newInstance(data);
		tail->setNext(newNode);
		tail = tail->getNext();
		m_size++;
		return *this;
	}
	//data �߰�
	List<Elem>& add_first(Elem data)
	{
		Node<Elem>* newNode = Node<Elem>::newInstance(data);
		newNode->setNext(head->getNext());
		newNode->setPrev(head);
		m_size++;
		return *this;
	}
	Elem peek_prevAccessedData()
	{
		return iter->getData();
	}
	void delete_prevAccessedData()
	{
		if (iter == head) return;
		Node<Elem>* delTarget = iter;
		if (delTarget == tail)
			tail = tail->getPrev();
		iter = iter->getPrev();
		iter->setNext(delTarget->getNext());
		Node<Elem>::destroyInstance(delTarget);
		m_size--;
	}

	void iterReset() { iter = head; }
	bool isNextDataExist() { return iter->getNext() != nullptr; }
	bool isPrevDataExist() { return iter->getPrev() != nullptr && iter->getPrev() != head; }
	Elem getNextData() 
	{
		iter = iter->getNext();
		return iter->getData();
	}
	Elem getPrevData()
	{
		iter = iter->getPrev();
		return iter->getData();
	}
};

#endif
