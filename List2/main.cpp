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
	for (int i = 0; i < n;i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	list.reverse_print();


}