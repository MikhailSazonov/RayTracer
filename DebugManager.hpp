#pragma once

#include <cassert>
#include <iostream>
#include <mutex>

class DebugManager {
    public:
        inline static bool debug{false};

    private:
        inline static std::mutex mutex_;

    public:
        template <typename T>
        static void assert_equal(T&& left, T&& right) {
            if (left != right) {
                std::lock_guard lock(mutex_);
                std::cerr << "Not equal: " << left << "; " << right << '\n';
                assert(false);
            }
        }

        template <typename T>
        static void assert_equal_approx(T&& left, T&& right) {
            if (std::abs(left - right) >= 1e-9) {
                std::lock_guard lock(mutex_);
                std::cerr << "Not approximately equal: " << left << "; " << right << '\n';
                assert(false);
            }
        }
};

#define CHECK_EQUAL(x, y) if (DebugManager::debug) \
                                { DebugManager::assert_equal(x, y); }

#define CHECK_EQUAL_APPROX(x, y) if (DebugManager::debug) \
                                { DebugManager::assert_equal_approx(x, y); }

