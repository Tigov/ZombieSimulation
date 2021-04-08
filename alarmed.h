//CS-273-Final project
//ZOMBIE APOCALYPSE SIMULATOR
//Created by: Alaina Stockdill, Sakina Vidyarthi, Viktor Pisarenko

#include <iostream>
#include <ctime>
#include "citizen.h"

#ifndef ALARMED_H
#define ALARMED_H

//This class represents an alarmed citizen and is a derived class of citizens.
// It defines how an alarmed citizen will interact with ignorant citizens and stores
// the current location and state of the citizen
class Alarmed : public Citizen {
public:
    //Alarmed constructor
    //Input: location of citizen
    Alarmed(std::string location) {
        curLocation = location;
        state = "Alarmed";
    }

    //Defines an interaction of an alarmed citizens
    //Input: other citizen to interact with, deque of citizens, and probabilities
    void interact(Citizen*& other, std::deque<Citizen*>& citizens, int X, int Y, int Z) {
        int randnum; //stores random number to determine how the two citizens interact
        //If the alarmed citizen is interacting with an ignorant person
        if (other->getState() == "Ignorant") { 
            randnum = rand() % 100;
            if(randnum < Y) { //If the citizen becomes alarmed
                delete other;
                other = NULL;
                other = new Alarmed(this->curLocation); //have pointer point to alarmed
                citizens.push_back(other); //add to interaction list
            }
        }
    }

    //Alarmed destructor
    ~Alarmed(){
    }
};

//end of alarmed class
#endif
