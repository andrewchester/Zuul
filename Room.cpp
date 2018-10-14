#include <iostream>
#include "Room.h"

//Constructor
Room::Room(const char* name, int* x, int* y) {
  this->name = const_cast<char*>(name);
  this->x = x;
  this->y = y;
}
//Destructor for name, x, y, and items.
Room::~Room(){
  delete name;
  delete x;
  delete y;
  for (std::vector<char*>::iterator it = items.begin(); it != items.end(); ++it){
    delete *it;
  }
}

//Setters
void Room::setX(int x){
  *this->x = x;
}
void Room::setY(int y){
  *this->y = y;
}
void Room::setName(char* name){
  this->name = name;
}

//Getters
int* Room::getX(){
  return this->x;
}
int* Room::getY(){
  return this->y;
}
std::vector<char*>* Room::getItems(){ //Maybe return a pointer here instead?
  return &items;
}
char* Room::getName(){
  return this->name;
}

//Adds an item to item
void Room::addItem(const char* item){ //Takes a string literal so you can room.addItem("Item")
  this->items.push_back(const_cast<char*>(item));
}
//Takes a string literal, searches the item vector for the passed string, removes it, then exits the loop
void Room::removeItem(const char* item){
  std::vector<char*>::iterator it;
  for (it = this->items.begin(); it != this->items.end(); ++it){
    if (strcmp(*it, item) == 0){
      it = this->items.erase(it); //Make sure it isn't invalid
      break;
    }
  }
}
//Tests if a room  has an item, loops through the vector items, and when it finds the item, returns true
bool Room::hasItem(const char* item){
  std::vector<char*>::iterator it;
  for (it = this->items.begin(); it != this->items.end(); ++it){
    if (strcmp(*it, const_cast<char*>(item)) == 0){ //Iterate over items, if we find it, return true
      return true; //Efficiency of the search doesn't matter, there won't be more than 10 items in a room
    }
  }
  return false;
}
//Prints out the items in the room
void Room::printItems(){
  std::vector<char*>::iterator it;
  for (it = this->items.begin(); it != this->items.end(); ++it){ //Looping over items from the data struct
    if(it == this->items.begin()){ //Just print out the item if it's first
      std::cout << *it;
    }else{ //For all others include a comma
      std::cout << ", " << *it;
    }
  }
}
