#ifndef CARD_H
#define CARD_H

#include <iostream>
using namespace std;

class Card
{
    public:
        int suit;
        int rank;
        Card();
        int GetCardValue();
};

#endif