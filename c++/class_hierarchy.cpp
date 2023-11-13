#include<iostream>
#include<conio.h>
#include<stdlib.h>
using namespace std;

// show - метод выводит атрибут класса и наследуемые атрибуты
// каждый класс имеет констурктор по умолчанию и иницилизирующий конструтор
// там где наследование в конструторе выполняется иницилизация из базовых классов
class B1 {

	int b1;

public:

	B1() {};    // конструктор по умолчанию

	B1(int b10) { b1 = b10; }       // иницилизирующий конструктор

	void show_B1() { cout << "B1 = " << b1 << " "; }
};

class B2 {

	int b2;

public:

	B2() {};

	B2(int b20) { b2 = b20; }

	void show_B2() { cout << "B2 = " << b2 << " "; }
};

class D1 : protected B1 {

	int d1;

public:

	D1(int x, int y) :B1(y) { d1 = x; }

	void show_D1() {
		cout << "D1 = " << d1 << " ";

		show_B1();

	}
};

class D2 : public B1 {

	int d2;

public:

	D2(int x, int y) : B1(y) { d2 = x; };


	void show_D2() {
		cout << "D2 = " << d2 << " ";

		show_B1();
	}
};

class D3 : protected D2, protected B2 {

	int d3;

public:

	D3(int x, int y, int z, int i) : D2(y, z), B2(i) { d3 = x; };

	void show_D3() {
		cout << "D3 = " << d3 << " ";

		show_D2();
		show_B2();
	}
};
class D4 : public D1, public D3 {

	int d4;

public:

	D4(int x, int y, int z, int i, int j, int k, int m) : D1(y, z), D3(i, j, k, m) { d4 = x; };

	void show_D4() {
		cout << "D4 = " << d4 << " ";

		show_D1();
		show_D3();
	}
};



int main() {
	setlocale(LC_ALL, "Russian"); // Русская локализация консоли
	D4 Dd4(100, 200, 300, 400, 500, 600, 700);
	cout << "Иерархия D4: ";
	Dd4.show_D4();
	//getch();
	cout << endl;
	system("pause");
	return 0;
}
