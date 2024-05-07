//do NOT submit this file

//while you can modify this file to create your own test cases, make sure your submitted files can compile with the original unmodified version of this file

#include <iostream>
#include "ramenRestaurant.h"

using std::cout;
using std::endl;

int main()
{
    int* p = new int(123);
    int* q = p;
    cout << p << endl;
    cout << &p << endl;
    cout << *p << endl;
    cout << q << endl;
    cout << &q << endl;
    cout << *q << endl;

    *q = 456;
    cout << p << endl;
    cout << &p << endl;
    cout << *p << endl;
    cout << q << endl;
    cout << &q << endl;
    cout << *q << endl;
//    p = new int(1232);


    return 0;
}