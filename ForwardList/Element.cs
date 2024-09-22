using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Remoting.Messaging;

namespace ForwardList
{
	internal class Element<T>
	{
		public T Data { get; set; }		//Значение элемента
		public Element<T> pNext { get; set; }  //Следующий элемент

		public Element (T Data, Element<T> pNext = null)
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
