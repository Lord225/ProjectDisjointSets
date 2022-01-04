#pragma once
#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <chrono>
#include <map>
#include <fstream>

class BenchmarkRegistry
{
public:
    using registry_type = std::tuple<std::string, long double, long double>;
    std::vector<registry_type> registry;

    void add_to_registry(std::string name, long double X, long double Y)
    {
        registry.emplace_back(std::make_tuple(name, X, Y));
    }

    void generate_csv(std::string path)
    {
        std::map<std::string, std::vector<std::tuple<long double, long double>>> xy;

        for (const auto& [name, X, Y] : registry)
        {
            if (!xy.contains(name))
                xy.emplace(name, std::vector<std::tuple<long double, long double>>());
            xy[name].push_back(std::make_tuple(X, Y));
        }

        for (auto& [key, val] : xy)
        {
            std::sort(val.begin(), val.end(), [](const auto& x, const auto& y)
                {
                    const auto& [x_a, x_b] = x;
                    const auto& [y_a, y_b] = y;

                    return x_b > y_b;
                });

            std::fstream outfile;


            for (const auto& [name, XY] : xy)
            {
                outfile.open(path + "/" + name + ".csv", std::ios::trunc | std::ios::out);

                outfile << "X,Y" << std::endl;
                for (const auto& [x, y] : XY)
                    outfile << x << "," << y << std::endl;

				std::cout << "Saved: " << path << "/" << name << ".csv" << std::endl;
                outfile.close();
            }
        }
    }
};

//TODO: ZUPDATEUJ by dzia³a³o dobrze z Disjoint sets.
class Benchmark
{
public:
    long double total_time;
    unsigned long long iterations = 0;
    std::string name;

    virtual ~Benchmark() = default;

#pragma optimize("", off)
    template<typename T>
    static T& doNotOptimize(T& data) { return data; }

    Benchmark&& runBenchmark(std::string _name, long double max_time = 500'000'000, unsigned long long int max_iters = 50'000)
    {
        name = _name;
        using namespace std::chrono;

        total_time = 0.0;
        iterations = 0;

        while (total_time < max_time && iterations < max_iters)
        {
            setup();

            const auto start = high_resolution_clock::now();

            bench();

            const auto end = high_resolution_clock::now();

            total_time += duration_cast<nanoseconds>(end - start).count();

            iterations += 1;
        }
        return std::move(*this);
    }

    template<typename T>
    std::string get_good_ratio(T value)
    {
        using namespace std::chrono;
        if (value < 1'000)
            return std::to_string(value) + "ns";

        if (value < 1'000'000)
            return std::to_string(value / 1'000) + "us";

        if (value < 1'000'000'000)
            return std::to_string(value / 1'000'000) + "ms";

        return std::to_string(value / 1'000'000'000) + "s";
    }
    Benchmark&& generate_summary()
    {
        using namespace std::chrono;
        std::cout << "Benchmark Summary" << std::endl;
        std::cout << name << std::endl;
        std::cout << "Value: " << get_X_mesurment() << std::endl;
        std::cout << "Total: " << get_good_ratio(total_time) << std::endl;
        std::cout << "Call:  " << get_good_ratio(get_Y_mesurment()) << std::endl;
        std::cout << "Iter:  " << iterations << std::endl;
        std::cout << "-------------------------\n\n";

        return std::move(*this);
    }

    Benchmark&& register_output(BenchmarkRegistry& registry)
    {
        registry.add_to_registry(name, get_X_mesurment(), get_Y_mesurment());
        return std::move(*this);
    }

    virtual void setup() = 0;
    virtual void bench() = 0;
    virtual long double get_X_mesurment() = 0;
    virtual long double get_Y_mesurment()
    {
        return total_time / static_cast<long double>(iterations);
    }
};

class Range
{
    int _begin;
    int _end;
    int _stride;
public:
    Range(int begin, int end, int stride = 1) : _begin(begin), _end(end), _stride(stride)
    {
        if (!((begin >= end && stride < 0) || (end >= begin && stride > 0)))
        {
            throw std::logic_error("Invalid Range");
        }
    }
    class range_iter
    {
    public:
        int _stride;
        int _pos;

        range_iter& operator++()
        {
            this->_pos += _stride;
            return *this;
        }
        bool operator!=(range_iter& other) const
        {
            return other._pos != _pos;
        }
        int operator*() const
        {
            return _pos;
        }
    };

    [[nodiscard]] range_iter begin() const
    {
        return range_iter{ _stride, _begin };
    }
    [[nodiscard]] range_iter end() const
    {
        return range_iter{ _stride, _end };
    }
};