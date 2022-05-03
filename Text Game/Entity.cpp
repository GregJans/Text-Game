#include "Entity.h"
#include<iostream>


int Entity::getHealth() const { return health; }
int Entity::getLevel() const { return level; }
int Entity::getRewardDrop() const { return rewardDrop; }
string Entity::getName() const { return name; }
Weapon& Entity::getWeapon() { return weapon; }

//setters
void Entity::setHealth(int newHealth) { health = newHealth; }
void Entity::setLevel(int newLevel) { level = (newLevel >= 0 && newLevel <= 100) ? newLevel : 0; }
void Entity::setName(const string& newName) { name = newName; }

void Entity::takeDamage(int damage) {
	setHealth(health - damage);
	if (health <= 0) die();
}

void Entity::attack(Entity& target) {
	if (weapon.getDurability() > 0) {
		target.takeDamage(weapon.getDamage());
		weapon.useDurability();
	}
	else {
		std::cout << "Your weapon has run out of uses" << std::endl;
	}
}

void Entity::die() {
	std::cout << "The " << getName() << " has been defeated" << std::endl;
	Entity::~Entity();
}

// ~~~~~~~~~~~~~~~~~~~~~ PLAYER SPECIFICS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Player::die() {
	std::cout << "~~~~~~ YOU HAVE BEEN MADE DIED ~~~~~~" << std::endl;
	std::exit(0);
}

void Player::collectReward(int amount) {
	ballance += amount;
	std::cout << "You have found $" << amount << " bringing your grand total to $" << ballance << std::endl;
}

void Player::pay(int price) {
	ballance -= price;
	std::cout << '$' << price << " well spent!" << std::endl;
}

void Player::levelUp() {
	setLevel(getLevel() + 1);
	maxHealth += 10;
}
