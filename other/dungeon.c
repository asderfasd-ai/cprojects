#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct Room Room;
enum Direction { NORTH, SOUTH, EAST, WEST, DIR_COUNT };

struct Room {
  char *name;
  char *desc;

  Room *exit[DIR_COUNT];
};

typedef struct {
  Room town[2];
  Room trail[6];
} World;

typedef struct {
  int hp;
  int dmg;
} monsterStats;

typedef struct {
  int hp;
  int dmg;
  int sp;
  int armor;
  Room *location;
} playerStats;

// typedef struct {
//   int itemNum;
// } Bag;
int bag[10];
playerStats player;
typedef struct {
  int equippedNum;
} Equipment;

Equipment slot[3];

playerStats playerStat = {100, 10, 10, 20};
monsterStats monsterStat[6] = {{10, 1}, {15, 2}, {25, 4},
                               {30, 6}, {50, 8}, {75, 10}};

typedef enum {
  BANDAGE,
  POTION,
  DAGGER,
  SHORTSWORD,
  BROADSWORD,
  AXE,
  CLOTH,
  LEATHER,
  IRON,
  STEEL,
  MITHRIL,
  ICOUNT
} Items;

typedef enum { RAT, KOBOLD, ORC, OGRE, TROLL, WYVERN, MCOUNT } Monster;

const char *monster_names[] = {[WYVERN] = "wyvern", [TROLL] = "troll",
                               [OGRE] = "ogre",     [ORC] = "orc",
                               [KOBOLD] = "kobold", [RAT] = "rat"};

const char *item_names[] = {
    [BANDAGE] = "bandage",        [POTION] = "potion",
    [DAGGER] = "small dagger",    [SHORTSWORD] = "short sword",
    [BROADSWORD] = "broad sword", [AXE] = "large axe",
    [CLOTH] = "cloth rags",       [LEATHER] = "leather breastplate",
    [IRON] = "iron breastplate",  [STEEL] = "steel armor",
    [MITHRIL] = "mithril plate"};

const char *get_monster_names(Monster c) {
  if (c >= 0 && c < MCOUNT) {
    return monster_names[c];
  }
  return "Unknown";
}

const char *get_item_names(Items c) {
  if (c >= 0 && c < ICOUNT) {
    return item_names[c];
  }
  return "Unknown";
}
void initWorld(World *world);
void initPlayer(void);
int printIntro(void);
void showInventory();
void campFire(void);
void commandPrompt();
void restBreak();
int selectAction(void);

Monster createMonster(void);

int main() {
  World world;
  initWorld(&world);

  srand(time(NULL));
  int choice = printIntro();
  initPlayer();
  player.location = &world.town[1];
  campFire();
  //  selectAction();

  // Monster monster = createMonster();
  // printf("a wild %s appears!\n", get_monster_names(monster));
  // printf("hp is %d\n", monsterStat[monster].hp);
  // printf("damage is %d\n", monsterStat[monster].dmg);

  return 0;
}

void initWorld(World *world) {

  world->town[0].name = "Towni west\n";
  world->town[0].desc = "\nShops n shit\n";
  world->town[0].exit[EAST] = &world->town[1];

  world->town[1].name = "Town east\n";
  world->town[1].desc = "Second town room\n";
  world->town[1].exit[WEST] = &world->town[0];
}

void commandLook(Room *location) {
  printf("%s", location->name);
  printf("%s", location->desc);
  printf("\nExits:"); // DO EXITS.
  if (location->exit[NORTH] != NULL)
    printf(" north");
  if (location->exit[EAST] != NULL)
    printf(" east");
  if (location->exit[WEST] != NULL)
    printf(" west");
  if (location->exit[SOUTH] != NULL)
    printf(" south");
  printf("\n");
}

void initPlayer(void) {
  int i;
  for (i = 0; i < 10; i++) {
    bag[i] = -1;
  }
  bag[0] = BANDAGE;
  bag[1] = CLOTH;
  bag[2] = DAGGER;
}

int printIntro(void) {
  int choice;
  printf("===========================\n");
  printf("     Dungeon Adventure     \n");
  printf("===========================\n\n\n\n");
  printf("1.  Explore\n");
  printf("2.  Quit\n\n");
  printf("Choice? ");
  scanf("%d", &choice);
  return choice;
}

void showInventory() {
  int i;
  printf("\n");
  for (i = 0; i <= 10; i++) {
    if (bag[i] != -1) {
      printf("%s\n", get_item_names(bag[i]));
    }
  }
  commandPrompt();
}

void campFire(void) {
  int choice;
  /* Sort of a break between engagements to check inventory, change equipment,
   * or heal etc..*/
  printf("\n-----------------------------\n");
  printf("1) Inventory  3) Continue    \n");
  printf("2) Rest       4) Save & Quit \n");
  printf("-----------------------------\n\n\n");
  printf("How will you proceed? \n");
  commandPrompt();

  scanf("%d", &choice);
  if (choice == 1) {
    showInventory();
    sleep(1);
    campFire();
  }
  if (choice == 2) {
    restBreak();
  }
  if (choice == 3) {
    selectAction();
  }
  if (choice == 4) {
    commandLook(player.location);
  }
}

void restBreak() {
  int chance = rand() % 100 + 1;
  printf("You decide to rest...\n");
  printf("waiting 3 seconds...\n");
  sleep(3);
  if (chance >= 50) {
    printf("ambush\n");
  } else {
    printf("regain health\n");
    sleep(1);
    campFire();
  }
}

void commandPrompt() {
  printf("HP: %d SP: %d > ", playerStat.hp, playerStat.sp);
}

Monster createMonster(void) {
  int num = rand() % 100 + 1;

  if (num >= 95) {
    return WYVERN;
  }
  if (num >= 85) {
    return TROLL;
  }
  if (num >= 70) {
    return OGRE;
  }
  if (num >= 50) {
    return ORC;
  }
  if (num >= 30) {
    return KOBOLD;
  }
  return RAT;
}

int selectAction(void) {
  int choice;
  Monster monster = createMonster();

  printf("\nYou have decided to continue...\n\n\n");
  printf("a wild %s appears!\n", get_monster_names(monster));
  printf("\nHow will you proceed?\n\n");
  printf("-----------------------------\n");
  printf("1) Attack          3) Use item\n");
  printf("2) Cast spell      4) Run away\n");
  printf("-----------------------------\n");
  commandPrompt();
  scanf("%d", &choice);
  return choice;
}
