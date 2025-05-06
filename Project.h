#ifndef PROJECT_H
#define PROJECT_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Person.h"

using namespace std;

class Project
{
protected:
    string projectID;
    string projectName;
    string startDate;
    string endDate;
    string status;
    string description;
    vector<Person> assigned_persons;

public:
    Project();
    Project(const string& id,const string& name,const string& startDate,string endDate,string status, const string& description);
    void assignPerson(const Person& person);
    void display() const;
    void displayProject() const;

    string getID() const;
    string getProjectName() const;
    string getStartDate() const;
    string getEndDate() const;
    string getStatus() const;
    string getDescription() const;
    vector<Person> getAssignedPersons() const;


    void setID(const string& id);
    void setProjectName(const string& name);
    void setStartDate(const string& startDate);
    void setEndDate(string endDate);
    void setStatus(const string& status);
    void setDescription(const string& description);

    friend istream& operator>>(istream& in, Project& project);
    friend ostream& operator<<(ostream& out, const Project& project);


    static void loadFromFile();
    void saveToFile() const;
    bool loadProjectFromFile(const string& projectID);
};

#endif // PROJECT_H
