#pragma once
#include <iostream>

template<typename t>
class List
{
private:
	struct Node
	{
		t element;
		Node* prev;
		Node* next;
	};

	Node* _head;
	Node* _tail;
	int _size;

	Node* getNode(int index)
	{
		Node* currentNode = _head;

		//if (currentNode == NULL) return NULL;

		/* while¹® ¹öÀü
		int count = 0;
		while(currentNode != NULL)
		{
			currentNode = currentNode->next;
			if(count++ >= index) break;
		}
		*/
		for (int i = 0; (i < index) && currentNode != NULL; i++)
		{
			currentNode = currentNode->next;
		}

		return currentNode;
	}

public:
	List()
	{
		/*_head = new List<t>::Node;
		_tail = new List<t>::Node;
		_head->next = _tail;
		_tail->prev = _head;*/
		_head = NULL;
		_tail = NULL;
		_size = 0;
	}
	~List()
	{

	}
	void pushBack(t element)
	{
		Node* newNode;
		Node* prevNode;
		if (_size == 0)
		{
			newNode = _head = _tail = new Node;
			newNode->next = NULL;
			newNode->prev = NULL;
			newNode->element = element;
		}
		else
		{
			prevNode = _tail;
			prevNode->next = newNode = new Node;

			_tail = newNode;
			
			newNode->next = NULL;
			newNode->prev = prevNode;
			newNode->element = element;
		}

		_size++;
	}

	t popBack()
	{
		Node* lastNode = _tail;
		
		if (lastNode == NULL) return NULL;

		Node* prevNode = lastNode->prev;
		t element = lastNode->element;
		
		_tail = prevNode;
		prevNode->next = NULL;

		delete lastNode;

		_size--;

		return element;
	}

	void pushFront(t element)
	{
		Node* newNode;
		Node* nextNode;
		if (_size == 0)
		{
			newNode = _head = _tail = new Node;
			newNode->next = NULL;
			newNode->prev = NULL;
			newNode->element = element;
		}
		else
		{
			nextNode = _head;
			nextNode->prev = newNode = new Node;

			_head = newNode;

			newNode->next = nextNode;
			newNode->prev = NULL;
			newNode->element = element;
		}

		_size++;
	}

	t popFront()
	{
		Node* firstNode = _head;
		Node* nextNode = firstNode->next;
		t element = firstNode->element;

		if (_head == NULL) return NULL;

		_head = nextNode;
		nextNode->prev = NULL;

		delete firstNode;

		_size--;

		return element;
	}

	void insert(int index, t element)
	{
		Node* newNode = new Node;
		Node* currentNode = getNode(index);

		if (currentNode == NULL)
		{
			pushBack(element);
			return;
		}

		Node* prevNode = currentNode->prev;
		//Node* nextNode = currentNode->next;

		if (prevNode == NULL)
		{
			pushFront(element);
			return;
		}

		prevNode->next = newNode;
		newNode->next = currentNode;

		currentNode->prev = newNode;
		newNode->prev = prevNode;

		newNode->element = element;

		_size++;
	}

	t erase(int index)
	{
		Node* indexNode = getNode(index);

		if (indexNode == NULL)
		{
			return NULL;
		}

		t element = indexNode->element;
		Node* prevNode = indexNode->prev;
		Node* nextNode = indexNode->next;

		if (prevNode == NULL) return popFront();
		if (nextNode == NULL) return popBack();

		prevNode->next = nextNode;
		nextNode->prev = prevNode;

		delete indexNode;

		_size--;

		return element;
	}

	void printAllElement()
	{
		if (_size < 1) return;

		Node* currentNode = _head;

		while (currentNode != NULL)
		{
			std::cout << currentNode->element << std::endl;
			currentNode = currentNode->next;
		}
	}

	void printReverseAllElement()
	{
		if (_size < 1) return;

		Node* currentNode = _tail;

		while (currentNode != NULL)
		{
			std::cout << currentNode->element << std::endl;
			currentNode = currentNode->prev;
		}
	}
};

