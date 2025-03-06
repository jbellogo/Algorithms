
# Maximum Cardinality of Independent Intervals subset
Given a set of n-ranges $S={(a_i, b_i) | i=1, 2, ..., n}$  find the size of the set $|S'|$ where:
$S' \subseteq S$  such that no two ranges in $S'$ overlap.

It is not a matroid!!!!

Our objective is to maximize the number of intervals in $S'$, so we will use a greedy algorothm which compares the right endpoints of the ranges.





