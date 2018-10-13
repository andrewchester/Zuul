#include <iostream>
#include "Room.h"

int main(){
  Room* r = new Room("Test room", 0, 0);
  std::cout << "Name of r is: " << r->getName() << std::endl;
  std::cout << "x,y of r is: " << r->getX() << ", " << r->getY() << std::endl;
  r->addItem("Test1");
  r->addItem("Test2");
  r->printItems();
  std::cout << std::endl;
  std::cout << r->hasItem("Test1") << std::endl;
  r->removeItem("Test1");
  r->printItems();
  std::cout << std::endl;
  delete r;
  return 0;
}
