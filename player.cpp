#include <iostream>
#include <string.h>
#include "player.h"

/*
*   A class for the player, essentially a mobile room with an item limit
*/
//Constructor with a default null value for room
Player::Player(){
    this->current = 0;
}
Player::Player(Room* room = 0){
    this->current = room;
}

//Getters
Room* Player::getCurrentRoom(){
    return this->current;
}
int Player::numItems(){
	return this->items.size();
}

//Setters
void Player::setCurrentRoom(Room* room){
    this->current = room;
}

//Functions for managing items
//Adds item(s) to the vector items. Duplicates the item when you add it so if items are being moved between rooms or between the room and player, delete the original item pointer
void Player::addItem(const char* item){
    Item* itemPointer = new Item(item, this);
    items.push_back(itemPointer);
}
void Player::addItem(char* item){
    Item* itemPointer = new Item(item, this);
    items.push_back(itemPointer);
}
void Player::addItem(Item* item){
    Item* itemPointer = new Item(item->getName(), this);
    items.push_back(itemPointer);
}

//Removes an item from the vector items, deletes the pointer as well
void Player::removeItem(const char* item){
    std::vector<Item*>::iterator it;
    for(it = this->items.begin(); it != this->items.end(); ++it) //Iterating over items
        if(strcmp((*it)->getName(), item) == 0){ //If it contains the item, delete it
            delete *it;
            it = this->items.erase(it);
			it--;
        }
}
void Player::removeItem(char* item){
    std::vector<Item*>::iterator it;
    for(it = this->items.begin(); it != this->items.end(); ++it) //Iterating over items
        if(strcmp((*it)->getName(), item) == 0){ //If it contains the item, delete it
            delete *it;
            it = this->items.erase(it);
			it--;
		}
}
void Player::removeItem(Item* item){
    std::vector<Item*>::iterator it;
    for(it = this->items.begin(); it != this->items.end(); ++it) //Iterating over items
        if(*it == item){ //If it contains the item, delete it
            delete *it;
            it = this->items.erase(it);
			it--;
        }
}

//Tests if the room contains an item
bool Player::hasItem(const char* item){
    std::vector<Item*>::iterator it;
    for(it = this->items.begin(); it != this->items.end(); ++it) //Iterating over items
        if(strcmp((*it)->getName(), item) == 0) //If it contains the item, delete it
           return true;
    return false;
}
bool Player::hasItem(char* item){
    std::vector<Item*>::iterator it;
    for(it = this->items.begin(); it != this->items.end(); ++it) //Iterating over items
        if(strcmp((*it)->getName(), item) == 0) //If it contains the item, delete it
            return true;
    return false;
}
bool Player::hasItem(Item* item){
    std::vector<Item*>::iterator it;
    for(it = this->items.begin(); it != this->items.end(); ++it) //Iterating over items
        if(*it == item) //If it contains the item, delete it
            return true;
    return false;
}

Item* Player::getItem(const char* item){
	std::vector<Item*>::iterator it;
    for(it = this->items.begin(); it != this->items.end(); ++it) //Iterating over items
        if(strcmp((*it)->getName(), item) == 0) //If it contains the item, delete it
           return *it;
    return 0;
}
Item* Player::getItem(char* item){
    std::vector<Item*>::iterator it;
    for(it = this->items.begin(); it != this->items.end(); ++it) //Iterating over items
        if(strcmp((*it)->getName(), item) == 0) //If it contains the item, delete it
            return *it;
    return 0;
}
Item* Player::getItem(Item* item){
    std::vector<Item*>::iterator it;
    for(it = this->items.begin(); it != this->items.end(); ++it) //Iterating over items
        if(*it == item) //If it contains the item, delete it
            return *it;
    return 0;
}

void Player::printItems(){
	std::cout << "You're holding: ";
	std::vector<Item*>::iterator it;
	for(it = items.begin(); it != items.end(); ++it){
		std::cout << (*it)->getName() << " ";
	}
	std::cout << std::endl;
}