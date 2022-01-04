#pragma once
#include "../DisjointSetBase.h"
#include <vector>

namespace ListImplementation
{
	template<typename T>
	struct Node
	{
		Node *next;
		Node *repr;
		T data;
		int size;

		Node(T data) : repr(nullptr), next(nullptr), data(data), size(1)
		{}
	};

	template<typename T>
	class DisjointSetList : public DisjointSetBase<T, Node<T>*>
	{
		std::vector<std::unique_ptr<Node<T>>> nodes;
	public:
		DisjointSetList& operator= (DisjointSetList&&) = default;

		Node<T>* Find(Node<T>* t) override
		{
			return t->repr;
		}

		void Union(Node<T>* x, Node<T>* y) override
		{
			Node<T>* rX = Find(x);
			Node<T>* rY = Find(y);
			if (rX != rY)
			{
				//If necessary rename roots to ensure that we attach a smaller set - y 
				//to a larger set - x
				if (rX->size < rY->size)
					std::swap(rX, rY);

				rX->size += rY->size;
				//attaching lists
				while (rX->next != nullptr)
				{
					rX = rX->next;
				}
				rX->next = rY;

				while (rY != nullptr)
				{
					rY->repr = rX->repr;
					rY = rY->next;
				}
				
			}
		}

		Node<T> *MakeSet(T el) override
		{
			nodes.emplace_back(std::make_unique<Node<T>>(Node<T>(el)));
			nodes[nodes.size() - 1]->repr = nodes[nodes.size() - 1].get();
			return nodes[nodes.size()-1].get();
		}

		T GetElement(Node<T> *t) override
		{
			return t->data;
		}
		~DisjointSetList() override
		{
		}
	};
}

