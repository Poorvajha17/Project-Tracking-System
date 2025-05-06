#include"Task.h"
#include"Person.h"
#include"Project.h"
#include<string>
#include <iomanip>
#include<iostream>

using namespace std;


Task::Task(const string& id,const string& name,const string& startDate,const string& endDate,const string& status1,const string& description,const string& ID,const Person& person,string due,string status2):Project(id,name,startDate,endDate,status1,description)
{
    taskID=ID;
    assignedPerson=person;
    dueDate=due;
    status=status2;
}

void Task::setTaskID(const string& ID)
{
    this->taskID=ID;
}

void Task::setAssignedPerson(const Person& person)
{
    this->assignedPerson=person;
}

void Task::setDueDate(string Due)
{
    this->dueDate=Due;
}

void Task::setStatus(string status)
{
    this->status=status;
}

string Task::getTaskID() const
{
    return taskID;
}

Person Task::getAssignedPerson() const
{
    return assignedPerson;
}

string Task::getDueDate() const
{
    return dueDate;
}

string Task::getStatus() const
{
    return status;
}

void Task::display() const
{
    ifstream file("tasks.txt");
    string fileTaskID, fileProjectID, fileAssignedPersonID, fileAssignedPersonName, fileAssignedPersonRole, fileDueDate, fileStatus;
    bool found = false;

    if (file.is_open())
    {
        while (file >> fileTaskID >> fileProjectID >> fileAssignedPersonID >> fileDueDate >> fileStatus) {
            if (fileTaskID == taskID) {
                cout << left << setw(10) << fileTaskID;
                cout << left << setw(15) << fileProjectID;
                cout << left << setw(15) << fileAssignedPersonID;
                cout << left << setw(15) << fileDueDate;
                cout << left << setw(15) << fileStatus << endl;
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "Task with ID " << taskID << " not found." << endl;
        }

        file.close();
    }
    else
    {
        cout << "Unable to open tasks file for reading." << endl;
    }
}



void Task::readFromTasksFile()
{
    ifstream file("tasks.txt");
    string taskID, projectID, assignedPersonID, dueDate, status;

    if (file.is_open())
    {
        cout << left << setw(16) << "Task ID";
        cout << left << setw(16) << "Project ID";
        cout << left << setw(16) << "Assigned Person ID";
        cout << left << setw(16) << "Due Date";
        cout << left << setw(16) << "Status" << endl;

        while (file >> taskID >> projectID >> assignedPersonID >> dueDate >> status)
        {
            cout << left << setw(16) << taskID;
            cout << left << setw(16) << projectID;
            cout << left << setw(16) << assignedPersonID;
            cout << left << setw(16) << dueDate;
            cout << left << setw(16) << status << endl;
        }
        file.close();
    }
    else
    {
        cout << " Unable to open tasks file for reading." << endl;
    }
}

void Task::appendToTasksFile() const
{
    ofstream file("tasks.txt", ios::app);
    if (file.is_open())
    {
        file << left << setw(15) << taskID;
        file << left << setw(15) << getID();
        file << left << setw(15) << assignedPerson.getID();
        file << left << setw(15) << dueDate;
        file << left << setw(15) << status << endl;
        file.close();
    }
    else
    {
        cout<<" Unable to open tasks file for appending."<<endl;
    }
}

void Task::removeFromFile(const string& filename, const string& taskID)
{
    ifstream inFile(filename);
    ofstream outFile("temp.txt");

    if (!inFile.is_open())
    {
        cerr << "Error opening file: " << filename <<endl;
        return;
    }

    string line;
    while (getline(inFile, line))
    {
        if (line.find(taskID) == string::npos)
        {
            outFile << line <<endl;
        }
    }

    inFile.close();
    outFile.close();

    remove(filename.c_str());

    rename("temp.txt", filename.c_str());

    cout << "Task with ID " << taskID << " removed from file successfully." <<endl;
}
