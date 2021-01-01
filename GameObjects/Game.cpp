#include "Game.h"
#include<iostream>
using namespace std;

Game::Game()
{
    cout << "---------------Black Jack----------------\n";
    isPlaying = true;
}

void Game::CreateGame()
{
    cout << "\n- Creating Game\n" << endl;
    CreateDealer();

    player_validation:    
    cout << "\nHow many players are playing? (1-7) : ";
    int playersPlaying;
    cin >> playersPlaying;
    cout << endl;
    if(playersPlaying < 1 || playersPlaying > 7)
    {
        cout << "\n"<< playersPlaying <<" players cannot sit on the seats available.\n";
        goto player_validation; // jump to line 16
    }

    for(int i = 0; i < playersPlaying; i++)
    {
        cout << "\nPlayer " << (i + 1) << endl;
        Player getPlayer = CreatePlayer();
        getPlayer.id = i;
        players.push_back(getPlayer);
    }
}

void Game::ShowRules()
{
    cout << "\nMake sure you set your console shell to fullscreen before playing!\n\n";
    // Display Black Jack Rules
    cout << "\n*********RULES**********\n";
    cout << "\nObjective: The purpose of the game is to get as close to or equal to 21 points without going over 21.\n";
    cout << "\nGame starts by prompting the player to place a bet using available credits before cards are dealt.\n";
    cout << "\nPlayer starts with 2 cards facing up.\n";
    cout << "\nPlayer can request a card or stand based on card value total.\n";
    cout << "\nA pair of cards on initial deal can be split into two hands and aother card is dealt for each hand.\n";
    cout << "\nSplit doubles bet for the respective round.\n";
    cout << "\nPlayer can also double down on current hand.\n";
    cout << "\nDouble down is a request for a single card and can only be used once cards are first dealt.\n";
    cout << "\nDouble down can be used on a split.\n";
    cout << "\nPlayer can surrender if dealer is shown an ace as their face card.\n";
    cout << "\nSurrender is only available as first decision of a hand and is the option to surrender directly after the dealer has checked for blackjack.\n";
    cout << "\nHouse takes half the bet and returns the other half to the player. This terminates the player's interest in hand.\n";
    cout << "\nDealer gets two cards, one card face up and the other face down.\n";
    cout << "\nDealer can Hit or Stand until 17 points.\n";
    cout << "\nFace cards are worth 10 points each (J, Q, K).\n";
    cout << "\nOther cards are worth number on the card.\n";
    cout << "\nAce is either a 1 or 11 depending on the hand total.\n";
    cout << "\n***************************\n";
}

Player Game::CreatePlayer()
{
    
    // For multiple players add for loops for the number of players
    string newPlayerName;
    int newPlayerCredits;
    cout << "\nEnter your name please: ";
    cin >> newPlayerName;
    cout << "\nWelcome " << newPlayerName << ", how many credits would you like to deposit: ";
    cin >> newPlayerCredits;

    if (newPlayerCredits < 0)
    {
        do
        {
            cout << "\nSorry cannot proceed. Credit amount must be positive!\nPlease enter valid credit amount: ";
            cin >> newPlayerCredits;
            cout << endl;
        } while (newPlayerCredits < 0);
    }
        
    Player player(newPlayerName, newPlayerCredits);
    return player;
}

void Game::CreateDealer()
{
    dealer = new Dealer();
}

void Game::ClearCards()
{
    for (int i = 0; i < players.size(); ++i)
    {
        for(int j = 0; j < players[i].hands.size(); ++j)
        {
            players[i].hands[j].cards.clear();
        }
        players[i].hands.clear();
        players[i].isPlaying = true;
    }

    dealer->cards.clear();
}

void Game::QuitGame(Player *player)
{
    player->isPlaying = false; // player status
    cout << "\nThank you for playing, " << player->playerName << "!\n";
}

void Game::CheckRestart()
{
    cout << "\nRound Complete. Do you want to restart the game? (y/N) : ";
    char restartChoice;
    cin >> restartChoice;
    cout << endl;
    if (restartChoice == 'y' || restartChoice == 'Y')
    {
        ClearCards();
    }
    else // Stop Playing game
    {
        isPlaying = false;
    }
}

void Game::PlayGame()
{

    // Distribute Cards
    DistributeCards();
    cout << "\n - Cards Distributed\n";
    ShowAllPlayerStats();

    // Turn based player progression Surrender, Split, Double Down, Hit, Stand
    for (int i = 0; i < players.size(); i++)
    {
        Player *player = &players[i];

        cout << endl << "--------------- " << player->playerName << "'s turn ---------------\n";

        // Display cards
        ShowPlayerHands(player);
        ShowDealerCards();

        // Check surrender if dealer got an Ace
        if(ShouldSurrender(player, player->hands[0].handBet))
        {
            cout << endl << player->playerName << " Surrenders!\n";
            continue;
        }

        // Check if player can and wants to split
        if(CheckSplit(player))
        {
            cout << "\nThe player will now split the cards\n";
            player->CardsSplit();
            ShowPlayerHands(player);
        }
        // cout << endl << player->playerName << " has " << player->hands.size() << " hand" << endl;
        for(int i = 0; i < player->hands.size(); i++)
        {
            int roundCounter = 0;
            while(player->hands[i].handStatus == Playing)
            {
                // If player hand scores a blackjack no need to check for options
                if(CheckBlackJack(&player->hands[i]))
                {
                    player->hands[i].handStatus = StandHand;
                    break;
                }
                cout << "\n - Choose your option:\n1) Hit 2) Stand ";
                if(roundCounter == 0) // Only check for double down at first
                {
                    cout << "3) DoubleDown ";
                }
                cout << ": ";
                int option;
                cin >> option;
                cout << endl;

                switch(option)
                {
                    case 1: 
                        Hit(&player->hands[i]);
                        break;

                    case 2: 
                        Stand(&player->hands[i]);
                        break;

                    case 3: 
                        if(roundCounter == 0)
                        {
                            DoubleDownOnHand(&player->hands[i]);
                            break;
                        }

                    default : cout << "\n - Invalid choice!\n";
                }
                player->hands[i].handScore = CalculateScore(player->hands[i].cards);

                // Show Player hand and player score
                ShowPlayerHands(player);
                cout << "\nHand score is : " << player->hands[i].handScore << endl;

                // Check if Player's Hand busted
                if(CheckBust(&player->hands[i]))
                {
                    player->hands[i].handStatus = LoseHand;
                    cout << endl <<  "\n - Hand Busted!\n";
                }

                // cout << "\nHand status is : " << player->hands[i].handStatus << endl;
                roundCounter++;
            }
        }
        player = nullptr;
    }
    
    // Check Dealer Cards
    cout << "\n-------- Now checking for dealer cards ---------\n";
    CheckDealerCards();
    cout << "\n----------------------------------------------\n";

    cout << "\n-------- Checking which players won! -----------\n";
    // Check all the players in a loop
    // Check all the player's hands to see how many winnings the respective player gets
    for(int i = 0; i < players.size(); ++i)
    {
        Player *player = &players[i];

        // cout << endl << player->playerName << " Player check..\n";
        // cout << endl << player->hands.size() << " player number of hands check..\n";

        for(int j = 0; j < player->hands.size(); ++j) ///// causing segmentation fault
        {
        //    cout << endl << player->hands[j].handStatus << " Player hand status check..\n";
            if(player->hands[j].handStatus == StandHand)
            {
                // Check hand win
                int winCondition = CheckPlayerCardsWin(player->hands[j].cards);
                // cout << "\n - The win condition is : " << winCondition << endl;
                switch(winCondition)
                {
                    case -1: // Lose
                        player->hands[j].handStatus = LoseHand;
                    break;

                    case 0: // Draw
                        player->hands[j].handStatus = PushHand;
                    break;

                    case 1: // Win
                        if(player->hands[j].hasDoubleDown)
                        {
                            player->hands[j].handStatus = DoubleDownWinHand;
                        }
                        else
                        {
                            player->hands[j].handStatus = WinHand;
                        }
                    break;

                    default: cout << "\n - Error: Cannot decide the win condition on the hand.\n";
                }
            }
            else
            {
                cout << "\n - Player hand not in game (Busted/Surrendered/Quit).\n";
            }
            
        }
        cout << "\n - Finished checking " << player->playerName << endl;
        GiveCredits(player);
        player = nullptr;
    }
    cout << "\n--------------------------------------------------------------\n";
    // Ask if user wants to restart the game
    CheckRestart();
}

int Game::Bet(Player *player)
{
    cout << endl << player->playerName << "\n";
    // Bet check
    should_play: // Jump to
    cout << "\nCurrent Credits : " << player->credits << ". What amount would you like to bet? (-1 to Quit) : ";
    int bet;
    cin >> bet;
    cout << endl;
    // Check bet
    if (bet == -1)
    {
        QuitGame(player); // Player exits the game
        return -1;
    }

    if (bet < 1 || bet > player->credits)
    {
        cout << "Entered credits not valid!";
        goto should_play; // Jump to should_play
    }

    // Bet valid reduce the player credits and play Game
    player->credits -= bet;
    // End of Bet check
    return bet;
}

void Game::DistributeCards()
{
    
    for (int i = 0; i < players.size(); i++)
    {
        Player *player = &players[i];
        int getPlayerBet = Bet(player);

        if (player->isPlaying)
        {
            if (player->hands.size() > 1)
            {
                cout << "\nPlayer Cheating. Handsize is greater than 1 before distributing the cards!\n";
            }

            // Deal Cards
            Hand *newHand = new Hand();
            newHand->cards.push_back(dealer->deck->GetCard());
            player->hands.push_back(*newHand); // To Player
            player->hands[0].handBet = getPlayerBet;  
            delete newHand;
            newHand = nullptr;  
        }
        else
        {
            cout << endl << player->playerName << " is not playing\n";
        }
        
        // cout << endl << player->playerName << " has hands : " << player->hands.size() << " and cards : " << player->hands[0].cards.size() << endl;
    }

    dealer->cards.push_back(dealer->deck->GetCard()); // To Dealer
    // cout << "\nDistributed 1 card to each player and dealer\n";

    for (int i = 0; i < players.size(); i++)
    {
        Player *player = &players[i];

        if (!player->isPlaying)
        {
            cout << endl << player->playerName << " is not playing\n";
            continue;
        }
            
        // Deal Cards
        player->hands[0].cards.push_back(dealer->deck->GetCard()); // To Player

        // ShowPlayerCards(player);
        player->hands[0].handScore = CalculateScore(player->hands[0].cards);
        // cout << endl << player->playerName << " has hands : " << player->hands.size() << " and cards : " << player->hands[0].cards.size() << endl;

    }

    dealer->cards.push_back(dealer->deck->GetCard()); // To Dealer
}

void Game::ShowAllPlayerStats()
{
    cout << "\n*********** Here are all the players *********\n";
    cout << "\nTotal players playing : " << players.size() << endl;

    for (int i = 0; i < players.size(); i++)
    {
        cout << "\nPlayer name : " << players[i].playerName << endl;
        cout << "\nHand size : " << players[i].hands.size() << endl;
        for (int j = 0; j < players[i].hands.size(); ++j)
        {
            cout << "\nHand " << j + 1 << endl;
            cout << "\nHand status : " << players[i].hands[j].handStatus << endl;
            cout << "\nHand Bet : " << players[i].hands[j].handBet << endl;
            cout << "\nHand Score : " << players[i].hands[j].handScore << endl;
        }
        ShowPlayerHands(&players[i]);
        cout << "\nPlayer's total credits : " << players[i].credits << endl;
        cout << endl;
    }
    cout << "\n*********************************************\n";

}

bool Game::CheckSplit(Player *player)
{
    if (player->hands[0].cards[0].GetCardValue() == player->hands[0].cards[1].GetCardValue())
    {
        cout << "\nDo you want to split the cards (y/N)? Splitting will double the bet amount.";
        char splitChar = 'N';
        cin >> splitChar;
        if(splitChar == 'y' || splitChar == 'Y')
        {
            return true;
        }
    }
   
    // cout << "\nCannot split.\n";
    return false;
}

bool Game::CheckBust(Hand *playerHand)
{
    if(playerHand->handScore > 21)
        return true;
    return false;
}

void Game::ShowPlayerHands(Player *player)
{
    cout << "\n" << player->playerName << "'s Cards:\n ";
    
    for (int i = 0; i < player->hands.size(); ++i)
    {
        if (player->hands.size() > 1)
            cout << "\nHand " << i + 1 << endl;
        ShowCards(player->hands[i].cards);
    }

    cout << endl;
}

void Game::ShowCards(vector<Card> cardsArray)
{
    for (int i = 0; i < cardsArray.size(); i++)
    {
        switch (cardsArray[i].rank)
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
            cout << cardsArray[i].rank;
            break;
        }
        switch (cardsArray[i].suit)
        {
        case Spades:
            cout << " "
                 << "S\t";
            break;
        case Hearts:
            cout << " "
                 << "H\t";
            break;
        case Diamonds:
            cout << " "
                 << "D\t";
            break;
        case Clubs:
            cout << " "
                 << "C\t";
            break;
        default:
            cout << "!!";
            break;
        }
    }
}

void Game::ShowDealerCards()
{
    // cout << "\n- Dealer has : " << dealer->cards.size() << " cards." << endl;
    cout << "\nDealer's Cards:\n ";
    for (int i = 0; i < dealer->cards.size(); i++)
    {
        if(i < dealer->cardsToShow)
        {
            switch (dealer->cards[i].rank)
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
                cout << dealer->cards[i].rank;
                break;
            }
            switch (dealer->cards[i].suit)
            {
            case Spades:
                cout << " "
                     << "S\t";
                break;
            case Hearts:
                cout << " "
                     << "H\t";
                break;
            case Diamonds:
                cout << " "
                     << "D\t";
                break;
            case Clubs:
                cout << " "
                     << "C\t";
                break;
            default:
                cout << "!!";
                break;
            }
        }
        else
        {
            cout << "??\t";
        }
    }
    cout << endl;
}

bool Game::ShouldSurrender(Player *player, int bet)
{
    // Player can surrender if dealer is showing an ace as their face card
    if(dealer->cards[0].rank != Ace)
    {
        return false;
    }

    char checkSurrenderInput;
    cout << "\nDo you want to surrender?(y/n)" << endl;
    cin >> checkSurrenderInput;

    if(checkSurrenderInput == 'y' || checkSurrenderInput == 'Y')   
    {
        // Get Half the credits back to the player
        player->credits += (bet / 2);
        player->ShowTotalCredits();
        // Then Quit
        QuitGame(player);
        return true;
    }

    return false;
}

bool Game::CheckBlackJack(Hand *playerHand)
{
    playerHand->handScore = CalculateScore(playerHand->cards);
    if (playerHand->handScore == 21 && playerHand->cards.size() == 2)
    {
        return true;
    }
    // cout << "\n- Didn't score a blackjack.\n";
    return false;
}

void Game::Hit(Hand *playerHand)
{
    cout << "\n - Hit!\n";
    playerHand->cards.push_back(dealer->deck->GetCard());
}

void Game::Stand(Hand *playerHand)
{
    cout << "\n - Stand!\n";
    playerHand->handStatus = StandHand;
}

void Game::DoubleDownOnHand(Hand *playerHand)
{
    cout << "\n - Double Down\n";
    playerHand->hasDoubleDown = true;
    Hit(playerHand);
    Stand(playerHand);
}

void Game::CheckDealerCards()
{
    dealer->cardsToShow += 10;
    ShowDealerCards();
    dealer->totalScore = CalculateScore(dealer->cards);
    cout << "\nDealer score : " << dealer->totalScore << endl;

    while (dealer->totalScore < 17)
    {
        dealer->cards.push_back(dealer->deck->GetCard());
        ShowDealerCards();
        dealer->totalScore = CalculateScore(dealer->cards);
        cout << "\nDealer score : " << dealer->totalScore << endl;
    }
    if(dealer->totalScore > 21)
    {
        cout << "\n - Dealer Busted!\n";
    }
}

int Game::CalculateScore(vector<Card> cardsArray)
{
    // cout << "\nArray has " << cards.size() << " cards." << endl;
    int totalScore = 0;
    int aceCount = 0;
    for (int i = 0; i < cardsArray.size(); i++)
    {
        if (cardsArray[i].rank == 1)
        {
            aceCount++;
        }
        else
        {
            totalScore += cardsArray[i].GetCardValue();
        }
    }

    // Ace will be 1 or 21 depending on other values of the cards
    for (int i = 0; i < aceCount; i++)
    {
        if ((totalScore + 11) <= 21)
        {
            totalScore += 11;
        }
        else
        {
            totalScore += 1;
        }
    }

    return totalScore;
}

int Game::CheckPlayerCardsWin(vector<Card> cardsArray)
{
    int playerScore = CalculateScore(cardsArray);
    // Player and dealer scored a blackjack
    if (playerScore == 21 && cardsArray.size() == 2 && dealer->totalScore == 21 && dealer->cards.size() == 2)
    {
        return 0; // Draw
    }

    // Player scored 21 points but dealer scored a blackjack
    if (playerScore == 21 && cardsArray.size() > 2 && dealer->totalScore == 21 && dealer->cards.size() == 2)
    {
        return -1; // Lose
    }

    // Player scored Blackjack and dealer didn't
    if (playerScore == 21 && cardsArray.size() == 2)
    {
        return 1; // Win
    }
    else
    {
        if(playerScore > 21)
            return -1; // Lose
        if (playerScore > dealer->totalScore)
        {
            return 1; // Win
        }
        if(playerScore == dealer->totalScore)
            return 0; // Draw
        if (playerScore < dealer->totalScore)
        {
            return -1; // Lose
        }
    }

    cout << "\nCheckPlayerCardsWin() function couldn't find the outcome of the hand\n";
    return -1;
}

void Game::GiveCredits(Player *player)
{
    // cout << endl << player->playerName << " you have " << player->hands.size() << " hands.\n";
    for(int i = 0; i < player->hands.size(); ++i)
    {
        switch(player->hands[i].handStatus)
        {
            case WinHand: 
                player->credits += player->hands[i].handBet * 2;
                cout << endl << player->playerName << ", you win : " << player->hands[i].handBet * 2 << " credits.";
            break;

            case DoubleDownWinHand: 
                player->credits += player->hands[i].handBet * 3;
                cout << endl << player->playerName << ", you win : " << player->hands[i].handBet * 3 << " credits.";
            break;

            case PushHand: 
                player->credits += player->hands[i].handBet;
                cout << endl << player->playerName << ", you recieved Push of : " << player->hands[i].handBet << " credits.";
            break;

            default: cout << "\nSorry " << player->playerName << " your hand state is not applicable for any type of winnings.\n";
        }
        cout << "\n" << player->playerName << "'s total credits are : " << player->credits << "\n";
    }
}