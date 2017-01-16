#ifndef CARD_H_
#define CARD_H_

#include <iostream>
#include "algorithm"

using namespace std;

enum Shape {
    Club,
    Diamond,
    Heart,
    Spade
};

enum Figure {
    Jack,
    Queen,
    King,
    Ace
};

class Card {
private:
    //represent the shape in enum.
    Shape shape;
public:
    virtual Card* clone()=0;
    int getShape() const;

    //c-tor get char.
    Card(char c);

//    //copy c-tor.
//    Card(const Card &other);

    virtual string toString() = 0; //Returns the string representation of the card "<value><shape>" exp: "12S" or "QD"
    //represent the shape in char (public?!/))
    char chShape;

    //overloading operators.
    bool operator>(const Card &other) const;

    bool operator<(const Card &other) const;

    bool operator==(Card &other);

    bool compareCard(int *a, int *b);

//    bool operator< (const Card& first, const Card& second)const ;
//    bool operator> (const Card& first,const Card& second)const;
    //compare between cards by value and shape
    bool compareTo(const Card &other) const;

    virtual int getValue() const =0;

    virtual ~Card();
};

class FigureCard : public Card {
private:
    Figure figure;
    //represent the figure in char
    char chFigure;
    int valFigure;
public:
    //FigureCard(const FigureCard& other);
    virtual Card* clone() override ;
    virtual int getValue() const override;

    FigureCard(char f, char s);

    virtual string toString() override;
    virtual ~FigureCard();
};

class NumericCard : public Card {
private:
    //Todo get highest value + get most card of value

//represent the value of card.
    int number;
public:
   // NumericCard(const NumericCard& other);
    virtual Card* clone() override ;
    NumericCard(int num, char s);

    virtual int getValue() const override;

    virtual string toString() override;
    virtual ~NumericCard();
};

#endif