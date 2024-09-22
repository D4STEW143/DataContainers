using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace ForwardList
{
	internal class ForwardList: IEnumerable
	{
		Element Head;
		public uint Size { get; private set; }
		public IEnumerator GetEnumerator() => new Enumerator(Head);
		public void Add(int Data) => push_back(Data);
		public ForwardList()
		{
			Head = null;
			Size = 0;
			Console.WriteLine($"LConstr: \t {GetHashCode()}");
		}
		public ForwardList(int[] values)
		{
			if (values.Length == 0)
				throw new ArgumentException("Массив не должен быть пустым.");

			Head = new Element(values[0]);
			Element current = Head;

			for (int i = 1; i < values.Length; i++)
			{
				current.pNext = new Element(values[i]);
				current = current.pNext;
			}
		}
		~ForwardList()
		{
			Console.WriteLine($"LDestr: \t {GetHashCode()}");
		}
		public void Clear()
		{
			while (Head != null) pop_back();
			Head = null;
		}

		//Adding elements:
		public void push_front(int Data)
		{
			/*//1) Создаем новый элемент
			Element New = new Element(Data);

			//2) Подключаем новый элемент к списку
			//New.pNext = Head;

			//3) Смещаем голову на новый элемент
			Head = New;*/

			Head = new Element(Data, Head);// { pNext = Head } - Не понимаю почему такой вариант тоже работает. Это автосвойство?

			Size++;
		}
		public void push_back(int Data)
		{
			if (Head == null) push_front(Data);
			else
			{
				Element Temp = Head;
				while (Temp.pNext != null) Temp = Temp.pNext;
				Temp.pNext = new Element(Data);
			}
			Size++;
		}

		public void insert(int Data, int Index)
		{
			if (Index > Size) return;
			if (Index == 0) push_front(Data);
			else
			{
				//Доходим до нужного элемента
				Element Temp = Head;
				for (int i = 0; i < Index - 1; i++) Temp = Temp.pNext;
				//if (Temp.pNext == null) break;
				//else Temp = Temp.pNext;
				//Создаем новый элемент и
				//Включаем элемент в список
				//New.pNext = Temp.pNext;
				Temp.pNext = new Element(Data, Temp);

				Size++;
			}
		}

		//Removing elements
		public void pop_front()
		{
			Head = Head.pNext;
			/*
			C++
			Element erase = Head; Сохраняем адрес удаляемого элемента
			Head = Head.pNext; Исключаем элемент из списка
			*/
			Size--;
		}
		public void pop_back()
		{
			if (Head == null) return;
			if (Head.pNext == null) pop_front();
			else
			{
				Element Temp = Head;
				while (Temp.pNext.pNext != null) Temp = Temp.pNext;
				Temp.pNext = null;
			}
			Size--;
		}
		public void erase(int Index)
		{
			if (Index > Size) return;
			if (Index == 0) pop_front();
			else
			{
				Element Temp = Head;
				for (int i = 0; i < Index - 1; i++) Temp = Temp.pNext;
				Temp.pNext = Temp.pNext.pNext;
			}
			Size--;
		}

		//Methods
		public void Print()
		{
			Element Temp = Head;    //Temp - итератор
									//Итератор это указатель, при помощи которого можно получить доступ к элементам структуры данных.
			while (Temp != null)
			{
				Console.Write($"{Temp.Data}\t");
				Temp = Temp.pNext;  //Переход на следующий элемент
			}
			Console.WriteLine();
		}
	}
}
