#include <iostream>
using namespace std;

int main()
{
    char ROCK = 'r';
    char SCISSORS = 's';
    char PAPER = 'p';

    char Player1, Player2;
    cout << "Player 1, enter your move (r for rock, p for paper, s for scissors) : " << Player1;
    cin >> Player1;
    cout << "Player 2, enter your move (r for rock, p for paper, s for scissors) : " << Player2;
    cin >> Player2;

    if (Player1 == Player2)
    {
        cout << "It's a draw" << endl;
    }
    else if ((Player1 == 'r' && Player2 == 's') || (Player1 == 's' && Player2 == 'p') || (Player1 == 'p' && Player2 == 'r'))
    {
        cout << "Player 1 wins";
    }
    else if ((Player2 == 'r' && Player1 == 's') || (Player2 == 's' && Player1 == 'p') || (Player2 == 'p' && Player1 == 'r'))
    {
        cout << "Player 2 wins";
    }
    return 0;
}