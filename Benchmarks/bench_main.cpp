#include <iostream>
#include "BenchmarkBase.h"
#include "BenchmarksImpl.h"
#include "../ProjectDisjointSets/Implementations/DisjointSetMap.h"
#include "../ProjectDisjointSets/Implementations/DisjointSetList.h"
#include "../ProjectDisjointSets/Implementations/DisjointSetTrees.h"
#include "../ProjectDisjointSets/Implementations/DisjointSetTreesCom.h"
#include "../ProjectDisjointSets/Implementations/DisjointSetTreesComRan.h"
#include "../ProjectDisjointSets/Implementations/DisjointSetTreesRan.h"

void benchmark_makeset_function()
{
    const int intervals = 25'000;
    const int max = 500'000;
    BenchmarkRegistry registry;

    for (auto i : Range(100'000, max, intervals))
        MakeSetBench<MapImplementation::DisjointSetMap<int>>(i, 1).runBenchmark("Map MakeSet").generate_summary().register_output(registry);
    for (auto i : Range(100'000, max, intervals))
        MakeSetBench<MapImplementation::DisjointSetMap<std::string>>(i, "Long Long Long Long Long Long String String String String").runBenchmark("Map MakeSet string").generate_summary().register_output(registry);

    for (auto i : Range(100'000, max, intervals))
        MakeSetBench<TreesImplementation::DisjointSetTrees<int>>(i, 1).runBenchmark("Tree MakeSet").generate_summary().register_output(registry);
    for (auto i : Range(100'000, max, intervals))
        MakeSetBench<TreesImplementation::DisjointSetTrees<std::string>>(i, "Long Long Long Long Long Long String String String String").runBenchmark("Tree MakeSet string").generate_summary().register_output(registry);

    for (auto i : Range(100'000, max, intervals))
        MakeSetBench<ListImplementation::DisjointSetList<int>>(i, 1).runBenchmark("List MakeSet").generate_summary().register_output(registry);
    for (auto i : Range(100'000, max, intervals))
        MakeSetBench<ListImplementation::DisjointSetList<std::string>>(i, "Long Long Long Long Long Long String String String String").runBenchmark("List MakeSet string").generate_summary().register_output(registry);

    registry.generate_csv("../BenchOutput/MakeSet/");
}

void benchmark_union_with_first_function()
{
    const int intervals = 100;
    BenchmarkRegistry registry;
    const std::string long_string = "Long Long Long Long Long Long String String String String";

    for (auto i : Range(1'000, 5'000, intervals))
        UnionAllWithFirstBench<MapImplementation::DisjointSetMap<int>>(i, 1).runBenchmark("Map Union first").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        UnionAllWithFirstBench<ListImplementation::DisjointSetList<int>>(i, 1).runBenchmark("List Union first").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        UnionAllWithFirstBench<TreesImplementation::DisjointSetTrees<int>>(i, 1).runBenchmark("Tree Union first").generate_summary().register_output(registry);

    for (auto i : Range(1'000, 5'000, intervals))
        UnionAllWithFirstBench<MapImplementation::DisjointSetMap<std::string>>(i, long_string).runBenchmark("Map Union first (str)").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        UnionAllWithFirstBench<ListImplementation::DisjointSetList<std::string>>(i, long_string).runBenchmark("List Union first (str)").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        UnionAllWithFirstBench<TreesImplementation::DisjointSetTrees<std::string>>(i, long_string).runBenchmark("Tree Union first (str)").generate_summary().register_output(registry);


    registry.generate_csv("../BenchOutput/Union/");
}

void benchmark_union_random_function()
{
    const int intervals = 100;
    BenchmarkRegistry registry;
    const std::string long_string = "Long Long Long Long Long Long String String String String";

    for (auto i : Range(1'000, 5'000, intervals))
        UnionRandomBench<MapImplementation::DisjointSetMap<int>>(i, i, 1).runBenchmark("Map Union rnd").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        UnionRandomBench<ListImplementation::DisjointSetList<int>>(i, i, 1).runBenchmark("List Union rnd").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        UnionRandomBench<TreesImplementation::DisjointSetTrees<int>>(i, i, 1).runBenchmark("Tree Union rnd").generate_summary().register_output(registry);
   
    for (auto i : Range(1'000, 5'000, intervals))
        UnionRandomBench<TreesComImplementation::DisjointSetTreesCom<int>>(i, i, 1).runBenchmark("Tree Union compression rnd").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        UnionRandomBench<TreesComRanImplementation::DisjointSetTreesComRan<int>>(i, i, 1).runBenchmark("Tree Union compression rank rnd").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        UnionRandomBench<TreesRanImplementation::DisjointSetTreesRan<int>>(i, i, 1).runBenchmark("Tree Union rank rnd").generate_summary().register_output(registry);

    registry.generate_csv("../BenchOutput/UnionRnd/");
}

void benchmark_union_random_const_to_union_function()
{
    const int intervals = 100;
    BenchmarkRegistry registry;
    const std::string long_string = "Long Long Long Long Long Long String String String String";

    for (auto i : Range(1'000, 1'000, intervals))
        UnionRandomBench<MapImplementation::DisjointSetMap<int>>(i, 100, 1).runBenchmark("(Const To union) Map Union rnd", 100'000'000, 50'000).generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        UnionRandomBench<ListImplementation::DisjointSetList<int>>(i, 100, 1).runBenchmark("(Const To union) List Union rnd", 100'000'000, 50'000).generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        UnionRandomBench<TreesImplementation::DisjointSetTrees<int>>(i, 100, 1).runBenchmark("(Const To union) Tree Union rnd", 100'000'000, 50'000).generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        UnionRandomBench<TreesComImplementation::DisjointSetTreesCom<int>>(i, 100, 1).runBenchmark("(Const To union) Tree Union rnd compression", 100'000'000, 50'000).generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        UnionRandomBench<TreesComRanImplementation::DisjointSetTreesComRan<int>>(i, 100, 1).runBenchmark("(Const To union) Tree Union rnd compression rank rnd", 100'000'000, 50'000).generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        UnionRandomBench<TreesRanImplementation::DisjointSetTreesRan<int>>(i, 100, 1).runBenchmark("(Const To union) Tree Union rnd rank rnd", 100'000'000, 50'000).generate_summary().register_output(registry);


    registry.generate_csv("../BenchOutput/UnionRndConstToUnion/");
}

void benchmark_union_first_and_rnd_function()
{
    const int intervals = 100;
    BenchmarkRegistry registry;

    for (auto i : Range(1'000, 5'000, intervals))
        UnionAllWithFirstBench<ListImplementation::DisjointSetList<int>>(i, 1).runBenchmark("List Union first").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        UnionAllWithFirstBench<TreesImplementation::DisjointSetTrees<int>>(i, 1).runBenchmark("Tree Union first").generate_summary().register_output(registry);

    for (auto i : Range(1'000, 5'000, intervals))
        UnionRandomBench<ListImplementation::DisjointSetList<int>>(i, i, 1).runBenchmark("List Union rnd").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        UnionRandomBench<TreesImplementation::DisjointSetTrees<int>>(i, i, 1).runBenchmark("Tree Union rnd").generate_summary().register_output(registry);

    registry.generate_csv("../BenchOutput/ /");
}

void benchmark_union_with_pre_union_function()
{
    const int intervals = 100;
    BenchmarkRegistry registry;

    for (auto i : Range(1'000, 5'000, intervals))
        PreUnionRandomBench<ListImplementation::DisjointSetList<int>>(i, i/100, 100, 1).runBenchmark("List Union first (groups)").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        PreUnionRandomBench<TreesImplementation::DisjointSetTrees<int>>(i, i / 100, 100, 1).runBenchmark("Tree Union first (groups)").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        PreUnionRandomBench<TreesComImplementation::DisjointSetTreesCom<int>>(i, i / 100, 100, 1).runBenchmark("Tree Union first (groups) compression").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        PreUnionRandomBench<TreesComRanImplementation::DisjointSetTreesComRan<int>>(i, i / 100, 100, 1).runBenchmark("Tree Union first (groups) compression rank rnd").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        PreUnionRandomBench<TreesRanImplementation::DisjointSetTreesRan<int>>(i, i / 100, 100, 1).runBenchmark("Tree Union first (groups) rank rnd").generate_summary().register_output(registry);

    registry.generate_csv("../BenchOutput/UnionRndGroups/");
}
void benchmark_union_my_benchmark()
{
    const int intervals = 1000;
    BenchmarkRegistry registry;
    const std::string long_string = "Long Long Long Long Long Long String String String String";

    for (auto i : Range(1'000, 5'000, intervals))
        UnionRandomMyBench<MapImplementation::DisjointSetMap<int>>(i, i/2, 1).runBenchmark("Map Union rnd").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        UnionRandomMyBench<ListImplementation::DisjointSetList<int>>(i, i/2, 1).runBenchmark("List Union rnd").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        UnionRandomBench<TreesImplementation::DisjointSetTrees<int>>(i, i/2, 1).runBenchmark("Tree Union rnd").generate_summary().register_output(registry);

    for (auto i : Range(1'000, 5'000, intervals))
        UnionRandomMyBench<TreesComImplementation::DisjointSetTreesCom<int>>(i, i/2, 1).runBenchmark("Tree Union compression rnd").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        UnionRandomMyBench<TreesComRanImplementation::DisjointSetTreesComRan<int>>(i, i/2, 1).runBenchmark("Tree Union compression rank rnd").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        UnionRandomMyBench<TreesRanImplementation::DisjointSetTreesRan<int>>(i, i/2, 1).runBenchmark("Tree Union rank rnd").generate_summary().register_output(registry);

    registry.generate_csv("../BenchOutput/UnionMichal/");
}


void benchmark_find_listish()
{
    const int intervals = 500;
    BenchmarkRegistry registry;
    const std::string long_string = "Long Long Long Long Long Long String String String String";

    //for (auto i : Range(1'000, 5'000, intervals))
        //FindListishRandomBench<MapImplementation::DisjointSetMap<int>>(i, i / 2, 1).runBenchmark("Map Union rnd").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        FindListishRandomBench<ListImplementation::DisjointSetList<int>>(i, i / 2, 1).runBenchmark("List Find Listish rnd").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        FindListishRandomBench<TreesImplementation::DisjointSetTrees<int>>(i, i / 2, 1).runBenchmark("Tree Find Listish rnd").generate_summary().register_output(registry);

    for (auto i : Range(1'000, 5'000, intervals))
        FindListishRandomBench<TreesComImplementation::DisjointSetTreesCom<int>>(i, i / 2, 1).runBenchmark("Tree Find Listish compression rnd").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        FindListishRandomBench<TreesComRanImplementation::DisjointSetTreesComRan<int>>(i, i / 2, 1).runBenchmark("Tree Find Listish compression rank rnd").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        FindListishRandomBench<TreesRanImplementation::DisjointSetTreesRan<int>>(i, i / 2, 1).runBenchmark("Tree Find Listish rank rnd").generate_summary().register_output(registry);

    registry.generate_csv("../BenchOutput/FindListish/");
}

void fixed_size_union()
{
    const int intervals = 500;
    const int to_union_divider = 128;
    BenchmarkRegistry registry;
    const std::string long_string = "Long Long Long Long Long Long String String String String";

    //for (auto i : Range(1'000, 5'000, intervals))
        //FindListishRandomBench<MapImplementation::DisjointSetMap<int>>(i, i / 2, 1).runBenchmark("Map Union rnd").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        UnionWithFixedSet<ListImplementation::DisjointSetList<int>>(i, i / to_union_divider, 1).runBenchmark("List Union Const rnd").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        UnionWithFixedSet<TreesImplementation::DisjointSetTrees<int>>(i, i / to_union_divider, 1).runBenchmark("Tree Union Const rnd").generate_summary().register_output(registry);

    for (auto i : Range(1'000, 5'000, intervals))
        UnionWithFixedSet<TreesComImplementation::DisjointSetTreesCom<int>>(i, i / to_union_divider, 1).runBenchmark("Tree Union Const compression rnd").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        UnionWithFixedSet<TreesComRanImplementation::DisjointSetTreesComRan<int>>(i, i / to_union_divider, 1).runBenchmark("Tree Union Const compression rank rnd").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        UnionWithFixedSet<TreesRanImplementation::DisjointSetTreesRan<int>>(i, i / to_union_divider, 1).runBenchmark("Tree Union Const rank rnd").generate_summary().register_output(registry);

    registry.generate_csv("../BenchOutput/UnionConst/");
}

int main()
{
    std::cout << "Benchmarks:\n";

    //benchmark_makeset_function();

    //benchmark_union_with_first_function();

    //benchmark_union_random_function();

    //fixed_size_union();

	//benchmark_find_listish();

	//benchmark_union_first_and_rnd_function();

    benchmark_union_random_const_to_union_function();

    benchmark_union_with_pre_union_function();
}

