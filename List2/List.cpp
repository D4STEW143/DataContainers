#include"List.h"
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////Определение класса (Class defenition)///////////////////////////////


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

////////////////////Конец определения класса (Class defenition end)//////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////