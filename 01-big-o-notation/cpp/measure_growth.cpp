// Empirically demonstrates how different complexity classes actually behave
// as input size grows. Compile and run to see real timings.
//
// The point isn't the exact numbers (those depend on your machine) — it's the
// *ratio* between rows. Watch how the O(n^2) time roughly quadruples when n
// doubles, while O(n) time roughly doubles, and O(log n) barely changes at all.

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <iomanip>

using Clock = std::chrono::high_resolution_clock;

// Prevents the optimizer from discarding "unused" results and skipping the
// work entirely. Without this, -O2 can see that a function's return value
// is never used and delete the whole loop, which would make every timing
// look like O(1) regardless of what the function actually does.
volatile long long sink;

// O(1): work does not depend on input size.
int constantTime(const std::vector<int> &arr) {
    return arr.empty() ? 0 : arr[0];
}

// O(n): a single pass over the input.
long long linearTime(const std::vector<int> &arr) {
    long long total = 0;
    for (int x : arr) total += x;
    return total;
}

// O(n log n): std::sort (introsort) as a stand-in for merge/quicksort.
void linearithmicTime(std::vector<int> arr) {
    std::sort(arr.begin(), arr.end());
}

// O(n^2): compare every pair of elements.
long long quadraticTime(const std::vector<int> &arr) {
    long long count = 0;
    for (size_t i = 0; i < arr.size(); i++) {
        for (size_t j = 0; j < arr.size(); j++) {
            if (arr[i] == arr[j]) count++;
        }
    }
    return count;
}

// O(log n): repeatedly halve n until it reaches 1.
int logarithmicTime(int n) {
    int steps = 0;
    while (n > 1) {
        n /= 2;
        steps++;
    }
    return steps;
}

template <typename Func, typename... Args>
double timeIt(Func func, Args&&... args) {
    auto start = Clock::now();
    sink = static_cast<long long>(func(std::forward<Args>(args)...));
    auto end = Clock::now();
    return std::chrono::duration<double>(end - start).count();
}

// Overload for void-returning functions (e.g. linearithmicTime, which sorts
// in place and returns nothing) so timeIt still compiles for them.
template <typename... Args>
double timeIt(void (*func)(Args...), Args... args) {
    auto start = Clock::now();
    func(args...);
    auto end = Clock::now();
    return std::chrono::duration<double>(end - start).count();
}

int main() {
    std::vector<int> sizes = {500000, 1000000, 2000000, 4000000};

    std::cout << std::right
              << std::setw(8) << "n" << " | "
              << std::setw(10) << "O(1)us" << " | "
              << std::setw(10) << "O(log n)" << " | "
              << std::setw(10) << "O(n)" << " | "
              << std::setw(12) << "O(n log n)" << " | "
              << std::setw(10) << "O(n^2)" << "\n";
    std::cout << std::string(72, '-') << "\n";

    for (int n : sizes) {
        std::vector<int> arr(n);
        std::iota(arr.begin(), arr.end(), 0);

        double tConst = timeIt(constantTime, arr);
        double tLog = timeIt(logarithmicTime, n);
        double tLin = timeIt(linearTime, arr);
        double tNLogN = timeIt(linearithmicTime, arr);

        // Cap O(n^2) input size so the demo finishes quickly, but let the
        // cap itself grow with n so the quadratic trend is still visible.
        int capped = std::min(n, 2000 + n / 500);
        std::vector<int> smallArr(arr.begin(), arr.begin() + capped);
        double tQuad = timeIt(quadraticTime, smallArr);

        std::cout << std::fixed << std::setprecision(6)
                  << std::setw(8) << n << " | "
                  << std::setw(10) << tConst * 1e6 << " | "
                  << std::setw(10) << tLog << " | "
                  << std::setw(10) << tLin << " | "
                  << std::setw(12) << tNLogN << " | "
                  << std::setw(10) << tQuad << "\n";
    }

    std::cout << "\nNote: O(n^2) column uses a capped (but still growing) array size so the\n";
    std::cout << "demo finishes quickly -- even so, notice it grows far faster than the rest.\n";

    return 0;
}
