#include <iostream>
#include <limits.h>

using namespace std;

void setup(char board[6][7]) 
{
  cout << endl;
  for (int i = 5; i >= 0; i--) 
  {
    cout << i + 1 << ' ';
    for (int j = 0; j < 7; j++)
    {
      cout << board[i][j] << ' ';
    }
    cout << endl;
  }
  cout << "  1 2 3 4 5 6 7" << endl;
  cout << endl;
}

int validate_column(char board[6][7], int column)
{
  while (cin.fail() || column < 1 || column > 7) 
  {
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    cout << "Invalid Input, please enter a number between 1 and 7: ";
    cin >> column;
  }
  return column;
}

int add_row(char board[6][7], int column)
{
  for (int i = 0; i < 6; i++)
  {
    if (board[i][column - 1] == '-')
    {
      return i; // Return the first available row
    }
  }
  return -1;
}

bool all_filled(char board[6][7]) 
{
  bool full = true;
  for (int i = 0; i < 6; i++) 
  {
    for (int j = 0; j < 7; j++) 
    {
      if (board[i][j] == '-') 
      {
        full = false;
      }
    }
  }
  return full;
}

bool check_completed(char board[6][7], int no_entered, char check) 
{
  // Check horizontal
  for (int i = 0; i < 6; i++) 
  {
    for (int j = 0; j < 4; j++) 
    {
      if (board[i][j] == check && board[i][j + 1] == check && board[i][j + 2] == check && board[i][j + 3] == check) 
      {
        return true;
      }
    }
  }

  // Check vertical
  for (int j = 0; j < 7; j++) 
  {
    for (int i = 0; i < 3; i++) 
    {
      if (board[i][j] == check && board[i + 1][j] == check && board[i + 2][j] == check && board[i + 3][j] == check) 
      {
        return true;
      }
    }
  }

  // Check diagonal (bottom-left to top-right)
  for (int i = 3; i < 6; i++) 
  {
    for (int j = 0; j < 4; j++) 
    {
      if (board[i][j] == check && board[i - 1][j + 1] == check && board[i - 2][j + 2] == check && board[i - 3][j + 3] == check) 
      {
        return true;
      }
    }
  }

  // Check diagonal (top-left to bottom-right)
  for (int i = 0; i < 3; i++) 
  {
    for (int j = 0; j < 4; j++) 
    {
      if (board[i][j] == check && board[i + 1][j + 1] == check && board[i + 2][j + 2] == check && board[i + 3][j + 3] == check) 
      {
        return true;
      }
    }
  }

  return false; // No winning condition met
}

int player_vs_player(char board[6][7]) 
{
  int pos, row, column;
  int no_entered = 0;
  bool full, completed;
  cout << endl;
  cout << "Player 1 = \"O\"" << endl;
  cout << "Player 2 = \"X\"" << endl;
  cout << endl;
  cout << "Player 1 go first" << endl;
  cout << endl;
  cout << "Player 1's turn: ";
  cin >> pos; // validate it later
  board[0][pos - 1] = 'O';
  full = all_filled(board);
  setup(board);
  no_entered++;
  while (full == false) 
  {
    // Player 2
    cout << "Player 2's turn: ";
    cin >> column;
    column = validate_column(board, column);
    row = add_row(board, column);
    while (row == -1) 
    {
      cout << "Column is full, please enter another column: " << endl;
      cin >> column;
      row = add_row(board, column);
    }
    no_entered += 1;
    board[row][column - 1] = 'X';
    setup(board);
    completed = check_completed(board, no_entered, 'X');
    if (completed == true) 
    {
      return 1;
    }
    full = all_filled(board);
    if (full == true) 
    {
      return -1;
    }
    // Player 1
    cout << "Player 1's turn: ";
    cin >> column;
    column = validate_column(board, column);
    row = add_row(board, column);
    while (row == -1) 
    {
      cout << "Column is full, please enter another column: " << endl;
      cin >> column;
      row = add_row(board, column);
    }
    no_entered += 1;
    board[row][column - 1] = 'O';
    setup(board);
    completed = check_completed(board, no_entered, 'O');
    if (completed == true) 
    {
      return 2;
    }
    full = all_filled(board);
  }
  return -1;
}

int evaluate_board(char board[6][7]) 
{
  // Simple evaluation: +10 for AI win, -10 for player win, 0 for draw or
  // ongoing
  if (check_completed(board, 0, 'X'))
    return 10; // AI wins
  if (check_completed(board, 0, 'O'))
    return -10; // Player wins
  return 0;     // Ongoing or draw
}

int minimax(char board[6][7], int depth, bool isMaximizing, int maxDepth = 7) 
{
    int score = evaluate_board(board);
    if (score == 10 || score == -10 || depth >= maxDepth)
        return score;
    if (all_filled(board))
        return 0;

    if (isMaximizing) 
    {
        int bestScore = INT_MIN;
        for (int col = 1; col <= 7; col++) 
        {
            int row = add_row(board, col);
            if (row != -1) 
            {            
                board[row][col - 1] = 'X';
                bestScore = max(bestScore, minimax(board, depth + 1, false, maxDepth));
                board[row][col - 1] = '-';
            }
        }
        return bestScore;
    }
    else 
    {
        int bestScore = INT_MAX;
        for (int col = 1; col <= 7; col++) 
        {
            int row = add_row(board, col);
            if (row != -1) 
            {             
                board[row][col - 1] = 'O';
                bestScore = min(bestScore, minimax(board, depth + 1, true, maxDepth));
                board[row][col - 1] = '-';
            }
        }
        return bestScore;
    }
}

int minimax_algo(char board[6][7]) 
{
    int bestValue = INT_MIN;
    int bestMove = -1;

    for (int col = 1; col <= 7; col++) 
    {
        int row = add_row(board, col);
        if (row != -1) 
        {
            // Simulate opponent's move for blocking
            board[row][col - 1] = 'O';
            if (check_completed(board, 0, 'O')) 
            {
                board[row][col - 1] = '-'; // Undo simulation
                return col; // Block this move immediately
            }
            board[row][col - 1] = '-'; // Undo simulation

            // Simulate AI's move
            board[row][col - 1] = 'X';
            int moveValue = minimax(board, 0, false); // Minimax evaluation
            board[row][col - 1] = '-'; // Undo move

            // Update best move if value is greater
            if (moveValue > bestValue) 
            {
                bestValue = moveValue;
                bestMove = col;
            }
        }
    }
    return bestMove;
}


int player_vs_AI(char board[6][7]) 
{
  int pos, row, column, choice;
  int no_entered = 0;
  bool full, completed;
  cout << endl;
  cout << "Player 1 = \"O\"" << endl;
  cout << "Computer = \"X\"" << endl;
  cout << endl;
  cout << "Wanna go first or challenge me?" << endl;
  cout << "1. Go first" << endl;
  cout << "2. Challenge me" << endl;
  cin >> choice;
  while (choice != 1 && choice != 2) 
  {
    cout << "Invalid Output, Please enter between 1 or 2";
    cin >> choice;
  }
  if (choice == 1) 
  {
    cout << "Your turn: ";
    cin >> pos;
    pos = validate_column(board, pos);
    board[0][pos - 1] = 'O';
    full = all_filled(board);
    setup(board);
    no_entered++;
    while (full == false) 
    {
      // AI
      cout << "My turn:" << endl;
      column = minimax_algo(board);
      column = validate_column(board, column);
      row = add_row(board, column);
      no_entered += 1;
      board[row][column - 1] = 'X';
      setup(board);
      completed = check_completed(board, no_entered, 'X');
      if (completed == true) 
      {
        return 1;
      }
      full = all_filled(board);
      if (full == true) 
      {
        return -1;
      }
      // Player
      cout << "Your turn: ";
      cin >> column;
      column = validate_column(board, column);
      row = add_row(board, column);
      while (row == -1) 
      {
        cout << "Column is full, please enter another column: " << endl;
        cin >> column;
        row = add_row(board, column);
      }
      no_entered += 1;
      board[row][column - 1] = 'O';
      setup(board);
      completed = check_completed(board, no_entered, 'O');
      if (completed == true) 
      {
        return 2;
      }
      full = all_filled(board);
    }
  }
  else 
  {
    full = all_filled(board);
    while (full == false) 
    {
      // AI
      cout << "My turn:" << endl;
      column = minimax_algo(board);
      column = validate_column(board, column);
      row = add_row(board, column);
      no_entered += 1;
      board[row][column - 1] = 'X';
      setup(board);
      completed = check_completed(board, no_entered, 'X');
      if (completed == true) 
      {
        return 1;
      }
      full = all_filled(board);
      if (full == true) 
      {
        return -1;
      }
      // Player
      cout << "Your turn: ";
      cin >> column;
      column = validate_column(board, column);
      row = add_row(board, column);
      while (row == -1) 
      {
        cout << "Column is full, please enter another column: " << endl;
        cin >> column;
        row = add_row(board, column);
      }
      no_entered += 1;
      board[row][column - 1] = 'O';
      setup(board);
      completed = check_completed(board, no_entered, 'O');
      if (completed == true) 
      {
        return 2;
      }
      full = all_filled(board);
    }
  }
  return -1;
}

int main() {
  int choice, winner;
  cout << "-----------------------------" << endl;
  cout << "Welcome to the Connect 4 Game" << endl;
  cout << "-----------------------------" << endl;
  cout << endl;
  cout << "Rules:" << endl;
  cout << "The player entering first will enter in only first row" << endl;
  cout << "If there is a ball in first row, then it can be filled vertically"
       << endl;
  cout << "If a player's 4 boxes are consecutively filled either "
          "horizantally, "
          "vertically or diagonally, that player will win "
       << endl;
  cout << endl;
  cout << "The setup is as follow:" << endl;
  char board[6][7];
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 7; j++) {
      board[i][j] = '-';
    }
  }
  setup(board);
  cout << "Do you want to play against Computer or another player? " << endl;
  cout << "For Computer, press 1" << endl;
  cout << "For Player, press 2" << endl;
  cin >> choice;

  while ((choice != 1 && choice != 2) || cin.fail()) 
  {
    cout << "Invalid Choice, Please enter between 1 or 2" << endl;
    cin >> choice;
  }
  if (choice == 2) 
  {
    winner = player_vs_player(board);
    if (winner == 1) 
    {
      cout << "Player 2 wins" << endl;
    }
    else if (winner == 2) 
    {
      cout << "Player 1 wins" << endl;
    }
    else 
    {
      cout << "It's a draw" << endl;
    }
  } 
  else 
  {
    winner = player_vs_AI(board);
    if (winner == 1) 
    {
      cout << "Hard..Luck..Computer won" << endl;
    }
    else if (winner == 2) 
    {
      cout << "You won" << endl;
    }
    else 
    {
      cout << "Unlucky It's a draw" << endl;
    }
  }
  return 0;
}