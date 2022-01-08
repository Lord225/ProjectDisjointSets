#pragma once
#include "../DisjointSetBase.h"
#include <vector>

namespace TreesRanImplementation
{
	template<typename T>
	struct Node
	{
		Node *parent;
		T data;
		int rank;

		Node()
			: parent(this), data(T()), rank(0)
		{}
	};


	template<typename T>
	class DisjointSetTreesRan : public DisjointSetBase<T, Node<T> *>
	{
		std::vector<Node<T> *> nodes;
	public:
		DisjointSetTreesRan &operator= (DisjointSetTreesRan &&new_set)
		{
			this->~DisjointSetTreesRan();
			nodes = std::move(new_set.nodes);
			return *this;
		}

		Node<T> *Find(Node<T> *t) override
		{
			if (t->parent != t)
			{
				return Find(t->parent);
			}

			return t;
		}

		void Union(Node<T> *x, Node<T> *y) override
		{
			// Replace nodes by roots
			Node<T> *rX = Find(x);
			Node<T> *rY = Find(y);

			if (rX != rY)
			{

				// If necessary, rename roots to ensure that
				// x has rank at least as large as that of y
				if (rX->rank < rY->rank)
				{
					Node<T> *temp{ rX };
					rX = rY;
					rY = temp;
				}
				// Make x the new root
				rY->parent = rX;
				// If necessary, increment the rank of x
				if (rX->rank == rY->rank)
					rX->rank++;
			}
		}

		Node<T> *MakeSet(T el) override
		{
			Node<T> *new_node{ new Node<T> };
			new_node->data = el;
			nodes.push_back(new_node);
			return new_node;
		}

		T GetElement(Node<T> *t) override
		{
			return t->data;
		}
		~DisjointSetTreesRan() override
		{
			for (Node<T> *i : nodes)
			{
				delete i;
			}
		}

	};
}

