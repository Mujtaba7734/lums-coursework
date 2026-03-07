#include <iostream>
using namespace std;

int main()
{
    int a= 7;
    int b = 8;
    int c = 9;
    int d = 10;
    
    string result1 = ( (a++ < --b) && (++c > d--) ) ? "Condition satisfied" : "Condition Unsatisfied";
    /* b is decremented by 1 before, b = 7 & a remains same because it is getting post-incremented
       comparing 7 < 7 gives false
       after comparing, a is now incremented to give a = 8
       in && (and) operator, if first expression is false, whole gives false
       so, the answer will be condition unsatisfied and second expression will not be checked 
       and no change to the value
       */  
     
    cout << "result1: " << result1 << ", a: "<< a << ", b: "<< b << ", c: "<< c <<", d: "<< d << endl;

    string result2 = ( (a-- < ++b ) || (--c > d++) )? "Condition satisfied" : "Condition Unsatisfied";
    /* a is unchanged, b is incremented before, b = 8, comparing a < b, 8 < 8 will be false
       now a in decremented, a = 7 
       OR operator, so sees second expression
       c is decremented before comparing, c = 7, d is unchanged
       comparing c > d, 7 > 10, which is false
       now, after comparing d is incremented to give 11
       both are false, so the condition is unsatisfied */

    cout << "result2: " << result2 << ", a: "<< a << ", b: "<< b << ", c: "<< c <<", d: "<< d << endl;
    
    int result3 = a++ + ++b * --c - d--;
    /* BODMAS, so multipliction first,c are both pre-incremented/ decremented,
       b is incremented, b = 9, c = 7, c is decremented
       so  7 + 63 -11  = 59 
       now, a is incremented, a =8, d is decremented 10*/
    cout << "result3: " << result3 << ", a: "<< a << ", b: "<< b << ", c: "<< c <<", d: "<< d << endl;
    
    return 0;
}