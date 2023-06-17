#include <ThreadPool.hpp>
#include "../../test_utils.hpp"

using namespace std::chrono_literals;

int main() {
    std::cout << "POOL\n";
    test([](){
        Executors::ThreadPool pool(1);
        bool done = false;
        pool.Submit([&](){
            done = true;
        });
        pool.Start();
        pool.WaitIdle();
        pool.Stop();
        assert(done);
    }, "Simple");
    test([](){
        Executors::ThreadPool pool(3);
        std::atomic<int> counter{0};
        for (size_t i = 0; i < 100; ++i) {
            pool.Submit([&](){
                counter.fetch_add(1);
            });
        }
        pool.Start();
        pool.WaitIdle();
        pool.Stop();
        assert_equal(counter.load(), 100);
    }, "Increments");
    test([](){
        Executors::ThreadPool pool(5);
        pool.Start();
        std::atomic<int> counter{0};
        for (size_t i = 0; i < 1000; ++i) {
            pool.Submit([&](){
                counter.fetch_add(1);
            });
        }
        pool.WaitIdle();
        pool.Stop();
        assert_equal(counter.load(), 1000);
    }, "Submit while working");
    test([](){
        Executors::ThreadPool tp(4);
        tp.Start();
        int counter1{0};
        int counter2{0};
        Task pingpong1;
        Task pingpong2;

        pingpong1 = [&]() {
            ++counter1;
            if (counter1 < 1000) {
                tp.Submit(pingpong1);
            }
        };
        pingpong2 = [&]() {
            ++counter2;
            if (counter2 < 1000) {
                tp.Submit(pingpong2);
            }
        };
        tp.Submit(pingpong1);
        tp.Submit(pingpong2);
        tp.WaitIdle();
        tp.Stop();
        assert_equal(counter1, 1000);
        assert_equal(counter2, 1000);
    }, "Ping pong");
    std::cout << "All tests passed!\n\n";
}
