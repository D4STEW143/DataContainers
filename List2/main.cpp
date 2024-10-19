#include<iostream>

using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimeter "\n---------------------------\n"
//#define BASE_CHECK
//#define ITERATORS_CHECK

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstr: \t" << this << endl;
		}
		~Element()
		{
			cout << "EDestr: \t" << this << endl;
		}
		friend class List;
	}*Head, * Tail;	//Объявляем 2 указателя на объекты класса Element
											//непосредственно после описания класса
	size_t size;	//Количество элементов списка

	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp) :Temp(Temp) {}
		~ConstBaseIterator() {}
		bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		int operator*()const
		{
			return Temp->Data;
		}
	};
public:
	class ConstIterator:public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp) :ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "ITConstr: \t" << this << endl;
#endif // DEBUG

		}
		~ConstIterator()
		{
#ifdef DEBUG
			cout << "ITDestr: \t" << this << endl;
#endif // DEBUG

		}

		//pref++
		ConstIterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		//post++
		ConstIterator& operator++(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		//pref--
		ConstIterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		//post--
		ConstIterator& operator--(int)
		{
			ConstIterator old = Temp;
			Temp = Temp->pPrev;
			return old;
		}
	};
	ConstIterator begin()const
	{
		return Head;
	}
	ConstIterator end()const
	{
		return nullptr;
	}	

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
		ConstReversIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;	
		}
		ConstReversIterator& operator++(int)
		{
			ConstReversIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ConstReversIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstReversIterator& operator--(int)
		{
			ConstReversIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
	};
	ConstReversIterator rbegin()const
	{
		return Tail;
	}
	ConstReversIterator redn()const
	{
		return nullptr;
	}

	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp) : ConstIterator(Temp) {}
		~Iterator() {}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	Iterator end()
	{
		return nullptr;
	}
	Iterator begin()
	{
		return Head;
	}

	class ReversIterator: public ConstReversIterator
	{
	public:
		ReversIterator(Element* Temp) : ConstReversIterator(Temp) {}
		~ReversIterator() {}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	ReversIterator rbegin()
	{
		return Tail;
	}
	ReversIterator redn()
	{
		return nullptr;
	}

	List()
	{
		//Конструктор по умолчанию создает пустой список
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstr: \t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); it++) push_back(*it);
	}
	List(const List& other): List() //без делегирования может падать 
	{
		*this = other;
#ifdef DEBUG
		cout << "LCopyConstr: \t" << this << endl;
#endif // DEBUG

	}
	List(List&& other):List()
	{
		*this = std::move(other); //Явный вызов MoveAssigment
	}
	~List()
	{
		//while(Head) pop_front();
		while (Tail) pop_back();
		cout << "LDestr: \t" << this << endl;
	}

	//Operators
	List& operator=(const List& other)
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
	List& operator=(List&& other)
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
	void push_front(int Data)
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
	void push_back(int Data)
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
	void insert(int Data, int Index)
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
	void pop_front()
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
	void pop_back()
	{
		if (Head == Tail) return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	void erase(int Index)
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
	void print()const
	{
		cout << "Head: \t" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Tail: \t" << Tail << endl;

		cout << "Количество элементов списка: " << size << endl;
	}
	void reverse_print()const
	{
		cout << "Tail: \t" << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Head: \t" << Head << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
};

List operator+(const List& left, const List& right)
{
	List buffer;
	for (List::ConstIterator it = left.begin(); it != left.end(); it++)buffer.push_back(*it);
	for (List::ConstIterator it = right.begin(); it != right.end(); it++)
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
	List list1 = { 3,5,8,13,21 };
	List list2 = { 34,55,89 };
	List list3 = list1 + list2;
	for (int i : list1) cout << i << tab; cout << endl;
	for (int i : list2) cout << i << tab; cout << endl;
	for (int i : list3) cout << i << tab; cout << endl;

	for (List::Iterator it = list1.begin(); it != list1.end(); ++it)
	{
		*it *= 10;
	}
	for (int i : list1) cout << i << tab; cout << endl;

}