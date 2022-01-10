#pragma once
#include "BenchmarkBase.h"
#include "../ProjectDisjointSets/DisjointSetBase.h"
#include <random>

RandomArray randomArray;

/// <summary>
/// 
/// </summary>
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

template<DisjointSetConcept DisjointSetType>
class UnionWithFixedSet : public Benchmark
{
public:
    DisjointSetType set;
    std::default_random_engine gen;
    std::uniform_int_distribution<int> distribution;

    using NodeType = DisjointSetType::NodeType;
    using DataType = DisjointSetType::DataType;

    std::vector<NodeType> universe;

    const int to_insert;
    const int to_find;
    const DataType init;

    UnionWithFixedSet(int to_insert, int to_find, DataType init) : to_insert(to_insert), init(init), to_find(to_find) {}

    void setup() override
    {
        set = DisjointSetType();
        gen = std::default_random_engine(42);  // Same seed
        distribution = std::uniform_int_distribution<int>(0, universe.size());
    	universe.clear();

        for (size_t i = 0; i < to_insert; i++)
            universe.push_back(set.MakeSet(doNotOptimize(init)));

        for (size_t i = 0; i < to_insert - 1; i += 2) {
            set.Union(universe[i], universe[i + 1]);
        }
        for (size_t i = 1; i < to_insert - 1; i += 4) {
            set.Union(universe[i], universe[i + 1]);
        }
        for (size_t i = 3; i < to_insert - 1; i += 8) {
            set.Union(universe[i], universe[i + 1]);
        }
        for (size_t i = 7; i < to_insert - 1; i += 16) {
            set.Union(universe[i], universe[i + 1]);
        }
    }

    void bench() override
    {
        
        for (size_t i = 0; i < to_find - 1; i++)
        {
            const NodeType first = universe[distribution(gen)];
            const NodeType second = universe[distribution(gen)];

            set.Union(first, second);
        }
        doNotOptimize(set);
    }

    long double get_X_mesurment() override
    {
        return to_insert;
    }
};
