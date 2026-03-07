#include <iostream>
#include <limits>
using namespace std;

int main(){
    cout << "Range of char is from " << numeric_limits<char>::min() << " to " << numeric_limits<char>::max() <<endl;
    cout << "Range of int is from " << numeric_limits<int>::min() << " to " << numeric_limits<int>::max() <<endl;
    cout << "Range of float is from " << numeric_limits<float>::min() << " to " << numeric_limits<float>::max() <<endl;
    cout << "Range of double is from " << numeric_limits<double>::min() << " to " << numeric_limits<double>::max() <<endl;
    return 0;  
}