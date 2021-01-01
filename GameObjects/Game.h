#include "Dealer.h"
#include "Player.h"
class Game
{
    private:
        Dealer *dealer;
        vector <Player> players;
        Player CreatePlayer();
        void CreateDealer();
        int Bet(Player *player);
        void DistributeCards();
        void ShowPlayerHands(Player *player);
        void ShowCards(vector<Card> cardsArray);
        void ShowDealerCards();
        void ClearCards();
        void QuitGame(Player *player);
        void ShowAllPlayerStats();

        void CheckRestart();

        bool ShouldSurrender(Player *player, int bet);
        int CalculateScore(vector<Card> cardsArray);

        bool CheckSplit(Player *player);
        void Hit(Hand *playerHand);
        void Stand(Hand *playerHand);
        void DoubleDownOnHand(Hand *playerHand);

        bool CheckBlackJack(Hand *playerHand);
        bool CheckBust(Hand *playerHand);
        void CheckDealerCards();
        int CheckPlayerCardsWin(vector<Card> cardsArray);
        void GiveCredits(Player *player);

    public:
        bool isPlaying;
        
        Game();
        void CreateGame();
        void ShowRules();
        void PlayGame(); 
};
