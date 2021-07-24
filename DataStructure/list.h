#ifndef __LIST_H__
#define __LIST_H__
#include <cstring>
#include <iostream>

using std::cout;
using std::endl;

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
	Node<Elem>& setData(Elem data) 
	{ 
		this->data = data; 
		return *this;
	}
	Node<Elem>& setPrev(Node<Elem>* prev)
	{
		if (prev != nullptr)
		{
			this->prev = prev;
			prev->next = this;
		}
		else if (this->prev != nullptr)
		{
			this->prev->next = nullptr;
			this->prev = nullptr;
		}
		return *this;
	}
	Node<Elem>& setNext(Node<Elem>* next)
	{
		if (next != nullptr)
		{
			this->next = next;
			next->prev = this;
		}
		else if (this->next != nullptr)
		{
			this->next->prev = nullptr;
			this->next = nullptr;
		}
		return *this;
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

	friend std::ostream& operator<<(std::ostream& os, Node<Elem>& node)
	{
		cout << "[NodeInfo]" << endl;
		cout << "data: " << node.getData() << endl;
		cout << "prev: ";
		if (node.getPrev() == nullptr)
			cout << "nullptr" << endl;
		else
			cout << node.getPrev()->getData() << endl;
		cout << "next: ";
		if (node.getNext() == nullptr)
			cout << "nullptr" << endl;
		else
			cout << node.getNext()->getData() << endl;
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
		//head와 tail이 더미 노드를 가리키도록 설정
		head = tail = iter = Node<Elem>::newInstance();

		m_size = 0;
	}
	~List()
	{
		//더미노드를 만날 때까지 노드 제거
		while (head != tail)
		{
			Node<Elem>* delTarget = tail;
			//tail을 한칸 이전으로 옮기면서 tail의 next 연결 해제
			tail = tail->getPrev();
			tail->setNext(nullptr);
			//이전에 tail이 가리킨 노드 삭제
			Node<Elem>::destroyInstance(delTarget);
		} 
		//더미노드 제거
		Node<Elem>::destroyInstance(head);
	}

	unsigned int size() { return m_size; }
	bool isEmpty() { return m_size == 0; }

	//data 추가
	List<Elem>& add_last(Elem data)
	{
		Node<Elem>* newNode = Node<Elem>::newInstance(data);
		tail->setNext(newNode);
		tail = tail->getNext();
		m_size++;
		return *this;
	}
	//data 추가
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
	Elem getNextData() 
	{
		iter = iter->getNext();
		return iter->getData();
	}
};

#endif
