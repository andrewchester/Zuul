#include <string.h>
#include "item.h"

//Constructor with const char*
Item::Item(const char* name, Room* room){
    this->name = new char[strlen(name)]; //Allocate memory for name
    this->room = room;
    this->player = 0;
    strcpy(this->name, name); //Copy values into name
}
//Constructor for char*, virtually identical to the const char* one
Item::Item(char* name, Room* room){
    this->name = new char[strlen(name)]; //Allocate memory for name
    this->room = room;
    this->player = 0;
    strcpy(this->name, name); // Copy values into name
}
//Constructor for player with const char*, could be used to add default items to player
Item::Item(const char* name, Player* player){
    this->name = new char[strlen(name)]; //Allocate memory for name
    this->player = player;
    this->room = 0;
    strcpy(this->name, name); //Copy values into name
}
//Constructor for player char*, virtually identical to the const char* one
Item::Item(char* name, Player* player){
    this->name = new char[strlen(name)]; //Allocate memory for name
    this->player = player;
    this->room = 0;
    strcpy(this->name, name); // Copy values into name
}

//Destructor
Item::~Item(){
    delete name, player;
}

//Getters 
char* Item::getName(){
    return this->name;
}
Room* Item::getRoom(){
    return this->room;
}
//Setters
void Item::setName(char* name){
    strcpy(this->name, name);
}
void Item::setName(const char* name){
    strcpy(this->name, name);
}