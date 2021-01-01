#include "Card.h"
#include <iostream>
#include <array>
using namespace std;

const int NUMOFCARDS = 52;
const int NUMOFSUITS = 4;
const int NUMOFRANKS = 13;

enum Suits
{
    Spades,
    Hearts,
    Diamonds,
    Clubs
};
enum Ranks
{
    Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King
};
class Deck
{
    private:
        array<Card, NUMOFCARDS> cards;
        int currentCardIndex;
    public:
        Deck();
        void CreateDeck();
        void ShuffleDeck();
        void DisplayDeck();
        Card GetCard();
};