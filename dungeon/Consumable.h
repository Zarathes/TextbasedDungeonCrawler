#include "Item.h"

class Consumable : public Item{
public:
	Consumable(std::string name, int points);
	void setName(std::string nameNew);
	void setDescription(std::string descr);
	std::string getName();
	std::string getDescription();
	int use();
private:
};