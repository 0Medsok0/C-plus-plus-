#include<iostream>
#include<conio.h>
#include<stdlib.h>
using namespace std;


int main()
{
    setlocale(LC_ALL, "Russian");
    int x = 0;
    int count = 3;
    string pass;
    string key = "1234";
    while (x != 2) {
        cout << "Введите 1/2:" << endl;
        cout << "1. Ввести пароль" << endl;
        cout << "2. Изменить пароль" << endl;
        cout << "3. Выход" << endl;
        cout << "x = ";
        cin >> x;

        switch (x)
        {
        case 1:
            cout << "Введите пароль: ";
            cin >> pass;
            if (pass == key) {
                cout << "Добро пожаловать!" << endl;
                
            }
            else {
                count--;
                cout << "Неверно" << endl;
                cout << "Осталось попыток: " << count << endl;
            }
            break;
        case 2:
            std::cout << "Введите новый пароль: ";
            cin >> pass;
            count = 3;
            break;
        case 3:
            std::cout << "Нажат выход" << "\n";
            break;
        default:
            std::cout << "Нет такой опции" << "\n";
            break;
        }
        if (count <= 0) {
            cout << "Несанкционированный доступ!" << endl;
        }
        if (x == 3)
            break;
    }
}
