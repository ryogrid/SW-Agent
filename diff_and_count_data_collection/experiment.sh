##!/bin/sh

./diff_and_count_bench_client eval_overhead_primitive 1000 -dest localhost:1024
./diff_and_count_bench_client eval_overhead_frame 1000 640 480 -dest localhost:1024
./diff_and_count_bench_client eval_bandwidth_stream 20 1 1024 1024 -dest localhost:1024
./diff_and_count_bench_client eval_bandwidth_rpc 20 1 1024 1024 -dest localhost:1024
