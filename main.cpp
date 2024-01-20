#include <iostream>
#include "bignum.h" 

using namespace std;

int main(){
    system("color b");
    
    bint a, b;

    cin >> a >> b;

    system("cls & color c");

    cout << a << " - " << b << " = " << a - b << '\n';
    cout << b << " - " << a << " = " << b - a << '\n';
    cout << a << " + " << b << " = " << a + b << '\n';
    cout << a << " * " << b << " = " << a * b << '\n';
    cout << a << " / " << b << " = " << a / b << '\n';
    cout << b << " / " << a << " = " << b / a << '\n';
    
    cout << '\n';
    cout << a << " < " << b;
    a < b ? cout << " -> True" : cout << " -> False";
    cout << '\n';
    
    cout << a << " > " << b;
    a > b ? cout << " -> True" : cout << " -> False";
    cout << '\n';

    cout << b << " < " << a;
    b < a ? cout << " -> True" : cout << " -> False";
    cout << '\n';

    cout << b << " > " << a;
    b > a ? cout << " -> True" : cout << " -> False";
    cout << '\n';

    system("pause");

    return 0;
}