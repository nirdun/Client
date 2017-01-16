#include "Player.h"
PlayerType2::PlayerType2(string nameType2,int playerPos):Player(nameType2,playerPos){}
int PlayerType2::leastCard() {
    int leastCard = 4;
    int lowestCard;
    for (map<int, int>::iterator it = cardsMap.begin(); it != cardsMap.end(); it++) {
        int currentAmount = (*it).second;
        if (currentAmount < leastCard) {
            leastCard = currentAmount;
            lowestCard = (*it).first;
        } else if (currentAmount == leastCard) {
            // same sign
            if (lowestCard * (*it).first > 0) {
                lowestCard = (lowestCard < (*it).first) ? lowestCard : (*it).first;
            } else {
                lowestCard = (lowestCard > (*it).first) ? lowestCard : (*it).first;
            }

        }
    }
    return lowestCard;
}
int PlayerType2::whatToAsk(){
    return leastCard();
}

int PlayerType2::whoToAskFrom(vector<Player *> &players) {
    int posToAsk=0;
    if(players.at(0)==this){
        posToAsk=1;
    }
    std::vector<Player*>::iterator it;
    for (unsigned int i=0; i<players.size(); i++) {
        if((players[i])==this){
            continue;
        }
        if(players.at(i)->getNumberOfCards()>=players.at(posToAsk)->getNumberOfCards()){
            posToAsk=i;

        }

    }
    return posToAsk;
}
Player* PlayerType2::clone() {
    return new PlayerType2 (*this);
}
PlayerType2::~PlayerType2() {}