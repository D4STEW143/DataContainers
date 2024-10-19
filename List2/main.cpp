#include"List.h"
#include"List.cpp"

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	cout << "Push front" << endl;
	for (int i = 0; i < n;i++)
	{
		list.push_back(rand() % 100);
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
	cout << "Введите индекс куда вставить: "; cin >> insertIndex;
	cout << "Введите что вставить: "; cin >> insertData;
	try
	{
		list.insert(insertData, insertIndex);
		list.print();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
	cout << delimeter;
	cout << "Erase" << endl;
	int eraseIndex;
	cout << "Индекс элемента для удаления: "; cin >> eraseIndex;
	list.erase(eraseIndex);
	list.print();
	cout << delimeter;
	//list.reverse_print();  
#endif // BASE_CHECK

#ifdef ITERATORS_CHECK
	List list = { 3,5,8,13,21 };
	//list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	for (List::Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

	for (List::ReversIterator it = list.rbegin(); it != list.redn();it++)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // ITERATORS_CHECK
	//NRVO - Named Return Value Optimization
	List<int> list1 = { 3,5,8,13,21 };
	List<int> list2 = { 34,55,89 };
	List<int> list3 = list1 + list2;
	for (int i : list1) cout << i << tab; cout << endl;
	for (int i : list2) cout << i << tab; cout << endl;
	for (int i : list3) cout << i << tab; cout << endl;

	for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it)
	{
		*it *= 10;
	}
	for (int i : list1) cout << i << tab; cout << endl;

	List<double> d_list = { 2.7, 3.14, 5.1, 8.3 };
	for (double i : d_list) cout << i << tab; cout << endl;
	for (List<double>::ReversIterator it = d_list.rbegin(); it != d_list.rend(); ++it) cout << *it << tab; cout << endl;

	List<std::string> s_list = { "Ах","ты","ж","Ежтыкин","ты","20" };
	for (std::string i : s_list) cout << i << tab; cout << endl;
	for (List<std::string>::ReversIterator it = s_list.rbegin(); it != s_list.rend(); ++it) cout << *it << tab; cout << endl;

}