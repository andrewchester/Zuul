#ifndef ITEM_H
#define ITEM_H

#include "room.h"
#include "player.h"

//Telling the compiler that these classes exist, seems like a really bad idea, but I'm not getting any errors
class Room;
class Player;

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