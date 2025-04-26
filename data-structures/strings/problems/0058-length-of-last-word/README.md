# 0058 Length of Last Word

Given a string `s` consisting of words and spaces, return the length of the last word in the string.

A *word* is a maximal substring consisting of non-space characters only.

---

#### Example 1:

> Input: s = "Hello World"  
> Output: 5

Explanation: The last word is `"World"` with length 5.

---

#### Example 2:

> Input: s = "   fly me   to   the moon  "  
> Output: 4

Explanation: The last word is `"moon"` with length 4.

---

#### Example 3:

> Input: s = "luffy is still joyboy"  
> Output: 6

Explanation: The last word is `"joyboy"` with length 6.

---

### Constraints:

- $1 \leq \text{s.length} \leq 10^4$
- `s` consists of only English letters and spaces `' '`.
- There will be at least one word in `s`.

---

# Solution

Main idea here is to iterate through the string, treating it as a sequence of space-separated words. The key thing is that the question wants the **length**, not the actual word—so we can skip a lot of unnecessary string operations.

Let’s do this **without using Python’s `split()` magic**.

---

## Initial Solution

First idea: just loop through the string and keep building up the current word in a string variable. Every time we hit a space, we reset the word. At the end, whatever’s left in that string is our last word—just return its length.

If `n = len(s)`, our time complexity is $O(n)$ and space complexity is **worst-case $O(n)$**, which happens when the input is a single word (no spaces). That’s because we’re building the word character by character and storing it.

---

## Optimizations

We can do better in two ways:

### 1. Reduce space to $O(1)$  
This is the **most important** optimization. We don’t actually need to store the last word—we only care about its length. So instead of keeping a string in memory, we just keep a counter (an `int`) that tracks the length of the last word we’ve seen. Super easy and way more efficient.

No string building = no heap allocations = cleaner and faster.

---

### 2. Iterate in reverse (early stopping in most cases)  
This doesn’t improve the worst-case time complexity (still $O(n)$), but in practice, it often finishes faster. 

The idea is:  
- Start from the end of the string  
- Skip trailing spaces (whitespaces left of the last non-trivial charachter in s)
- Start counting until we hit a space again  

That way, we avoid touching most of the string unless we really have to (like when the whole string is one long word with no spaces).

---

This two-step optimization gives you a clean, constant-space, linear-time solution that’s also fast in practice.
