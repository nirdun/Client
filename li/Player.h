#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>

#include "Hand.h"

using namespace std;

class Player : public Hand {
private:
    int position;
    const string name;

public:
    Player(string strName, int playerPos);

    string getName();   //Returns the name of the player
    unsigned int getPosition();   //Returns the position of the player
    virtual int whoToAskFrom(vector<Player *> &players)=0;//TODO...
    virtual int whatToAsk()=0;
    virtual Player* clone()=0;
    vector<Card *> cardsToPass(int value);

    string printHand();

    virtual ~Player();
};


class PlayerType1 : public Player {  //For strategy 1
public:
    PlayerType1(string nameType1, int playerPos);
    int mostCard();
    virtual int whoToAskFrom(vector<Player *> &players) override;
    virtual Player* clone()override ;
    virtual int whatToAsk() override;


    virtual ~PlayerType1();

};

//
class PlayerType2 : public Player {  //For strategy 2
public:
    PlayerType2(string nameType2, int playerPos);

    int leastCard();

    virtual int whoToAskFrom(vector<Player *> &players) override;

    virtual int whatToAsk() override;
    virtual Player* clone() override ;

    virtual ~PlayerType2();
};

class PlayerType3 : public Player {  //For strategy 3
private:
    unsigned int askFrom;
public:


    PlayerType3(string nameType3, int playerPos);

    int highestValue();

    virtual int whoToAskFrom(vector<Player *> &players) override;

    virtual int whatToAsk() override;
    virtual Player* clone() override ;
    virtual ~PlayerType3();

};

class PlayerType4 : public Player {  //For strategy 4
private:
    unsigned int askFrom;
public:
    virtual Player* clone() override ;

    PlayerType4(string nameType4, int playerPos);

    int lowestValue();

    virtual int whoToAskFrom(vector<Player *> &players) override;

    virtual int whatToAsk() override;

    virtual ~PlayerType4();
};

#endif