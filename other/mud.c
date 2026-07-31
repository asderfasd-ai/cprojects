#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// COLORS
#define RESET "\x1b[0m"
#define BLACK "\x1b[30m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"
#define BOLD "\x1b[1m"

typedef struct Room Room;
typedef struct Object Object;
typedef struct Mobile Mobile;
typedef enum { RAT, CRAB, SEAGULL, JELLYFISH, SHARK, WHALE, MCOUNT } MobileType;
enum Direction { NORTH, SOUTH, EAST, WEST, DIR_COUNT };

struct Room {
  char *name;
  char *desc;
  Object *objects;
  Mobile *mobiles;

  Room *exit[DIR_COUNT];
};

typedef struct {
  Room town[9];
  Room trail[6];
} World;

struct Mobile {
  MobileType type;
  int hp;
  int dmg;
  Mobile *next;
};

typedef struct {
  int hp;
  int maxhp;
  int dmg;
  int sp;
  int maxsp;
  int armor;
  int inv[5];
  Room *location;
} Player;

int bag[10];
typedef struct {
  int equippedNum;
} Equipment;

Player player = {.hp = 100,
                 .maxhp = 100,
                 .dmg = 10,
                 .sp = 10,
                 .maxsp = 10,
                 .armor = 20,
                 .location = NULL};

typedef enum {
  BANDAGE,
  POTION,
  KNIFE,
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

struct Object {
  Items type;
  char *name;
  char *description;
  Object *next;
};

typedef struct {
  char *name;
  char *description;
} ItemData;

ItemData itemData[ICOUNT] = {
    [BANDAGE] = {"bandage", "an unused bandage lies here."},
    [POTION] = {"potion", "a small potion lies here."}};

Object *createObject(Items item) {
  Object *obj = malloc(sizeof(Object));
  obj->type = item;
  obj->name = itemData[item].name;
  obj->description = itemData[item].description;
  obj->next = NULL;
  return obj;
}

Object *findObject(Room *room, const char *name) {
  Object *obj = room->objects;
  while (obj != NULL) {
    if (strcasecmp(obj->name, name) == 0)
      return obj;
    obj = obj->next;
  }
  return NULL;
}
Object *takeObject(Room *room, const char *name) {
  Object *current = room->objects;
  Object *previous = NULL;
  while (current != NULL) {

    if (strcasecmp(current->name, name) == 0) {

      if (previous == NULL)
        room->objects = current->next;
      else
        previous->next = current->next;

      current->next = NULL;
      return current;
    }

    previous = current;
    current = current->next;
  }

  return NULL;
}

const char *mobile_names[] = {[WHALE] = "whale",         [SHARK] = "shark",
                              [JELLYFISH] = "jellyfish", [SEAGULL] = "seagull",
                              [CRAB] = "crab",           [RAT] = "rat"};
const char *item_names[] = {
    [BANDAGE] = "bandage",        [POTION] = "potion",
    [KNIFE] = "small knife",      [SHORTSWORD] = "short sword",
    [BROADSWORD] = "broad sword", [AXE] = "large axe",
    [CLOTH] = "cloth rags",       [LEATHER] = "leather breastplate",
    [IRON] = "iron breastplate",  [STEEL] = "steel armor",
    [MITHRIL] = "mithril plate"};

const char *get_mobile_names(MobileType c) {
  if (c >= 0 && c < MCOUNT) {
    return mobile_names[c];
  }
  return "Unknown";
}
const char *get_item_names(Items c) {
  if (c >= 0 && c < ICOUNT) {
    return item_names[c];
  }
  return "Unknown";
}

// FUNCTION PROTOTYPES
void initWorld(World *world);
void movePlayer(Player *player, enum Direction dir);
void doCommand(Player *player, char command[], int size);
void initPlayer(Player *player);
void commandLook(Room *location);
void showInventory(Player *player);
void commandPrompt(Player *player);

int main() {
  World world;
  char command[50];
  initWorld(&world);

  srand(time(NULL));
  initPlayer(&player);
  player.location = &world.town[1];

  while (1) {
    doCommand(&player, command, sizeof(command));
  }
  return 0;
}

void movePlayer(Player *player, enum Direction dir) {
  if (player->location->exit[dir] != NULL) {
    player->location = player->location->exit[dir];
    commandLook(player->location);
  }
}

void loadObject(Room *room, Object *obj) {
  obj->next = room->objects;
  room->objects = obj;
}

void doCommand(Player *player, char command[], int size) {
  commandPrompt(player);
  if (fgets(command, size, stdin) != NULL) {
    command[strcspn(command, "\n")] = '\0';
  }

  char *verb = strtok(command, " ");
  char *arg = strtok(NULL, "");
  if (verb == NULL) {
    return;
  }
  if (strcmp(command, "levelup") == 0) {
    player->maxhp += 20;
  }
  if (strcmp(command, "load") == 0) {
    Object *obj = createObject(POTION);
    loadObject(player->location, obj);
  }
  if (strcmp(command, "get") == 0) {
    if (verb == NULL)
      return;
    if (arg == NULL)
      printf("Get what?");
    else {
      if (player->location->objects != NULL) {
        printf("I SEE ITEMS\n");
        Object *obj = takeObject(player->location, arg);
        if (obj != NULL)
          printf("Found %s\n", obj->name);
      }
    }
  }
  if (strcmp(verb, "look") == 0 || strcmp(verb, "l") == 0) {
    if (verb == NULL)
      return;
    if (arg == NULL) {
      commandLook(player->location);
    } else {
      printf("You don't see %s here\n", arg);
    }
  }
  if (strcmp(command, "inventory") == 0 || strcmp(command, "i") == 0) {
    showInventory(player);
  }
  if (strcmp(command, "quit") == 0 || strcmp(command, "q") == 0) {
    printf("Goodbye.\n");
    exit(EXIT_SUCCESS);
  }
  if (strcmp(command, "west") == 0 || strcmp(command, "w") == 0) {
    movePlayer(player, WEST);
  }
  if (strcmp(command, "east") == 0 || strcmp(command, "e") == 0) {
    movePlayer(player, EAST);
  }
  if (strcmp(command, "south") == 0 || strcmp(command, "s") == 0) {
    movePlayer(player, SOUTH);
  }
  if (strcmp(command, "north") == 0 || strcmp(command, "n") == 0) {
    movePlayer(player, NORTH);
  }
}

void initWorld(World *world) {
  memset(world, 0, sizeof(*world));

  world->town[0].name = "Town west";
  world->town[0].desc = "Shops n shit";
  world->town[0].exit[EAST] = &world->town[1];
  world->town[0].exit[NORTH] = &world->town[2];

  world->town[1].name = "Town east";
  world->town[1].desc = "Second town room";
  world->town[1].exit[WEST] = &world->town[0];

  world->town[2].name = "Shop";
  world->town[2].desc = "This is a shop.";
  world->town[2].exit[SOUTH] = &world->town[0];
}

void commandLook(Room *location) {
  Object *obj = location->objects;
  printf(BOLD GREEN "\n[%s]\n" RESET, location->name);
  printf("\n%s\n", location->desc);
  while (obj != NULL) {
    printf("%s\n", obj->description);
    obj = obj->next;
  }
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
  obj = NULL;
}

void initPlayer(Player *player) {
  int i;
  for (i = 0; i < 10; i++) {
    player->inv[i] = -1;
  }
  player->inv[0] = BANDAGE;
  player->inv[1] = CLOTH;
  player->inv[2] = KNIFE;
}

void showInventory(Player *player) {
  int i;
  printf("You have:\n");
  for (i = 0; i < 5; i++) {
    if (player->inv[i] != -1) {
      printf("%s\n", get_item_names(player->inv[i]));
    }
  }
  // commandPrompt(player);
}

void commandPrompt(Player *player) {
  printf("HP: %d/%d SP: %d/%d > ", player->hp, player->maxhp, player->sp,
         player->maxsp);
}
