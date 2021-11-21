#include <iostream>
#include "DisjointSetBase.h"

template<typename T>
struct Node
{
    T el;
    Node* next;
    Node* root;
};
template<typename T>
struct NodeForset
{
    T el;
    Node* el;
    Node* root;
};

template<typename T>
class DisjointList : DisjointSetBase<T, Node<T>*>
{
public:
    // Odziedziczono za pośrednictwem elementu DisjointSetBase
    virtual Node<T>* Find(Node<T>* t) override
    {

    }

    virtual void Union(Node<T>* x, Node<T>* y) override
    {

    }

    virtual Node<T>* MakeSet(T el) override
    {

    }

};

template<typename T>
class DisjointArray : DisjointSetBase<T, int>
{
public:
    // Odziedziczono za pośrednictwem elementu DisjointSetBase
    virtual int Find(int t) override
    {

    }

    virtual void Union(int x, int y) override
    {

    }

    virtual int MakeSet(T el) override
    {

    }

};

int main()
{
    DisjointList<int> XD;
    auto* ptr = XD.MakeSet(1);
    DisjointArray<int> XD;

    auto index = XD.MakeSet(1);
}
