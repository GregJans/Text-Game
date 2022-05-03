#ifndef WEAPON_H
#define WEAPON_H
#include<string>

class Weapon
{
	int damage, durability;

public:
	//getters
	int getDamage() const;
	int getDurability() const;
	//setters
	void setDamage(int d);
	void setDurability(int d);

	void useDurability();

	std::string name;
};

class Knife : public Weapon {
public:
	Knife() {
		setDamage(20);
		setDurability(10);
		name = "Knife";
	}

};

class BaseballBat : public Weapon {
public:
	BaseballBat() {
		setDamage(100);
		setDurability(5);
		name = "Baseball Bat";
	}
};


class Blaster : public Weapon {
public:
	Blaster() {
		setDamage(1000);
		setDurability(100);
		name = "Blaster";
	}
};

#endif