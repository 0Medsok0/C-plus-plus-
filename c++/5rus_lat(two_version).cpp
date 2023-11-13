#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
using namespace std;
#define Nlayers 3      // число слоев
#define Nmaxneu 30       // максимальное число нейронов в слое
#define Nminneu 4        // минимальное число нейронов в слое
#define Ntemp 10         // число шаблонов
//#define RAND_MAX 1 

ifstream f; //файловый поток для ввода
int m;


void loadPatterns(float pattern[Ntemp][Nmaxneu], float target[Ntemp][Nminneu])
{
    
 int i,j,k;
 f.open("patterns.txt"); //открытие файла
 if (!f) {
 cout << "Can't open file!";
 }
 else {
 while (!f.eof()) {
    
 for(i=0;i<Ntemp;i++){
    f >> m; //считываем номер шаблона, пропускаем его он значится индексом i
    for(j=0;j<Nmaxneu;j++){
        f >> m;  //считываем шаблон
        pattern[i][j] = m;
    }
    for(k=0; k<Nminneu;k++){
        f >> m;                 // метка шаблона, target цель для нейроной сети
        target[i][k]=m;
    }
 }
    cout<<"Template ready!"<<endl;
 }
 f.close(); //закрытие файла
 }
}

void ForwardPass(float net[Nlayers][Nmaxneu], float out[Nlayers][Nmaxneu], int struc[Nlayers], float w[Nlayers][Nmaxneu][Nmaxneu]){
    int i,j,k;
    for(k=1;k<Nlayers;k++){                                 // цикл слоев
        for(i=0;i<struc[k];i++){                            // цикл текущего слоя
            net[k][i]=0;                                    // ставим значения нейрона на 0, чтобы вычислить его взвешанную сумму        
            for(j=0;j<struc[k-1];j++)                       // цикл нейронов предыдущего слоя
                net[k][i]+=out[k-1][j]*w[k][j][i];      // вычисляем взвешенную сумму
            out[k][i]=1/(1+exp(-net[k][i]));            // выполняем активацию нейрона
        }
    }
}




int main(void)
{
    int STRUC[Nlayers]= {30,25,4}; //– структура сети (количество нейронов в каждом слое)
    //i – номер нейрона в текущем слое (i=1… Nн.max)
    //j – номер нейрона в предыдущем слое (j=1… Nн.max)
    //k – номер слоя (k=0…Nсл)
    //m – номер шаблона (m=1...Nш)
    // flg - для проверки данных, tab - табуляция в печати одномерного цикла
    int i, j, k, m, flg = 0, tab=0;
    //NET[0…Nсл, 1…Nн.max] – массив величин NET для нейронов;
    // OUT[0…Nсл, 1…Nн.max] – массив выходов нейронов;
    // W[1…Nсл, 1…Nн.max, 1…Nн.max] – массив весов;
    // PATTERN[1…Nш, 1…Nн.max] – массив входных шаблонов;
    // TARGET[1…Nш, 1… Nн.min] – массив целевых значений.
    float NET[Nlayers][Nmaxneu], OUT[Nlayers][Nmaxneu], W[Nlayers][Nmaxneu][Nmaxneu];
    float PATTERN[Ntemp][Nmaxneu], TARGET[Ntemp][Nminneu];
    float th; // порог выходного слоя
    char ch; //код команды
 
    for(k = 0; k < Nlayers; k++)
        for(j = 0; j < Nmaxneu; j++)
            for(i = 0;i < Nmaxneu; i++)
                W[k][j][i] = -1 + 2 * (float)rand()/RAND_MAX;           // генерация весовых коэффициентов нейроной сети
  
    
    
    do {                                                                // отображение меню
        cout << "\nMenu:" << endl;
        cout << "1: Load patterns" << endl;
        cout << "2: Calc pattern" << endl;
        cout << "3: Exit" << endl;
        cout << "\n Select menu item: ";
        cin >> ch;

        switch (ch) {                                                   // выбор меню
        case '1':
            loadPatterns(PATTERN, TARGET);
            break;
        case '2':
            for(i = 0; i<Ntemp;i++)
                for(j = 0; j<Nmaxneu;j++)
                     flg +=PATTERN[i][j];                              //для проверки загрузки данных из файла
            
            if(flg >= 2){
                do{cout<<"Number template(1-10): "; cin>>m;            // Выбор шаблона
                }while(m <1 && m>Ntemp);cout<<endl;

                for(i=0;i<Nmaxneu;i++)
                    OUT[0][i] = PATTERN[m-1][i];                       // Загрузка патерна в нулевой слой
                
                ForwardPass(NET,OUT,STRUC,W);                           // прогоняем патерн через нейросеть
                
                cout<<endl<<"Input: "<<endl;
                for(i=0;i<Nmaxneu;i++){cout<<OUT[0][i]<<" "; tab++;    // Печать входных данных 5x6
                    if(tab == 5){cout<<endl;tab = 0;}}
                
                cout<<endl<<"Target: ";
                for(i=0;i<Nminneu;i++) cout<<TARGET[m-1][i]<<" ";      // Выводим цель
                cout<<endl;

                th = 0.7;  // пороговое значение все числа меньшие th равны 0, большие равны 1, получим код распозноного изображения
                cout<<endl<<"Output: ";
                for(i=0;i<Nminneu;i++){
                    if(OUT[Nlayers][i]>=th)  
                        cout<<1<<" ";       // код
                    else
                        cout<<0<<" ";       // код
                }
                cout<<endl<<"(";
                for(i=0;i<Nminneu;i++)
                    cout<<OUT[Nlayers][i]<<" "; // Выходной слой
                cout<<")"<<endl;
            }
            else
                cout<<"go load patterns"; // выводим сообщение если данные не загружены

            break;
        default:
            cout << "Wrong item!" << endl;
            break;
        }
    } while (ch != '3');

    return 0;

}
