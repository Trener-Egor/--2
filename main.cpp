#include <iostream>

#include "bstree.hpp"

int main()

{
	BSTree btree_1;
	size_t n;

	std::cout << "Enter the num of vertices: ";
	std::cin >> n;
	std::cout << "Enter keys:\n";

	for (size_t i = 0;i < n; ++i)
	{
		int key;
		std::cin >> key;
	    std::cout << "Key " << key;
		bool isInserted = btree_1.add_element(key);
		
		if (isInserted) {
		  std::cout << " inserted\n";
		} 
		else {
			std::cout << " not inserted\n";
		}
	}	
	std::cout << "\nPrint tree:\n";
	btree_1.print();
	std::cout << "\nEnter the search num: ";
	std::cin >> n;

	if (btree_1.find_element(n))
	{
		std::cout << "found\n";
	}
	else
	{
		std::cout << "not found\n";
	}
	std::cout << "\nEnter the deletet num: ";
	std::cin >> n;

	if (btree_1.delete_element(n))
	{
		std::cout << "deleted\n";
	}
	else
	{
		std::cout << "not deleted\n";
	}
	std::cout << "\nPrint tree:\n";
	btree_1.print();
	btree_1.save_to_file("btree_1.txt");

	std::cout << "\ncreate new tree\n";
	BSTree	btree_2;
	btree_2.load_from_file("btree_1.txt");
	std::cout << "print tree:\n";
	btree_1.print();
	
	std::cout << "\nCreate new tree using initializer list\n";
	BSTree btree_3{-3, 16, 49, 92, 51, 4, 3, -18};
	std::cout << "\nCrint tree:\n";
	btree_3.print();
}
