1)Программа, которая проверяет знание таблицы умножения. Программа просит ввести 2 числа, затем запрашивает результат их умножения.
Пользователь вводит ответ. Если ответ правильный, программа сообщает об этом, если ответ неверный, программа выводит правильный ответ.

#include <iostream>
using namespace std;

int main()
{
int first_number, second_number, result, r;
cout << "Enter the first number: "; // вводим первое число
cin >> first_number;
cout << "Enter the second number: "; // вводим второе число
cin >> second_number;
result = first_number * second_number; //реузльтат
cout << first_number << " x " << second_number << " = ";
cin >> r; // вводим результат
if (r != result) // если результат равен результату
cout << "Incorrect "; // то выводим правильно
else // иначе
cout << "correct "; // выводим правильно
cout << result;
return 0;
}

2)В стандартном потоке даны три строки, разделённые пробелом.
Каждая строка состоит из строчных латинских букв и имеет длину не более 30 символов.
Выведите в стандартный вывод лексикографически минимальную из них.
// Пример :
// m mm mmm
// Ответ : m


#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::string str1, str2, str3;
    std::cin >> str1 >> str2 >> str3;
    std::cout << std::min({str1, str2, str3}) << std::endl;
    return 0;
}

3)На вход вашей программе в стандартном вводе даны действительные коэффициенты _A_, _B_ и C уравнения _Ax² + Bx + C = 0_. 
Выведите все его различные действительные корни в любом порядке. Гарантируется, что хотя бы один из коэффициентов не равен нулю

#include <iostream>
#include <cmath>

int main() {
    double A, B, C;
    std::cin >> A >> B >> C;

    double discriminant = B * B - 4 * A * C;

    if (discriminant > 0) {
        double root1 = (-B + sqrt(discriminant)) / (2 * A);
        double root2 = (-B - sqrt(discriminant)) / (2 * A);
        std::cout << root1 << " " << root2 << std::endl;
    } else if (discriminant == 0) {
        double root = -B / (2 * A);
        std::cout << root << std::endl;
    }

    return 0;
}


4)На вход вашей программе в стандартном вводе даны действительные коэффициенты _A_, _B_ и C уравнения _Ax² + Bx + C = 0_.
Выведите все его различные действительные корни в любом порядке. Гарантируется, что хотя бы один из коэффициентов не равен нулю

#include <iostream>
#include <cmath>

int main() {
    double A, B, C;
    std::cin >> A >> B >> C;

    double discriminant = B * B - 4 * A * C;
    if (discriminant > 0) {
        double root1 = (-B + std::sqrt(discriminant)) / (2 * A);
        double root2 = (-B - std::sqrt(discriminant)) / (2 * A);
        std::cout << root1 << " " << root2;
    } else if (discriminant == 0) {
        double root = -B / (2 * A);
        std::cout << root;
    }
  
    return 0;
}

5)Дана строка. Найдите в этой строке второе вхождение буквы **f** и выведите индекс этого вхождения. 
Если буква **f** в данной строке встречается только один раз, выведите число -1, а если не встречается ни разу, выведите число -2. Индексы нумеруются с нуля

#include <iostream>
#include <string>
using namespace std;

int main() {
    string str;
    cin >> str;
    
    int count = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == 'f') {
            count++;
            
            if (count == 2) {
                cout << i << endl;
                return 0;
            }
        }
    }
    
    if (count == 1) {
        cout << -1 << endl;
    } else {
        cout << -2 << endl;
    }
    
    return 0;
}

6)На вход дано натуральное число _N_. Выведите его в двоичной системе счисления без ведущих нулей
  
#include <iostream>
#include <bitset>
using namespace std;

//1000
//1111101000

int main() {
    int N;
    cin >> N;
    cout << bitset<32>(N).to_string().substr(bitset<32>(N).to_string().find('1')) << endl;
    return 0;
}

7)
Ограничение по времени 1 сек
Ограничение по памяти 256мб

Окочив чертеж и подписав все цифры, Александров со спокойной отчетливостью назвал все линии и все размеры,спрятал мелок в карман и по строевому вытянулся,
глядя в холодные глаза полковника.Александр Куприн."Юнкера".Дополнительное задание,полученное Алексеем от строгово учителя,было следующим:
требовалось выбрать на плоскости точку и провести через нее n различных прямых. После этого нужно было построить m различных окружностей с центром в отмеченной точке.
На сколько частей все линии делят плоскоть?

Формат фходных данных:
Две строки входных данных содержат два неотрицательных целых числа n и m
(0 <=n,m <=10^8)
    
#include <iostream>

int main() {
    int n, m;
    std::cin >> n >> m;
    int parts = (n * (n + 1) / 2) * (m * (m + 1) / 2);
    std::cout << parts << std::endl;
    return 0;
}

8) Polindrom Function

// Enter a string: ded
// The entered string is a palindrome.


#include <iostream>
#include <string>
using namespace std;

bool IsPalindrom(string str) {
    for (int i = 0; i < str.length() / 2; i++) {
        if (str[i] != str[str.length() - 1 - i]) {
            return false;
        }
    }
    return true;
}

int main() {
    string input;
    cout << "Enter a string: ";
    cin >> input;
    
    if (IsPalindrom(input)) {
        cout << "The entered string is a palindrome." << endl;
    } else {
        cout << "The entered string is not a palindrome." << endl;
    }
    
    return 0;
}

9) //Polindrom(2)
    
// Напишите функцию, которая* называется *PalindromFilter*
// * возвращает *vector<string>*
// * принимает *vector<string>* words и *int minLength* и возвращает все строки из вектора words, которые являются палиндромами и имеют длину не меньше *minLength*

//Result:
    
// level 
// stats


#include <iostream>
#include <vector>

using namespace std;

bool isPalindrome(string str) {
    int len = str.length();
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return false;
        }
    }
    return true;
}

vector<string> PalindromFilter(vector<string>& words, int minLength) {
    vector<string> result;
    for (string word : words) {
        if (word.length() >= minLength && isPalindrome(word)) {
            result.push_back(word);
        }
    }
    return result;
}

int main() {
    vector<string> words = {"level", "hello", "stats", "word"};
    int minLength = 4;
    vector<string> filteredWords = PalindromFilter(words, minLength);
    for (string word : filteredWords) {
        cout << word << endl;
    }
    return 0;
}

10)

// функция *MoveStrings*, которая принимает два вектора строк,
// *source* и *destination*, и дописывает все строки из первого вектора в конец второго.
// После выполнения функции вектор *source* должен оказаться пустым.

//Result: Барнаул Новосибирск Уфа Томск

#include <iostream>
#include <vector>
#include <string>

void MoveStrings(std::vector<std::string>& source, std::vector<std::string>& destination) {
    destination.insert(destination.end(), source.begin(), source.end());
    source.clear();
}

int main() {
    std::vector<std::string> source = {"Уфа", "Томск"};
    std::vector<std::string> destination = {"Барнаул", "Новосибирск"};
    
    MoveStrings(source, destination);
    
    // Print the contents of destination
    for(const auto& str : destination) {
        std::cout << str << " ";
    }
    
    std::cout << std::endl;

11)
//функция *void Reverse(vector<int>& v)*,
//которая переставляет элементы вектора в обратном порядке


// 1 2 3 4 5 reverse to 5 4 3 2 1  

#include <iostream>
#include <vector>
#include <algorithm>

void Reverse(std::vector<int>& v) {
    std::reverse(v.begin(), v.end());
}

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    Reverse(v);
    
    for (int num : v) {
        std::cout << num << " ";
    }
    
    return 0;
}
    
    return 0;
}

12)
//функция *vector<int> Reversed(const vector<int>& v)*, возвращающуя копию вектора v, в которой числа переставлены в обратном порядке.

// 1 2 3 4 5 reversing  5 4 3 2 1


#include <iostream>
#include <vector>

std::vector<int> Reversed(const std::vector<int>& v) {
  std::vector<int> reversed_v(v.rbegin(), v.rend());
  return reversed_v;
}

int main() {
  std::vector<int> original_v = {1, 2, 3, 4, 5};
  std::vector<int> reversed_v = Reversed(original_v);

  // Print the reversed vector
  for (int num : reversed_v) {
    std::cout << num << " ";
  }

  return 0;
}

13)
// Дано n вещественных чисел. Определить, образуют ли они возрастающую последовательность

// Числа образуют возрастающую последовательность.

#include <iostream>
#include <vector>

bool isIncreasingSequence(std::vector<double> numbers) {
    for (int i = 1; i < numbers.size(); i++) {
        if (numbers[i] <= numbers[i-1]) {
            return false;
        }
    }
    return true;
}

int main() {
    // Example usage
    std::vector<double> numbers = {1.2, 2.4, 3.6, 4.8};
    bool isIncreasing = isIncreasingSequence(numbers);
    if (isIncreasing) {
        std::cout << "Числа образуют возрастающую последовательность." << std::endl;
    } else {
        std::cout << "Числа не образуют возрастающую последовательность." << std::endl;
    }
    
    return 0;
}
