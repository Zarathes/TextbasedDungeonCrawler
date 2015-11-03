#ifndef __hero__
#define __hero__


#include <iostream>
#include <vector>
#include <stack>
#include "Character.h"
#include "Room.h"
#include "Equipable.h"
#include "Consumable.h"

class Hero: public Character{
public:
	Hero();

	void insertCurrentRoom(Room *room);
	Room* getCurrentRoom();
	void showStatistics();
	void showBag();
	void underAttack(int points);
	void run();
	bool living();

	void SetCommand(TYPES::ACTION_LIST command);
	void Execute();
private:
	int experiancePoints;
	int perceptionPoints;
	bool alive;
	std::vector<Consumable> consumable;
	std::vector<Equipable> equipment;
	std::stack<Room*> rooms;
	Room *currentRoom;
};

#endif