#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include "player.h"
#include "item.h"

//Telling the compiler that these classes exist, seems like a really bad idea, but I'm not getting any errors
class Player;
class Item;

class Room{
    private:
        char* name;
        char* description;
        std::vector<Item*> items;

    public:
        //Pointers to connected rooms, by default null
        //Public so I don't have to write getters and setters for all of them
        Room* NORTH;
        Room* EAST;
        Room* SOUTH;
        Room* WEST;

        //Constructors and Destructor
        Room(const char* name, const char* description);
        Room(char* name, char* description);
        Room();
        ~Room();

        //Getters
        char* getName();
        char* getDescription();
        std::vector<Item*>* getItems();

        //Setters
        void setName(const char* name);
        void setName(char* name);
        void setDescription(const char* description);
        void setDescription(char* description);

        //Functions for managing items
        void addItem(const char* item);
        void addItem(char* item);
        void addItem(Item* item);
        
        void removeItem(const char* item);
        void removeItem(char* item);
        void removeItem(Item* item);

        bool hasItem(const char* item);
        bool hasItem(char* item);
        bool hasItem(Item* item);

        //To print out its items, doesn't use std::endl, so it can be inserted into a string
        void printItems();
};
#endif