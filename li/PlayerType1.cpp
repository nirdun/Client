#include "Player.h"
PlayerType1::PlayerType1(string nameType1,int playerPos) : Player(nameType1,playerPos){}

//Finding the value with whe most cards.
int PlayerType1::mostCard() {
    int mostCards = 0;
    int highestCard;
    for (map<int, int>::iterator it = cardsMap.begin(); it != cardsMap.end(); it++) {
        int currentAmount = (*it).second;
        if (currentAmount > mostCards) {
            mostCards = currentAmount;
            highestCard = (*it).first;
        } else if (currentAmount == mostCards) {
            // same sign
            if (highestCard * (*it).first > 0) {
                highestCard = (highestCard > (*it).first) ? highestCard : (*it).first;
            } else {
                highestCard = (highestCard < (*it).first) ? highestCard : (*it).first;
            }

        }
    }
    return highestCard;
}

int PlayerType1::whatToAsk(){
    return mostCard();
}

int PlayerType1::whoToAskFrom(vector<Player *> &players) {
    int posToAsk=0;
    if(this->getPosition()==0){
        posToAsk=1;
    }
    for (unsigned int i=0; i<players.size(); i++) {
        if(i==this->getPosition()){
            continue;
        }
        if(players.at(i)->getNumberOfCards()>=players.at(posToAsk)->getNumberOfCards()){
            posToAsk=i;

        }

    }
    return posToAsk;
}
Player* PlayerType1::clone() {
    return new PlayerType1 (*this);
}
PlayerType1::~PlayerType1() {}