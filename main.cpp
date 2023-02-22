//
//  main.cpp
//  ConsoleWheel
//
//  Created by Ben Schwartz on 2/22/22.
//

#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <string>
#include <fstream>
#include <vector>
#include "time.h"



#define DELAY 150




// Function to creating loading bar
void loadingBar(size_t size)
{
    char a = '-', b = '*';
    
    std::cout.precision(3);
    
    size_t count = 0;
    
    
    for (size_t i = 1; i < size; ++i) {
        printf("\t\t\t");
        
        for (size_t j = 0; j < i; ++j) std::cout << a;
        for (size_t j = 0; j < size - i; ++j) std::cout << b;

        std::cout << "\r" << std::flush;
        
        for (size_t j = 1; j < DELAY; ++j) {
            
            for (size_t k = 0; k < 12; ++k)
                std::cout << char(rand() % 93 + 33);
            
            double pct = double(++count) / double((size * DELAY));
            pct *= 100;
            
            pct = pct < 10 ? std::round( pct * 100.0 ) / 100.0 : std::round( pct * 1000.0 ) / 1000.0;
            std::cout <<  " [" << pct << "%]";
            
            
            std::cout << "\r" << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
}

std::string get_winner(std::ifstream &str) {
    srand(static_cast<unsigned int>(time(NULL)));
    
    struct Choice { std::string name; size_t pct; };
       
    std::vector<Choice> choices;
    
    std::string choice;
    size_t sum = 0;
    
    while (str >> choice) {
        if (choice.at(0) == '#') break;
        
        size_t pct;
        str >> pct;
        sum += pct;
        choices.push_back({choice, pct});
        
    }
    if (sum > 100) {
        std::cout << "error: sum over 100\n";
        exit(1);
    }
    else if (sum < 100)
        choices.push_back({"selection not made", 100 - sum});
    
    int num = static_cast<int>(rand() % 100 + 1);
    
    std::string winner = "";
    
    for (Choice &c: choices) {
        num -= c.pct;
        if (num < 0) {
            winner = c.name;
            break;
        }
    }
    if (winner == "")
        winner = choices.back().name;
    
    return winner;
}

int main() {
    
    std::ifstream str("in.txt");

    if (!str.is_open()) {
        std::cout << "error opening 'in.txt', make sure it exists and is formatted correctly";
        exit(1);
    }
    
    
    
    system("clear");
    
    std::cout << "\n\n\n\n\t\t\tDoing good calculation...\n\n\t\t\r" << std::flush;
    
    loadingBar(30);
    
    system("clear");
    
    try {
        std::cout << "------------------------------\n";
        std::cout << "WINNER:    ";
        std::string winner = get_winner(str);
        for (size_t i = 0; i < winner.size(); ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << winner[i] << std::flush;
        }
        std::cout << "\n-------------------------\nProcess completed.";
    } catch (std::exception e) {
        std::cout << "usage: ./wheel \n***(make sure in.txt is formatted correctly)\n";
    }

    return 0;
}

