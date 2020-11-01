import kotlin.math.*
import kotlin.random.*

const val MAX_HEALTH = 10
const val MAX_LEVEL = 20
const val POTION_PRICE = 100

fun getRandomNumber(min: Int, max: Int) = Random.nextInt(min, max);

open class Creature
{
    protected var m_name = ""
    protected var m_char = ' '
    protected var m_health = 0
    protected var m_damage = 0
    protected var m_gold = 0

    constructor(name : String, ch : Char, health : Int, damage : Int, gold : Int) {
        m_name = name
        m_char = ch
        m_health = health
        m_damage = damage
        m_gold = gold
    }
    fun getName() : String = m_name
    fun getChar() : Char = m_char
    fun getHealth() : Int = m_health
    fun getDamage() : Int = m_damage
    fun getGold() : Int = m_gold
    fun reduceHealth (health : Int) {
        m_health -= health
    }
    fun isDead() : Boolean = (m_health <= 0)
    fun addGold(gold : Int) {
        m_gold += gold
    }
}

class Player(name : String) : Creature(name, '@', MAX_HEALTH, 1, 0)
{
    private var m_level = 1
    private var hasPotion : Boolean = false
    fun getLevel() : Int = m_level
    fun levelUp() {
        ++m_level
        ++m_damage
    }
    fun buyPotion() {
        hasPotion = true
        m_gold -= POTION_PRICE
    }
    //fun hasPotion() : Boolean = hasPotion
    fun canBuyPotion() : Boolean = (m_gold >= POTION_PRICE)
    fun restoreHealth() {
        if (hasPotion) m_health = MAX_HEALTH
        hasPotion = false
    }
    fun hasWon() : Boolean = (m_level >= MAX_LEVEL)
}

enum class MonsterType {
    DRAGON,
    ORC,
    SLIME,
    GOBLIN,
    BEAST,
    MAX_TYPES;

    companion object {
        private val values = values()
        fun getByValue(value: Int) = values.firstOrNull { it.ordinal == value }!!
    }
}

class MonsterData
{
    var name = ""
    var character = ' '
    var health = 0
    var damage = 0
    var gold = 0

    constructor(name : String, ch : Char, health : Int, damage : Int, gold : Int) {
        this.name = name
        this.character = ch
        this.health = health
        this.damage = damage
        this.gold = gold
    }

}

var monsterData : MutableMap<MonsterType, MonsterData> = mutableMapOf()

class Monster(type : MonsterType) : Creature(monsterData[type]!!.name, monsterData[type]!!.character, monsterData[type]!!.health,
    monsterData[type]!!.damage, monsterData[type]!!.gold)
{
}

fun getRandomMonster() : Monster = Monster(MonsterType!!.getByValue(getRandomNumber(0, (MonsterType.MAX_TYPES.ordinal - 1) * 10) % (MonsterType.MAX_TYPES.ordinal)))

fun attackMonster(player : Player , monster : Monster) {
    if (player.isDead())
        return;

    monster.reduceHealth(player.getDamage());
    println("You hit the ${monster.getName()} for ${player.getDamage()} damage.")

    if (monster.isDead())
    {
        println("You have killed the ${monster.getName()}")
        player.levelUp();
        println("You are now level ${player.getLevel()}, your attack has increased and is now ${player.getDamage()}.")
        player.addGold(monster.getGold());
        println("You found ${monster.getGold()} gold. Now you have ${player.getGold()} gold.")
        if (player.getHealth() < MAX_HEALTH && player.canBuyPotion()) {
            println("Your health is now ${player.getHealth()}, you can buy potion for $POTION_PRICE gold to restore it. Press (B) to buy and restore.")
            val toBuy = readLine()!![0]
            if (toBuy == 'B' || toBuy == 'b') {
                player.buyPotion()
                player.restoreHealth()
            }
        }
    }
    else
        println("${monster.getHealth()} of the monster's health left.")
}

fun attackPlayer(player : Player , monster : Monster) {
    if (monster.isDead())
        return;

    player.reduceHealth(monster.getDamage());
    println("The ${monster.getName()} hit you for ${monster.getDamage()} damage.")

    if (player.isDead())
        return;
    else
        println("${player.getHealth()}  of your health left.")
}

fun fightMonster(player : Player) {
    println("You have ${player.getHealth()} health and are carrying ${player.getGold()} gold. Your damage is ${player.getDamage()}.")
    var monster = getRandomMonster()
    println("\nYou have encountered a ${monster.getName()} (${monster.getChar()}). It has ${monster.getHealth()} health, " +
            "deals ${monster.getDamage()} damage and it's death will bring you ${monster.getGold()} gold.")

    do
    {
        println("(R)un or (F)ight: ")
        val symbol = readLine()!![0]

        if ((symbol == 'R') || (symbol == 'r'))
        {
            if (getRandomNumber(0, 99) >= 50)
            {
                println("You successfully ran away.")
                return;
            }
            else
            {
                println("Running away failed. ")
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
            println("Wrong symbol!")
            continue;
        }
    } while(true);
}


fun main(args: Array<String>) {
    monsterData[MonsterType.DRAGON] = MonsterData("dragon", 'D', 20, 4, 100)
    monsterData[MonsterType.ORC] = MonsterData("orc", 'o', 4, 2, 25)
    monsterData[MonsterType.SLIME] = MonsterData("slime", 's', 1, 1, 15)
    monsterData[MonsterType.GOBLIN] = MonsterData("goblin", 'g', 2, 2, 20)
    monsterData[MonsterType.BEAST] = MonsterData("beast", 'B', 10, 3, 50)

    println("Greetings! This is a simple text game where the player meets random monsters\nand fights them or runs away " +
            "(50% chance of successful running).\nAfter defeating a monster, the player's level increases so as the player's attack.\n" +
            "The player wins the game when reaches $MAX_LEVEL lvl. The game is over when the player runs out of health points.\n " +
            "After level up you can buy health potion for $POTION_PRICE gold to restore health to max. \n" +
            "Beware of dragons, they are a little bit imbalanced and this was made on purpose, so good luck :)")
    println("Enter your name: ")
    val playerName = readLine()!!

    var player = Player(playerName)
    println("Welcome, ${player.getName()}!")

    while ((!player.isDead()) && (!player.hasWon()))
        fightMonster(player);

    if (player.isDead())
        println("You died at level ${player.getLevel()} and with ${player.getGold()} gold.")
    else if (player.hasWon())
        println("Congratulations! You have won with ${player.getGold()} gold.")
}