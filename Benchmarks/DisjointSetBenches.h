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



