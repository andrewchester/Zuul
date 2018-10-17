/*
* Andrew Chester, Per. 2 Zuul
* Zuul is a text based console game that allows you to explore rooms and pickup items
*/
#include <iostream>
#include <map>

#include "parser.h"
#include "room.h"
#include "player.h"
#include "item.h"

void iniRooms(std::map<const char*, Room>* rooms){
  //Initialize rooms here
}

int main(){
  std::map<const char*, Room> rooms;
  
  Parser parser;
  Player p;
  
  char command[30] = "help";
  bool playing = true;

  iniRooms(&rooms);

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
  return 0;
}
