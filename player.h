#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include "item.h"

class Item; //So item is defined in player's implementation(player.cpp)

class Player{
    private:
        Room* current;
        std::vector<Item*> items;
        int itemLimit;
    
    public:
        Player(Room* current);
        
        //Getters
        Room* getCurrentRoom();
        std::vector<Item*>* getItems();
        int getItemLimit();

        //Setters
        void setCurrentRoom(Room* current);
        void setItemLimit(int itemLimit);

        //Functions for managing items
        //same as room which means the original pointer needs to be deleted
        void addItem(const char* item);
        void addItem(char* item);
        void addItem(Item* item);
        
        void removeItem(const char* item);
        void removeItem(char* item);
        void removeItem(Item* item);

        bool hasItem(const char* item);
        bool hasItem(char* item);
        bool hasItem(Item* item);
};
#endif