#include <benchmark/benchmark.h>

#include "queue.hpp"

template <typename queue_type>
static void BM_queue_native(benchmark::State &state)
{
    for (auto _ : state) {
        queue_type queue;

        for (int count = 0; count != state.range(0); ++count)
            queue.push(count);

        long int sum = queue.front();
        while (queue.size() != 1) {
            sum += queue.front();
            queue.pop();
            sum += queue.front();
        }
    }
}

BENCHMARK(BM_queue_native<my_containers::queue_stacks<int>>)->Arg(10000000)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_queue_native<my_containers::queue_list<int>>)->Arg(10000000)->Unit(benchmark::kMillisecond);

template <typename queue_type>
static void BM_queue_hard(benchmark::State &state)
{
    for (auto _ : state) {
        queue_type queue;

        for (int count = 0; count != state.range(0); ++count)
            queue.push(count);

        long int sum = queue.front();
        while (queue.size() != 1) {
            sum += queue.front();
            queue.pop();
            sum += queue.back();
        }
    }
}

BENCHMARK(BM_queue_hard<my_containers::queue_stacks<int>>)->Arg(10000)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_queue_hard<my_containers::queue_list<int>>)->Arg(10000)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
