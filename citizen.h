//CS-273-Final project
//ZOMBIE APOCALYPSE SIMULATOR
//Created by: Alaina Stockdill, Sakina Vidyarthi, Viktor Pisarenko

#include <iostream>
#include <map>
#include <string>
#include <algorithm>

#ifndef CITIZEN_H
#define CITIZEN_H

//This represents a citizens and contains data concerning their location and their 
// state. It defines how a citizen will move by randomizing the district they
// will move to and has get functions associated with class variables
class Citizen {
protected:
    std::string curLocation; //current location of a citizen
    std::string state; //current state of a citizen

public:
    //Empty constructor
    Citizen() {};
    
    //Constructor for a citizen
    //Input: location and state
    Citizen(std::string setState, std::string location) : state(setState), curLocation(location) {};

    //Defines how a ciitzen will move districts
    //Input: the layout of simville - determine where a citizen can move given location
    void move(std::map<std::string, std::vector<std::string>> layout) {
        int num; //used for a random number
        if (curLocation == "Downtown") { 
            num = rand() % 4; //Randomizes which district they will move to
            curLocation = layout["Downtown"][num];
        } else { //The only other location they can move to is downtown
            curLocation = "Downtown";
        }
    }

    //Defines how a citizen will interact with another citizen
    //Input: other citizen to interact with, deque of citizens that will interact, probabilities
    virtual void interact(Citizen*& other, std::deque<Citizen*>& citizens, int X, int Y, int Z) = 0;

    //Gets the current location of the citizen
    //Ouput: location
    std::string getLocation() {
        return curLocation;
    }

    //Gets the current state of a citizen
    //Output: state
    std::string getState() {
        return state;
    }

    //Virtual destructor of citizen
    virtual ~Citizen() {};
    
};


#endif