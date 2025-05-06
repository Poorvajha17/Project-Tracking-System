#include"Tracker.h"
#include"Issue.h"
#include<string>
#include <chrono>
#include<ctime>
#include<iostream>
#include <algorithm>
#include<iomanip>

using namespace std;

Tracker::Tracker(const Project& project):project(project){}

void Tracker::addTask(const Task& task)
{
    tasks.push_back(task);
}

void Tracker::displayProjectStatus() const
{
    cout<<"** Project Details: **"<<endl;
    project.displayProject();
    cout << endl << endl;
}

void Tracker::displayTaskStatus(const string& projectID) const
{
    cout << "** Task Details:**" << endl;
    cout << "------------------------------------------------------------------------------------" << endl;
    cout << left << setw(10) << "Task ID";
    cout << left << setw(15) << "Project ID";
    cout << left << setw(20) << "assigned person";
    cout << left << setw(15) << "Due Date";
    cout << left << setw(15) << "Status" << endl;
    cout << "------------------------------------------------------------------------------------\n" << endl;

    ifstream file("tasks.txt");
    if (!file.is_open())
    {
        cerr << " Unable to open tasks file for reading." << endl;
        return;
    }

    string fileProjectID, fileTaskID, fileDueDate, fileStatus,fileAssignedID;
    while (file >> fileTaskID >> fileProjectID >> fileAssignedID >> fileDueDate >> fileStatus)
    {
        if (fileProjectID == projectID)
        {
            cout << left << setw(10) << fileTaskID;
            cout << left << setw(15) << fileProjectID;
            cout << left << setw(20) << fileAssignedID;
            cout << left << setw(15) << fileDueDate;
            cout << left << setw(15) << fileStatus << endl;
        }
    }
    cout << "------------------------------------------------------------------------------------\n" << endl;
    cout << endl << endl;
    file.close();
}

void Tracker::addIssue(const Issue& issue)
{
    issues.push_back(issue);
}

void Tracker::removeIssue(const string& issueID)
{
    issues.erase(remove_if(issues.begin(), issues.end(), [&](const Issue& issue) { return issue.getIssueID() == issueID;}), issues.end());
}

void Tracker::displayIssueStatus(const string& projectID) const
{
    cout << "** Issue Details: **" << endl;
    cout << "------------------------------------------------------------------------------------\n" << endl;
    cout << left << setw(15) << "Issue ID";
    cout << left << setw(20) << "Description";
    cout << left << setw(20) << "Status";
    cout << left << setw(15) << "Project ID" << endl;
    cout << "------------------------------------------------------------------------------------\n" << endl;

    ifstream file("issues.txt");
    if (!file.is_open())
    {
        cerr << "Unable to open issues file for reading." << endl;
        return;
    }

    string fileIssueID, fileDescription, fileStatus, fileProjectID;
    while (file >> fileIssueID >> fileDescription >> fileStatus >> fileProjectID)
    {
        if (fileProjectID == projectID)
        {
            cout << left << setw(15) << fileIssueID;
            cout << left << setw(20) << fileDescription;
            cout << left << setw(20) << fileStatus;
            cout << left << setw(15) << fileProjectID << endl;
        }
    }
    cout << "------------------------------------------------------------------------------------\n" << endl;

    file.close();
    cout << endl << endl;
}

