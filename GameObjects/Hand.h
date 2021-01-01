#include "Card.h"
#include <vector>

enum cardStatus
{
    Playing,
    StandHand,
    WinHand,
    DoubleDownWinHand,
    PushHand,
    LoseHand
};

class Hand
{
    public:  
        vector<Card> cards;
        int handStatus;
        int handBet;
        int handScore;

        bool hasDoubleDown;

        Hand();
};