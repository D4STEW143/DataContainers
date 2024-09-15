using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ForwardList
{
	internal class ForwardList
	{
		Element Head;
		public ForwardList()
		{
			Head = null;
            Console.WriteLine($"LConstr:\t{GetHashCode()}");
		}
		~ForwardList()
		{
            Console.WriteLine($"LDestr:\t{GetHashCode()}");
		}
	}
}
