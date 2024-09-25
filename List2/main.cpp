#include<iostream>

using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimeter "\n---------------------------\n"

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
			cout << "EConstr:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestr:\t" << this << endl;
		}
		friend class List;
	}*Head, * Tail;	//Объявляем 2 указателя на объекты класса Element
	//непосредственно после описания класса
	size_t size;	//Количество элементов списка
public:
	List()
	{
		//Конструктор по умолчанию создает пустой список
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstr: \t" << this << endl;
	}
	~List()
	{
		cout << "LDestr: \t" << this << endl;
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
			Element* New = new Element(Data);

			//Присоединяем элемент к списку
			New->pNext = Head;

			//Присоединяем список к элементу
			Head->pPrev = New;

			//Смещаем голову на новый элемент
			Head = New;
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
		if (Index > size) return;
		if (Index == size) { push_back(Data); return; }
		if (Index == 0) { push_front(Data); return; }
		else
		{
			Element* Temp = Head;
			for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
			Temp->pNext = new Element(Data, Temp->pNext, Temp->pPrev);
			size++;
		}
	}

//Deleting elements
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr) return;
		else
		{
			Head = Head->pNext;
			Head->pPrev = nullptr;
		}
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr && Tail == nullptr) return;
		else
		{
			Tail = Tail->pPrev;
			Tail->pNext = nullptr;
		}
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

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	cout << "Push front" << endl;
	for (int i = 0; i < n;i++)
	{
		list.push_front(rand() % 100);
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
	cout << "Введите что вставить: "; cin >> insertData;
	cout << "Введите индекс куда вставить: "; cin >> insertIndex;
	list.insert(insertData, insertIndex);
	list.print();
	cout << delimeter;
	cout << "Erase" << endl;
	int eraseIndex;
	cout << "Индекс элемента для удаления: "; cin >> eraseIndex;
	list.erase(eraseIndex);
	list.print();
	cout << delimeter;
	//list.reverse_print();


}