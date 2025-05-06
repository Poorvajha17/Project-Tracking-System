#ifndef HEAD_H
#define HEAD_H

#include "User.h"
#include<iostream>
#include <string>

using namespace std;

class Head : public User
{

public:
    Head(const string& username, const string& password);

    string getRole() const;

    void displayListOfProjectsManaged() const;

    void addProject();
    void assignTasks() const;
    void deleteProject();
    void loadDiscardedProjects();
    void accessTrackerAndTrackProject() const;
};

#endif // HEAD_H
