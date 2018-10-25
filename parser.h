#include <fstream>
#include <vector>
#include <map>

#include "room.h"

class Parser{
    private:
        void toLower(char* str);
    public:
		void substr(char* str, int begin, int end);
        bool isValid(char* command);
        bool parseCommand(char* command, Player* player);
        void parseFromFile(std::vector<Room*>* rooms, const char* path);
        void parseConnectionsFromFile(std::vector<Room*>* rooms, const char* path);
};