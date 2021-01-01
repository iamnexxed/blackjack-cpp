#include <iostream>
#include <vector>
#include "Hand.h"

using namespace std;

class Player
{
    public:
        int id;
        string playerName;
        int credits;
        vector<Hand> hands;
       
       bool isPlaying;

        Player();
        Player(string getPlayer, int getCredits);

        void CardsSplit();

        void ShowTotalCredits();
};