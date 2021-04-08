//CS-273-Final project
//ZOMBIE APOCALYPSE SIMULATOR
//Created by: Alaina Stockdill, Sakina Vidyarthi, Viktor Pisarenko

//Zombie Simulator class

#include <string> //header file for string
#include <map> //STL MAP
#include <queue> //STL QUEUE
#include <vector> //STL VECTOR
#include <list> //STL LIST
#include <ctime> //SEED CURRENT TIME
#include <deque> //STL DEQUE

#include "citizen.h"
#include "zombie.h"
#include "ignorant.h"
#include "alarmed.h"
#include "report.h"


#ifndef ZOMBIE_SIMULATOR_H
#define ZOMBIE_SIMULATOR_H

//start of ZombieSim class
class ZombieSim {
private:
    int clock; //stores time click
    int maxTime; //stores maximum days of simulation
    int X; //Probability a ignorant turns into a zombie
    int Y; //Probability an ignorant turns into an alarmed
    int Z; //Probability an alarmed turns into zombie
    int Q; //Probability a citizen moves districts

    std::map<std::string, std::vector<std::string> > layout; //map stores the layout of Simville
    std::map<std::string, std::vector<Citizen*> > simville; //map stores the citizens of simville with districts
    std::deque<Citizen*> citizensPQ; //deque stores pointer to citizen states
    std::vector<std::string> districts; //vector stores simville districts

public:
    //Constructor 
    ZombieSim(int maxTime, int X, int Y, int Z, int Q) {
        Report report; //initialize a new report
        clock = 0; //set the time to start at 0
        this->X = X; //Probability an ignorant turns to zombie
        this->Y = Y; //Probability an ignorant turn to alarmed
        this->Z = Z; //Probability an alarmed turns to zombie
        this->Q = Q; //Probability a citizen moves
        this->maxTime = maxTime; //set maximum days

        //Creates a vector containing all of the district names
        districts.push_back("Medical Hill");
        districts.push_back("The Docks");
        districts.push_back("Downtown");
        districts.push_back("Soho");
        districts.push_back("The University");

        //Create layout map which will deteremine where a citizen can move
        for(int i = 0; i < 5; i++) {
            if(districts[i] != "Downtown") { //if citizen is not in downtown then insert them in downtown
                //every district can only "see" downtown
                layout.insert(std::pair<std::string, std::vector<std::string>>(districts[i], {"Downtown"}));
            } else { //else insert them in other districts - downtown can "see" all other districts
                layout.insert(std::pair<std::string, std::vector<std::string>>(districts[i], {"Medical Hill",
                "The Docks", "Soho", "The University"}));
            }
        }

        //Create all the citizens and add them into the simville map
        for(int i = 0; i < districts.size(); i++) { //add citizens into each district
            for (int j = 0; j < 400; j++) { 
                //All citizens start as ignorant, live is current district, work alternates for each new citizen 
                simville[districts[i]].push_back(new Ignorant(districts[i], districts[j % 5])); 
            }
        }
        
        //Remove ignorant and add zombie to the end of medical hill
        delete (simville["Medical Hill"][simville["Medical Hill"].size() - 1]); // get rid of the last person in medical hill
        simville["Medical Hill"].pop_back(); // to insure no weird null pointer stuff happens
        simville["Medical Hill"].push_back(new Zombie("Medical Hill")); // push a zombie to the back ofmedical hill
        citizensPQ.push_back(simville["Medical Hill"][simville["Medical Hill"].size() - 1]); // push this zombie to the dequeue
    }


    // This function runs the simulator - it moves all the citizens and handles all interactions
    void runSim() {
        Report report; //object to output information to the terminal

        //Temp map stores citizens in their new locations
        //Prevents map from changing sizes when iterating through map - prevents duplicate movements
        std::map <std::string, std::vector<Citizen*> > tempMap; 
       
        for(clock = 0; clock < maxTime; clock++) { //Time click loop
            std::cout << "Time Click: " << clock << std::endl;
            //Each citizen moves
            for (auto itr = simville.begin(); itr != simville.end(); itr++) { //for each district
                for (int i = 0; i < itr->second.size(); i++) { //for each citizen in that district
                    
                    if(rand() % 100 < Q){ //Probablility a citizen moves districts

                        itr->second[i]->move(layout); //move that citizen
                    }
                    //Searches temp map for pair with key of the location of the current citizen
                    if(tempMap.find(itr->second[i]->getLocation()) == tempMap.end()) { 
                        //If the key with current location couldn't be found, a pair is automatically created
                        tempMap[itr->second[i]->getLocation()].push_back(itr->second[i]); //adds citizen
                    } else { //If the the key with location of citizen exisits, the citizen is added to that pair
                        tempMap[itr->second[i]->getLocation()].push_back(itr->second[i]);
                    }
                }
            }
            //Copy temp back to simville map - simville contains citizens with updated locations
            for (auto itr = simville.begin(); itr != simville.end(); itr++) { //districts
                itr->second.clear(); //Clears vector with citizens at current district
                itr->second = tempMap[itr->first]; //Copies vector
                tempMap[itr->first].clear(); //Clears temp map
            }
           
        
            //Iterate through vector and call interact methods
            int n = 0; //random index to interact with
            std::string location; //stores location of interaction
            int qSize;
            qSize = citizensPQ.size(); //stores size of queue from beginning of time click
            //Have each citizen that is in the deque at beginning of time click interact
            for(int i = 0; i < qSize; i++) {
                location = citizensPQ[i]->getLocation(); //set current location to location of citizen in queue
                n = rand() % simville[location].size();
                //Citizen at front of queue interacts with random citizen in same location
                citizensPQ[i]->interact(simville[location][n], citizensPQ, X, Y, Z);
            }

            report.updateReport(clock, simville); // count how many zombies, alarmed or ignorant citizens there are and update the count of each one
            if (report.getZombieCount() >= 2000) { // if everybody turns into a zombie stop running
                break;
            }

        }
        report.printReport(clock); // print all of the important info
    }

    //Destructor to free up memory
    ~ZombieSim() {
        for (auto itr = simville.begin(); itr != simville.end(); itr++) { //districts
            for (int i = 0; i < itr->second.size(); i++) {// for each vector in district
               delete (itr->second)[i];// delete each citizen in each vector in each district
            }
        }
    }

};
#endif
