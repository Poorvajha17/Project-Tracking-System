#include "Head.h"
#include "Project.h"
#include "person.h"
#include "Tracker.h"
#include "Task.h"
#include <iostream>
#include<sstream>
#include <fstream>

using namespace std;

Head::Head(const string& username, const string& password) : User(username, password) {}

string Head::getRole() const
{
    return "Head";
}

void Head::displayListOfProjectsManaged() const
{
    cout << "Projects Managed by " << getUsername() << ":" << endl;
    Project::loadFromFile();
}

void Head::addProject()
{
    Project project1;
    cin >> project1;
    project1.saveToFile();
    cout << "\n************** Added project *****************" << endl << endl;
}

void Head::deleteProject()
{
    string projectId;
    cout << "Enter Project ID to delete: ";
    cin >> projectId;
    cout << endl;

    ifstream projectsFile("projects.txt");
    ofstream tempProjectsFile("temp_projects.txt");
    ofstream discardedFile("discarded_projects.txt", ios::app);

    if (!projectsFile || !tempProjectsFile || !discardedFile)
    {
        cerr << "Error: Unable to open files." << endl;
        return;
    }

    string line;
    bool found = false;
    vector<string> memberIds;
    while (getline(projectsFile, line))
    {
        istringstream iss(line);
        string id;
        if (!(iss >> id) || id.empty())
        {
            tempProjectsFile << line << endl;
            continue;
        }
        if (id == projectId)
        {
            found = true;

            discardedFile << line << endl;
            while (getline(projectsFile, line))
            {
                if (line.empty() || line[0] == 'P')
                {
                    break;
                }
                else
                {
                    string userId = line.substr(0, 4);
                    memberIds.push_back(userId);
                }
            }
        }
        else
        {
            tempProjectsFile << line << endl;
        }
    }

    projectsFile.close();
    tempProjectsFile.close();
    discardedFile.close();

    if (!found)
    {
        cerr << "Project ID \"" << projectId << "\" not found." << endl;
        discardedFile.close();
        return;
    }

    if (remove("projects.txt") != 0)
    {
        cerr << " Unable to delete projects file." << endl;
    }
    if (rename("temp_projects.txt", "projects.txt") != 0) {
        cerr << " Unable to rename temp file." << endl;
    }
    else
    {
        cout << "********** Project with ID " << projectId << " deleted successfully ***********" << endl << endl;
    }

    for (const auto& memberId : memberIds)
    {
        Person person;
        if (!person.loadPersonFromFile(memberId))
         {
            cerr << "Error: Person ID \"" << memberId << "\" not found." << endl;
            continue;
        }
        person.updateStatus(false);
    }
}

void Head :: loadDiscardedProjects()
{
    ifstream discardedFile("discarded_projects.txt");
    if (!discardedFile)
    {
        cerr << "Error: Unable to open discarded projects file." << endl;
        return;
    }

    string line;
    cout << "Discarded Projects:" << endl;
    cout << "----------------------------------------------------------------------------------------\n" << endl;
    while (getline(discardedFile, line))
    {
        cout << line << endl << endl;
    }
     cout << "----------------------------------------------------------------------------------------\n" << endl;
    discardedFile.close();
}


void Head::accessTrackerAndTrackProject() const
{
    string targetProjectID;
    cout << "Enter the project ID:";
    cin >> targetProjectID;
    cout << "\nAccessing tracker and tracking project for Manager: " << endl;
    ifstream file("projects.txt");
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string id, name, startDate, endDate, status, description;
            ss >> id >> name >> startDate >> endDate >> status;
            getline(ss, description);

             if (id == targetProjectID)
            {
                Project project(id, name, startDate, endDate, status, description);

                while (getline(file, line) && !line.empty())
                {
                    stringstream personSS(line);
                    string personID, personName, personRole, assigned;
                    personSS >> personID >> personName >> personRole >> assigned;
                    Person person(personID, personName, personRole,true);

                    if (assigned == "Yes")
                        project.assignPerson(person);
                }

                file.close();
                Tracker tracker1(project);
                cout << endl;
                tracker1.displayProjectStatus();
                cout << endl;
                tracker1.displayTaskStatus(project.getID());
                cout << endl;
                tracker1.displayIssueStatus(project.getID());
                cout << endl;
                return;
            }
        }
        cout << "Project with ID \"" << targetProjectID << "\" not found." << endl;
    }
    else
    {
        cout << "Error: Unable to open file for reading." << endl;
    }
}


void Head::assignTasks() const
{
    int numTasks;
    cout << "Enter the number of tasks to assign: ";
    cin >> numTasks;
    cin.ignore();
    cout << endl;

    for (int i = 0; i < numTasks; ++i)
    {
        string taskID, projectID, dueDate, status , assignedPersonID , role , name;

        cout << "Enter Task ID: ";
        getline(cin, taskID);
        cout << "Enter Project ID: ";
        getline(cin, projectID);
        Project project;
        if (!project.loadProjectFromFile(projectID))
        {
            cerr << "*********** Project not found ************" << endl << endl;
            return;
        }
        dueDate = project.getEndDate();
        status = project.getStatus();

        Person person;
        bool personFound = false;
        while (!personFound)
        {
            cout << "Enter assigned Person ID:";
            getline(cin, assignedPersonID);
            cout << endl;

            if (!person.loadPersonFromFile(assignedPersonID))
            {
                cerr << "Person not found. Please enter a valid Person ID." << endl;
            }
            else
            {
                personFound = true;
            }
        }

        name = person.getName();
        role = person.getRole();
    Task newTask(projectID,project.getProjectName(),project.getStartDate(),project.getEndDate(),project.getStatus(),project.getDescription(),taskID,person,dueDate,status);
    newTask.appendToTasksFile();
    }
}
