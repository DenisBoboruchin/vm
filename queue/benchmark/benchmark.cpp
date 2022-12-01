#include <benchmark/benchmark.h>

#include "queue.hpp"

static void BM_queue_stacks(benchmark::State& state) {
    for (auto _ : state)
    {
        my_containers::queue_stacks<int> queue;

        for (int count = 0; count != state.range (0); ++count)
            queue.push (count);

        int sum = queue.front ();
        while (queue.size () != 1)
        {
            sum += queue.front ();
            queue.pop ();
            sum += queue.front ();
        }
    }
}
BENCHMARK(BM_queue_stacks)->Arg(10000)->Unit(benchmark::kMillisecond);

static void BM_queue_list(benchmark::State& state) {
    for (auto _ : state)
    {
        my_containers::queue_list<int> queue;

        for (int count = 0; count != state.range(0); ++count)
            queue.push (count);
    
        int sum = queue.front ();
        while (queue.size () != 1)
        {
            sum += queue.front ();
            queue.pop ();
            sum += queue.front ();
        }
    }
}
BENCHMARK(BM_queue_list)->Arg(10000)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
