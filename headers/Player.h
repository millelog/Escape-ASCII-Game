#ifndef PLAYER_H
#define PLAYER_H
#include "Actor.h"

class Player : public Actor{
private:
	int keys;
	int apples;
	bool invulnerable;
public:
	Player();
	void reset();
	void enableInvuln();
	void disableInvuln();
	bool getInvuln();
	int getKeys();
	bool addKey();
	bool addApple();
	void eatApple();
	int getApples();
	void checkCurrentTile(location, Floor&);
	void move(Floor&, char);
};
#endif