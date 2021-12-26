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

		Node()
			: repr(this), next(nullptr), data(T()), size(1)
		{}
	};


	template<typename T>
	class DisjointSetList : public DisjointSetBase<T, Node<T>*>
	{
		std::vector<Node<T>*> nodes;
	public:
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
				{
					Node<T> *temp{ rX };
					rX = rY;
					rY = temp;
				}
				
				rX->size += rY->size;
				//attaching lists
				while (rX->next)
				{
					rX = rX->next;
				}
				rX->next = rY;

				while (rY)
				{
					rY->repr = rX->repr;
					rY = rY->next;
				}
				
			}
		}

		Node<T> *MakeSet(T el) override
		{
			Node<T> *new_node{new Node<T>};
			new_node->data = el;
			nodes.push_back(new_node);
			return new_node;
		}

		T GetElement(Node<T> *t) override
		{
			return t->data;
		}
		~DisjointSetList()
		{
			for (auto &i : nodes)
			{
				delete i;
			}
		}
	};
}

