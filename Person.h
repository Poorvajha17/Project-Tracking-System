#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Person
{
private:
    string ID;
    string name;
    string role;
    bool assignedToProject;
public:
    Person();
    Person(const string& ID, const string& name, string role,bool assignedToProject);

    string getID() const;
    string getName() const;
    string getRole() const;
    bool isAssignedToProject() const;

    void setID(const string& ID);
    void setName(const string& name);
    void setRole(string role);
    void setAssignedToProject(bool assigned);

    void display() const;
    void loadFromFile();
    bool loadPersonFromFile(const string& personID);
    void updateStatus(bool assigned);
    void addToFile() const;

    friend istream& operator>>(istream& in, Person& person);
};

#endif // PERSON_H

