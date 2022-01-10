#pragma once
#include "Benchmark.h"
#include "../ProjectDisjointSets/Implementations/DisjointSetMap.h"
#include "../ProjectDisjointSets/Implementations/DisjointSetList.h"
#include "../ProjectDisjointSets/Implementations/DisjointSetTrees.h"
#include "../ProjectDisjointSets/Implementations/DisjointSetTreesCom.h"
#include "../ProjectDisjointSets/Implementations/DisjointSetTreesComRan.h"
#include "../ProjectDisjointSets/Implementations/DisjointSetTreesRan.h"

RandomArray randomArray;

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
        universe.clear();
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

    UnionRandomBench(int to_insert, int to_union, DataType init) : to_insert(to_insert), init(init), to_union(to_union) {}

    void setup() override
    {
        set = DisjointSetType();
        universe.clear();
        for (size_t i = 0; i < to_insert; i++)
            universe.push_back(set.MakeSet(doNotOptimize(init)));
    }

    void bench() override
    {
        for (size_t i = 0; i < to_union - 1; i++)
        {
            const NodeType first = universe[rand() % universe.size()];
            const NodeType second = universe[rand() % universe.size()];

            set.Union(first, second);
        }
        doNotOptimize(set);
    }

    long double get_X_mesurment() override
    {
        return to_insert;
    }
};


template<DisjointSetConcept DisjointSetType>
class PreUnionRandomBench : public Benchmark
{
public:
    DisjointSetType set;
    using NodeType = DisjointSetType::NodeType;
    using DataType = DisjointSetType::DataType;

    std::vector<NodeType> universe;

    const int to_insert;
    const int to_union;
    const int to_pre_union;
    const DataType init;

    PreUnionRandomBench(int to_insert, int to_union, int to_pre_union, DataType init) : to_insert(to_insert), init(init), to_union(to_union), to_pre_union(to_pre_union) {}

    void setup() override
    {
        set = DisjointSetType();
        universe.clear();
        for (size_t i = 0; i < to_insert; i++)
            universe.push_back(set.MakeSet(doNotOptimize(init)));

        for(auto i : Range(0, universe.size()/ to_pre_union - 1))
            for (auto j : Range(i* to_pre_union, i* to_pre_union + to_pre_union - 1))
            	set.Union(universe[i* to_pre_union], universe[j]);
    }

    void bench() override
    {
        for (size_t i = 0; i < to_union - 1; i++)
        {
            const NodeType first = universe[rand() % universe.size()];
            const NodeType second = universe[rand() % universe.size()];

            set.Union(first, second);
        }
        doNotOptimize(set);
    }

    long double get_X_mesurment() override
    {
        return to_insert;
    }
};


template<DisjointSetConcept DisjointSetType>
class UnionRandomMyBench : public Benchmark
{
public:
    DisjointSetType set;
    using NodeType = DisjointSetType::NodeType;
    using DataType = DisjointSetType::DataType;

    std::vector<NodeType> universe;

    const int to_insert;
    const int to_union;
    const DataType init;

    UnionRandomMyBench(int to_insert, int to_union, DataType init) : to_insert(to_insert), init(init), to_union(to_union) {}

    void setup() override
    {
        set = DisjointSetType();
        universe.clear();
        for (size_t i = 0; i < to_insert; i++)
            universe.push_back(set.MakeSet(doNotOptimize(init)));
        for (size_t i = 0; i < to_insert / 5; i++)
        {
            const NodeType first = universe[rand() % universe.size()];
            const NodeType second = universe[rand() % universe.size()];

            set.Union(first, second);
        }
    }

    void bench() override
    {
        for (size_t i = 0; i < to_union - 1; i++)
        {
            const NodeType first = universe[rand() % universe.size()];
            const NodeType second = universe[rand() % universe.size()];

            set.Union(first, second);
        }
        doNotOptimize(set);
    }

    long double get_X_mesurment() override
    {
        return to_insert;
    }
};


template<DisjointSetConcept DisjointSetType>
class FindListishRandomBench : public Benchmark
{
public:
    DisjointSetType set;
    using NodeType = DisjointSetType::NodeType;
    using DataType = DisjointSetType::DataType;

    std::vector<NodeType> universe;

    const int to_insert;
    const int to_find;
    const DataType init;
    std::vector<int> randomness;

    FindListishRandomBench(int to_insert, int to_find, DataType init) : to_insert(to_insert), init(init), to_find(to_find) {}

    void setup() override
    {
        set = DisjointSetType();
        universe.clear();
        for (size_t i = 0; i < to_insert; i++)
            universe.push_back(set.MakeSet(doNotOptimize(init)));
        for (size_t i = 0; i < to_insert / 3; i++)
        {
            const NodeType first = universe[i + 1];
            const NodeType second = universe[i];

            set.Union(first, second);
        }
        for (size_t i = (to_insert / 3) + 2; i < 2 * (to_insert / 3); i++)
        {
            const NodeType first = universe[i + 1];
            const NodeType second = universe[i];

            set.Union(first, second);
        }
        for (size_t i = 2 * (to_insert / 3) + 3; i < (to_insert / 3) - 2; i++)
        {
            const NodeType first = universe[i + 1];
            const NodeType second = universe[i];

            set.Union(first, second);
        }
        randomness = randomArray.get_random(to_insert);
    }

    void bench() override
    {
        for (size_t i = 0; i < to_find - 1; i++)
        {
            set.Find(universe[randomness[i]]);
        }
        doNotOptimize(set);
    }

    long double get_X_mesurment() override
    {
        return to_insert;
    }
};