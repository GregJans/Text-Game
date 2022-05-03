#pragma once
#include<string>
#include<iostream>
#include "Weapon.h"

using std::string;

class Entity
{
public:

	Entity(int lvl, int healthModif, string name) {
		setLevel(lvl);
		setHealth(lvl * healthModif);
		setName(name);
	}

	//getters
	int getHealth() const;
	int getLevel() const;
	int getRewardDrop() const;
	string getName() const;
	Weapon& getWeapon();
	
	//setters
	void setHealth(int newHealth);
	void setLevel(int newLevel);
	void setName(const string& newName);

	virtual void takeDamage(int damage);
	virtual void attack(Entity& target);

protected:
	Weapon weapon;
	int rewardDrop;
	virtual void die();
private:
	int health, level;
	string name;
};

class Ninja : public Entity {
public:
	Ninja(int lvl) : Entity(lvl, 5, "Ninja") {
		rewardDrop = 5;
		weapon = Knife();
	}
};

class Monster : public Entity {
public:
	Monster(int lvl) : Entity(lvl, 100, "Monster") {
		rewardDrop = 10;
		weapon = BaseballBat();
	}
};

class MiniBoss : public Entity {
public:
	MiniBoss(int lvl) : Entity(lvl, 1000, "Mini Boss") {
		rewardDrop = 100;
		weapon = Blaster();
	}
};

class Player : public Entity {
public:
	bool hasItems;
	
	Player(Weapon& wep): Entity(1, 100, "Player") {
		setWeapon(wep);
		maxHealth = 100;
		ballance = 0;
		hasItems = true;
	}

	//getters
	int getBallance() const { return ballance; }
	int getMaxHealth() const { return maxHealth; }

	//setter
	void setWeapon(Weapon& wep) { weapon = wep; }

	//other
	void collectReward(int amount);
	void pay(int price);
	void levelUp();
	void die() override;
private:
	// tracks player's health without taking damage into account
	int maxHealth, ballance;
};

