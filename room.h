#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include "item.h"

class Room{
    private:
        char* name;
        char* description;
        int* x;
        int* y;
        std::vector<Item*> items;

    public:
        //Constructors and Destructor
        Room(const char* name, const char* description, int x, int y);
        Room(char* name, char* description, int x, int y);
        ~Room();

        //Getters
        char* getName();
        char* getDescription();
        int* getX();
        int* getY();
        std::vector<Item*>* getItems();

        //Setters
        void setName(const char* name);
        void setName(char* name);
        void setDescription(const char* description);
        void setDescription(char* description);
        void setX(int x);
        void setY(int y);

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
};
#endif