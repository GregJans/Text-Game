#include "Item.h"
#include<iostream>

// general item use
void Item::use(Player& player) { std::cout << "Item Used" << std::endl; }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ POTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ EXPLOSIVES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::vector<std::string> Explosive::explosive_names = { "Singular Explosive", "AOE Explosive" };
std::vector<int> Explosive::quantities = { 0, 0 };

void SingularExplosive::use(Entity& target) {
	std::cout << "Kaboom! It's time to finish off that pesky " << target.getName() << std::endl;
	target.setHealth(1);
}

