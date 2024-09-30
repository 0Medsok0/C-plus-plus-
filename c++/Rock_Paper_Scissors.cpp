#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
    srand(time(0));

    int playerChoice, computerChoice;

    std::cout << "Enter your choice (1 for rock, 2 for paper, 3 for scissors): ";
    std::cin >> playerChoice;

    computerChoice = rand() % 3 + 1;

    std::cout << "Computer's choice: ";
    switch (computerChoice) {
        case 1:
            std::cout << "rock\n";
            break;
        case 2:
            std::cout << "paper\n";
            break;
        case 3:
            std::cout << "scissors\n";
            break;
    }

    if (playerChoice == computerChoice) {
        std::cout << "It's a tie!\n";
    } else if ((playerChoice == 1 && computerChoice == 3) ||
               (playerChoice == 2 && computerChoice == 1) ||
               (playerChoice == 3 && computerChoice == 2)) {
        std::cout << "You win!\n";
    } else {
        std::cout << "Computer wins!\n";
    }

    return 0;
}
