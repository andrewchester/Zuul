#ifndef ITEM_H
#define ITEM_H

#include "room.h"

class Item{
    private:
        char* name;
        Room* room;
        //Add player here when implemented

    public:
        Item(char* name, Room* room);
        Item(const char* name, Room* room);
        ~Item();

        //Getters
        char* getName();
        Room* getRoom();

        //Setters
        void setName(const char* name);
        void setName(char* name);
};

#endif