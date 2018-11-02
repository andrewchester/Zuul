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
  player.setCurrentRoom(rooms[0]);

  Room* lastRoom;
  bool firstRun = true;
  while(playing){
    //Get input
    lastRoom = player.getCurrentRoom();
    while(!parser.isValid(command)){
      std::cout << std::endl << "> ";
      std::cin.get(command, 30);
      std::cin.clear();
      std::cin.ignore(100, '\n');
      if(!parser.isValid(command))
        std::cout << "Invalid command. Try 'help'" << std::endl;
    }
    //Do something with that input
    playing = parser.parseCommand(command, &player);
    command[0] = '/';  //Change the first character of command so that parser.isValid won't recognize it
    if(lastRoom != player.getCurrentRoom() || firstRun){
      std::cout << "Current Room: " << player.getCurrentRoom()->getName() << "\n" << "  " << player.getCurrentRoom()->getDescription() << std::endl;
      std::cout << std::endl << "  Has: ";
      player.getCurrentRoom()->printItems();
      std::cout << std::endl << "  You can go: ";
      player.getCurrentRoom()->printConnections(false);
      std::cout << std::endl << std::endl; 

      const char* key = "NORTH";
      std::map<const char*, Room*> exits = *player.getCurrentRoom()->getExits();
      std::map<const char*, Room*>::iterator it;
      for(it = exits.begin(); it != exits.end(); ++it){
        std::cout << it->first << ": ";
        if(it->second != 0)
          std::cout << it->second->getName();
        else
          std::cout << 0;
        std::cout << std::endl;
        if(strcmp(key, it->first) == 0)
          std::cout << "Key matches: " << it->first << std::endl;
      }
      std::cout << std::endl;
      
      if ( exits.find(key) == exits.end() ) {
        std::cout << "Has " << key << std::endl;
        std::cout << key << " is: " << exits[key] << std::endl;
      } else {
        std::cout << "Doesn't have " << key << std::endl;
      }
      firstRun = false;
    }
  }
  return 0;
}
