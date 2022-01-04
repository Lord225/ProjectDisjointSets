#pragma once
#include "../DisjointSetBase.h"
#include <map>

namespace MapImplementation
{
	template<typename T>
	struct Node
	{
		size_t parent;
		T data;


		Node(size_t parent, T data)
			: parent(parent), data(data)
		{}
		Node()
			: parent(0), data(T())
		{}
	};

	template<typename T>
	class DisjointSetMap : public DisjointSetBase<T, size_t>
	{
		unsigned int unique_counter = 0;
		using DJSetsReprType = std::map<size_t, Node<T>>;
		DJSetsReprType _disjoint_sets;
	public:
		size_t Find(size_t t) override
		{
			// This implementation asserts that parent is always representate
			return this->_disjoint_sets[t].parent;
		}

		void Union(size_t x, size_t y) override
		{
			size_t rX = Find(x);
			size_t rY = Find(y);

			for (auto& [key, val] : _disjoint_sets)
			{
				if (rX == val.parent)
					val.parent = rY;
			}
		}

		size_t MakeSet(T el) override
		{
			size_t unique_id = unique_counter++;
			this->_disjoint_sets.insert(std::make_pair(unique_id, Node<T>(unique_id, el)));
			return unique_id;
		}

		T GetElement(size_t t) override
		{
			return this->_disjoint_sets[t].data;
		}
		~DisjointSetMap() override
		{

		}
	};
}

