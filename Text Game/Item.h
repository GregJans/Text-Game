#ifndef ITEM_H
#define ITEM_H
#include<string>
#include<vector>
#include "Entity.h"

class Item {
protected:
	const int price;
public:
	static void use(Player& player);
};

struct Potion : public Item {
	static enum types { HEALTH, STRENGTH };
	static std::vector<std::string> potion_names;
	static std::vector<int> quantities;
	static const int price = 5;
};


class HealthPotion : public Potion {
public:
	static void use(Player& player);
};

class StrengthPotion : public Potion {
public:

	static int turnsLeft;
	static const int buffModifier = 100;
	static int initialPlayerDamage;

	static void use(Player& player);
};


struct Explosive : public Item {
	static enum types { SINGULAR, AOE };
	static std::vector<std::string> explosive_names;
	static std::vector<int> quantities;
	static const int price = 10;
};

class SingularExplosive : public Explosive {
public:
	static void use(Entity& target);
};

#endif