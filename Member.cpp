#include "Member.h"
#include "Issue.h"
#include "Tracker.h"
#include<iostream>
#include<string>
#include<vector>
#include <fstream>
#include<sstream>
#include<iomanip>

Member::Member(const string& username, const string& password) : User(username, password) {}

string Member::getRole() const
{
    return "Member";
}


void Member::updateProjectStatus()
{
    string project_id;
    cout << "Enter the Project ID:";
    cin >> project_id;
    string new_status;
    cout << "Enter the status to be updated:";
    cin >> new_status;
    cout << endl;
    ifstream infile("projects.txt");
    ofstream outfile("temp.txt");

    string line;
    bool projectUpdated = false;
    while (getline(infile, line))
    {
        if (line.find(project_id) != string::npos)
        {
            istringstream iss(line);
            string id, name, start_date, end_date, status, description;
            iss >> id >> name >> start_date >> end_date >> status;
            getline(iss, description);
            status = new_status;

            outfile << setw(15) << left << id << setw(15) << left << name << setw(15) << left << start_date << setw(15) << left << end_date << setw(5) << left << status << left << description << endl;

            projectUpdated = true;
        }
        else
        {
            outfile << line << endl;
        }
    }

    infile.close();
    outfile.close();

    if (projectUpdated)
    {
        if (remove("projects.txt") != 0)
        {
            cerr << " Unable to delete original projects file." << endl;
            return;
        }
        if (rename("temp.txt", "projects.txt") != 0)
        {
            cerr << " Unable to rename temporary file." << endl;
            return;
        }

        cout << "******* Project with ID \"" << project_id << "\" updated successfully *******" << endl << endl;

        ifstream infile2("projects.txt");
        while (getline(infile2, line))
        {
            if (line.find(project_id) != string::npos)
            {
                cout << endl << "Updated Project Details: " << endl << endl ;
                cout << "------------------------------------------------------------------------------------------------------------\n" << endl;
                cout << line << endl;
                cout << "------------------------------------------------------------------------------------------------------------\n" << endl;
                cout << endl;
                break;
            }
        }
    }
    else
    {
        cout << "Project with ID \"" << project_id << "\" not found." << endl;
    }
}



void Member::updateTaskProgress()
{
    string task_id;
    cout << "Enter the Task ID:";
    cin >> task_id;
    string new_status;
    cout << "Enter the status to be updated:";
    cin >> new_status;
    cout  << endl;
    ifstream infile("Tasks.txt");
    ofstream outfile("temp.txt");

    string line;
    bool taskUpdated = false;
    while (getline(infile, line))
    {
        if (line.find(task_id) != string::npos)
        {
            istringstream iss(line);
            string id, name, start_date, end_date, status, project_id;
            iss >> id >> name >> start_date >> end_date >> status >> project_id;

            status = new_status;

            outfile << setw(16) << left << id << setw(16) << left << name << setw(16) << left << start_date << setw(16) << left << end_date << setw(16) << left << status << setw(16) << left << setw(16) << left << project_id << endl;

            taskUpdated = true;
        }
        else
        {
            outfile << line << endl;
        }
    }

    infile.close();
    outfile.close();

    if (taskUpdated)
    {
        if (remove("Tasks.txt") != 0)
        {
            cerr << " Unable to delete original tasks file." << endl;
            return;
        }
        if (rename("temp.txt", "Tasks.txt") != 0)
        {
            cerr << " Unable to rename temporary file." << endl;
            return;
        }

        cout << "******* Task with ID \"" << task_id << "\" updated successfully *******" << endl << endl;

        ifstream infile2("Tasks.txt");
        while (getline(infile2, line))
        {
            if (line.find(task_id) != string::npos)
            {
                cout << "Updated Task Details: " << endl << endl;
                cout << "------------------------------------------------------------------------------------------------------------\n" << endl;
                cout << line << endl;
                cout << "------------------------------------------------------------------------------------------------------------\n" << endl;
                cout << endl;
                break;
            }
        }
    }
    else
    {
        cout << "Task with ID \"" << task_id << "\" not found." << endl;
    }
}


void Member::addIssue()
{
    Issue issue;
    cout << "Enter the details of the Issue:" << endl;
    cin >> issue;
    issue.appendToIssuesFile();

    ifstream infile("Issues.txt");
    string line;
    while (getline(infile, line))
    {
        if (line.find(issue.getIssueID()) != string::npos)
        {
            cout << endl << "Added Issue Details: "<< endl;
            cout << "------------------------------------------------------------------------------------------------------------\n" << endl;
            cout << line << endl;
            cout << "------------------------------------------------------------------------------------------------------------\n" << endl << endl;
            break;
        }
    }
}

void Member::updateIssueStatusOrDescription()
{
    string issue_id;
    cout << "Enter the Issue ID:";
    cin >> issue_id;
    string new_status;
    cout << "Enter the status to be updated:";
    cin >> new_status;
    cout << endl;
    ifstream infile("issues.txt");
    ofstream outfile("temp.txt");

    string line;
    bool issueUpdated = false;
    while (getline(infile, line))
    {
        if (line.find(issue_id) != string::npos)
        {
            istringstream iss(line);
            string id, description, status, project_id;
            iss >> id >> description >> status >> project_id;

            status = new_status;

            outfile << setw(15) << left << id << setw(20) << left << description << setw(20) << left << status << setw(15) << left << project_id << endl;
            issueUpdated = true;
        }
        else
        {
            outfile << line << endl;
        }
    }

    infile.close();
    outfile.close();

    if (issueUpdated)
    {
        if (remove("issues.txt") != 0)
        {
            cerr << " Unable to delete original issues file." << endl;
            return;
        }
        if (rename("temp.txt", "issues.txt") != 0)
        {
            cerr << " Unable to rename temporary file." << endl;
            return;
        }

        cout << "******** Issue with ID \"" << issue_id << "\" updated successfully *******" << endl << endl;

        ifstream infile2("issues.txt");
        while (getline(infile2, line))
        {
            if (line.find(issue_id) != string::npos)
            {
                cout << "Updated Issue Details: " << endl << endl;
                cout << "------------------------------------------------------------------------------------------------------------\n" << endl;
                cout << line << endl;
                cout << endl;
                cout << "------------------------------------------------------------------------------------------------------------\n" << endl;
                break;
            }
        }
    }
    else
    {
        cout << "Issue with ID \"" << issue_id << "\" not found." << endl;
    }
}
void Member::accessTrackerAndTrackProject() const
{
    string userID;
    cout << "Enter the User ID:";
    cin >> userID;
    cout << endl;
    ifstream tasksFile("Tasks.txt");
    if (!tasksFile)
    {
        cerr << " Unable to open tasks file." << endl;
        return;
    }

    string projectID;
    string line;
    bool found = false;
    while (getline(tasksFile, line))
    {
        istringstream iss(line);
        string taskID, taskProjectID, assignedUserID;
        iss >> taskID >> taskProjectID >> assignedUserID;


        if (assignedUserID == userID)
        {
            projectID = taskProjectID;
            found = true;
            break;
        }
    }

    tasksFile.close();

    if (!found)
    {
        cout << "No tasks found for UserID: " << userID << endl;
        return;
    }

    Project project;
    project.loadProjectFromFile(projectID);
    Tracker tracker(project);


    cout << "Project Details for UserID: " << userID << endl;
    tracker.displayProjectStatus();
    cout << endl;
    tracker.displayTaskStatus(projectID);
    cout << endl;
    tracker.displayIssueStatus(projectID);
    cout << endl;
}
