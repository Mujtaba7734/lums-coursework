#include <iostream>
using namespace std;

void getStudentDetails(string &name, int &rollnumber, int &score1, int &score2, int &score3 )
{
    cout << "Enter Student's name (no spaces): ";
    cin >> name;
    cout << "Enter roll number: ";
    cin >> rollnumber;
    cout << "Enter score for subject 1 (0-100): ";
    cin >> score1;
    while (score1 < 0 || score1 > 100)
    {
        cout << "Enter score for subject 1 (0-100): ";
        cin >> score1;
    }
    cout << "Enter score for subject 2 (0-100): ";
    cin >> score2;
    while (score2 < 0 || score2 > 100)
    {
        cout << "Enter score for subject 2 (0-100): ";
        cin >> score2;
    }
    cout << "Enter score for subject 3 (0-100): ";
    cin >> score3;
    while (score3 < 0 || score3 > 100)
    {
        cout << "Enter score for subject 3 (0-100): ";
        cin >> score3;
    } 
}

int calculateAverageAndGrade(char &grade, int &score1, int &score2, int &score3 )
{
    int average = (score1 + score2 + score3) / 3;
    if (average >= 85)
    {
        grade = 'A';
    }
    else if (average >= 70 && average < 85)
    {
        grade = 'B';
    }
    else if (average >= 50 && average < 70)
    {
        grade = 'C';
    }
    else
    {
        grade = 'F';
    }
    return average;
}

void displayStudentDetails(string name, int rollnumber, int average, char grade)
{
    cout << endl;
    cout << "Student Details: " << endl;
    cout << "Name: " << name << endl;
    cout << "Roll Number: " << rollnumber << endl;
    cout << "Average Score: " << average << endl;
    cout << "Grade: " << grade;
}

int main()
{
    string name;
    char grade;
    int rollnumber, score1, score2, score3, average;
    getStudentDetails(name, rollnumber, score1, score2, score3);
    average = calculateAverageAndGrade(grade, score1, score2, score3);
    displayStudentDetails(name, rollnumber, average, grade);
    return 0;
}