#include "Deck.h"
#include <iostream>
#include <random>    // std::default_random_engine

using namespace std;

Deck::Deck()
{
    currentCardIndex = 0;
}

void Deck::CreateDeck()
{
    int k = 0;
    for (int i = 0; i < NUMOFSUITS; i++)
    {
        for (int j = 1; j <= NUMOFRANKS; j++, k++)
        {
            cards[k].suit = i;
            cards[k].rank = j;
        }
    }
    cout << "- Deck Created\n" << endl;
    // DisplayDeck();
}

// ShuffleDeck() -> Causing memory leaks on pointers. Need to find the exact cause. Using arrays
// as a solution.
void Deck::ShuffleDeck()
{
    // Obtain a time-based seed:
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    // cout << "Seed is : " << seed;

    // STL shuffle function
    default_random_engine generatedEngine = default_random_engine(seed);
    shuffle(cards.begin(), cards.end(), generatedEngine);

    DisplayDeck();
    cout << "\n\n- Deck Shuffled" << endl;
}

void Deck::DisplayDeck()
{
    for (int i = 0; i < NUMOFCARDS; i++)
    {
        if (i % NUMOFRANKS == 0)
            cout << endl << endl;

        switch (cards[i].rank)
        {
            case Ace:
                cout << "A";
                break;
            case Jack:
                cout << "J";
                break;
            case Queen:
                cout << "Q";
                break;
            case King:
                cout << "K";
                break;
            default:
                cout << cards[i].rank;
                break;
        }
        switch (cards[i].suit)
        {
            case Spades:
                cout << " " << "S\t";
                break;
            case Hearts:
                cout << " " << "H\t";
                break;
            case Diamonds:
                cout << " " << "D\t";
                break;
            case Clubs:
                cout << " " << "C\t";
                break;
            default:
                cout << "!!";
                break;
        }      
        
    }
}

Card Deck::GetCard()
{
    // Safe condition check so index doesn't go out of bounds
    if(currentCardIndex >= 52)
    {
        // Deck shuffles if deck is emptied
        ShuffleDeck();
        currentCardIndex = 0;
        return cards[currentCardIndex];
    }
    // cout << "\nCurrent Card Index: " << currentCardIndex << endl;
    return cards[currentCardIndex++];
}
