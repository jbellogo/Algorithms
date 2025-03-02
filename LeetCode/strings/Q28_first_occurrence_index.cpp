#include <string>

using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.length() > haystack.length()){
            return -1; // not feasible, space issue
        }
        // i is possible starting point of mathcing strings in haystack
        for (int i = 0; i < haystack.length(); i++){
            // attempt to math all of needle starting at that position 
            bool iisAns = true;
            for (int j = 0; j < needle.length(); j++){
                if (i+j >= haystack.length()){
                    return -1;  // not feasible, space issue
                }
                if (haystack[i+j] != needle[j]){
                    iisAns = false;
                    break; // efficiency form 3ms to 1ms of runtime. 
                }
            }
            if (iisAns) {
                return i;
            }
        }
        return -1;
    }
};