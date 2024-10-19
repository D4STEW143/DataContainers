#pragma once
#include<iostream>

using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimeter "\n---------------------------\n"
//#define BASE_CHECK
//#define ITERATORS_CHECK


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////ќб€ъ€вление класса (Class declaration)//////////////////////////////
template <typename T> class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev) {}
		~Element() {}
		friend class List;
	}*Head, * Tail;	//ќбъ€вл€ем 2 указател€ на объекты класса Element
	//непосредственно после описани€ класса
	size_t size;							// оличество элементов списка

	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp) :Temp(Temp) {}
		~ConstBaseIterator() {}
		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;
		T operator*()const;
	};
public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp) :ConstBaseIterator(Temp) {}
		~ConstIterator() {}

		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};

	class ConstReversIterator :public ConstBaseIterator
	{
	public:
		ConstReversIterator(Element* Temp) :ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "RITConstr: \t" << this << endl;
#endif // DEBUG

		}
		~ConstReversIterator()
		{
#ifdef DEBUG
			cout << "RITDestr: \t" << this << endl;
#endif // DEBUG

		}
		ConstReversIterator& operator++();
		ConstReversIterator operator++(int);
		ConstReversIterator& operator--();
		ConstReversIterator operator--(int);
	};

	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp) : ConstIterator(Temp) {}
		~Iterator() {}
		T& operator*();
	};

	class ReversIterator : public ConstReversIterator
	{
	public:
		ReversIterator(Element* Temp) : ConstReversIterator(Temp) {}
		~ReversIterator() {}
		T& operator*();
	};

	ConstIterator begin()const;
	ConstIterator end()const;
	ConstReversIterator rbegin()const;
	ConstReversIterator redn()const;
	Iterator end();
	Iterator begin();
	ReversIterator rbegin();
	ReversIterator rend();

	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	List(List<T>&& other);
	~List();

	//Operators
	List<T>& operator=(const List<T>& other);
	List<T>& operator=(List<T>&& other);
	//Methods
//Adding elements
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);

	//Deleting elements
	void pop_front();
	void pop_back();
	void erase(int Index);

	//All
	void print()const;
	void reverse_print()const;
};
//////////////////// онец об€ъ€вление класса (Class declaration end)/////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
