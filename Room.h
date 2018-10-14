#include <vector>
#include <stdio.h>
#include <ctype.h>
#include <cstring>

class Room  {

  private:
    int* x;
    int* y;
    char* name;
    std::vector<char*> items;

  public:
    Room(const char* name, int* x, int* y);
    ~Room();

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
    void removeItem(const char* item);
    bool hasItem(const char* item);

    //A function to print out all items in the room
    void printItems();
};
