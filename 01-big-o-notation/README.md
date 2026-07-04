# Big-O Notation

Before writing a single data structure, you need a language for talking about how "good" an algorithm is. Big-O is that language. It describes how the **runtime** or **memory usage** of an algorithm grows as the input size grows — not the exact time in seconds (that depends on your CPU), but the *shape* of the growth curve.

## Why it matters

Two algorithms can both "work" and still be worlds apart in practice. Sorting 10 items with a bad algorithm and a good one both finish instantly. Sorting 10 million items is where the difference between O(n log n) and O(n²) turns "instant" into "will not finish in your lifetime."

Every data structure and algorithm in this repo will be described using Big-O. If this topic isn't solid, nothing after it will fully make sense — so take your time here.

## The core idea

We care about **growth rate as input size (n) approaches infinity**, and we ignore:
- Constants (`O(2n)` is written as `O(n)`)
- Lower-order terms (`O(n² + n)` is written as `O(n²)`, because for large `n`, the `n²` term dominates)

We keep only the term that grows fastest, because that's what determines behavior at scale.

## Common complexity classes (best to worst)

| Notation | Name | Example |
|---|---|---|
| O(1) | Constant | Accessing an array element by index |
| O(log n) | Logarithmic | Binary search |
| O(n) | Linear | Scanning an array once |
| O(n log n) | Linearithmic | Merge sort, quicksort (average) |
| O(n²) | Quadratic | Nested loop over the same array (bubble sort) |
| O(2ⁿ) | Exponential | Naive recursive Fibonacci, generating all subsets |
| O(n!) | Factorial | Generating all permutations |

Each step down this table is a **meaningfully different tier**, not a small difference. At n = 1,000,000: O(n) does a million operations. O(n²) does a trillion. That's the difference between milliseconds and hours.

## How to analyze code: count the operations

Rule of thumb: **look at your loops and recursive calls.**

**Rule 1 — Sequential statements add:**
```python
def example(arr):
    print(arr[0])       # O(1)
    for x in arr:        # O(n)
        print(x)
```
Total: O(1) + O(n) = O(n) (constants drop out)

**Rule 2 — Nested loops multiply:**
```python
def example(arr):
    for i in arr:         # O(n)
        for j in arr:     # O(n) for each i
            print(i, j)
```
Total: O(n) × O(n) = O(n²)

**Rule 3 — Loop that cuts the problem in half each time → O(log n):**
```python
def example(n):
    while n > 1:
        n = n // 2        # halves every iteration
```
If n starts at 1024, this loop runs only 10 times (2^10 = 1024). That's the signature of logarithmic growth.

**Rule 4 — Recursion: draw the recursion tree.**
For recursive functions, complexity = (number of calls) × (work per call). We cover this rigorously in the [Recursion](../05-recursion) topic, but the short version: a recursive function that makes 2 calls on a problem of size `n-1` each time (like naive Fibonacci) branches into roughly 2ⁿ total calls — hence O(2ⁿ).

## Space complexity

The same notation describes **memory**, not just time. Ask: how much *extra* space does the algorithm use relative to the input?

- Reversing an array in-place → O(1) extra space
- Creating a copy of the array → O(n) extra space
- Recursion also costs space: each call sits on the call stack, so a recursive function with a depth of `n` uses O(n) space even if it does no other allocation.

There is often a **time-space tradeoff**: you can frequently make something faster by using more memory (e.g. caching/memoization in the [DP topics](../13-dp-1d)) or use less memory at the cost of more time.

## Best, Average, and Worst Case

Big-O usually refers to **worst case** unless stated otherwise, but it's worth distinguishing:
- **Best case**: the friendliest possible input (e.g., searching for the first element in a list)
- **Average case**: expected performance over random inputs
- **Worst case**: the most adversarial possible input

Example: Quicksort is O(n log n) on average but O(n²) in the worst case (already-sorted input with a naive pivot choice). Both facts matter — this is why real-world quicksort implementations randomize the pivot.

## Common pitfalls

- **Confusing O(n) space with O(n) time.** They're independent axes — always state which one you mean.
- **Forgetting hidden costs.** `list.pop(0)` in Python looks like O(1) but is actually O(n), because every remaining element has to shift. String concatenation in a loop (`s = s + char`) is O(n) *per operation* in many languages because strings are immutable, making an O(n) loop of concatenations actually O(n²) overall.
- **Big-O is not "always faster in practice."** An O(n log n) algorithm can be slower than an O(n²) one for small `n`, because Big-O hides constant factors. It only guarantees behavior *as n grows large*.
- **Big-Θ vs Big-O vs Big-Ω.** Strictly, Big-O is an upper bound, Big-Ω is a lower bound, and Big-Θ is a tight bound (both). In casual industry usage (and in this repo), "Big-O" is almost always used the way Big-Θ is meant — as a description of actual growth, not just an upper limit. It's worth knowing the distinction exists even if nobody enforces it in interviews.

## Practice: identify the complexity

Solutions and explanations are in [`problems.md`](./problems.md). Try to work out the complexity of each snippet yourself before checking.

## Next topic

→ [Arrays](../02-arrays)
