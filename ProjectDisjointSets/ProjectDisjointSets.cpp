#include <iostream>
#include <vector>

#include "DisjointSetBase.h"
#include "Implementations/DisjointSetMap.h"
#include "Implementations/DisjointSetList.h"
#include "Implementations/DisjointSetTrees.h"

template<typename T, typename EL_TYPE>
void PrintSet(DisjointSetBase<T, EL_TYPE>& set, std::vector<EL_TYPE> universe)
{
	for (auto i : universe)
	{
		std::cout << i << " " << set.GetElement(set.Find(i)) << std::endl;
	}
}

int main()
{
	std::cout << "Map:\n";
	{
		auto set = MapImplementation::DisjointSetMap<int>();

		set.MakeSet(1);
		set.MakeSet(2);
		set.MakeSet(3);
		set.MakeSet(4);
		set.Union(1, 2);
		set.Union(3, 4);
		set.MakeSet(5);
		set.Union(4, 5);
		set.MakeSet(6);
		set.MakeSet(7);

		PrintSet(set, { 1,2,3,4,5,6,7 });
	}
	std::cout << "List:\n";
	{
		auto list_set = ListImplementation::DisjointSetList<int>();
		auto first = list_set.MakeSet(1);
		auto second = list_set.MakeSet(2);
		auto third = list_set.MakeSet(3);
		auto fourth = list_set.MakeSet(4);
		std::cout << list_set.Find(second)->data << "\n";
		list_set.Union(first, second);
		std::cout << list_set.Find(first)->data << "\n";
		std::cout << list_set.Find(second)->data << "\n";
		list_set.Union(third, second);
		std::cout << "union third and second\n";
		std::cout << list_set.Find(first)->data << "\n";
		std::cout << list_set.Find(second)->data << "\n";
		std::cout << list_set.Find(third)->data << "\n";

		PrintSet(list_set, { first,second,third,fourth });
	}
	std::cout << "Trees:\n";
	{
		auto trees_set = TreesImplementation::DisjointSetTrees<int>();
		auto first = trees_set.MakeSet(1);
		auto second = trees_set.MakeSet(2);
		auto third = trees_set.MakeSet(3);
		auto fourth = trees_set.MakeSet(4);
		std::cout << trees_set.Find(second)->data << "\n";
		trees_set.Union(first, second);
		std::cout << trees_set.Find(first)->data << "\n";
		std::cout << trees_set.Find(second)->data << "\n";
		trees_set.Union(third, second);
		std::cout << "union third and second\n";
		std::cout << trees_set.Find(first)->data << "\n";
		std::cout << trees_set.Find(second)->data << "\n";
		std::cout << trees_set.Find(third)->data << "\n";

		PrintSet(trees_set, { first,second,third,fourth });
	}

}
