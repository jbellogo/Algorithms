# Climbing Stairs

You are climbing a staircase. It takes `n` steps to reach the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

---

## Solution

This is a classic **dynamic programming** problem. At any step `n`, the number of ways to reach it is the sum of:
- The ways to reach step `n - 1` (by taking a single step), and
- The ways to reach step `n - 2` (by taking a step of size two).

You might be tempted to also consider taking two single steps starting from step `n - 2`, but that path already passes through step `n - 1`, so it's already accounted for in the first case.

There are several ways to implement the solution:

1. **Naive recursive approach**  
   - Time: $O(2^n)$  
   - Space: $O(n)$ (due to the call stack)

2. **Recursive with memoization**  
   - Time: $O(n)$  
   - Space: $O(n)$  

3. **Iterative with a list**  
   - Time: $O(n)$  
   - Space: $O(n)$  

4. **Iterative with two variables (`last` and `second_last`)**  
   - Time: $O(n)$  
   - Space: $O(1)$ (optimal)

> **Note:** Iterative solutions are often more efficient than their recursive counterparts—not necessarily in time complexity, but in overhead and clarity. Transitioning from recursion to iteration helps expose the structure of the recurrence more clearly and the fact that we know it will take n steps to get our solution. In this case, the problem reveals a classic *second-order linear recurrence*.
