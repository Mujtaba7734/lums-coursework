#include <SFML/Graphics.hpp>
#include <iostream>
#include <limits.h>
#include <cstring> // For memset

using namespace std;

// Constants
const int ROWS = 6;
const int COLS = 7;
const float CELL_SIZE = 100.f;

// Function to check if the board is full
bool allFilled(char board[ROWS][COLS]) 
{
    for (int i = 0; i < ROWS; i++) 
    {
        for (int j = 0; j < COLS; j++) 
        {
            if (board[i][j] == '-') 
            {
                return false;
            }
        }
    }
    return true;
}

// Function to find the first available row in a column
int addRow(char board[ROWS][COLS], int column) 
{
    for (int i = 0; i < ROWS; i++) 
    {
        if (board[i][column - 1] == '-') 
        {
            return i;
        }
    }
    return -1;
}

// Function to check whether anyone won or not
bool checkCompleted(char board[ROWS][COLS], char check) 
{
    for (int i = 0; i < ROWS; i++) 
    {
        for (int j = 0; j < COLS; j++) 
        {
            // Horizontal check
            if (j <= COLS - 4 && 
                board[i][j] == check && 
                board[i][j + 1] == check && 
                board[i][j + 2] == check && 
                board[i][j + 3] == check) 
            {
                return true;
            }

            // Vertical check
            if (i <= ROWS - 4 && 
                board[i][j] == check && 
                board[i + 1][j] == check && 
                board[i + 2][j] == check && 
                board[i + 3][j] == check) 
            {
                return true;
            }

            // Diagonal (bottom-left to top-right)
            if (i <= ROWS - 4 && j <= COLS - 4 && 
                board[i][j] == check && 
                board[i + 1][j + 1] == check && 
                board[i + 2][j + 2] == check && 
                board[i + 3][j + 3] == check) 
            {
                return true;
            }

            // Diagonal (top-left to bottom-right)
            if (i >= 3 && j <= COLS - 4 && 
                board[i][j] == check && 
                board[i - 1][j + 1] == check && 
                board[i - 2][j + 2] == check && 
                board[i - 3][j + 3] == check) 
            {
                return true;
            }
        }
    }
    return false;
}

// Function to evaluate the board
int evaluateBoard(char board[ROWS][COLS]) 
{
    if (checkCompleted(board, 'X'))
        return 10; // AI wins
    if (checkCompleted(board, 'O'))
        return -10; // Player wins
    return 0;     // Ongoing or draw
}

// Function for making difficulty window in SFML
int selectDifficulty(sf::Font &font) 
{
    sf::RenderWindow difficultyWindow(sf::VideoMode(400, 300), "Select Difficulty");

    sf::Text title;
    title.setFont(font);
    title.setString("Select Difficulty:");
    title.setCharacterSize(30);
    title.setFillColor(sf::Color::White);
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.left + titleBounds.width / 2, titleBounds.top + titleBounds.height / 2);
    title.setPosition(difficultyWindow.getSize().x / 2, 50);

    sf::Text easyButton, mediumButton, hardButton;

    easyButton.setFont(font);
    easyButton.setString("Easy");
    easyButton.setCharacterSize(24);
    easyButton.setFillColor(sf::Color::Green);
    easyButton.setPosition(150, 100);

    mediumButton.setFont(font);
    mediumButton.setString("Medium");
    mediumButton.setCharacterSize(24);
    mediumButton.setFillColor(sf::Color::Blue);
    mediumButton.setPosition(150, 150);

    hardButton.setFont(font);
    hardButton.setString("Hard");
    hardButton.setCharacterSize(24);
    hardButton.setFillColor(sf::Color::Red);
    hardButton.setPosition(150, 200);

    while (difficultyWindow.isOpen()) 
    {
        sf::Event event;
        while (difficultyWindow.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                difficultyWindow.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(difficultyWindow);

                if (easyButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) 
                {
                    difficultyWindow.close();
                    return 3; // Easy
                }
                if (mediumButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) 
                {
                    difficultyWindow.close();
                    return 5; // Medium
                }
                if (hardButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) 
                {
                    difficultyWindow.close();
                    return 7; // Hard
                }
            }
        }

        difficultyWindow.clear(sf::Color::Black);
        difficultyWindow.draw(title);
        difficultyWindow.draw(easyButton);
        difficultyWindow.draw(mediumButton);
        difficultyWindow.draw(hardButton);
        difficultyWindow.display();
    }
    return 5; // Default to Medium if window is closed
}

// Minimax function with alpha-beta pruning
int miniMax(char board[ROWS][COLS], int depth, bool isMaximizing, int alpha, int beta, int maxDepth = 7) 
{
    int score = evaluateBoard(board);
    if (score == 10 || score == -10 || depth >= maxDepth || allFilled(board))
    {
        return score;
    }
    if (isMaximizing) 
    {
        int bestScore = INT_MIN;
        for (int col = 1; col <= COLS; col++) 
        {
            int row = addRow(board, col);
            if (row != -1) {
                board[row][col - 1] = 'X';
                bestScore = max(bestScore, miniMax(board, depth + 1, false, alpha, beta, maxDepth));
                board[row][col - 1] = '-';
                alpha = max(alpha, bestScore);
                if (beta <= alpha) break; // Alpha-beta pruning
            }
        }
        return bestScore;
    }
    else 
    {
        int bestScore = INT_MAX;
        for (int col = 1; col <= COLS; col++) 
        {
            int row = addRow(board, col);
            if (row != -1) 
            {
                board[row][col - 1] = 'O';
                bestScore = min(bestScore, miniMax(board, depth + 1, true, alpha, beta, maxDepth));
                board[row][col - 1] = '-';
                beta = min(beta, bestScore);
                if (beta <= alpha) break; // Alpha-beta pruning
            }
        }
        return bestScore;
    }
}

// AI move using minimax
int minimaxAlgorithm(char board[ROWS][COLS], int maxDepth) 
{
    int bestValue = INT_MIN;
    int bestMove = -1;

    for (int col = 1; col <= COLS; col++) 
    {
        int row = addRow(board, col);
        if (row != -1) {
            board[row][col - 1] = 'X';
            int moveValue = miniMax(board, 0, false, INT_MIN, INT_MAX, maxDepth);
            board[row][col - 1] = '-';

            if (moveValue > bestValue) 
            {
                bestValue = moveValue;
                bestMove = col;
            }
        }
    }
    return bestMove;
}

// Function to draw the game board
void drawBoard(sf::RenderWindow &window, char board[ROWS][COLS]) 
{
    for (int i = 0; i < ROWS; i++) 
    {
        for (int j = 0; j < COLS; j++) 
        {
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            cell.setFillColor(sf::Color(0, 0, 255));
            cell.setPosition(j * CELL_SIZE, i * CELL_SIZE);
            window.draw(cell);

            sf::CircleShape token(CELL_SIZE / 2 - 5);
            token.setPosition(j * CELL_SIZE + 5, i * CELL_SIZE + 5);
            if (board[ROWS - 1 - i][j] == 'O') 
            {
                token.setFillColor(sf::Color::Yellow);
            } 
            else if (board[ROWS - 1 - i][j] == 'X') 
            {
                token.setFillColor(sf::Color::Red);
            } 
            else 
            {
                token.setFillColor(sf::Color::White);
            }
            window.draw(token);
        }
    }
}

// Function to display the menu
bool showMenu(sf::Font &font) 
{
    sf::RenderWindow menuWindow(sf::VideoMode(400, 300), "Connect 4 - Menu");

    sf::Text title;
    title.setFont(font);
    title.setString("Welcome to Connect 4!");
    title.setCharacterSize(30);
    title.setFillColor(sf::Color::White);
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.left + titleBounds.width / 2, titleBounds.top + titleBounds.height / 2);
    title.setPosition(menuWindow.getSize().x / 2, 50); // Center horizontally at Y=50

    sf::Text aiButton;
    aiButton.setFont(font);
    aiButton.setString("Player vs AI");
    aiButton.setCharacterSize(24);
    aiButton.setFillColor(sf::Color::Green);
    sf::FloatRect aiBounds = aiButton.getLocalBounds();
    aiButton.setOrigin(aiBounds.left + aiBounds.width / 2, aiBounds.top + aiBounds.height / 2);
    aiButton.setPosition(menuWindow.getSize().x / 2, 120); // Center horizontally at Y=120

    sf::Text playerButton;
    playerButton.setFont(font);
    playerButton.setString("Player 1 vs Player 2");
    playerButton.setCharacterSize(24);
    playerButton.setFillColor(sf::Color::Blue);
    sf::FloatRect playerBounds = playerButton.getLocalBounds();
    playerButton.setOrigin(playerBounds.left + playerBounds.width / 2, playerBounds.top + playerBounds.height / 2);
    playerButton.setPosition(menuWindow.getSize().x / 2, 180); // Center horizontally at Y=180

    while (menuWindow.isOpen()) 
    {
        sf::Event event;
        while (menuWindow.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
            {
                menuWindow.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(menuWindow);

                if (aiButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) 
                {
                    menuWindow.close();
                    return true; // Play against AI
                } 
                else 
                {
                    if (playerButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) 
                    {
                        menuWindow.close();
                        return false; // Play against Player
                    }
                }
            }
        }

        menuWindow.clear(sf::Color::Black);
        menuWindow.draw(title);
        menuWindow.draw(aiButton);
        menuWindow.draw(playerButton);
        menuWindow.display();
    }
    return false; 
}

// Function for whole game algorithm
void runGame(char board[ROWS][COLS], bool againstAI, sf::Font &font, int difficulty) 
{
    sf::RenderWindow window(sf::VideoMode(COLS * CELL_SIZE, ROWS * CELL_SIZE + 50), "Connect 4");

    // Text for displaying the result
    sf::Text resultText;
    resultText.setFont(font);
    resultText.setCharacterSize(36);
    resultText.setFillColor(sf::Color::Yellow);

    // Overlay for winner announcement
    sf::RectangleShape textBox;
    textBox.setSize(sf::Vector2f(COLS * CELL_SIZE, 100));
    textBox.setFillColor(sf::Color(50, 50, 50, 200)); // Semi-transparent dark grey

    // Buttons
    sf::RectangleShape playAgainButton(sf::Vector2f(200, 50));
    playAgainButton.setFillColor(sf::Color::Green);
    playAgainButton.setPosition(COLS * CELL_SIZE / 2 - 100, ROWS * CELL_SIZE / 2);

    sf::RectangleShape exitButton(sf::Vector2f(200, 50));
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setPosition(COLS * CELL_SIZE / 2 - 100, ROWS * CELL_SIZE / 2 + 60);

    // Button labels
    sf::Text playAgainText, exitText;
    playAgainText.setFont(font);
    playAgainText.setString("Play Again");
    playAgainText.setCharacterSize(24);
    playAgainText.setFillColor(sf::Color::White);
    playAgainText.setPosition(playAgainButton.getPosition().x + 50, playAgainButton.getPosition().y + 10);

    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(24);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(exitButton.getPosition().x + 75, exitButton.getPosition().y + 10);

    // Text for displaying the current turn
    sf::Text turnText;
    turnText.setFont(font);
    turnText.setCharacterSize(35);
    turnText.setPosition(COLS * CELL_SIZE / 2 - 100, ROWS * CELL_SIZE);

    // Initial player turn and color
    turnText.setString("Player 1's Turn");
    turnText.setFillColor(sf::Color::Yellow); 

    bool playerTurn = true; // true -> Player 1, false -> Player 2 (or AI in Player vs AI mode)
    bool completed = false;

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle player moves
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !completed) 
            {
                int column = event.mouseButton.x / CELL_SIZE + 1;
                int row = addRow(board, column);

                if (row != -1) 
                { 
                    char currentPlayer = playerTurn ? 'O' : 'X';
                    board[row][column - 1] = currentPlayer;

                    // Check if the current player has won
                    if (checkCompleted(board, currentPlayer)) 
                    {
                        resultText.setString(playerTurn ? "Player 1 Wins!" : (againstAI ? "AI Wins!" : "Player 2 Wins!"));
                        completed = true;
                    }
                    else if (allFilled(board)) 
                    {
                        resultText.setString("It's a Draw!");
                        completed = true;
                    }

                    // Switch turns and update turn text color
                    playerTurn = !playerTurn;
                    if (!completed) 
                    {
                        if (playerTurn) 
                        {
                            turnText.setString("Player 1's Turn");
                            turnText.setFillColor(sf::Color::Yellow); // Player 1's token color (Yellow)
                        } 
                        else 
                        {
                            turnText.setString(againstAI ? "AI's Turn" : "Player 2's Turn");
                            turnText.setFillColor(sf::Color::Red); // Player 2 or AI token color (Red)
                        }
                    }
                }

                // AI move (if applicable)
                if (againstAI && !playerTurn && !completed) 
                {
                    int aiMove = minimaxAlgorithm(board, difficulty);
                    row = addRow(board, aiMove);
                    board[row][aiMove - 1] = 'X';

                    if (checkCompleted(board, 'X')) 
                    {
                        resultText.setString("AI Wins!");
                        completed = true;
                    }

                    playerTurn = true;
                    turnText.setString("Player 1's Turn");
                    turnText.setFillColor(sf::Color::Yellow); // Back to Player 1's color
                }
            }

            // Handle buttons after game completion
            if (completed && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (playAgainButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) 
                {
                    memset(board, '-', ROWS * COLS * sizeof(char));
                    window.close(); 
                    runGame(board, againstAI, font, difficulty); // Start the game again
                    return;
                }
                if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) 
                {
                    window.close(); // "Exit" button
                    return;
                }
            }
        }
        // Draw the board
        window.clear(sf::Color(128, 128, 128)); // Grey background
        drawBoard(window, board);

        if (completed)
        {
            // Draw winner announcement
            sf::RectangleShape blurOverlay;
            blurOverlay.setSize(sf::Vector2f(COLS * CELL_SIZE, ROWS * CELL_SIZE));
            blurOverlay.setFillColor(sf::Color(0, 0, 0, 150)); // Semi-transparent black
            blurOverlay.setPosition(0, 0);
            window.draw(blurOverlay);

            sf::FloatRect textBounds = resultText.getLocalBounds();
            resultText.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
            resultText.setPosition(COLS * CELL_SIZE / 2, textBox.getSize().y / 2);

            window.draw(textBox);
            window.draw(resultText);

            window.draw(playAgainButton);
            window.draw(playAgainText);
            window.draw(exitButton);
            window.draw(exitText);
        }
        else 
        {
            window.draw(turnText);
        }

        window.display();
    }
}

// Main function
int main() 
{
    char board[ROWS][COLS];
    memset(board, '-', sizeof(board));

    sf::Font font;
    if (!font.loadFromFile("F:\\Chrome downloads\\times.ttf")) 
    {
        cout << "Error loading font!" << endl;
        return -1;
    }

    bool againstAI = showMenu(font);

    int difficulty = 5; 
    if (againstAI) 
    {
        difficulty = selectDifficulty(font); // Ask for difficulty
    }

    runGame(board, againstAI, font, difficulty);

    return 0;
}
