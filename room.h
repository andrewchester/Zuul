#ifndef ROOM_H //Header guard for room
#define ROOM_H

#include <vector>
#include <stdio.h>
#include <ctype.h>
#include <cstring> 

//A class for the rooms in the game, holds its x, y position, name, and the items it contains
class Room  {
  private:
    int* x;
    int* y;
    char* name;
    std::vector<char*> items; 

  public:
    //Constructor takes a string literal and two int pointers
    Room(const char* name, int* x, int* y); 
    ~Room(); //In the destructor all the memory for the rooms name, x, y and values inside items is 

    //Getters
    int* getX();
    int* getY();
    std::vector<char*>* getItems();
    char* getName();

    //Setters
    void setX(int x);
    void setY(int y);
    void setName(char* name);

    //Functions for managing items
    void addItem(const char* item);
    void removeItem(const char* item, bool deleting);
    bool hasItem(const char* item);
    bool hasItem(char* item);

    //A function to print out all items in the room
    void printItems();
};
#endif