#include<iostream>
#include<cmath>
using namespace std;

int main() {
    char op;
    float num1, num2;

    cout << "Enter operator: +, -, *, /, s (sine), c (cosine), t (tangent), o (cotangent), p (percentage), r (square root), q (square): ";
    cin >> op;

    switch(op) {
        case '+':
            cout << "Enter two operands: ";
            cin >> num1 >> num2;
            cout << num1+num2;
            break;

        case '-':
            cout << "Enter two operands: ";
            cin >> num1 >> num2;
            cout << num1-num2;
            break;

        case '*':
            cout << "Enter two operands: ";
            cin >> num1 >> num2;
            cout << num1*num2;
            break;

        case '/':
            cout << "Enter two operands: ";
            cin >> num1 >> num2;
            if(num2 != 0.0)
                cout << num1/num2;
            else
                cout << "Error! Division by zero is not allowed.";
            break;

        case 's':
            cout << "Enter a number: ";
            cin >> num1;
            cout << sin(num1);
            break;

        case 'c':
            cout << "Enter a number: ";
            cin >> num1;
            cout << cos(num1);
            break;

        case 't':
            cout << "Enter a number: ";
            cin >> num1;
            cout << tan(num1);
            break;

        case 'o':
            cout << "Enter a number: ";
            cin >> num1;
            if(tan(num1) != 0.0)
                cout << 1/tan(num1);
            else
                cout << "Error! Cotangent of zero is not defined.";
            break;

        case 'p':
            cout << "Enter two operands: ";
            cin >> num1 >> num2;
            cout << (num1/num2)*100;
            break;

        case 'r':
            cout << "Enter a number: ";
            cin >> num1;
            if(num1 >= 0.0)
                cout << sqrt(num1);
            else
                cout << "Error! Square root of a negative number is not defined.";
            break;

        case 'q':
            cout << "Enter a number: ";
            cin >> num1;
            cout << num1*num1;
            break;

        default:
            cout << "Error! Operator is not correct";
            break;
    }

    return 0;
}
