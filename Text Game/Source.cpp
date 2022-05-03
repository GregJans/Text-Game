#include<iostream>
#include<vector>
#include<iomanip>
#include "Entity.h"
#include "Item.h"
#include<ctime>
#include<cstdlib>

void printMenu();
void useInventory();
void useShop();
void levelOver();
void playLevel(int lvlNum);
void changeWeapon();
void generateEnemies(int lvlNum);


// level and/or enemy data
std::vector<Entity> enemiesLeft;
std::vector<int> enumber = { 1, 2, 1, 5, 2, 1 };
std::vector<Entity> levelEnemies;

//player data
std::vector<Weapon> wepOptions = { Knife() };
Player player = Player(wepOptions[0]);
int StrengthPotion::initialPlayerDamage = player.getWeapon().getDamage();
int currentLevel = 1;

int main() {
	int ans;

	do {
		std::cout << "Welcome to [Generic Game Name]" << std::endl;
		std::cout << "Options:" <<
			std::endl << '\t' << "1) Play Next Level" <<
			std::endl << '\t' << "2) Change Weapons" <<
			std::endl << '\t' << "3) Visit Shop" <<
			std::endl << '\t' << "0) Quit" <<
			std::endl << "> ";

		std::cin >> ans;

		switch (ans)
		{
		case 1:
			if (currentLevel <= enumber.size()) playLevel(currentLevel);
			else std::cout << "You have completed all levels" << std::endl;
			break;
		case 2:
			changeWeapon();
			break;
		case 3:
			useShop();
			break;
		default:
			break;
		}
	} while (ans != 0);
	
}

void playLevel(int lvlnum) {
	generateEnemies(lvlnum);
	enemiesLeft = levelEnemies;
	Entity* currentEnemy;
	int choice;

	do {
		if (enemiesLeft.size() >= 1) currentEnemy = &enemiesLeft.back();
		else {
			levelOver();
			break;
		}

		printMenu();
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			system("cls");
			std::cout << "You chose to attack the lvl:" << currentEnemy->getLevel() << ' ' << currentEnemy->getName() << " with health : " << currentEnemy->getHealth() << std::endl;

			StrengthPotion::turnsLeft--;
			if (StrengthPotion::turnsLeft == 0) {
				player.getWeapon().setDamage(StrengthPotion::initialPlayerDamage);
				std::cout << "Oh No! Your Strength Potion has run out" << std::endl;
			}

			player.attack(*currentEnemy);

			if (currentEnemy->getHealth() <= 0) {
				enemiesLeft.pop_back();
				player.collectReward(currentEnemy->getRewardDrop());
			}
			else {
				std::cout << "The new health is: " << currentEnemy->getHealth() << std::endl;

				currentEnemy->attack(player);
				std::cout << "The " << currentEnemy->getName() << " has attacked for " << currentEnemy->getWeapon().getDamage() << std::endl;
			}
			break;
		case 2:
			system("cls");
			useInventory();
		default:
			break;
		}

		

	} while (choice != 0);
	
}

void generateEnemies(int lvlNum) {
	srand(time(NULL));
	levelEnemies.clear();

	for (int i = 0; i < enumber[lvlNum - 1]; i++) {

		switch (lvlNum)
		{
		case 1:
			levelEnemies.push_back(Ninja((rand() % 5) + 1));
			break;
		case 2:
			levelEnemies.push_back(Ninja((rand() % 5) + 10));
			break;
		case 3:
			levelEnemies.push_back(Monster((rand() % 10) + 5));
			break;
		case 4:
			levelEnemies.push_back(Ninja((rand() % 10) + 10));
			break;
		case 5:
			levelEnemies.push_back(Monster((rand() % 5) + 20));
			break;
		case 6:
			levelEnemies.push_back(MiniBoss(5));
		default:
			break;
		}
	}
}

void printMenu() {
	std::cout << "Enemies: " << std::endl;
	for (Entity e : enemiesLeft) {
		std::cout << '\t' << "Entity Type: " << std::setw(10) << std::left << e.getName();
		std::cout << std::setw(20) << std::right << "Level: " << std::setw(3) << std::left << e.getLevel();
		std::cout << std::setw(20) << std::right << "Health: " << e.getHealth() << std::endl;
	}
	std::cout << std::endl << "Your Health: " << player.getHealth() << '/' << player.getMaxHealth() << std::endl;


	std::cout << std::endl << "Options:\n 1) Attack\n 2) View Inventory\n 0) Run" << std::endl << "> ";
}

void levelOver() {
	system("cls");
	std::cout << " ~~~~~~~ LEVEL COMPLETE ~~~~~~~~" << std::endl;
	currentLevel++;

	if (currentLevel == 2) {
		wepOptions.push_back(BaseballBat());
		std::cout << "Baseball Bat Unlocked!" << std::endl;
	}
	else if (currentLevel == 3) {
		wepOptions.push_back(Blaster());
		std::cout << "Blaster Unlocked!" << std::endl;
	}

	player.levelUp();
}

void changeWeapon() {
	system("cls");
	int count = 1, response;

	std::cout << "Choose your weapon:" << std::endl;
	for (Weapon& w : wepOptions) {
		std::cout << '\t' << count << ") " << w.name << " / damage: " << w.getDamage() << " / durability: " << w.getDurability() << std::endl;
		count++;
	}

	std::cout << "> ";
	std::cin >> response;

	player.setWeapon(wepOptions[response - 1]);
}

void useInventory() {
	
	if (!player.hasItems) {
		std::cout << "Your Inventory is empty" << std::endl;
		return;
	}

	int response;
	do {

		std::cout << "Choose your Category:" << std::endl;

		std::cout << "\t1) Potions" << std::endl << "\t2) Explosives" << std::endl << "\t0) Back" << std::endl << "> ";

		std::cin >> response;

		switch (response)
		{
		case 1:
			system("cls");
			std::cout << "Potions:" << std::endl;
			for (int i = 0; i < Potion::potion_names.size(); i++) {
				std::cout << '\t' << i + 1 << ") " << Potion::quantities[i] << "x " << Potion::potion_names[i] << std::endl;
			}

			std::cout << "> ";
			std::cin >> response;

			if (response - 1 == Potion::HEALTH) {
				if (Potion::quantities[Potion::HEALTH] > 0) HealthPotion::use(player);
				else std::cout << "You do not have any of that item" << std::endl;
			}
			else if (response - 1 == Potion::STRENGTH) {
				if (Potion::quantities[Potion::STRENGTH] > 0) {
					StrengthPotion::turnsLeft = 3;
					StrengthPotion::use(player);
				}
				else std::cout << "You do not have any of that item" << std::endl;
			}
			break;
		case 2:
			std::cout << "That feature is not currently avaliable" << std::endl;
			break;

		default:
			break;
		}
	} while (response != 0);
}

void useShop() {
	int response;
	do {

		std::cout << "Choose your Category:" << std::endl;
		std::cout << "\t1) Potions" << std::endl << "\t2) Explosives" << std::endl << "\t0) Back" << std::endl << "> ";

		std::cin >> response;

		switch (response)
		{
		case 1:
			system("cls");
			std::cout << "Potions:" << std::endl;
			for (int i = 0; i < Potion::potion_names.size(); i++) {
				std::cout << '\t' << i + 1 << ") " << Potion::potion_names[i] << " ($" << Potion::price << " each)" << std::endl;
			}
			std::cout << "Your current ballance is: " << player.getBallance() << std::endl;
			std::cout << "> ";
			std::cin >> response;

			if (player.getBallance() < Potion::price) std::cout << "Sorry but you do not have enough funds" << std::endl;

			//else
			try { Potion::quantities[response - 1]++; player.pay(Potion::price); }
			catch (...) { std::cout << "Nothing Purchased"; }
			
			break;
		case 2:
			std::cout << "That feature is not currently avaliable" << std::endl;
			break;

		default:
			break;
		}
	} while (response != 0);
}
