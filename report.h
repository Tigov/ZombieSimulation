//CS-273-Final project
//ZOMBIE APOCALYPSE SIMULATOR
//Created by: Alaina Stockdill, Sakina Vidyarthi, Viktor Pisarenko

#ifndef REPORT_H
#define REPORT_H
#include <iostream>

//Report class

// this class is used to show useful information 
class Report {
public:
    Report() {}; //constructor

    void printReport(int time) { //the last thing to be printed, after everything runs 
        std::cout << "Total zombies: " << zombieCount << std::endl; //prints no. of zombies
        std::cout << "Total alarmed: " << alarmedCount << std::endl; //prints no. of alarmed
        std::cout << "Total ignorant: " << ignorantCount << std::endl; //prints no. of ignorant
        std::cout << "Simulator run time: " << time << std::endl; //prints day number
    }
    

//update the count
    void updateReport(int time, std::map<std::string, std::vector<Citizen*> > const & simville) { // outputs the amount of each type of citizen and at which time click
        //set counts back to 0 so we dont count duplicates
        zombieCount = 0;
        alarmedCount = 0;
        ignorantCount = 0;
        
        //Iterate through map to count each of the types
        for (auto itr = simville.begin(); itr != simville.end(); itr++) { //districts
            for (int i = 0; i < itr->second.size(); i++) { //for vector in each district

                        //update each value 
                if(itr->second[i]->getState() == "Ignorant"){ 
                    ignorantCount++;
                }
                if((itr->second[i])->getState() == "Alarmed"){
                    alarmedCount++;
                }
                if(itr->second[i]->getState() == "Zombie"){
                    zombieCount++;
                }
            }
        }

        //output useful information
        std::cout << std::endl;
        std::cout << "At time " << time << ": " << std::endl;
        std::cout << "Zombies: " << zombieCount << std::endl;
        std::cout << "Alarmed: " << alarmedCount << std::endl;
        std::cout << "Ignorant: " << ignorantCount << std::endl;
        std::cout << std::endl;
    }

    //getter function
    int getZombieCount() {
        return zombieCount;
    }

private:
    //different counts
    int zombieCount = 0;
    int alarmedCount = 0;
    int ignorantCount = 0;
};

#endif
