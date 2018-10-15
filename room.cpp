#include <string.h>
#include "room.h"

////////////////////////////////////////////////////////////////////////////////
//Constructor using string literals
Room::Room(const char* name, const char* description, int x, int y){
    //Allocate memory for variables
    this->name = new char[strlen(name)];
    this->description = new char[strlen(description)];
    this->x = new int;
    this->y = new int;

    //Copy data to variables
    strcpy(this->name, name);
    strcpy(this->description, description);
    *this->x = x;
    *this->y = y;
}
//Constructor using char*, virtually the same as using const char*
Room::Room(char* name, char* description, int x, int y){
    //Allocate memory for variables
    this->name = new char[strlen(name)];
    this->description = new char[strlen(description)];
    this->x = new int;
    this->y = new int;

    //Copy data to variables
    strcpy(this->name, name);
    strcpy(this->description, description);
    *this->x = x;
    *this->y = y;
}
Room::~Room(){
    delete name, description, x, y; //Delete variables from constructor

    //Delete all the items in items
    std::vector<Item*>::iterator item; 
    for(item = this->items.begin(); item != this->items.end(); ++item){
        delete *item;
        item = this->items.erase(item);
    }
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//Getters
char* Room::getName(){
    return this->name;
}
char* Room::getDescription(){
    return this->description;
}
int* Room::getX(){
    return this->x;
}
int* Room::getY(){
    return this->y;
}
std::vector<Item*>* Room::getItems(){
    return &this->items;
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//Setters
void Room::setName(const char* name){
    strcpy(this->name, name);
}
void Room::setName(char* name){
    strcpy(this->name, name);
}
void Room::setDescription(const char* description){
    strcpy(this->description, description);
}
void Room::setDescription(char* description){
    strcpy(this->description, description);
}
void Room::setX(int x){
    *this->x = x;
}
void Room::setY(int y){
    *this->y = y;
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//Functions for managing items

//Adds item(s) to the vector items. Duplicates the item when you add it so if items are being moved between rooms or between the room and player, delete the original item pointer
void Room::addItem(const char* item){
    Item* itemPointer = new Item(item, this);
    items.push_back(itemPointer);
}
void Room::addItem(char* item){
    Item* itemPointer = new Item(item, this);
    items.push_back(itemPointer);
}
void Room::addItem(Item* item){
    Item* itemPointer = new Item(item->getName(), this);
    items.push_back(itemPointer);
}

//Removes an item from the vector items, deletes the pointer as well
void Room::removeItem(const char* item){
    std::vector<Item*>::iterator it;
    for(it = this->items.begin(); it != this->items.end(); ++it) //Iterating over items
        if(strcmp((*it)->getName(), item) == 0){ //If it contains the item, delete it
            delete *it;
            it = this->items.erase(it);
        }
}
void Room::removeItem(char* item){
    std::vector<Item*>::iterator it;
    for(it = this->items.begin(); it != this->items.end(); ++it) //Iterating over items
        if(strcmp((*it)->getName(), item) == 0){ //If it contains the item, delete it
            delete *it;
            it = this->items.erase(it);
        }
}
void Room::removeItem(Item* item){
    std::vector<Item*>::iterator it;
    for(it = this->items.begin(); it != this->items.end(); ++it) //Iterating over items
        if(*it == item){ //If it contains the item, delete it
            delete *it;
            it = this->items.erase(it);
        }
}

//Tests if the room contains an item
bool Room::hasItem(const char* item){
    std::vector<Item*>::iterator it;
    for(it = this->items.begin(); it != this->items.end(); ++it) //Iterating over items
        if(strcmp((*it)->getName(), item) == 0) //If it contains the item, delete it
           return true;
    return false;
}
bool Room::hasItem(char* item){
    std::vector<Item*>::iterator it;
    for(it = this->items.begin(); it != this->items.end(); ++it) //Iterating over items
        if(strcmp((*it)->getName(), item) == 0) //If it contains the item, delete it
            return true;
    return false;
}
bool Room::hasItem(Item* item){
    std::vector<Item*>::iterator it;
    for(it = this->items.begin(); it != this->items.end(); ++it) //Iterating over items
        if(*it == item) //If it contains the item, delete it
            return true;
    return false;
}

////////////////////////////////////////////////////////////////////////////////