#include <iostream>
#include "bignum.h" 

using namespace std;

int main(){
    system("color b");
    
    bint a = {2, {2, 1}, 0}/*12*/, b = {2, {3, 1}, 1}/*-13*/; 

    system("cls & color c");

    cout << (b > a);

    system("pause");

    return 0;
}