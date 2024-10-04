/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) Project
/******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables. You 
 */
 // ♥, ♠, ♦, ♣
const char* suit[4] = {"\U00002665","\U00002660","\U00002666","\U00002663"}; // H, S, D, C
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
  /******** You complete ****************/
  for(int i = 51; i >= 1 ; i--)
  {
    int j = rand() % (i + 1); //shuffles deck
    int temp = cards[j];//next 3 lines switches positions
    cards[j] = cards[i];
    cards[i] = temp;
  }
}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 *
 *  Must use the suit and type arrays to lookup
 *   the appropriate characters to print.
 */
void printCard(int id)
{
  /******** You complete ****************/
  int typesVal = id % 13; //gives you the correct type
  int suitsVal = id / 13; //gives you the correct suit
  cout << type[typesVal] << suit[suitsVal] << " "; //prints them out in correct format

}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 *
 * Must use the values array to lookup the appropriate
 *  card return value.
 */
int cardValue(int id)
{
  /******** You complete ****************/
  return value[id % 13];
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
  /******** You complete ****************/
  for(int i = 0; i < numCards; i++)
  {
    printCard(hand[i]);
  }
  cout << " ";//prints out the cards
}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
  /******** You complete ****************/
  int total = 0;//keeps track of total score
  int aceTotal = 0;//keeps track of aces
  for(int i = 0; i < numCards; i++)
  {
    total += cardValue(hand[i]);//adds up card values
    if(cardValue(hand[i]) == 11)//aces originally count as 11
    {
      aceTotal++;
    }
  }
  if(aceTotal > 0 && total > 21)//if we do have an ace and the total is a bust
  {
    total -= 10;//count the ace as a 1
    aceTotal--;
  }
  return total;//store the total amount in function
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];//dealer
  int phand[9];//player
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  /******** You complete ****************/
  char play = 'y';
  char decision;
  
  while(play == 'y')
  {
    for(int i = 0; i < 52; i++)//initializing the cards array
    {
      cards[i] = i;
    }

    shuffle(cards);
    
    for(int i = 0; i < 2; i++)//assigns player and dealer first two cards
    {
      dhand[i] = cards[i*2+1];
      phand[i] = cards[i*2];
    }
    int dhandNum = 2;//starting with two cards
    int phandNum = 2;//keeps track of how many cards

    int typeNum = dhand[1] % 13;
    int suitNum = dhand[1] / 13;

    int pTotal = getBestScore(phand, phandNum);//returns players total
    int dTotal = getBestScore(dhand, dhandNum);//returns dealers total

    cout << "Dealer: ? ";
    printCard(dhand[1]);
    cout << endl;//first card is hidden second is shown
    cout << "Player: ";
    printHand(phand, phandNum);
    cout << endl;

    bool continuing = true;//seeing if turn is still happening
    
    while((pTotal < 21) && (continuing))
    {
      cout << "Type 'h' to hit and 's' to stay: " << endl;
      cin >> decision;
      
      if(decision == 'h')//if player chooses to hit they recieve another card
      {
        phand[phandNum] = cards[phandNum + 2];
        phandNum++;
        cout << "Player: ";
        printHand(phand, phandNum);//prints out new card
        pTotal = getBestScore(phand, phandNum);
      }
      
      else if(decision == 's')//if they choose to stay
      {
        while(dTotal < 17)//dealer has to take another card if less than 17
        {
          dhand[dhandNum] = cards[dhandNum + phandNum];
          dhandNum++;
          dTotal = getBestScore(dhand, dhandNum);
        }
        continuing = false;//dealers turn is over once over 17 so leave loop
      }
      else//if put anything but h or s program will quit
      {
        break;
      }
    }

    if(pTotal > 21)//if players total is over 21 they automatically lose
    {
      cout << "Player busts" << endl;
      cout << "Lose " << pTotal << " " << dTotal << endl;
    }

    else if(pTotal == 21)//player is exactly at 21 so goes to dealers turn
    {
      while(dTotal < 17)//if dealer has less than 17 they have to take new card until over 17
      {
        dhand[dhandNum] = cards[dhandNum + phandNum];
        dhandNum++;
        dTotal = getBestScore(dhand, dhandNum);
      }
      cout << "Dealer: ";
      printHand(dhand, dhandNum);
      cout << endl;
      cout << "Win " << pTotal << " " << dTotal << endl;
    }

    else if((dTotal > 21) && (pTotal <= 21))//dealer busts but player still under or at 21
    {
      cout << "Dealer: ";
      printHand(dhand, dhandNum);//can't call in cout since void
      cout << endl;
      cout << "Dealer busts" << endl;
      cout << "Win " << pTotal << " " << dTotal << endl;
    }

    else if((dTotal < pTotal) && (dTotal < 21) && (pTotal < 21))//player has a higher total so they win
    {
      cout << "Dealer: ";
      printHand(dhand, dhandNum);
      cout << endl;
      cout << "Win " << pTotal << " " << dTotal << endl;
    }

    else if((dTotal > pTotal) && (dTotal < 21) && (pTotal < 21))//dealer has higher total so player loses
    {
      cout << "Dealer: ";
      printHand(dhand, dhandNum);
      cout << endl;
      cout << "Lose " << pTotal << " " << dTotal << endl;
    }

    else if((dTotal == pTotal) && (dTotal < 21) && (pTotal < 21))//both players tie
    {
      cout << "Dealer: ";
      printHand(dhand, dhandNum);
      cout << endl;
      cout << "Tie " << pTotal << " " << dTotal << endl;
    }

    cout << endl;
    cout << "Play again? [y/n]" << endl;//asks user if they want to play again
    cin >> play;//if yes it goes through while loop again
  }
  return 0;
}
