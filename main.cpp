//CS-273-1 -Final project
//ZOMBIE APOCALYPSE SIMULATOR
//Created by: Alaina Stockdill, Sakina Vidyarthi, Viktor Pisarenko
//12-14-2020

//Main

#include <iostream> //header files for file io
#include <string> //for string
#include <map> //for STL map
#include <ctime> //for seeding random 

#include "zombie_simulator.h" 
#include "zombie.h"
#include "alarmed.h"
#include "citizen.h"
#include "ignorant.h"
#include "report.h"

//start of main function
int main() {
    srand(time(NULL)); //seed current time
    int maxTime; //variable for total days simulation lasts
    int X; //for probability an ignorant person becomes a zombie
    int Y; //for probability an ignorant person becomes alarmed
    int Z; //for the probability an alarmed person becomes a zombie
    int Q; //for probability a citizen moves districts

    std::cout << "Welcome to the Zombie Apocalypse Simulator!" << std::endl;
    std::cout << "Please enter how many days you would like the simulator to run: ";
    std::cin >> maxTime;
    std::cout << "Please enter the probability an ignorant person becomes a zombie: ";
    std::cin >> X; 
    std::cout << "Please enter the probability an ignorant person becomes alarmed: ";
    std::cin >> Y;
    std::cout << "Please enter the probability an alarmed person becomes a zombie: ";
    std::cin >> Z;
    std::cout << "Please enter the probability a citizen moves districts: ";
    std::cin >> Q;
    
    ZombieSim simulator(maxTime, X, Y, Z, Q); //calling zombie simulator object to pass the probabilities
    simulator.runSim(); //calling simulator to run the simulation

    return 0;
}
 //end of main function