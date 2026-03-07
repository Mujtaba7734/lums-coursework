#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    int steps;
    int pac_x = 3;
    int pac_y = 4;
    int villain_x, villain_y = 0;
    int randomNum;
    string direction;
    srand(time(0));

    cout << "Enter the number of steps the villain can take: ";
    cin >> steps;

    for (int count = 1; count <= steps; count ++)
    {
        randomNum = (rand() % 4) + 1;
        if (randomNum == 1)
        {
            villain_y += 1;
            direction = "UP";
        }
        else if (randomNum == 2)
        {
            villain_y -= 1;
            direction = "DOWN";
        }
        else if (randomNum == 3)
        {
            villain_x -= 1;
            direction = "LEFT";
        }
        else
        {
            villain_x += 1;
            direction = "RIGHT";
        }
        cout << "Step " << count << ": Random Number = " << randomNum << " (" << direction;
        cout << "), New position = (" << villain_x << ", " << villain_y << ")" << endl;
        if ((pac_x == villain_x) && (pac_y == villain_y))
        {
            cout << "CAUGHT PACMAN at (3,4)" << endl;
            return 1;
        }
    }
    cout << "Pacman not caught! Final position of the villain: (" << villain_x << ", " << villain_y << ")" << endl;

    return 0;
}