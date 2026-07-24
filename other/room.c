#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  int roomNum;
  char roomName[25];
  char roomDesc[512];
  int exits;
  int players;
  int objects;
  int effects;
} Room;

void printRoom(Room room) {
  printf("%d", room.roomNum);
  printf("%c", room.roomDesc);
}

void modifyroomName(struct Room *s) {
        strcpy(s->roomName, "
	s->id = 100;

int main(void) {
    Room room1 = {001,
                  "The first room\n\n",
                  "This is the first room.  There is nothing much here.\n",
                  4,
                  0,
                  0,
                  0};
    printRoom(room1);

    return 0;
}
