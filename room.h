#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <map>
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
        std::map<const char*, Room*> exits;

    public:
        //Constructors and Destructor
        Room(const char* name, const char* description);
        Room(char* name, char* description);
        Room();
        ~Room();

        //Getters
        char* getName();
        char* getDescription();
        std::vector<Item*>* getItems();
        std::map<const char*, Room*>* getExits();

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

        //Printing out useful information
        void printItems();
        void printConnections(bool printNames);
};
#endif