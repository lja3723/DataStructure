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
	Node() :Node(data) 
	{
		memset(&data, 0, sizeof(Elem)); 
	}
	Node(Elem data, Node<Elem>* prev = nullptr, Node<Elem>* next = nullptr) 
	{
		this->data = data;
		this->prev = prev;
		this->next = next;
	}

	Node<Elem>& setData(Elem data) 
	{ 
		this->data = data; 
		return *this;
	}
	Elem getData() { return data; }
	Node<Elem>& setPrev(Node<Elem>*)
	{
		this->prev = prev;
		return *this;
	}

	Node<Elem>& setNext(Node<Elem>*)
	{
		this->next = next;
		return *this;
	}

	Node<Elem>* getPrev()
	{
		return prev;
	}

	Node<Elem>* getNext()
	{
		return next;
	}

	static Node<Elem>* newInstance()
	{
		return new Node<Elem>;
	}

	static Node<Elem>* newInstance(Elem data, Node<Elem>* prev = nullptr, Node<Elem>* next = nullptr)
	{
		return new Node<Elem>(data, prev, next);
	}

	static void destroyInstance(Node<Elem>* node)
	{
		if (node != nullptr)
			delete node;
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

	unsigned int size() { return m_size; }
	bool isEmpty() { return m_size == 0; }

	//data �߰�
	List<Elem>& add_last(Elem data)
	{
		tail->setNext(Node<Elem>::newInstance(data, tail));
		tail = tail->getNext();
		m_size++;
		return *this;
	}
	//data �߰�
	List<Elem>& add_first(Elem data)
	{
		head->setNext(Node<Elem>::newInstance(data, head, head->getNext()));
		head->getNext()->getNext()->setPrev(head->getNext());
		m_size++;
		return *this;
	}
	void delete_prevAccessedData()
	{
		Node<Elem>* delTarget = iter;
		if (delTarget == tail)
			tail = tail->getPrev();
		iter = iter->getPrev();
		delTarget->getPrev()->setNext(delTarget->getNext());
		delTarget->getNext()->setPrev(delTarget->getPrev());
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
