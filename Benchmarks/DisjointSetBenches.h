#pragma once
#include "Benchmark.h"
#include "../ProjectDisjointSets/Implementations/DisjointSetMap.h"
#include "../ProjectDisjointSets/Implementations/DisjointSetList.h"
#include "../ProjectDisjointSets/Implementations/DisjointSetTrees.h"

template<DisjointSetConcept DisjointSetType>
class MakeSetBench : public Benchmark
{
public:
    DisjointSetType set;
    using NodeType = DisjointSetType::NodeType;
    using DataType = DisjointSetType::DataType;

    const int to_insert;
    const DataType init;

    MakeSetBench(int to_insert, DataType init) : to_insert(to_insert), init(init) {}

    void setup() override
    {
        set = DisjointSetType();
    }

    void bench() override
    {
        for (size_t i = 0; i < to_insert; i++)
            set.MakeSet(doNotOptimize(init));
        
        doNotOptimize(set);
    }

    long double get_X_mesurment() override
    {
        return to_insert;
    }
};

template<DisjointSetConcept DisjointSetType>
class UnionAllWithFirstBench : public Benchmark
{
public:
    DisjointSetType set;
    using NodeType = DisjointSetType::NodeType;
    using DataType = DisjointSetType::DataType;
    
    std::vector<NodeType> universe;

    const int to_insert;
    const DataType init;

    UnionAllWithFirstBench(int to_insert, DataType init) : to_insert(to_insert), init(init)
    {
    }

    void setup() override
    {
        set = DisjointSetType();
        for (size_t i = 0; i < to_insert; i++)
            universe.push_back(set.MakeSet(doNotOptimize(init)));
    }

    void bench() override
    {
        const auto first = universe[0];
        for (size_t i = 0; i < to_insert-1; i++)
            set.Union(first, universe[i]);

        doNotOptimize(set);
    }

    long double get_X_mesurment() override
    {
        return to_insert;
    }
};

template<DisjointSetConcept DisjointSetType>
class UnionRandomBench : public Benchmark
{
public:
    DisjointSetType set;
    using NodeType = DisjointSetType::NodeType;
    using DataType = DisjointSetType::DataType;

    std::vector<NodeType> universe;

    const int to_insert;
    const int to_union;
    const DataType init;

    UnionRandomBench(int to_insert, int to_union, DataType init) : to_insert(to_insert), init(init), to_union(to_union)
    {
    }

    void setup() override
    {
        set = DisjointSetType();
        for (size_t i = 0; i < to_insert; i++)
            universe.push_back(set.MakeSet(doNotOptimize(init)));
    }

    void bench() override
    {
        for (size_t i = 0; i < to_insert - 1; i++)
        {
            const auto first = universe[rand() % universe.size()];
            const auto second = universe[rand() % universe.size()];

            set.Union(first, second);
        }
        doNotOptimize(set);
    }

    long double get_X_mesurment() override
    {
        return to_insert;
    }
};

