// curriculum.cpp
#include "Task.h"
#include <iostream>
#include <algorithm>

using namespace std;

// -------------------------
// Course Class Implementation
// -------------------------

Course::Course(const string &code, const string &name, int credits,
               const vector<int> &timeSlots, int roomCapacity)
{
    this->code = code;
    this->name = name;
    this->credits = credits;
    this->timeSlots = timeSlots;
    this->roomCapacity = roomCapacity;
}

string Course::getCode() const 
{
    return this->code;
}
string Course::getName() const 
{
    return this->name;
}
int Course::getCredits() const 
{
    return this->credits;
}
const vector<int> &Course::getTimeSlots() const
{
    return timeSlots;
}
int Course::getRoomCapacity() const 
{
    return roomCapacity;
}

void Course::print() const
{
    cout << "Course Code: " << this->code << endl;
    cout << "Name: " << this->name << endl;
    cout << "Credits: " << this->credits << endl;
    cout << "List of TimeSlots: " << endl;
    for (const int &timeslot : timeSlots)
    {
        cout << "- " << timeslot << endl;
    }
    cout << "Room Capacity: " << this->roomCapacity << endl;
}

// -------------------------
// Curriculum Class Implementation
// -------------------------

void Curriculum::addCourse(const Course &c)
{
    auto it = courses.find(c.getCode());
    if (it != courses.end())
    {
        it->second = c;
    }
    else
    {
        courses.insert({c.getCode(), c});
    }
    if (prereq.find(c.getCode()) != prereq.end())
    {
        prereq[c.getCode()] = vector<string>();
    }
}

Course *Curriculum::getCourse(const string &code)
{
    auto it = courses.find(code);
    if (it != courses.end())
    {
        return &(it->second);
    }
    return nullptr;
}

vector<string> Curriculum::getPrerequisites(const string &code)
{
    auto it = prereq.find(code);
    if (it != prereq.end())
    {
        return (it->second);
    }
    return vector<string>();;
}

string Curriculum::addPrerequisite(const string &course, const string &pre)
{
    if (course == pre)
    {
        return "A course cannot be a prerequisite of itself.";
    }

    if (courses.find(course) == courses.end())
    {
        return "addPrerequisite: course " + course + " not found";
    }

    if (courses.find(pre) == courses.end())
    {
        return "addPrerequisite: prerequisite " + pre + " not found";
    }

    if (find(prereq[course].begin(),prereq[course].end(), pre) == prereq[course].end())
    {
        prereq[course].push_back(pre);
        return "Prerequisite added";    
    }
    return "Prerequisite already exists";
}

bool Curriculum::removeCourse(const string &code)
{
    auto it = courses.find(code);
    if (it == courses.end())
    {
        return false;
    }
    courses.erase(code);
    prereq.erase(code);
    for (auto &entry: prereq)
    {
        entry.second.erase(find(entry.second.begin(), entry.second.end(), code), entry.second.end());
    }

    return true;
}

map<string, bool> Curriculum::getAvailableCourses(const vector<string> &completedList) const
{
    // dont have to do it
    return {};
}

bool Curriculum::canEnroll(const string &course, const vector<string> &completedList) const
{
    auto it = prereq.find(course);
    for (auto& entry : it->second)
    {
        if (find(completedList.begin(), completedList.end(), entry) == completedList.end())
        {
            return false;
        }
    }
    return true;
}

void Curriculum::printCurriculum() const
{
    if (courses.empty())
    {
        cout << "No courses in the list" << endl;
        return;
    }
    cout << "Courses: " << endl;
    for (auto &entry : courses)
    {
        entry.second.print();
        cout << "This course's prerequisite courses are: " << endl;
        auto it = prereq.find(entry.second.getCode());
        for (auto& check : it->second)
        {
            cout << check;
        }
    }
}
