#include <iostream>
#include <vector>

using namespace std;

enum class HeroClass {
    Warrior,
    Mage,
    Healer,
};

enum class ItemType {
    Weapon,
    Armor,
    Potion, 
};

enum class StatusEffect {
    None,
    Blessed,
    Cursed,
    Poisoned,
};

struct StatusFlags
{
    unsigned int blessed = 1;
    unsigned int cursed = 1;
    unsigned int poisoned = 1;
};

struct WeaponStats {
    int damage;
    int durability;
    bool twoHanded;
};

struct ArmorStats {
    int defense;
    int durability;
    bool magical;
};

struct PotionStats {
    int healAmount;
    int manaAmount;
};

union ItemProperties {
    WeaponStats Weapon;
    ArmorStats Armor;
    PotionStats Potion;
};

struct Item {
    string name;
    ItemType type;
    int weight;
    int value;
    ItemProperties props;
};

struct Hero {
    string name;
    HeroClass heroClass;
    int level;

    int hp; int maxHp;
    int mp; int maxMp;

    StatusFlags status;
    Item* equipment;
    int equippedCount;
};

struct Enemy {
    string name;
    int hp;
    int damage;
};

void printClassInfo() {
    cout << "Available classes:\n";
    cout << "  1 - Warrior  (HP: 100, MP: 20) \n";
    cout << "  2 - Mage     (HP: 60,  MP: 100) \n";
    cout << "  3 - Healer   (HP: 80,  MP: 60) \n";
}

void printItemInfo() {
    cout << "Available classes:\n";
    cout << "  1 - Weapon\n";
    cout << "  2 - Armor\n";
    cout << "  3 - Potion\n";
}

Enemy createEnemy() {
    Enemy enemy;
    cout << "Name: ";
    cin >> enemy.name;

    cout << "HP: ";
    cin >> enemy.hp;

    cout << "Damage:";
    cin >> enemy.damage;
    return enemy;
}

Item itemCreate() {
    Item item;
    

    cout << "Name ";
    cin >> item.name;

    //тип
    int itemChoice = 0;
    while (itemChoice < 1 || itemChoice > 3) {
        printItemInfo();
        cout << "Seletion class (1-3): ";
        cin >> itemChoice;
    }
    switch (itemChoice)
    {
    case 1: item.type = ItemType::Weapon;
        cout << "Damage: ";
        cin >> item.props.Weapon.damage;
        cout << "Durability: ";
        cin >> item.props.Weapon.durability;
        cout << "twoHanded (0,1): ";
        cin >> item.props.Weapon.twoHanded;
        break;
    case 2: item.type = ItemType::Armor;
        cout << "Defense: ";
        cin >> item.props.Armor.defense;
        cout << "Durability: ";
        cin >> item.props.Armor.durability;
        cout << "magical (0,1): ";
        cin >> item.props.Armor.magical;
        break;
    case 3: item.type = ItemType::Potion;

        cout << "Heal+: ";
        cin >> item.props.Potion.healAmount;
        cout << "Mana+: ";
        cin >> item.props.Potion.manaAmount;
        break;
    }

    //Вес
    cout << "Weight: ";
    cin >> item.weight;

    //Колличество
    cout << "Value: ";
    cin >> item.value;

    ItemProperties props;

    return item;
}

Hero createHero() {
    Hero hero;

    //Имя
    cout << "Name: ";
    cin >> hero.name;

    //Класс
    int classChoice = 0;
    while (classChoice < 1 || classChoice > 3) {
        printClassInfo();
        cout << "Seletion class (1-3) :";
        cin >> classChoice;
    }

    //Уровень
    cout << "lvl: ";
    cin >> hero.level;

    switch (classChoice)
    {
        case(1):
            hero.heroClass = HeroClass::Warrior;
            hero.hp = 100+ hero.level *20;
            hero.maxHp = 100 + hero.level * 20;
            hero.mp = 10 + hero.level * 2;
            hero.maxMp = 10 + hero.level * 2;
            break;
        case(2):
            hero.heroClass = HeroClass::Mage;
            hero.hp = 50 + hero.level * 8;
            hero.maxHp = 50 + hero.level * 8;
            hero.mp = 100 + hero.level * 25;
            hero.maxMp = 100 + hero.level * 25;
            break;
        case(3):
            hero.heroClass = HeroClass::Healer;
            hero.hp = 60 + hero.level * 10;
            hero.maxHp = 60 + hero.level * 10;
            hero.mp = 80 + hero.level * 20;
            hero.maxMp = 80 + hero.level * 20;
            break;

    }
    
    //Создаем пространства и чистим

    hero.status.blessed = 0;
    hero.status.cursed = 0;
    hero.status.poisoned = 0;

    hero.equippedCount = 0;
    hero.equipment = new Item[4];

    for (int i = 0; i < 4; i++) {
        hero.equipment[i].name = "None";
        hero.equipment[i].type = ItemType::Potion;
        hero.equipment[i].weight = 0;
        hero.equipment[i].value = 0;
    }

    return hero;
}

void destriyHero(Hero& hero) {
    delete[] hero.equipment;
    hero.equipment = nullptr;
    hero.equippedCount = 0;
}

void printHero(const Hero& hero) {
    cout << "Name: " << hero.name << "\n";

    string className;
    switch (hero.heroClass) {
    case HeroClass::Warrior: className = "Warrior"; break;
    case HeroClass::Mage:    className = "Mage";    break;
    case HeroClass::Healer:  className = "Healer";  break;
    }

    cout << "Class: " << className << "\n";
    cout << "LVL: " << hero.level << "\n";
    cout << "HP: " << hero.hp << "/" << hero.maxHp << "\n";
    cout << "MP: " << hero.mp << "/" << hero.maxMp << "\n";
    cout << "State: ";
    if (!hero.status.blessed && !hero.status.cursed && !hero.status.poisoned) {
        cout << "None";
    }
    else {
        if (hero.status.blessed)  cout << "Blessed ";
        if (hero.status.cursed)   cout << "Cursed ";
        if (hero.status.poisoned) cout << "Poisoned";
    } 
    cout << "\n";

    cout << "Inventory  (slot):\n";
    for (int i = 0; i < 4; ++i) {
        cout << "  [" << i << "] " << hero.equipment[i].name
            << " (type=" << static_cast<int>(hero.equipment[i].type)
            << ", weight=" << hero.equipment[i].weight
            << ", value=" << hero.equipment[i].value << ")\n";
    }
    cout << "closed slot: " << hero.equippedCount << " for 4\n";
}

void printItem(Item& item) {

    cout << "Name: " << item.name << "\n";
    
    switch (item.type) {
    case ItemType::Weapon: cout<<"Item type - Weapon\n Damage: "<<item.props.Weapon.damage<<"\nDurability"<<item.props.Weapon.durability<<"\nTwo Handed"<<item.props.Weapon.twoHanded; break;
    case ItemType::Armor: cout << "Item type - Armor\n Defense: " << item.props.Armor.defense << "\nDurability" << item.props.Armor.durability << "\nMagical" << item.props.Armor.magical; break;
    case ItemType::Potion: cout << "Item type - Potion\n Heal: " << item.props.Potion.healAmount << "\nMana" << item.props.Potion.manaAmount;  break;
    }
    cout << "Weight: " << item.weight << "\n";
    cout << "Value: " << item.value << "\n";
    
    
}

void printEnemy(Enemy& enemy) {

    cout << "Name: " << enemy.name << "\n";
    cout << "HP: " << enemy.hp << "\n";
    cout << "Damage: " << enemy.damage<< "\n";


}

int printActionMenu() {
	int selection;  
    cout << "\n--- Action Menu ---\n";
    cout << "1 - Attack\n";
    cout << "2 - Ability\n";
    cout << "0 - End Turn\n";
    cout << "Select action: ";
	cin >> selection;
	return selection;
}

void printInventory(Hero& hero) {
	cout << "\n--- Inventory ---\n";
	for (int i = 0; i < hero.equippedCount; ++i) {
		cout << "[" << i + 1 << "] " << hero.equipment[i].name
			<< " (type=" << static_cast<int>(hero.equipment[i].type)
			<< ", weight=" << hero.equipment[i].weight
			<< ", value=" << hero.equipment[i].value << ")\n";
	}
	if (hero.equippedCount == 0) {
		cout << "Inventory is empty.\n";
	}
}

int main()
{
    int idSelect,idSelectMenu;
    vector<Hero> heroes;
    vector<Enemy> enemys;
    vector<Item> items;
    
    cout << "START GAME : Lab 2\n" << endl;
    
    do {
        cout << "\n";
        cout << "\n1 - Create Player";
        cout << "\n2 - List Player";

        cout << "\n3 - Create Enemy";
        cout << "\n4 - List Enemy";

		cout << "\n5 - Create Item";
		cout << "\n6 - List Item";

        cout << "\n9 - Play";

        cout << "\n0 - Exit\nSelection: ";
        cin >> idSelectMenu;

		cout << "\n";
        bool game = true;
        switch (idSelectMenu) {
        case 1:
            heroes.push_back(createHero());//Создание персонажа
            break;

        case 2:
            if (heroes.empty()) {// Нет созданных персонажей
                cout << "\nDon't create players\n";
            }
            else {
                for (size_t i = 0; i < heroes.size(); ++i) {
                    cout << "\n--- Player - " << heroes[i].name << " -#" << (i + 1) << " ---\n";
                    printHero(heroes[i]);  // printHero принимает const Hero&
                }

                cout << "\n1 - open player (id)\n0-exit\nSelection: ";
                cin >> idSelect;
                int idSelectHero = idSelect - 1;
                while (idSelect) { // Выбор героя
                    printHero(heroes[idSelectHero]);
                    cout << "\n1 - add item inventory\n2 - delete item inventory\n0-Back Menu\nSelection: ";
                    cin >> idSelect;
                    if (idSelect) { // Функии с ивенторем персонажа
                            
                        switch (idSelect)
                        {
                        case 1://Добавляем в инветарь предмет из списка

                            if (idSelect && items.empty()) { // Если нет предметов можно создать
                                cout << "\nDont Item list\ncreate Item - 1\nback - 0\n Selection: ";
                                cin >> idSelect;
                                if (idSelect) {//создание
                                    items.push_back(itemCreate());
                                    cout << "\nItem Create\n";
                                }
                            }
                            else {
                                cout << "\nSelection ID Item\n";
                                for (size_t i = 0; i < items.size(); ++i) {
									cout << "\n--- Item - " << items[i].name << " -#" << (i + 1) << " ---\n";
                                    printItem(items[i]);//выврдим список предметов
									cout << "\n";
                                }
                                cout << "\n0 - Back\nSelect: ";
                                cin >> idSelect;

                                if (idSelect && !items.empty()) {//если есть предмет


                                    if (heroes[idSelectHero].equippedCount < 4) {
                                        heroes[idSelectHero].equipment[heroes[idSelectHero].equippedCount] = items[idSelect - 1];
                                        heroes[idSelectHero].equippedCount++;
                                    }
                                    else {
                                        cout << "\nInventory is full\n";

                                    }
                                }
                            }


                            break;

                        case 2:  //Удаляем предмет из инвентаря


                            // Показываем предметы
                            for (int i = 0; i < heroes[idSelectHero].equippedCount; ++i) {
                                cout << "\n[" << i + 1 << "] " << heroes[idSelectHero].equipment[i].name;
                            }
                            cout << "\nSelect ID item for delete (1-" << heroes[idSelectHero].equippedCount << "): ";
                            cin >> idSelect;

                            int index = idSelect - 1;  // переводим в 0-based индекс


                            

                            // Сдвигаем элементы влево, начиная с index+1
                            for (int i = index; i < heroes[idSelectHero].equippedCount - 1; ++i) {
                                heroes[idSelectHero].equipment[i] = heroes[idSelectHero].equipment[i + 1];
                            }

                            heroes[idSelectHero].equipment[3].name = "None";
                            heroes[idSelectHero].equipment[3].type = ItemType::Potion;
                            heroes[idSelectHero].equipment[3].weight = 0;
                            heroes[idSelectHero].equipment[3].value = 0;

                            // Уменьшаем счётчик
                            heroes[idSelectHero].equippedCount--;

                            cout << "item delete.\n";

                            break;
                        
                        }
                    }
                    
                }
                break;
                
            }
		case 3:
			enemys.push_back(createEnemy());
			break;
		case 4:
			if (enemys.empty()) {
				cout << "\nDont create enemys\n";
			}
			else {
				for (size_t i = 0; i < enemys.size(); ++i) {
					cout << "\n--- Enemy - " << enemys[i].name << " -#" << (i + 1) << " ---\n";
					printEnemy(enemys[i]);
                    cout << "\n";
				}
				
                cout << "\n(id) - Delete  Enemy\n0 - Back\nSelect: ";
                cin >> idSelect;

				if (idSelect && !enemys.empty()) {
					int index = idSelect - 1;  // переводим в 0-based индекс
					// Сдвигаем элементы влево, начиная с index+1
					for (int i = index; i < enemys.size() - 1; ++i) {
						enemys[i] = enemys[i + 1];
					}
					// Уменьшаем размер вектора
					enemys.pop_back();
					cout << "enemy delete.\n";
				}
			}
			break;
		case 5:
			items.push_back(itemCreate());
			break;
		case 6:
			if (items.empty()) {
				cout << "\nDont create items\n";
			}
			else {
				for (size_t i = 0; i < items.size(); ++i) {
					cout << "\n--- Item - " << items[i].name << " -#" << (i + 1) << " ---\n";
					printItem(items[i]);
                    cout << "\n";
				}
                cout << "\n";

                cout << "\n0 - Back\n1 - Delete\nSelect: ";
                cin >> idSelect;
				if (idSelect) {
					cout << "\nSelect ID item for delete (1-" << items.size() << "): ";
					cin >> idSelect;
					int index = idSelect - 1;  // переводим в 0-based индекс

					// Сдвигаем элементы влево, начиная с index+1
					for (int i = index; i < items.size() - 1; ++i) {
						items[i] = items[i + 1];
					}
					// Уменьшаем размер вектора
					items.pop_back();
					cout << "item delete.\n";
				}

			}
			break;

		case 9:
			cout << "\nGame Start\n";
			

            while (game) {
				// Игровой процесс
                // 1  Статусные эффекты 
                for (int i = 0; i < heroes.size(); ++i) {
                    // Игровой процесс для каждого героя
                    int damage = 3; // Пример урона, который герой получает
                    if (heroes[i].status.poisoned) {
                        if (heroes[i].status.blessed) {
                            damage *= 2; // Уменьшаем HP на 2

                        }
                        heroes[i].hp -= damage; // Уменьшаем HP на 5
                        cout << heroes[i].name << " is poisoned! HP reduced by " << damage << "HP\n";
                    }
                }
                // 2  Ход героев
                
				for (int i = 0; i < heroes.size(); ++i) {
					cout << "\n--- Hero - " << heroes[i].name << " -#" << (i + 1) << " ---\n";
					printHero(heroes[i]);

					int action = printActionMenu();

					int damage = 3; // Пример урона/лечения
					float damageAbility = 5; // Пример урона способностью
					int manaCost = 10; // Пример стоимости маны для способности
					

                    switch (heroes[i].heroClass)
                    {
					case HeroClass::Warrior:
                        damage = 15;
                        damageAbility = 1.5;
                        manaCost = 20;
                        break;
					case HeroClass::Mage:
                        damage = 15;
                        damageAbility = 3;
                        manaCost = 20;
                        break;
					case HeroClass::Healer:
                        damage = 6;
                        damageAbility = 1;
                        manaCost = 40;
                        break;
                    }

                    if (action) {
                        switch (action)
                        {
						case 1: // Attack
							cout << heroes[i].name << " attacks the enemy!\n";

							for (int j = 0; j < enemys.size(); ++j) {
								cout << "\n--- Enemy - " << enemys[j].name << " -#" << (j + 1) << " ---\n";
								cout << "HP: " << enemys[j].hp << "\n";
							}
							cout << "\nSelect Enemy to attack (1-" << enemys.size() << "): ";
							cin >> idSelect;
							cout << "\n";
                            if (heroes[i].equippedCount) {
								for (int j = 0; j < heroes[i].equippedCount; ++j) {
									if (heroes[i].equipment[j].type == ItemType::Weapon) {
										damage += heroes[i].equipment[j].props.Weapon.damage;
										break; // Используем только первое найденное оружие
									}
								}
                            }
                            if (heroes[i].status.blessed) {
                                enemys[idSelect - 1].hp -= round(damage * damageAbility*2); // Пример урона, который герой наносит врагу
                            }
                            else if(heroes[i].status.cursed) {
                                enemys[idSelect - 1].hp -= round(damage * damageAbility*0.5); // Пример урона, который герой наносит врагу
                            }
                            
                            else {
                                enemys[idSelect - 1].hp -= round(damage * damageAbility); // Пример урона, который герой наносит врагу
                            }
							break;

						case 2: // Ability
							

                            if (heroes[i].heroClass != HeroClass::Healer) {


                                for (int j = 0; j < enemys.size(); ++j) {
                                    cout << "\n--- Enemy - " << enemys[j].name << " -#" << (j + 1) << " ---\n";
									cout << "HP: " << enemys[j].hp << "\n";
                                }
                                cout << "\nSelect Enemy to attack (1-" << enemys.size() << "): ";
                                cin >> idSelect;

                                if (heroes[i].equippedCount) {
                                    for (int j = 0; j < heroes[i].equippedCount; ++j) {
                                        if (heroes[i].equipment[j].type == ItemType::Weapon) {
                                            damage += heroes[i].equipment[j].props.Weapon.damage;
                                            break; // Используем только первое найденное оружие
                                        }
                                    }
                                }

                                if (heroes[i].mp >= manaCost) {
                                    heroes[i].mp -= manaCost; // Уменьшаем MP на стоимость способности
                                    if (heroes[i].status.blessed) {
                                        enemys[idSelect - 1].hp -= round(damage * damageAbility * 2); // Пример урона, который герой наносит врагу
                                    }
                                    else if (heroes[i].status.cursed) {
                                        enemys[idSelect - 1].hp -= round(damage * damageAbility * 0.5); // Пример урона, который герой наносит врагу
                                    }
                                    else {
                                        enemys[idSelect - 1].hp -= round(damage * damageAbility); // Пример урона, который герой наносит врагу
                                    }
                                }
                                else {
                                    enemys[idSelect - 1].hp -= round(damage); // Пример урона, который герой наносит врагу
                                }
							}
							else {
								// Лечение союзника
                                for (size_t i = 0; i < heroes.size(); ++i) {
                                    cout << "\n--- Player - " << heroes[i].name << " -#" << (i + 1) << " ---\n";
									cout << "HP: " << heroes[i].hp << "/" << heroes[i].maxHp << "\n";
                                }

								cout << "\nSelect Hero to heal (1-" << heroes.size() << "): ";
								cin >> idSelect;
								if (heroes[i].mp >= manaCost) {
									heroes[i].mp -= manaCost; // Уменьшаем MP на стоимость способности
									heroes[idSelect - 1].hp += round(damage * damageAbility); // Пример лечения союзника
									if (heroes[idSelect - 1].hp > heroes[idSelect - 1].maxHp) {
										heroes[idSelect - 1].hp = heroes[idSelect - 1].maxHp; // Ограничиваем HP максимальным значением
									}
								}
								else {
									cout << "Not enough MP to use ability.\n";
								}
							}

							break;
                        
                        }
                    }

				}

                // 3
                
				for (int i = 0; i < heroes.size();++i) {

					cout << "\n--- Hero - " << heroes[i].name << " -#" << (i + 1) << " ---\n";
                    printInventory(heroes[i]);

                    cout << "\nSelect Item to use (1-" << heroes[i].equippedCount << "): ";
					cout << "\n0 - Skip\nSelect: ";
                    cin >> idSelect;
					cout << "\n";
                    if (idSelect && idSelect <= heroes[i].equippedCount) {
                        Item& selectedItem = heroes[i].equipment[idSelect - 1];
                        switch (selectedItem.type) {
                        case ItemType::Weapon:
                            cout << heroes[i].name << " equips the weapon: " << selectedItem.name << "\n";
                            break;
                        case ItemType::Armor:
                            cout << heroes[i].name << " equips the armor: " << selectedItem.name << "\n";
                            break;
                        case ItemType::Potion:
                            cout << heroes[i].name << " uses the potion: " << selectedItem.name << "\n";
                            // Применяем эффект зелья
                            heroes[i].hp += selectedItem.props.Potion.healAmount;
                            if (heroes[i].hp > heroes[i].maxHp) {
                                heroes[i].hp = heroes[i].maxHp; // Ограничиваем HP максимальным значением
                            }
                            heroes[i].mp += selectedItem.props.Potion.manaAmount;
                            if (heroes[i].mp > heroes[i].maxMp) {
                                heroes[i].mp = heroes[i].maxMp; // Ограничиваем MP максимальным значением
                            }
                            break;
                        }
                    }
                    else {
                        cout << "Invalid item selection.\n";
                    }

                    cout << heroes[i].name << " uses an item!\n";
                    
                    break;

				}
               
                // 4
                
				for (int i = 0; i < enemys.size(); ++i) {
					if (enemys[i].hp > 0) {
						cout << enemys[i].name << " attacks!\n";
						for (int j = 0; j < heroes.size(); ++j) {
							cout << "\n--- Hero - " << heroes[j].name << " -#" << (j + 1) << " ---\n";
							cout << "HP: " << heroes[j].hp << "/" << heroes[j].maxHp << "\n";
						}
						cout << "\nSelect Hero to attack (1-" << heroes.size() << "): ";
						cin >> idSelect;

						heroes[idSelect-1].hp -= enemys[i].damage; // Враг наносит урон герою
						cout << "\n";
					}
				}

				// Проверка состояния героев после действий врагов
				int heroesAlive = 0;
				for (int i = 0; i < heroes.size(); ++i) {
					if (heroes[i].hp > 0) {
						heroesAlive++;
					}
				}
				if (heroesAlive == 0) {
					cout << "\n\n\nAll heroes have been defeated! Game Over.\n\n\n";
					game = false;
					break;
				}

                // 5

				for (int i = 0; i < heroes.size(); ++i) {
					
					printHero(heroes[i]);
					if (heroes[i].hp <= 0) {
						cout << heroes[i].name << " has been defeated!\n";
					}
				}
                
            }
			break;
        case 0:
            break;
        }

        
        
    } while (idSelectMenu);
    

    if (!heroes.empty()) {
        for (int i = 0;i < heroes.size();++i) {
            destriyHero(heroes[i]);
        }
    }
    
    

    cout << "GameOver" << endl;
    return 0;
}

