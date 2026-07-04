"""
Empirically demonstrates how different complexity classes actually behave
as input size grows. Run this file directly to see real timings.

The point isn't the exact numbers (those depend on your machine) — it's the
*ratio* between rows. Watch how the O(n^2) time roughly quadruples when n
doubles, while O(n) time roughly doubles, and O(log n) barely changes at all.
"""

import time
import math


def constant_time(arr):
    """O(1): work does not depend on input size."""
    return arr[0] if arr else None


def linear_time(arr):
    """O(n): a single pass over the input."""
    total = 0
    for x in arr:
        total += x
    return total


def linearithmic_time(arr):
    """O(n log n): built-in sort (Timsort) as a stand-in for merge/quicksort."""
    return sorted(arr)


def quadratic_time(arr):
    """O(n^2): compare every pair of elements."""
    count = 0
    for i in range(len(arr)):
        for j in range(len(arr)):
            if arr[i] == arr[j]:
                count += 1
    return count


def logarithmic_time(n):
    """O(log n): repeatedly halve n until it reaches 1."""
    steps = 0
    while n > 1:
        n //= 2
        steps += 1
    return steps


def time_it(func, *args):
    start = time.perf_counter()
    func(*args)
    return time.perf_counter() - start


def main():
    sizes = [1_000, 2_000, 4_000, 8_000]

    print(f"{'n':>8} | {'O(1)':>10} | {'O(log n)':>10} | {'O(n)':>10} | {'O(n log n)':>12} | {'O(n^2)':>10}")
    print("-" * 72)

    for n in sizes:
        arr = list(range(n))

        t_const = time_it(constant_time, arr)
        t_log = time_it(logarithmic_time, n)
        t_lin = time_it(linear_time, arr)
        t_nlogn = time_it(linearithmic_time, arr)
        cap = min(n, 500 + n // 4)  # cap grows with n so the quadratic trend is still visible
        t_quad = time_it(quadratic_time, arr[:cap])

        print(f"{n:>8} | {t_const*1e6:>9.2f}µs | {t_log:>10.6f} | {t_lin:>10.6f} | {t_nlogn:>12.6f} | {t_quad:>10.6f}")

    print("\nNote: O(n^2) column uses a capped (but still growing) array size so the")
    print("demo finishes quickly — even so, notice it grows far faster than the rest.")


if __name__ == "__main__":
    main()
