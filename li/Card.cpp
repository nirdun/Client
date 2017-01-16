//
// Created by ניר דוניץ on 14.11.2016.
//

#include "Card.h"

Card::Card(char s):shape(),chShape() {
    switch (s) {
        case 'C':
            this->shape = Club;
            this->chShape = 'C';
            break;
        case 'D':
            this->shape = Diamond;
            this->chShape = 'D';
            break;
        case 'H':
            this->shape = Heart;
            this->chShape = 'H';
            break;
        case 'S':
            this->shape = Spade;
            this->chShape = 'S';
            break;
        default: {

        }
    }
}

int Card::getShape() const{
    return this->shape;
}

//true if this bigger than card.
bool Card:: compareTo(const Card &other) const{
    int first = this->getValue();
    int second = other.getValue();
    //by value
    if (first != second) {
        // same sign
        if (first * second > 0) {
            return (first > second);
        } else {//different sign
            return (first < 0);
        }
    }
        //by shape
    else {
        return this->shape > other.shape;
    }
}

bool Card::operator> (const Card& other) const {
    return this->compareTo(other);
}
bool Card::operator< (const Card& other)const
{
    return other.compareTo(*this);
}

//overloading '==' by checking value and shape.
bool Card::operator== (Card &other){
        return ((this->getValue()==other.getValue())&&(this->shape==other.shape));
}


Card::~Card() {}