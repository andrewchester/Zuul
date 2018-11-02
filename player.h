#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "item.h"
#include "room.h"

//Telling the compiler that these classes exist, seems like a really bad idea, but I'm not getting any errors
class Room;
class Item;

class Player{
    private:
        Room* current;
        std::vector<Item*> items;
        int itemLimit;
    
    public:
        Player();
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
		
		Item* getItem(const char* item);
		Item* getItem(char* item);
		Item* getItem(Item* item);
};
#endif