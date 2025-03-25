#include <set>
#include <string>
#include <iostream>
#include <cassert>

using namespace std;



/*
 * Complete the 'palindrome' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

int palindrome(string s) {
    int n = s.size();
    set<string> palindromes;
    for (int i = 0 ; i < n ; i++){
        
        // Check ODD palindromes 
        // i is center index
        palindromes.insert(string(1, s[i]));
        for (int wide = 1; 0 <= i-wide && i+wide <= n-1; wide++){
            char left = s[i-wide];
            char right = s[i+wide];
            if (left == right){
                string odd_palindrome = s.substr(i- wide, 2*wide+1);
                palindromes.insert(odd_palindrome);
            } else {
                break; // no longer a palindrome
            }
        }
        
        // Check EVEN palindromes 
        int left_index = i;
        int right_index = i+1;
        if (s[left_index]!=s[right_index]){
            continue;
        }
        for (int wide = 0;  0<=left_index-wide && right_index+wide < n ; wide++){
            char left = s[left_index-wide];
            char right = s[right_index+wide];
            if (left==right){
                string even_palindrome = s.substr(left_index - wide, 2*wide+2);
                palindromes.insert(even_palindrome);
            } else {
                break;
            }
        }
        
    }
    cout << "palindromes: " << endl;
    for (auto p : palindromes){
        cout << p << endl;
    }
    return palindromes.size();

}

void test1(){
    string s = "aabaa";
    int ans = palindrome(s);
    assert(ans == 5);
}

int main()
{
    test1();
}
