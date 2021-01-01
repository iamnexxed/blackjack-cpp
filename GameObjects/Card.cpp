#include "Card.h"
Card::Card()
{
    
}

int Card::GetCardValue()
{
    if (rank == 11 || rank == 12 || rank == 13)
    {
        return 10;
    }
    return rank;
}

