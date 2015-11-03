#include "Item.h"
class Equipable: public Item{
public:
	Equipable(std::string name, int points);
	void setName(std::string nameNew);
	void setDescription(std::string descr);
	std::string getName();
	std::string getDescription();
	void use();
private:
	std::string name;
	std::string description;
	int points;
};