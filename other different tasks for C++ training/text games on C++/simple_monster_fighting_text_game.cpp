#include <iostream>
#include <string>
#include <ctime>

/*

    This program demonstrates a simple text game, where the player meets random monsters and fights them or runs away
    (50% chance of successful running). After defeating a monster, the player's level increases so as the player's attack.
    The player wins the game when reaches 20 lvl. The game is over when the player runs out of health points.

    The data table with all monster types and characteristics are in the static array monsterData. 
    The characteristics are left as stated in the task, so without super luck it is nearly impossible to win the game
    (though adding the health restoration with leveling up (in Player::levelUp()) seems to be a solution).
    The random function is also left as stated in the task.

*/

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

class Creature
{
protected:
    std::string m_name;
    char m_char;
    int m_health;
    int m_damage;
    int m_gold;
public:
    Creature(std::string name, char ch, int health, int damage, int gold) :
        m_name{name}, m_char{ch}, m_health{health}, m_damage{damage}, m_gold{gold}
    {

    }

    const std::string& getName()
    {
        return m_name;
    }

    char getChar()
    {
        return m_char;
    }

    int getHealth()
    {
        return m_health;
    }

    int getDamage()
    {
        return m_damage;
    }

    int getGold()
    {
        return m_gold;
    }

    void reduceHealth(int health)
    {
        m_health -= health;
    }

    bool isDead()
    {
        return (m_health <= 0);
    }

    void addGold(int gold)
    {
        m_gold += gold;
    }
};

class Player : public Creature
{
private:
    int m_level = 1;
public:
    Player(std::string name) :
        Creature(name, '@', 10, 1, 0)
    {

    }

    int getLevel()
    {
        return m_level;
    }

    void levelUp()
    {
        ++m_level;
        ++m_damage;
    }

    bool hasWon()
    {
        return (m_level >= 20);
    }

};

class Monster : public Creature
{
public:
    enum Type
    {
        DRAGON,
        ORC,
        SLIME,
        MAX_TYPES
    };

    struct MonsterData
    {
        std::string name;
        char character;
        int health;
        int damage;
        int gold;
    };

    static MonsterData monsterData[MAX_TYPES];

    Monster(Type type) :
        Creature(monsterData[type].name, monsterData[type].character, monsterData[type].health,
                  monsterData[type].damage, monsterData[type].gold)
    {

    }

    static Monster getRandomMonster()
    {
        int type = getRandomNumber(0, MAX_TYPES - 1);
        return Monster(static_cast<Type>(type));
    }
};

Monster::MonsterData Monster::monsterData[Monster::MAX_TYPES]
{
    { "dragon", 'D', 20, 4, 100 },
    { "orc", 'o', 4, 2, 25 },
    { "slime", 's', 1, 1, 10 }
};

void attackMonster(Player& player, Monster& monster)
{
    if (player.isDead())
        return;

    monster.reduceHealth(player.getDamage());
    std::cout << "You hit the " << monster.getName() << " for " << player.getDamage() << " damage. ";

    if (monster.isDead())
    {
        std::cout << "You have killed the " << monster.getName() << std::endl;
        player.levelUp();
        std::cout << "You are now level " << player.getLevel() << ", your attack has increased and is now " << player.getDamage() << std::endl;
        std::cout << "You found " << monster.getGold() << " gold." << std::endl;
        player.addGold(monster.getGold());
    }
    else
        std::cout << monster.getHealth() << " of the monster's health left." << std::endl;
}

void attackPlayer(Player& player, Monster& monster)
{
    if (monster.isDead())
        return;

    player.reduceHealth(monster.getDamage());
    std::cout << "The " << monster.getName() << " hit you for " << monster.getDamage() << " damage. ";

    if (player.isDead())
        return;
    else
        std::cout << player.getHealth() << " of your health left." << std::endl;
}

void fightMonster(Player& player)
{
    std::cout << "You have " << player.getHealth() << " health and are carrying " << player.getGold() << " gold." << std::endl;
    Monster monster = Monster::getRandomMonster();
    std::cout << "You have encountered a " << monster.getName() << " (" << monster.getChar() << ")." << std::endl;

    do
    {
        std::cout << "(R)un or (F)ight: ";
        char symbol;
        std::cin >> symbol;

        if ((symbol == 'R') || (symbol == 'r'))
        {
            if (getRandomNumber(0, 1) == 1)
            {
                std::cout << "You successfully ran away."  << std::endl;
                return;
            }
            else
            {
                std::cout << "Running away failed. ";
                attackPlayer(player, monster);
                if (player.isDead()) return;
                continue;
            }
        }
        else if ((symbol == 'F') || (symbol == 'f'))
        {
            attackMonster(player, monster);

            while((!monster.isDead()) && (!player.isDead()))
            {
                attackPlayer(player, monster);
                attackMonster(player, monster);
            }
            return;
        }
        else
        {
            std::cout << "Wrong symbol!" << std::endl;
            continue;
        }
    } while(true);
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    rand();
    std::cout << "Greetings! This is a simple text game where the player meets random monsters\nand fights them or runs away " <<
        "(50% chance of successful running).\nAfter defeating a monster, the player's level increases so as the player's attack.\n" <<
        "The player wins the game when reaches 20 lvl. The game is over when the player runs out of health points.\n" <<
        "Beware of dragons, they are a little bit imbalanced and this was made on purpose, so good luck :)" << std::endl;
    std::cout << "Enter your name: ";
    std::string playerName;
    std::cin >> playerName;

    Player player(playerName);
    std::cout << "Welcome, " << player.getName() << ".\n";

    while ((!player.isDead()) && (!player.hasWon()))
        fightMonster(player);

    if (player.isDead())
        std::cout << "You died at level " << player.getLevel() << " and with " << player.getGold() << " gold." << std::endl;
    else if (player.hasWon())
        std::cout << "Congratulations! You have won with " << player.getGold() << " gold." << std::endl;
    system("pause");
    return 0;
}
