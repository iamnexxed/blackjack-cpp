#include "Player.h"
Player::Player()
{
    playerName = "UNNEXXED00000000000000";
    id = -1;
    credits = 0;
    isPlaying = true;
}

// Don't forget to add the variables that need to be initialized in the paramertized constructor
Player::Player(string getPlayer, int getCredits)
{
    playerName = getPlayer;
    id = 0;
    credits = getCredits;
    isPlaying = true;
}


void Player::ShowTotalCredits()
{
    cout << "\n" << playerName << " has " << credits << " credits." << endl; 
}

void Player::CardsSplit()
{
    if(hands.size() <= 0 || hands[0].cards.size() <= 0)
    {
        cout << "\n- Cannot split no cards in hand\n";
        return;
    }
    
    cout << "\n" << playerName << " will now split the cards..\n" << endl;
    credits -= hands[0].handBet;
    
    Hand *newHand = new Hand();
    newHand->cards.push_back(hands[0].cards.back());

    // Player hand
    hands[0].cards.pop_back();
    // Add card to the splitCards
    hands.push_back(*newHand);
    delete newHand;
    newHand = nullptr;
}