#include <benchmark/benchmark.h>

#include "queue.hpp"

static void BM_queue_stacks(benchmark::State& state) {
    for (auto _ : state)
    {
        int num = 10000;
        my_containers::queue_stacks<int> queue;

        for (int count = 0; count < state.range (); ++count)
            queue.push (count);
    }
}
BENCHMARK(BM_queue_stacks)->Range(0, 10000)->Unit(benchmark::kMillisecond);

static void BM_queue_list(benchmark::State& state) {
    for (auto _ : state)
    {
        int num = 10000;
        my_containers::queue_list<int> queue;

        for (int count = 0; count < state.range(); ++count)
            queue.push (count);
    }
}
BENCHMARK(BM_queue_list)->Range(0, 10000)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
