//#define BASE_CHECK
#define HOMEWORK
using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace ForwardList
{
	internal class Program
	{
		static void Main(string[] args)
		{
			Random rand = new Random(0);
#if BASE_CHECK
			Console.Write("Введите размер списка: ");
			int n = Convert.ToInt32(Console.ReadLine());
			ForwardList list = new ForwardList();
			for (int i = 0; i < n; i++)
			{
				list.push_back(rand.Next(100));
			}
			list.Print();
			//list.pop_front();
			//list.pop_back();
			//list.Print();
			//list.Clear();
			//list.Print();	
			Console.Write("Введите индекс добовляемого элемента: ");
			int index = Convert.ToInt32(Console.ReadLine());
			Console.Write("Введите значение добовляемого элемента: ");
			int value = Convert.ToInt32(Console.ReadLine());

			list.insert(value, index);
			list.Print();

			Console.Write("Введите индекс удаляемого элемента: ");
			int index1 = Convert.ToInt32(Console.ReadLine());
			list.erase(index1);
			list.Print();
#endif

#if HOMEWORK
			ForwardList<int> list = new ForwardList<int>() { 3, 5, 8, 13, 21 };
			list.Print();
			foreach (int i in list)Console.Write($"{i}\t");
			Console.WriteLine();
			ForwardList<double> d_list = new ForwardList<double>() { 2.7, 3.14, 5.2, 8.3 };
			foreach (double i in d_list) Console.Write($"{i}\t"); Console.WriteLine();
			ForwardList<string> s_list = new ForwardList<string>() { "a", "b", "c", "d", "e" };
			foreach (string i in s_list) Console.Write($"{i}\t"); Console.WriteLine();
#endif

		}
	}
}
