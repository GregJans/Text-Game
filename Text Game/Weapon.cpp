#include "Weapon.h"

int Weapon::getDamage() const { return damage; }
int Weapon::getDurability() const { return durability; }

void Weapon::setDamage(int d) { damage = d; }
void Weapon::setDurability(int d) { durability = d; }
void Weapon::useDurability() { if (durability > 0) setDurability(getDurability() - 1); }