# Data Structures

A queue is first in first out (FIFO) so if you add remainders iterativeely to a queue, you will first pop the smallest digit of x when the queue has max length, if you continue popping the queue, you will get the reverse of x.

# Edge Cases
int in c++ is a 32 bit signed integer, so it can range from -2^31 to 2^31 - 1.

## Overflow
If the reversed integer overflows, the function will return 0. It can happen if 
* x = INT_MIN
* x has 10 digits and is its reverse is greater than INT_MAX
example:
1534236469 reversed is 9646324351 which is greater than INT_MAX
1534236469 < INT_MAX < 9646324351

# Efficient Solution
I did not realize at first that if you allow for a linear recursive function, you can compute the reverse number in a linear time.

Think of the example x = 1234
At each iteration we would like to see the following progress on answer:
* ans = 4
* ans = 43
* ans = 432
* ans = 4321

this sequence can easily be achieved with:
\[ans = 10*ans + remainder; ans_0 = 0\]


