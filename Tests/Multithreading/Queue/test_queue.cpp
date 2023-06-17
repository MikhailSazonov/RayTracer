#include <MPMCQueue.hpp>
#include "../../test_utils.hpp"

#include <thread>
#include <cstdlib>
#include <vector>

using namespace std::chrono_literals;

int main() {
    std::cout << "QUEUE\n";
    test([](){
        // Simple
        Executors::MPMCQueue<int> queue;
        std::thread t1([&](){
            std::this_thread::sleep_for(10ms);
            queue.Put(1);
        });
        std::thread t2([&](){
            std::this_thread::sleep_for(5ms);
            queue.Put(2);
        });
        std::thread t3([&](){
            queue.Put(3);
        });
        t1.join();
        t2.join();
        t3.join();
        int sum = 0;
        while (!queue.Empty()) {
            auto next = queue.Take();
            assert(next != std::nullopt);
            sum += *next;
        }
        assert_equal(sum, 6);
    }, "Simple");
    test([](){
        // MPSC
        Executors::MPMCQueue<int> queue;
        std::vector<std::thread> thread_vector;
        std::vector<int> ints;
        // just for lulz
        size_t K = 100;
        size_t thread_count = 10;

        for (size_t i = 0; i < thread_count; ++i) {
            thread_vector.push_back(std::thread([&, i]() mutable {
                for (size_t j = 0; j < K; ++j) {
                    queue.Put(j);
                }
            }));
        }
        for (size_t i = 0; i < 10; ++i) {
            thread_vector[i].join();
        }
        int sum = 0;
        while (!queue.Empty()) {
            auto next = queue.Take();
            assert(next != std::nullopt);
            sum += *next;
        }
        assert_equal(sum, 10 * ((0 + 99) * 100 / 2));
    }, "Multi Producer Single Consumer");
    test([](){
        // SPMC
        Executors::MPMCQueue<int> queue;
        std::vector<std::thread> thread_vector;
        // just for lulz
        size_t K = 100;
        size_t thread_count = 10;

        for (size_t i = 0; i < K * thread_count; ++i) {
            queue.Put(5);
        }

        for (size_t i = 0; i < 10; ++i) {
            thread_vector.push_back(std::thread([&, i]() mutable {
                for (size_t j = 0; j < K; ++j) {
                    queue.Take();
                }
            }));
        }
        for (size_t i = 0; i < 10; ++i) {
            thread_vector[i].join();
        }
        assert(queue.Empty());
    }, "Single Producer Multi Consumer");
    test([](){
        // MPMC
        Executors::MPMCQueue<int> queue;
        std::vector<std::thread> thread_vector;
        std::vector<int> ints;

        // just for lulz
        size_t K = 1337'88;
        size_t thread_count = 10;

        for (size_t i = 0; i < thread_count; ++i) {
            thread_vector.push_back(std::thread([&, i]() mutable {
                for (size_t j = 0; j < K; ++j) {
                    queue.Put(31);
                    queue.Take();
                }
            }));
        }

        for (size_t i = 0; i < thread_count; ++i) {
            thread_vector[i].join();
        }
    }, "Multi Producer Multi Consumer");
    std::cout << "Tests passed!\n\n";
}