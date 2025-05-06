#ifndef TRACKER_H
#define TRACKER_H
#include"project.h"
#include"Task.h"
#include"issue.h"

class Tracker
{
private:
    Project project;
    vector<Task> tasks;
    vector<Issue> issues;

public:
    Tracker(const Project& project);

    void addTask(const Task& task);

    void displayProjectStatus() const;
    void calculateTimeLeftForProject() const;
    void displayTaskStatus(const string& projectID) const;
    void displayIssueStatus(const string& projectID) const;
    void addIssue(const Issue& issue);
    void removeIssue(const string& issueID);

};

#endif // TRACKER_H

