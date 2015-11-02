#include "stdafx.h"
#include "Game.h"

using std::map;
using std::pair;

#include <string>
using std::string;

using std::getline;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "Generator.h"
#include "ConcreteCommand.h"

//exceptions
using std::invalid_argument;
using std::out_of_range;


Game::Game() : running{ true }
{	
	if (generateDungeon()) {
		start();
	}
}

int Game::inputNumber(string question) {
	cout << question << endl;

	string input;
	int output;
	getline(cin, input);

	std::string::size_type rest;

	try {
		output = std::stoi(input, &rest);
	}
	catch (const invalid_argument& ia) {
		cout << "Invalid arguments: " << ia.what() << endl;
		return inputNumber(question);
	}
	catch (const out_of_range& oor) {
		cout << "Out of Range Error: " << oor.what() << endl;
		return inputNumber(question);
	}

	return output;
}

bool Game::generateDungeon() {
	Generator *dungenGenerator = new Generator();

	int levels = inputNumber("How many levels should the dungeon have?");
	int totalRooms = inputNumber("How many rooms should each layer have?");

	if (dungenGenerator->createDungeon(levels, totalRooms)) {
		currentRoom = dungenGenerator->getStartRoom();

		return true;
	}

	return false;
}

void Game::start(){
	while (running) {
		commands = currentRoom->getCommands();
		handelCommand();
	}
}

void Game::printCommands()
{
	int current = 1;

	int index = commands.size();
	for (auto const& a : commands)
	{
		if (current == index) {
			cout << a.first << ": " << a.second.second << endl;
		}
		else {
			cout << a.first << ": " << a.second.second << " | ";
		}

		current++;
	}
}

void Game::handelCommand()
{
	printCommands();
	int command = inputNumber("Choose a command: \n\r");

	try {
		if (commands.find(command) != commands.end()) {
			cout << "Your command is: " << commands[command].second << "." << endl;

			switch (commands[command].first) {
			case TYPES::ACTION_LIST::FIGHT:
				FightCommand(currentRoom).Execute();
				break;
			case TYPES::ACTION_LIST::RUN:
				RunCommand(currentRoom).Execute();
				break;
			case TYPES::ACTION_LIST::SEE_BAG:
				SeeBagCommand(currentRoom).Execute();
				break;
			case TYPES::ACTION_LIST::REST:
				RestCommand(currentRoom).Execute();
				break;
			case TYPES::ACTION_LIST::VIEW_MAP:
				ViewMapCommand(currentRoom).Execute();
				break;
			case TYPES::ACTION_LIST::VIEW_HERO:
				ViewHeroCommand(currentRoom).Execute();
				break;
			case TYPES::ACTION_LIST::CHANGE_ROOM:
				ChangeRoomCommand(currentRoom).Execute();
				break;
			}
		}
		else {
			throw invalid_argument("No valid Action");
		}
	}
	catch (const invalid_argument& ia) {
		cout << "Invalid arguments: " << ia.what() << endl;
		handelCommand();
	}
}

Game::~Game()
{
}