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

int main()
{
    std::cout << "Benchmarks:\n";

    benchmark_makeset_function();
    
}

