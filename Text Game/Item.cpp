#include "Item.h"
#include<iostream>

// general item use
void Item::use(Player& player) { std::cout << "Item Used" << std::endl; }

//specific potion data
std::vector<std::string> Potion::potion_names = { "Health Potion", "Strength Potion" };
std::vector<int> Potion::quantities = { 0, 0 };

void HealthPotion::use(Player& player) {
	std::cout << "Health potion used" << std::endl;
	player.setHealth(player.getMaxHealth());
	Potion::quantities[HEALTH]--;
}

void StrengthPotion::use(Player& player) {
	std::cout << "Strength potion used" << std::endl;
	initialPlayerDamage = player.getWeapon().getDamage();

	player.getWeapon().setDamage(initialPlayerDamage + buffModifier);
	Potion::quantities[STRENGTH]--;
}

int StrengthPotion::turnsLeft = 0;
