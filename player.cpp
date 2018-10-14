#include "player.h"

Player::Player(Room* startingRoom){
    this->currentRoom = startingRoom;
    this->inventorySize = 3;
}
Player::~Player(){
    //Clear the inventory array and delete the values if there are any
    //Values in the inventory are pointers moved from the Room the item was taken from, so the destructor in Room won't delete them
    if(this->inventory.size() != 0){
        std::vector<char*>::iterator it;
        for(it = this->inventory.begin(); it != this->inventory.end(); ++it){
            delete *it;
            it = this->inventory.erase(it); 
        }
    }
}

//Removes an item from the player
//You have to be careful with this function as it doesn't delete the pointer, simply removes it from the player
//It has to go along with adding the pointer to a room or somewhere else where you won't get a memory leak
void Player::removeItem(char* item){
    std::vector<char*>::iterator it;
    for(it = this->inventory.begin(); it != this->inventory.end(); ++it){ //Loop over inventory
        if(strcmp(*it, item) == 0){ //When we find the item
            it = this->inventory.erase(it); //Remove it
            return; //And exit the function
        }
    }
}
//Returns true if the player has an item
bool Player::hasItem(const char* item){
    std::vector<char*>::iterator it;
    for(it = this->inventory.begin(); it != this->inventory.end(); ++it){
        if(strcmp(*it, const_cast<char*>(item)) == 0){
            return true;
        }
    }
    return false;
}
//Returns  true if the player has an item, but takes a pointer as a parameter
bool Player::hasItem(char* item){
    std::vector<char*>::iterator it;
    for(it = this->inventory.begin(); it != this->inventory.end(); ++it){
        if(strcmp(*it, item) == 0){
            return true;
        }
    }
    return false;
}

//Picks up an item from a room, adds it to the player's inventory and removes it from the roop
void Player::pickup(char* item){
    if(this->inventory.size() >= this->inventorySize){ //Make sure we're not going over the player's limit
        std::cout << "You can't pickup that item now, your inventory is full." << std::endl;
        return;
    }
    if(this->currentRoom->hasItem(item)){
        this->inventory.push_back(item);
        currentRoom->removeItem(item, false);
        std::cout << "Picked up: " << item << " from the " << currentRoom->getName() << std::endl;
        return;
    }
    std::cout << item << " isn't in " << this->currentRoom->getName() << std::endl;
}
//Picks up an item from currentRoom using a string passed to it instead
void Player::pickup(const char* item){
    if(this->inventory.size() >= this->inventorySize){
        std::cout << "You can't pickup that item now, your inventory is full" << std::endl;
        return;
    }
    if(this->currentRoom->hasItem(item)){
        char* itemPointer = new char[strlen(item)];
        strcpy(itemPointer, item);
        this->inventory.push_back(itemPointer);
        this->currentRoom->removeItem(item, true); //We want to delete the room's pointer because we just created our own
        std::cout << "Picked up a " << item << " from the " << this->currentRoom->getName() << std::endl;
        return;
    }
    std::cout << item <<  " isn't in " << this->currentRoom->getName() << std::endl;
}

//Drops the item into the current room
void Player::drop(char* item){
    if(!this->hasItem(item)){ //Check if we even have the item first
        std::cout << "You're not holding a " << item << std::endl;
        return;
    }

    this->currentRoom->addItem(item);
    this->removeItem(item);
    std::cout << "Dropped a " << item << " into the " << currentRoom->getName() << std::endl;
}

//Getter and Setter for currentRoom
Room* Player::getCurrentRoom(){
    return this->currentRoom;
}
void  Player::setCurrentRoom(Room* room){
    this->currentRoom = room;
}