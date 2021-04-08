//CS-273-Final project
//ZOMBIE APOCALYPSE SIMULATOR
//Created by: Alaina Stockdill, Sakina Vidyarthi, Viktor Pisarenko

//Ignorant class

#include <iostream>
#include <string>
#include <algorithm>
#include "citizen.h"

#ifndef IGNORANT_H
#define IGNORANT_H

//This represents an ignorant citizen which is a derived class of citizen
//It contains where they live and work which will be used to define their move function

class Ignorant : public Citizen {
private:
    std::string live;
    std::string work;

public:
    //Default constructor
    Ignorant() {
        state = "Ignorant";
        live = "None assigned";
        work = "None assigned";
        curLocation = "None assigned";
        
    }

    //Constructor for Ignorant type
    //Input: where an ignorant citizen lives and works
    Ignorant(std::string live, std::string work) {
        state = "Ignorant";
        this->live = live;
        this->work = work;
        curLocation = live; //initialized to be where they live
    }

    //Defines how a citizen will move
    //Input: layout map
    void move(std::map<std::string, std::vector<std::string>>& layout) {
        if (curLocation == live) {  //go to work if at home
            curLocation = work;
        } else { //got to home if at work
            curLocation = live;
        }
    }

    //Indicates where a citizen lives
    //Output: which district a citizen lives in
    std::string getLive() {
        return live;
    }

    //Ignorant citizens will not interact with other citizens
    void interact(Citizen*& other, std::deque<Citizen*>& citizens, int X, int Y, int Z) {};

    //Destructor
    ~Ignorant() {};
};
#endif

//end of ignorant class