# Big-O Practice: Identify the Complexity

Work out the time complexity of each snippet before revealing the answer. Assume `n` is the length of the input.

---

### 1.
```python
def snippet(arr):
    total = 0
    for x in arr:
        total += x
    return total
```
<details>
<summary>Answer</summary>

**O(n)** — a single pass over the array.
</details>

---

### 2.
```python
def snippet(arr):
    for i in range(len(arr)):
        for j in range(i, len(arr)):
            print(arr[i], arr[j])
```
<details>
<summary>Answer</summary>

**O(n²)** — even though the inner loop shrinks as `i` grows, the total number of iterations is still proportional to n²/2, and constants are dropped. This pattern (comparing every pair) is always quadratic.
</details>

---

### 3.
```python
def snippet(arr, target):
    low, high = 0, len(arr) - 1
    while low <= high:
        mid = (low + high) // 2
        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            low = mid + 1
        else:
            high = mid - 1
    return -1
```
<details>
<summary>Answer</summary>

**O(log n)** — this is binary search. The search space is cut in half on every iteration.
</details>

---

### 4.
```python
def snippet(arr):
    n = len(arr)
    if n <= 1:
        return arr
    mid = n // 2
    left = snippet(arr[:mid])
    right = snippet(arr[mid:])
    return merge(left, right)   # merge is O(n)
```
<details>
<summary>Answer</summary>

**O(n log n)** — this is merge sort. There are log n levels of recursion (since the array halves each time), and at each level the total work across all recursive calls is O(n) (the merge step). log n levels × O(n) per level = O(n log n).

Note: this snippet also uses O(n log n) extra space when you account for the space used by slicing (`arr[:mid]`) at every level — worth noting separately from time complexity.
</details>

---

### 5.
```python
def snippet(n):
    if n == 0:
        return 1
    return n * snippet(n - 1)
```
<details>
<summary>Answer</summary>

**O(n)** time, **O(n)** space. It's a single chain of recursive calls (not branching), so it's linear — but each call adds a frame to the call stack, so space is also O(n), unlike the iterative version which would be O(1) space.
</details>

---

### 6.
```python
def snippet(s):
    result = ""
    for char in s:
        result = result + char
    return result
```
<details>
<summary>Answer</summary>

**O(n²)**, not O(n) — this is the classic hidden-cost trap. Strings are immutable in Python, so `result + char` creates a brand-new string each time, copying everything before it. Doing this n times costs 1 + 2 + 3 + ... + n ≈ O(n²). The fix is to append characters to a list and `''.join(list)` at the end, which is O(n).
</details>

---

### 7.
```python
def snippet(arr):
    seen = set()
    for x in arr:
        if x in seen:
            return True
        seen.add(x)
    return False
```
<details>
<summary>Answer</summary>

**O(n)** time, **O(n)** space. Set lookups (`x in seen`) and insertions are O(1) on average, so a single pass with constant-time work per element is linear overall. This is the standard pattern for "detect duplicates" — see the [Hashing](../04-hashing) topic.
</details>

---

### 8.
```python
def snippet(n):
    if n <= 1:
        return n
    return snippet(n - 1) + snippet(n - 2)
```
<details>
<summary>Answer</summary>

**O(2ⁿ)** — naive recursive Fibonacci. Each call branches into two more calls, forming a binary tree of depth n. This is the canonical example of exponential blowup from redundant recomputation, and the canonical motivation for memoization (see [Dynamic Programming — 1D](../13-dp-1d)).
</details>

---

## Self-check

If you got 6 and 8 right without looking, you've got the core idea. If you missed them, re-read the "Common pitfalls" and "Recursion" sections of the [README](./README.md) — those two patterns (hidden per-operation costs, and recursive branching) are the ones that trip people up in real interviews, not the simple loop-counting cases.
