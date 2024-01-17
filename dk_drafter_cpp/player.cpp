#include "player.h"

Player::Player() :id(0){}
Player::Player(std::string name, unsigned int id) : name(name), id(id){}
unsigned int Player::getID() { return id; }