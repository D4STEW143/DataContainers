using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ForwardList
{
	internal class Element
	{
		public int Data { get; set; }		//Значение элемента
		public Element pNext { get; set; }	//Следующий элемент

		public Element (int Data, Element pNext = null)
		{
			this.Data = Data;
			this.pNext = pNext;
            Console.WriteLine($"EConstr: \t {GetHashCode()}");
		}

		~Element()
		{
            Console.WriteLine($"EDestr: \t {GetHashCode()}");
		}
	}
}
