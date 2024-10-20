#include<iostream>
#include<ctime>

using namespace std;
using std::cin;
using std::cout;
using std::endl;

//#define DEBUG

#define tab '\t'
#define delimiter "\n------------------------------------------------\n"

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "Econstr: \t" << this << endl;
#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "Edestr: \t" << this << endl;
#endif // DEBUG
		}
		bool isLeaf()const
		{
			return pLeft == pRight;
		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;
private:
	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr) return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr) Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr) Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->isLeaf())
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (count(Root->pLeft) > count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}
	int minValue(Element* Root)const
	{
		if (Root == nullptr)throw exception("Error in minValue: Tree is empty");
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		if (Root == nullptr)throw std::exception("Error in maxValue: Tree is empty");
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int count(Element* Root)const
	{
		return !Root ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
	}
	int sum(Element* Root)const
	{
		return !Root ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}
	void print(Element* Root)const
		{
			if (Root == nullptr) return;
			print(Root->pLeft);
			cout << Root->Data << tab;
			print(Root->pRight);
		}
	int depth(Element* Root)const
	{
		if (Root == nullptr) return 0;
		int lDepth = depth(Root->pLeft);
		int rDepth = depth(Root->pRight);
		return std::max(lDepth, rDepth) + 1;

	}
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree()
	{
		Root = nullptr;
#ifdef DEBUG
		cout << "Tconstr: \t" << this << endl;
#endif // DEBUG
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
			insert(*it, Root);
	}
	~Tree()
	{
		clear();
#ifdef DEBUG
		cout << "Tdestr: \t" << this << endl;
#endif // DEBUG
	}
	
	void clear()
	{
		clear(Root);
		Root = nullptr;
	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int count()const
	{
		return count(Root);
	}
	int sum()const
	{
		return sum(Root);
	}
	double avg()const
	{
		return (double)sum(Root) / count(Root);
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}
	int depth()const
	{
		return depth(Root);
	}
	void printAsTree(Element* Root, int level)
	{
		if (Root)
		{
			printAsTree(Root->pLeft, level + 1);
			for (int i = 0;i < level;i++) cout << "   ";
			cout << Root->Data << endl;
			printAsTree(Root->pRight, level + 1);
		}
	}
};

class UniqueTree :public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

#define BASE_CHECK
#define EFFICIENCY
//#define UNIQUE_TREE
//#define PERFECT_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	try
	{
		int n;
		cout << "Введите количество элементов: "; cin >> n;
		Tree tree;
		for (int i = 0; i < n; i++)
		{
			tree.insert(rand() % 100);
		}
		//tree.print();
		cout << "Минимальное значение: " << tree.minValue() << endl;
		cout << "Максимально значение дерева:" << tree.maxValue() << endl;
		cout << "Количество элементов дерева:   " << tree.count() << endl;
		cout << "Сумма элементов дерева: " << tree.sum() << endl;
		cout << "Среднеарифметическое дерева: " << tree.avg() << endl;
		cout << "Глубина дерева: " << tree.depth() << endl;
		int value;
		cout << "Введите значение элемента для удаления: (Используй 24) "; cin >> value;
		clock_t start6 = clock();
		tree.erase(value);
		clock_t end6 = clock();
		//tree.print();
		cout << "Количество элементов массива:   " << tree.count() << endl;
		tree.printAsTree(tree.getRoot(), 0);
		cout << delimiter << endl;

#ifdef EFFICIENCY
		clock_t start = clock();
		tree.minValue();
		clock_t end = clock();
		cout << "Минимальное значение найдено за " << double(end - start) << " тиков. (~" << double(end - start) / CLOCKS_PER_SEC << " секунд). \n";
		clock_t start1 = clock();
		tree.maxValue();
		clock_t end1 = clock();
		cout << "Максимальное значение найдено за " << double(end1 - start1) << " тиков. (~" << double(end1 - start1) / CLOCKS_PER_SEC << " секунд). \n";
		clock_t start2 = clock();
		tree.count();
		clock_t end2 = clock();
		cout << "Количество элементов найдено за " << double(end2 - start2) << " тиков. (~" << double(end2 - start2) / CLOCKS_PER_SEC << " секунд). \n";
		clock_t start3 = clock();
		tree.sum();
		clock_t end3 = clock();
		cout << "Сумма элементов найдено за " << double(end3 - start3) << " тиков. (~" << double(end3 - start3) / CLOCKS_PER_SEC << " секунд). \n";
		clock_t start4 = clock();
		tree.avg();
		clock_t end4 = clock();
		cout << "Средне-арфиметическое элементов найдено за " << double(end4 - start4) << " тиков. (~" << double(end4 - start4) / CLOCKS_PER_SEC << " секунд). \n";
		clock_t start5 = clock();
		tree.depth();
		clock_t end5 = clock();
		cout << "Глубина дерева найдена за " << double(end5 - start5) << " тиков. (~" << double(end5 - start5) / CLOCKS_PER_SEC << " секунд). \n";

		cout << "Удаление выполнено за " << double(end6 - start6) << " тиков. (~" << double(end6 - start6) / CLOCKS_PER_SEC << " секунд). \n";

		cout << delimiter << endl;
#endif // EFFICIENCY


#ifdef UNIQUE_TREE
		UniqueTree u_tree;
		for (int i = 0; i < n; i++)
		{
			u_tree.insert(rand() % 100);
		}
		u_tree.print();
		cout << "Минимальное значение: " << u_tree.minValue() << endl;
		cout << "Максимальное значение: " << u_tree.maxValue() << endl;
		cout << "Количество элементов: " << u_tree.count() << endl;
		cout << "Сумма всех элементов: " << u_tree.sum() << endl;
		cout << "Средне-арифметическое всех элементов: " << u_tree.avg() << endl;
#endif // UNIQUE_TREE

	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
#endif // BASE_CHECK

#ifdef PERFECT_CHECK
	Tree tree =
	{
						50,

			25,						75,

		16,		32,				64,		85
	};
	tree.print();

	int value;
	cout << "Введите значение элемента для удаления: "; cin >> value;
	tree.erase(value);
	tree.print();
#endif // PERFECT_CHECK
}