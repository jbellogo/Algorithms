# Run Length ecndoing 

example
- "aaaabbccc" => 4a2b3c

Let's think of a few more examples:
- "abcd" => 1a1b1c1d
- "" = > 0
- aaaabbccca => 4a2b3c1a // because order matters, we are not just aggregating letter counts in a hash map.


## Solution:
simple iterative, we will have a count and compare items to the next one on the input list, if the match increase the counter, if not save the (count,letter) pair in string format and restart the count. 
