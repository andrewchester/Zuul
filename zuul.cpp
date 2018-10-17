/*
* Andrew Chester, Per. 2 Zuul
* Zuul is a text based console game that allows you to explore rooms and pickup items
*/
#include <iostream>
#include <fstream>
#include <string.h>
#include <map>

#include "parser.h"
#include "room.h"
#include "player.h"
#include "item.h"

int main(){
  std::map<char*, Room*> rooms;
  
  Parser parser;
  Player player;
  
  char command[30] = "help";
  bool playing = true;

  parser.parseFromFile(&rooms, "rooms.txt");
  
  std::map<char*, Room*>::const_iterator it;
  for(it = rooms.begin(); it != rooms.end(); ++it){
    std::cout << it->first << ":" << std::endl;
    std::cout << "\t" << "Description: " << it->second->getDescription() << std::endl;
    std::cout << "\t" << "Items: ";
    it->second->printItems();
    std::cout << std::endl;
  }
  /*
  while(playing){
    //Print the current location, description, etc
    
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
  */
  return 0;
}
