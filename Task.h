#ifndef TASK_H
#define TASK_H
#include<string>
#include"Project.h"

class Task : public Project
{
protected:
    string taskID;
    Person assignedPerson;
    string dueDate;
    string status;

public:
    Task(const string& id,const string& name,const string& startDate,const string& endDate,const string& status1,const string& description,const string& ID,const Person& person,string due,string status);

    void setTaskID(const string& ID);
    void setAssignedPerson(const Person& person);
    void setDueDate(string Due);
    void setStatus(string status);

    string getTaskID() const;
    Person getAssignedPerson() const;
    string getDueDate() const;
    string getStatus() const;

    void display() const;

    static void readFromTasksFile();
    void appendToTasksFile() const;

    void removeFromFile(const string& filename, const string& taskID);

};
#endif // TASK_H

