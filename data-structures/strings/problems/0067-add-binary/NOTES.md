# Notes

to_string makes the biggest differnce, it is about 5 times slower than integer + '0' to stringify. 

this is slow:

```cpp
...
int remainder = carry%2;
carry/=2;
ans  = to_string(remainder) + ans;
...
```

This is fast:

```cpp
...
int remainder = carry%2;
carry/=2;
ans  = remainder+'0';
...
```


