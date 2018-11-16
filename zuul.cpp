/*
* Andrew Chester, Per. 2 Zuul
* Zuul is a text based console game that allows you to explore rooms and pickup items
*/
#include <iostream>
#include <string.h>

#include "parser.h"
#include "room.h"
#include "player.h"
#include "item.h"

//A function for printing all room information, used for debugging the parse from file and parse connections functions in parser.cpp
void printRoomInformation(std::vector<Room*>* rooms){
  std::vector<Room*>::iterator it;
  for(it = rooms->begin(); it != rooms->end(); ++it){ //Loops over the rooms vector and prints all relevant information
    std::cout << (*it)->getName() << ":" << std::endl;
    std::cout << "\t" << "Description: " << (*it)->getDescription() << std::endl;
    std::cout << "\t" << "Items: ";
    (*it)->printItems();
    std::cout << std::endl;
    std::cout << "\t" << "Available connections: ";
    (*it)->printConnections(false);
    std::cout << std::endl;
  }
}

int main(){
  std::vector<Room*> rooms;
  
  Parser parser;
  Player player = Player();
  
  char command[30] = "help"; //Set the default command to help so the commands are printed out in the beginning
  bool playing = true;

  parser.parseFromFile(&rooms, "rooms.txt"); //Initialize all the rooms
  parser.parseConnectionsFromFile(&rooms, "connections.txt"); //Once all rooms are initialized, create the connections between them
  player.setCurrentRoom(rooms[0]); //Set the current room to the first one with the player, the order of the rooms in the vector doesn't matter that much except for the first one

  Room* lastRoom;//Used for testing if the player moved
  bool firstRun = true;
  while(playing){
    lastRoom = player.getCurrentRoom(); //Get the room the player is in at the start of the turn
    while(!parser.isValid(command)){ //While they haven't entered a valid input
      std::cout << std::endl << "> ";
      std::cin.get(command, 30); //Ask them for input
      std::cin.clear();
      std::cin.ignore(100, '\n');
      if(!parser.isValid(command)) //If they entered an invalid command, tell them
        std::cout << "Invalid command. Try 'help'" << std::endl;
    }
    //Do something with that input
    playing = parser.parseCommand(command, &player); //Once the loop is over, parse the command
    if((lastRoom != player.getCurrentRoom() || firstRun) && playing){ //If they've changed room then print out the room information
      std::cout << "Current Room: " << player.getCurrentRoom()->getName() << "\n" << "  " << player.getCurrentRoom()->getDescription() << std::endl;
      std::cout << std::endl << "  Has: ";
      player.getCurrentRoom()->printItems();
      std::cout << std::endl << "  You can go: ";
      player.getCurrentRoom()->printConnections(false);
      firstRun = false;
    }
	for (int i = 0; i < strlen(command); i++) command[i] = 0; //Clear the command they've entered
  }
  return 0;
}
