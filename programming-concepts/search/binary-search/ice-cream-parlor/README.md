# ice-cream-parlor
View 'Algorithms: Solve 'Ice Cream Parlor' Using Binary Search' from HackerRank on youtube. 

# Problem:
Given a hashmap of ice cream options key names and value prices and an amount of money to spend, find a set of two ice creams that enable you to spend all your money. 

## Approach 1: Brute force
Compute all possible 2 element subsets, and for each determine if their prices add up to the money you want to spend. 

**Complexity:** $ O(n^2) $

## Approach 2:
Since the task is about determining if such a subset (a,b) exist ie given the map:

> I = {"chocolate": $5, "vanilla": $5}  

the value of the boolean

$$ |\{(a,b) : (a,b \in \text{I.keys}) \cap (I[a]+I[b] = \text{target}) \cap (a \neq b) \} | > 1 $$

We can do a single loop for the a, and determine if there exists a b by searching for a flavor whose price matches the  complement (target-a) on the sorted array. This search can be done using binary search! in log(n) time 

**Complexity:**  $O(n \times \log{n})$ 


