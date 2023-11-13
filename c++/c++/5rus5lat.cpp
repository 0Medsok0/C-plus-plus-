#include <iostream>
#include <fstream>
#include <cmath>

const int Nсл = 4;
const int Nн_max = 30;
const int Nн_min = 4;
const int Nш = 10;

int STRUC[Nсл] = {30, 30, 25, 4};

float NET[Nсл + 1][Nн_max + 1];
float OUT[Nсл + 1][Nн_max + 1];
float W[Nсл][Nн_max + 1][Nн_max + 1];
float PATTERN[Nш][Nн_max + 1];
float TARGET[Nш][Nн_min];

void InitializeWeights() {
    for (int k = 0; k < Nсл; k++) {
        for (int i = 1; i <= STRUC[k + 1]; i++) {
            for (int j = 1; j <= STRUC[k]; j++) {
                W[k][j][i] = static_cast<float>(-1 + 2 * rand() / static_cast<float>(RAND_MAX));
            }
        }
    }
}

void ForwardPass() {
    for (int k = 0; k < Nсл; k++) {
        for (int i = 1; i <= STRUC[k + 1]; i++) {
            NET[k + 1][i] = 0;
            for (int j = 1; j <= STRUC[k]; j++) {
                NET[k + 1][i] += OUT[k][j] * W[k][j][i];
            }
            OUT[k + 1][i] = 1 / (1 + std::exp(-NET[k + 1][i]));
        }
    }
}

int main() {
    int choice;
    std::ifstream input;
    std::ofstream output;
    input.open("patterns.txt");
    output.open("output.txt");

    while (1) {
        std::cout << "Menu:" << std::endl;
        std::cout << "1: Load patterns" << std::endl;
        std::cout << "2: Calc pattern" << std::endl;
        std::cout << "3: Exit" << std::endl;
        std::cin >> choice;

        switch (choice) {
            case 1:
                // Load patterns
                for (int m = 0; m < Nш; m++) {
                    for (int i = 0; i < Nн_max; i++) {
                        input >> PATTERN[m][i];
                    }
                    for (int j = 0; j < Nн_min; j++) {
                        input >> TARGET[m][j];
                    }
                }
                break;
            case 2:
                // Calc pattern
                int k;// Perform forward pass
                ForwardPass();
                // Output results
                for (int i = 1; i <= STRUC[k + 1]; i++) {
                    output << OUT[Nсл][i] << " ";
                }
                output << std::endl;
                break;
            case 3:
                // Exit
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    input.close();
    output.close();

    return 0;
}
