#include<iostream>

using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimeter "\n---------------------------\n"
//#define BASE_CHECK
//#define ITERATORS_CHECK

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
	}*Head, * Tail;	//Объявляем 2 указателя на объекты класса Element
											//непосредственно после описания класса
	size_t size;							//Количество элементов списка

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
	class ConstIterator:public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp) :ConstBaseIterator(Temp) {}
		~ConstIterator() {}

		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};

	class ConstReversIterator:public ConstBaseIterator
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

	class ReversIterator: public ConstReversIterator
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


////////////////////////////////////////////////////////////////////////////
/////////////////////////////////Element////////////////////////////////////

/////////////////////////////////Element////////////////////////////////////
////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////
/////////////////////////////////Iterators//////////////////////////////////
///--------------------------ConstBaseIterator---------------------------///
template<typename T> bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T> bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}
template<typename T> T List<T>::ConstBaseIterator::operator*()const
{
	return Temp->Data;
}
///--------------------------ConstIterator-------------------------------///
template <typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
	this->Temp = this->Temp->pNext;
	return *this;
}
template <typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int)
{
	ConstIterator old = *this;
	this->Temp = this->Temp->pNext;
	return old;
}
template <typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
	this->Temp = this->Temp->pPrev;
	return *this;
}
template <typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = this->Temp;
	this->Temp = this->Temp->pPrev;
	return old;
}
///--------------------------ConstReversIterator--------------------------///
template<typename T>typename List<T>::ConstReversIterator& List<T>::ConstReversIterator::operator++()
{
	this->Temp = this->Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstReversIterator List<T>::ConstReversIterator::operator++(int)
{
	ConstReversIterator old = *this;
	this->Temp = this->Temp->pPrev;
	return old;
}
template<typename T>typename List<T>::ConstReversIterator& List<T>::ConstReversIterator::operator--()
{
	this->Temp = this->Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstReversIterator List<T>::ConstReversIterator::operator--(int)
{
	ConstReversIterator old = *this;
	this->Temp = this->Temp->pNext;
	return old;
}
///----------------------------------------------------------------------///
template<typename T> T& List<T>::Iterator::operator*()
{
	return this->Temp->Data;
}
template<typename T> T& List<T>::ReversIterator::operator*()
{
	return this->Temp->Data;
}
/////////////////////////////////Iterators//////////////////////////////////
////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////
/////////////////////////////////List members://////////////////////////////
template<typename T>typename List<T>::ConstIterator List<T>::end()const
{
	return nullptr;
}
template<typename T>typename List<T>::ConstIterator List<T>::begin()const
{
	return Head;
}
template<typename T>typename List<T>::ConstReversIterator List<T>::rbegin()const
{
	return Tail;
}
template<typename T>typename List<T>::ConstReversIterator List<T>::redn()const
{
	return nullptr;
}
template<typename T>typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T>typename List<T>::ReversIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T>typename List<T>::ReversIterator List<T>::rend()
{
	return nullptr;
}

template<typename T> List<T>::List()
{
	//Конструктор по умолчанию создает пустой список
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstr: \t" << this << endl;
}
template<typename T> List<T>::List(const std::initializer_list<T>& il) :List()
{
	for (T const* it = il.begin(); it != il.end(); it++) push_back(*it);
}
template<typename T> List<T>::List(const List<T>& other) : List() //без делегирования может падать 
{
	*this = other;
#ifdef DEBUG
	cout << "LCopyConstr: \t" << this << endl;
#endif // DEBUG

}
template<typename T> List<T>::List(List<T>&& other) :List()
{
	*this = std::move(other); //Явный вызов MoveAssigment
}
template<typename T> List<T>::~List()
{
	//while(Head) pop_front();
	while (Tail) pop_back();
	cout << "LDestr: \t" << this << endl;
}

//Operators
template <typename T>List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other) return *this;
	while (Head) pop_front();

	//Deepcopy
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
#ifdef DEBUG
	cout << "LCopyAssigment: \t" << this << endl;
#endif // DEBUG

	return *this;
}
template <typename T>List<T>& List<T>::operator=(List<T>&& other)
{
	if (this == &other)return *this;
	while (Head) pop_front();

	//Shallow copy
	this->Head = other.Head;
	this->Tail = other.Tail;
	this->size = other.size;

	//Обязательно нужно обнулить other
	other.Head = other.Tail = nullptr;
	other.size = 0;

#ifdef DEBUG
	cout << "LMoveAssigment: \t" << this << endl;
#endif // DEBUG

}
//Methods
//Adding elements
template <typename T> void List<T>::push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)
		Head = Tail = new Element(Data);
	else
	{
		//Создаем новый элемент
		//Element* New = new Element(Data);
		//Присоединяем элемент к списку
		//New->pNext = Head;
		//Присоединяем список к элементу
		//Head->pPrev = New;
		//Смещаем голову на новый элемент
		//Head = New;
		Head = Head->pPrev = new Element(Data, Head);
	}
	size++;
}
template <typename T> void List<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)
		Head = Tail = new Element(Data);
	else
	{
		Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;
	}
	size++;
}
template <typename T> void List<T>::insert(T Data, int Index)
{
	if (Index == 0) return push_front(Data);
	if (Index == size - 1) return push_back(Data);
	if (Index >= size) throw std::exception("insert: Out of range exeption");
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++) Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - Index - 1; i++) Temp = Temp->pPrev;
	}
	Temp->pNext->pPrev = Temp->pPrev->pNext = new Element(Data, Temp->pNext, Temp->pPrev);
	size++;
	/*if (Index > size) return;
	if (Index == size) { push_back(Data); return; }
	if (Index == 0) { push_front(Data); return; }
	else
	{
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		Temp->pNext = new Element(Data, Temp->pNext, Temp->pPrev);
		size++;
	}*/
}

//Deleting elements
template <typename T> void List<T>::pop_front()
{
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
		size = 0;
		return;
	}
	Head = Head->pNext;
	delete Head->pPrev;
	Head->pPrev = nullptr;
	size--;
}
template <typename T> void List<T>::pop_back()
{
	if (Head == Tail) return pop_front();
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}
template <typename T> void List<T>::erase(int Index)
{
	if (Index > size) return;
	if (Index == size) pop_back();
	if (Index == 0) pop_front();
	else
	{
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		Temp->pPrev->pPrev = Temp->pPrev;
		size--;
	}
}

//All
template <typename T> void List<T>::print()const
{
	cout << "Head: \t" << Head << endl;
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Tail: \t" << Tail << endl;

	cout << "Количество элементов списка: " << size << endl;
}
template <typename T> void List<T>::reverse_print()const
{
	cout << "Tail: \t" << Tail << endl;
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Head: \t" << Head << endl;
	cout << "Количество элементов списка: " << size << endl;
}
/////////////////////////////////List members://////////////////////////////
////////////////////////////////////////////////////////////////////////////


template<typename T>
List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> buffer;
	for (typename List<T>::ConstIterator it = left.begin(); it != left.end(); it++)buffer.push_back(*it);
	for (typename List<T>::ConstIterator it = right.begin(); it != right.end(); it++)
	{
		buffer.push_back(*it);
	}
	return buffer;
}

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	cout << "Push front" << endl;
	for (int i = 0; i < n;i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	cout << delimeter;
	cout << "Push back" << endl;
	list.push_back(rand() % 100);
	list.print();
	cout << delimeter;
	cout << "Pop front" << endl;
	list.pop_front();
	list.print();
	cout << delimeter;
	cout << "Pop back" << endl;
	list.pop_back();
	list.print();
	cout << delimeter;
	cout << "Insert" << endl;
	int insertIndex;
	int insertData;
	cout << "Введите индекс куда вставить: "; cin >> insertIndex;
	cout << "Введите что вставить: "; cin >> insertData;
	try
	{
		list.insert(insertData, insertIndex);
		list.print();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
	cout << delimeter;
	cout << "Erase" << endl;
	int eraseIndex;
	cout << "Индекс элемента для удаления: "; cin >> eraseIndex;
	list.erase(eraseIndex);
	list.print();
	cout << delimeter;
	//list.reverse_print();  
#endif // BASE_CHECK

#ifdef ITERATORS_CHECK
	List list = { 3,5,8,13,21 };
	//list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	for (List::Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

	for (List::ReversIterator it = list.rbegin(); it != list.redn();it++)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // ITERATORS_CHECK
	//NRVO - Named Return Value Optimization
	List<int> list1 = { 3,5,8,13,21 };
	List<int> list2 = { 34,55,89 };
	List<int> list3 = list1 + list2;
	for (int i : list1) cout << i << tab; cout << endl;
	for (int i : list2) cout << i << tab; cout << endl;
	for (int i : list3) cout << i << tab; cout << endl;

	for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it)
	{
		*it *= 10;
	}
	for (int i : list1) cout << i << tab; cout << endl;

	List<double> d_list = { 2.7, 3.14, 5.1, 8.3 };
	for (double i : d_list) cout << i << tab; cout << endl;
	for (List<double>::ReversIterator it = d_list.rbegin(); it != d_list.rend(); ++it) cout << *it << tab; cout << endl;

	List<std::string> s_list = { "Ах","ты","ж","Ежтыкин","ты","20" };
	for (std::string i : s_list) cout << i << tab; cout << endl;
	for (List<std::string>::ReversIterator it = s_list.rbegin(); it != s_list.rend(); ++it) cout << *it << tab; cout << endl;

}