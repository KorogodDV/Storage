#include <iostream>
#include <cassert>

template <class T>
class Node
{
	public:
		T value;
		Node<T>* next = 0;
};

template <class T>
class List
{
private:
	Node<T>* head;

public:

	List<T>()
	{
		head = 0;
	}

	List<T>(const List<T>& sample)
	{
		head = sample.head;
	}

	~List<T>()
	{}

	int length()
	{
		int len = 0;
		Node<T>* pointer = head;
		while (pointer != 0)
		{
			pointer = pointer->next;
			len++;
		}
		return len;
	}

	void pushFront(T val)
	{
		Node<T>* p = new Node<T>();
		p->value = val;
		p->next = head;
		head = p;
	}

	T popFront()
	{
		assert(head);
		Node<T>* new_head = head->next;
		T value = head->value;
		delete head;
		head = new_head;
		return value;
	}

	void operator+=(List<T> l2)
	{
		if (head == 0)
		{
			head = l2.head;
		}
		else
		{
			Node<T>* pointer = head;
			while (pointer->next != 0)
			{
				pointer = pointer->next;
			}
			pointer->next = l2.head;
		}
	}

	T* get(int index)
	{
		assert(index >= 0 && index < this->length());
		int i = 0;
		Node<T>* pointer = head;
		while (i != index)
		{
			pointer = pointer->next;
			i++;
		}
		return &(pointer->value);
	}

	bool contains(T value)
	{
		bool res = false;
		Node<T>* pointer = head;
		while ((pointer != 0) && !res)
		{
			if (pointer->value == value)
			{
				res = true;
			}
			pointer = pointer->next;
		}
		return res;
	}

	int findByValue(T value)
	{
		bool res = false;
		int pos = 0;

		Node<T>* pointer = head;
		while (pointer != 0)
		{
			if (pointer->value == value)
			{
				res = true;
				break;
			}
			pos++;
			pointer = pointer->next;
		}

		if (res)
			return pos;
		else
			return -1;
	}

	void erase()
	{
		Node<T>* pointer = head;
		head = 0;
		while (pointer != 0)
		{
			Node<T>* new_pointer = pointer->next;
			delete[] pointer;
			pointer = new_pointer;
		}
	}

	void append(T value)
	{
		if (head == 0)
			this->pushFront(value);
		else
		{
			Node<T>* pointer = head;
			while (pointer->next != 0)
				pointer = pointer->next;
			pointer->next = new Node<T>();
			pointer->next->value = value;
		}
	}

	int removeByValue(T value)
	{
		assert(this->contains(value));
		if (head->value == value)
		{
			this->popFront();
			return 0;
		}
		else
		{
			int index = 1;
			Node<T>* pointer = head;
			while (pointer->next->value != value)
			{
				pointer = pointer->next;
				index++;
			}
			Node<T>* new_pointer = pointer->next->next;
			delete[] pointer->next;
			pointer->next = new_pointer;
			return index;
		}
	}

	void removeByIndex(int i)
	{
		assert(i >= 0 && i < this->length());
		if (i == 0)
			this->popFront();
		else
		{
			int len = 0;
			Node<T>* pointer = head;
			while (len != i - 1)
			{
				pointer = pointer->next;
				len++;
			}
			Node<T>* new_pointer = pointer->next->next;
			delete[] pointer->next;
			pointer->next = new_pointer;
		}
	}
};

template <class T>
class Storage
{
	private:

		List<T> items;
		List<std::string> items_names;

	public:

		Storage()
		{
			items = List<T>();
			items_names = List<T>();
		}

		~Storage()
		{
			items.erase();
			delete[] items.head;
			items_names.erase();
			delete[] items_names.head;
		}

		void CreateObject(std::string name, T obj)
		{
			assert(!items_names.contains(name));
			items.pushFront(obj);
			items_names.pushFront(name);
		}
		
		void RemoveObject(T obj)
		{
			items_names.removeByIndex(items.removeByValue(obj));
		}

		void RemoveObject(std::string name)
		{
			items.removeByIndex(items_names.removeByValue(name));
		}

		/*T* GetObject(std::string name)
		{
			assert(items_names.contains(name));
			int index = items_names.removeByValue(name);
			T obj = 
			
		}*/

};


int main()
{
	List<int> a1;
	List<int> a2;
	int b = 5;
	a1.pushFront(b);
	a2.pushFront(b*b);
	//std::cout << a1.length();
	a1 += a2;
	a1.append(36);
	//std::cout << *a1.get(2);
	std::cout << a1.findByValue(36);
	//std::cout << a1.removeByValue(36);
	//std::cout << a1.popFront();
	//std::cout << a1.popFront();
}