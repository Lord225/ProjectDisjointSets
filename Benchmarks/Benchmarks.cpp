#include <iostream>
#include "Benchmark.h"
#include "DisjointSetBenches.h"

void benchmark_makeset_function()
{
    const int intervals = 25'000;
    BenchmarkRegistry registry;

    for (auto i : Range(100'000, 1'000'000, intervals))
        MakeSetBench<MapImplementation::DisjointSetMap<int>>(i, 1).runBenchmark("Map MakeSet").generate_summary().register_output(registry);
    for (auto i : Range(100'000, 1'000'000, intervals))
        MakeSetBench<MapImplementation::DisjointSetMap<std::string>>(i, "Long Long Long Long Long Long String String String String").runBenchmark("Map MakeSet string").generate_summary().register_output(registry);

    for (auto i : Range(100'000, 1'000'000, intervals))
        MakeSetBench<TreesImplementation::DisjointSetTrees<int>>(i, 1).runBenchmark("Tree MakeSet").generate_summary().register_output(registry);
    for (auto i : Range(100'000, 1'000'000, intervals))
        MakeSetBench<TreesImplementation::DisjointSetTrees<std::string>>(i, "Long Long Long Long Long Long String String String String").runBenchmark("Tree MakeSet string").generate_summary().register_output(registry);

    for (auto i : Range(100'000, 1'000'000, intervals))
        MakeSetBench<ListImplementation::DisjointSetList<int>>(i, 1).runBenchmark("List MakeSet").generate_summary().register_output(registry);
    for (auto i : Range(100'000, 1'000'000, intervals))
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
        UnionAllWithFirstBench<MapImplementation::DisjointSetMap<std::string>>(i, long_string).runBenchmark("Map Union first string").generate_summary().register_output(registry);

    for (auto i : Range(1'000, 5'000, intervals))
        UnionAllWithFirstBench<ListImplementation::DisjointSetList<int>>(i, 1).runBenchmark("List Union first").generate_summary().register_output(registry);
    for (auto i : Range(1'000, 5'000, intervals))
        UnionAllWithFirstBench<ListImplementation::DisjointSetList<std::string>>(i, long_string).runBenchmark("List Union first string").generate_summary().register_output(registry);

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

    registry.generate_csv("../BenchOutput/UnionRnd/");
}

int main()
{
    std::cout << "Benchmarks:\n";

    //benchmark_makeset_function();

    benchmark_union_random_function();
}

