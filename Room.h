#include <vector>
#include <stdio.h>
#include <ctype.h>
#include <cstring>

class Room  {

  private:
    int  x, y;
    std::vector<char*> items;
    char* name;

  public:
    //Constructors use string literals so you can just initialize a room with Room("name here") or pass json
    Room(const char* data);
    Room(const char* name, int x, int y);
    ~Room();

    //Getters
    int getX();
    int getY();
    std::vector<char*>* getItems();
    char* getName();

    //Setters
    void setX(int x);
    void setY(int y);
    void setName(char* name);

    //Functions for managing items
    void addItem(const char* item);
    void removeItem(const char* item);
    bool hasItem(const char* item);

    //A function to print out all items in the room
    void printItems();
};
