/*
* Andrew Chester, Per. 2 Zuul
* Zuul is a text based console game that allows you to explore rooms and pickup items
*/
#include <iostream>
#include <map>
#include <limits>

#include "parser.h"

int main(){
  Parser parser;
  char command[30] = "help";
  bool playing = true;

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
