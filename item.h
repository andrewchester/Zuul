#ifndef ITEM_H
#define ITEM_H
#include "room.h"
#include "player.h"

class Room; //Declare Room without initializing it, we can avoid the chicken-egg problem of room and item including each other this way
class Player; //Same as room

class Item{
    private:
        char* name;
        Room* room; //Holds the room it's in or
        Player* player; //The player whose holding it

    public:
        Item(char* name, Room* room);
        Item(const char* name, Room* room);
        Item(char* name, Player* player);
        Item(const char* name, Player* player);
        ~Item();

        //Getters
        char* getName();
        Room* getRoom();

        //Setters
        void setName(const char* name);
        void setName(char* name);
};

#endif