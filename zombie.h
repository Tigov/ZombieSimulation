//CS-273-Final project
//ZOMBIE APOCALYPSE SIMULATOR
//Created by: Alaina Stockdill, Sakina Vidyarthi, Viktor Pisarenko

#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "citizen.h"
#include "alarmed.h"
#include <ctime>
//Zombie class, child class to base class citizen
class Zombie : public Citizen {
public:
    Zombie(std::string location) { //constructor
        curLocation = location; //sets current location of zombie
        state = "Zombie"; //sets zombie state
    }

//function that handles interaction between citizens
//takes citizen state and changes it based on the probability
//takes citizen pointer that points to a citizen in the map
//deque contains citizens who are yet to interact : zombies and alarmed
    void interact(Citizen*& other, std::deque<Citizen*>& citizens, int X, int Y, int Z) { 
        int randnum; //stores random number to calculate probability
        //If the other citizen is ignorant
        if (other->getState() == "Ignorant") {// if zombie interacts with ignorant
            randnum = rand() % 100; //random number to determine if ignorant gets bitten
            if (randnum < X) { //if they get bitten
                
                delete other; //clear pointer
               
                other = new Zombie(this->curLocation); //have pointer point to zombie
                
                citizens.push_back(other); //add pointer to interact list
            } else { //Ignorant person becomes alarmed
                
                delete other; //clear pointer
               
                other = new Alarmed(this->curLocation); //have pointer point to zombie
                

                citizens.push_back(other);
            }
            
        } else if (other->getState() == "Alarmed") { //If the zombie is interacting with someone alarmed
            randnum = rand() % 100;
            if (randnum < Y) { //If they get bitten
                
                
                other = new Zombie(this->curLocation); //have pointer point to zombie
                

                //They do not get added to the deque since they are already there
            }
            
        }
    }
    ~Zombie(){ //destructor for zombie
        
    }
};

#endif

//end of zombie class