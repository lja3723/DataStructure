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
		//prev가 nullptr이 아닌 경우
		if (prev != nullptr)
		{
			//prev->next가 존재하는 경우
			//prev->next의 prev를 연결 해제
			if (prev->next != nullptr)
				prev->next->prev = nullptr;

			//prev의 next를 this로 설정
			prev->next = this;
		}

		//this->prev가 연결된 경우
		//this->prev의 next를 연결 해제
		if (this->prev != nullptr)
			this->prev->next = nullptr;

		this->prev = prev;
	}
	void setNext(Node<Elem>* next)
	{
		//next가 nullptr이 아닌 경우
		if (next != nullptr) 
		{
			//next->prev가 존재하는 경우
			//next->prev의 next를 연결 해제
			if (next->prev != nullptr)
				next->prev->next = nullptr;

			//next의 prev를 this로 설정
			next->prev = this;
		}

		//this->next가 연결된 경우
		//this->next의 prev를 연결 해제
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

	//Node 출력
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

	void printIterNode()
	{
		std::cout << *iter << std::endl;
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
