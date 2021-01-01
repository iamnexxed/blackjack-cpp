#include "Dealer.h"

Dealer::Dealer()
{
    deck = new Deck();
    deck->CreateDeck();
    deck->ShuffleDeck();
    cardsToShow = 1;
    totalScore = 0;
}

Dealer:: ~Dealer()
{
    delete deck;
}

