#ifndef CURRICULUM_H
#define CURRICULUM_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

class Course
{
    std::string code;
    std::string name;
    int credits;
    std::vector<int> timeSlots;
    int roomCapacity;

public:
    Course(const std::string &code, const std::string &name, int credits,
           const std::vector<int> &timeSlots = {}, int roomCapacity = 0);

    std::string getCode() const;
    std::string getName() const;
    int getCredits() const;
    const std::vector<int> &getTimeSlots() const;
    int getRoomCapacity() const;
    void print() const;
};

class Curriculum
{
    std::map<std::string, Course> courses;
    std::map<std::string, std::vector<std::string>> prereq;

public:
    void addCourse(const Course &c);
    Course* getCourse(const std::string &code);
    std::vector<std::string> getPrerequisites(const std::string &code);
    bool removeCourse(const std::string &code);
    std::string addPrerequisite(const std::string &course, const std::string &pre);
    std::map<std::string, bool> getAvailableCourses(const std::vector<std::string> &completedList) const;
    bool canEnroll(const std::string &course, const std::vector<std::string> &completedList) const;
    void printCurriculum() const;
};

#endif
