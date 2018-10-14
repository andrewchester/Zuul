#include <iostream>
#include "room.h"

//A class for the player
//It holds the room that the player is currently in, and all the items the player is holding(max of inventorySize)
class Player{
    private:
        Room* currentRoom;
        std::vector<char*> inventory; 
        int inventorySize; //The limit on the number of items a player can hold

        void removeItem(char* item); //Removes an item from the player, doesn't drop it, just removes the pointer
    public:
        Player(Room* startingRoom); //Takes the room that the player starts at, usually 0, 0 
        ~Player();
        
        void pickup(char* item); //Pickup an item from a room
        void pickup(const char* item);
        void drop(char* item); //Or drop an item into a room
        //Two hasItem functions, one for passing in string literals and one for just a pointer
        bool hasItem(const char* item); 
        bool hasItem(char* item); 

        void move(int direction); //Move will move the player around to different rooms
        /*
               Forward
                  1
        Left  -2  0  2  Right
                 -1
               Backward

        //Just return if it's zero
        */

       //Getter and Setter for currentRoom
       Room* getCurrentRoom();
       void setCurrentRoom(Room* room);
};