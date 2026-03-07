#include <iostream>
#include <limits>
using namespace std;

int main(){

    /*  prints the range of the datatype int
        adding 1 in max value resets it as it is sent back to the beginning value like adding 1 + 1 in base of 2 returns 10
        subtracting 1 from the min value makes the value to the max value like subtracting 1 from 11 in base of 2 returns 01*/ 
    int maxrange = numeric_limits<int>::max();
    int minrange = numeric_limits<int>::min();
    cout << "Max range: " << maxrange << endl;
    cout << "Min range: " << minrange << endl;
    maxrange +=1;
    minrange -=1;
    cout << "Max range: " << maxrange << endl;
    cout << "Min range: " << minrange << endl;

    return 0;
}