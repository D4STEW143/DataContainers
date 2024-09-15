//#define BASE_CHECK
#define HOMEWORK
using System;
using System.Collections.Generic;
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

#endif

#if HOMEWORK
			ForwardList list = new ForwardList() { 3, 5, 8, 13, 21 };
			foreach (int i in list)
			{
                Console.Write(i+"\t");
			}
            Console.WriteLine();
#endif

		}
	}
}
