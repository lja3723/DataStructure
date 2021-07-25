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
	bool (*comp)(const Elem& d1, const Elem& d2); //삽입 기준
	bool isRecentAccessNextDirect;

public:
	List(bool (*sortRule)(const Elem& d1, const Elem& d2) = nullptr)
	{
		//head와 tail이 각각 독립된 더미 노드를 가리킨다
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
		//데이터 노드 제거
		setIterFirst();
		while (isNextDataExist()) {
			getNextData();
			removeAccessedData();
		}

		//더미노드 제거
		Node<Elem>::destroyInstance(head);
		Node<Elem>::destroyInstance(tail);
	}

	void printIterNode()
	{
		std::cout << *iter << std::endl;
	}

	unsigned int size() { return m_size; }
	bool isEmpty() { return m_size == 0; }

	//data 추가
	List<Elem>& insert(Elem data)
	{
		//정렬 기준 없는 경우 뒤에 데이터 추가
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
		//정렬기준 마련된 경우 삽입 수행
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
		//정렬기준 마련된 경우 삽입 수행
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
		//accessedData가 없는 경우
		if (iter == head || iter == tail) 
			return iter->getData();

		//delTarget 설정
		Node<Elem>* delTarget = iter;
		Elem removedData = iter->getData();
		
		//최근 데이터 엑세스가 다음 방향인 경우
		if (isRecentAccessNextDirect)
		{ 
			//iter를 한칸 이전으로 옮기고 iter의 next를 delTarget의 next로 설정
			iter = iter->getPrev();
			iter->setNext(delTarget->getNext()); 
			//이후 delTarget의 prev와 next는 모두 nullptr이 됨
		}
		else //이전 방향인 경우
		{
			//iter를 한칸 이후로 옮기고 iter의 prev를 delTarget의 prev로 설정
			iter = iter->getNext();
			iter->setPrev(delTarget->getPrev());
			//이후 delTarget의 prev와 next는 모두 nullptr이 됨
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
