#include <iostream>
#include <vector>

#include "DisjointSetBase.h"
#include "Implementations/DisjointSetMap.h"

template<typename T, typename EL_TYPE>
void PrintSet(DisjointSetBase<T, EL_TYPE>& set, std::vector<T> universe)
{
	for (auto i : universe)
	{
		std::cout << i << " " << set.Find(i) << std::endl;
	}
}
int main()
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
	PrintSet(set, { 1,2,3,4,5 });
}
