#include <iostream>
#include "Room.h"
/*
  Going to read in data from txt or json
  Format:

  "NameOfRoom":{
    x:0,
    y:0,
    items: []
  }
}
*/

//This constructor is for unpacking data from a json
Room::Room(const char* data) {

}
//This is the default constructor for manually setting values, has default values 0,0 for x,y
Room::Room(const char* name, int x = 0, int y = 0) {
  this->name = const_cast<char*>(name);
  this->x = x;
  this->y = y;
}
//Destructor, deletes all dynamically allocated variables such as name and the contents of items
Room::~Room(){
  //delete name;
  /*
  for (std::vector<char*>::iterator it = items.begin(); it != items.end(); ++it){
    delete *it;
    it = items.erase(it);
  }
  */
}

//Setters
void Room::setX(int x){
  this->x = x;
}
void Room::setY(int y){
  this->y = y;
}
void Room::setName(char* name){
  this->name = name;
}

//Getters
int Room::getX(){
  return this->x;
}
int Room::getY(){
  return this->y;
}
std::vector<char*>* Room::getItems(){ //Return the address of the vector, by doing this we don't make a duplicate and we can modify the room's items
  return &items;
}
char* Room::getName(){
  return this->name;
}

//Adds an item to item
void Room::addItem(const char* item){ //Takes a string literal so you can room.addItem("Item")
  items.push_back(const_cast<char*>(item));
}
//Takes a string literal, searches the item vector for the passed string, deletes it, then exits the loop
void Room::removeItem(const char* item){
  std::vector<char*>::iterator it;
  for (it = items.begin(); it != items.end(); ++it){
    if (strcmp(*it, item) == 0){
      it = this->items.erase(it); //Make sure it isn't invalid
      break;
    }
  }
}
//Tests if a room  has an item, loops through the vector items, and when it finds the item, returns true
bool Room::hasItem(const char* item){
  std::vector<char*>::iterator it;
  for (it = items.begin(); it != items.end(); ++it){
    if (strcmp(*it, const_cast<char*>(item)) == 0){
      return true;
    }
  }
  return false;
}
//Prints out the items in the room
void Room::printItems(){
  std::vector<char*>::iterator it;
  for (it = items.begin(); it != items.end(); ++it){
    if(it == items.begin()){
      std::cout << *it;
    }else{
      std::cout << ", " << *it;
    }
  }
}
