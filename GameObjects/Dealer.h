#include "Card.h"
#include "Deck.h"
#include <vector>
class Dealer
{
    public:
        Deck *deck;
        vector<Card> cards;
        int cardsToShow;
        int totalScore;
        Dealer();
        ~Dealer();
};