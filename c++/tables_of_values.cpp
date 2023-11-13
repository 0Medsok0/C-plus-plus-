xn  xk             S(x)                  n        Y(x)

0.1  1     1+3x^2 +...+2n+1/n!*x^2^n     14    (1 + 2x^2)e^x^2


#include<iostream>
#include<conio.h>
#include<stdlib.h>
using namespace std;

int main() {
	double xn = 0.1, x;
	double xk = 1;
	int n = 14;
    double h = (xk - xn) / 10;	// шаг
	double S = 0;		//  для накопления суммы
	double Yx;
	int fi=1;
	x = xn;
	cout << "i" << "\t" << "x" << "\t" << "S" << "\t" << "Yx" << "\t"<< "| Yx - S |"<<endl;
	for (int i = 0; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			fi = fi * j; // факториал
		}
		S += ((2 * i + 1) / fi) * pow(x, 2 * i);			// приближенное решение
		Yx = (1 + 2 * pow(x, 2)) * exp(pow(x, 2));		// точное решение
		cout << i << "\t" << x << "\t" << S << "\t" << Yx << "\t"<<abs(Yx - S )<<endl;//  печать значений
		fi = 1;			// обновляем факториал для селдующего подсчета
		x += h;			//  увеличиваем икс
	}
}
