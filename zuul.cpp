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

void printRoomInformation(std::vector<Room*>* rooms){
  std::vector<Room*>::iterator it;
  for(it = rooms->begin(); it != rooms->end(); ++it){
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
  Player player;
  
  char command[30] = "help";
  bool playing = true;

  parser.parseFromFile(&rooms, "rooms.txt");
  parser.parseConnectionsFromFile(&rooms, "connections.txt");

  player.setCurrent(rooms[0]);
  
  while(playing){
    //Print the current location, description, etc

    std::cout << "You're in the " << player.getCurrentRoom()->getName() << std::endl;
    std::cout << player.getCurrentRoom()->getDescription() << std::endl;
    std::cout << "\t" << "It has: " << player.getCurrentRoom()->printItems() << std::endl;
    std::cout << "\t" << "You can go: " << player.getCurrentRoom()->printExits(false) << std::endl;
    
    //Get input
    while(!parser.isValid(command)){
      std::cout << "> ";
      std::cin.get(command, 30);
      std::cin.clear();
      std::cin.ignore(100, '\n');
      if(!parser.isValid(command))
        std::cout << "Invalid command. Try 'help'" << std::endl;
    }
    //Do something with that input
    playing = parser.parseCommand(command);
    command[0] = '/';  //Change the first character of command so that parser.isValid won't recognize it
  }
  return 0;
}
