#include "Head.h"
#include "Member.h"
#include "person.h"
#include "project.h"
#include "Task.h"
#include "Tracker.h"
#include "User.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    string username, password;
    int choice;
    cout << "***************** PROJECT TRACKING SYSYTEM ******************"<< endl;
    while(true)
    {
        cout << endl << "Enter username: ";
        getline(cin, username);
        cout << "Enter password: ";
        getline(cin, password);
        cout << endl;

        if (!User::userExists(username))
        {
            User newUser(username, password);
            cout << "New user created. Welcome, " << username << "!" << endl;
            break;
        }
        else
        {
            User currentUser(username, password);
            if (!currentUser.authenticateUser(username, password))
            {
                cout << "Invalid username or password. Please try again." << endl;
                continue;
            }
            break;
        }
    }

        try
        {
            if (username == "Manager")
            {
                Head manager(username, password);

                while (true)
                {

                    cout << "1. Display List of Projects Managed" << endl;
                    cout << "2. Add Project" << endl;
                    cout << "3. Delete Project" << endl;
                    cout << "4. Assign Tasks" << endl;
                    cout << "5. Access Tracker and Track Project" << endl;
                    cout << "6. Add persons to team" << endl;
                    cout << "7. View discarded projects" << endl;
                    cout << "8. View team members" << endl;
                    cout << "9. Exit" << endl << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;
                    cin.ignore();
                    cout << endl;
                    switch (choice)
                    {
                        case 1:
                            manager.displayListOfProjectsManaged();
                            break;
                        case 2:
                            {
                            Person person;
                            cout << "Team members:" << endl;
                            person.loadFromFile();
                            manager.addProject();
                            break;
                            }
                        case 3:
                            manager.deleteProject();
                            break;
                        case 4:
                        {
                            Person person;
                            cout << "Team members:" << endl;
                            person.loadFromFile();
                            manager.assignTasks();
                            break;
                        }
                        case 5:
                            manager.accessTrackerAndTrackProject();
                            break;
                        case 6:
                            {
                                Person person;
                                cin>>person;
                                person.addToFile();
                                cout << endl;
                                break;
                            }
                        case 7:
                            manager.loadDiscardedProjects();
                            cout << endl;
                            break;
                        case 8:
                            {
                                Person person;
                                cout << "Team members:" << endl;
                                person.loadFromFile();
                                break;
                            }
                        case 9:
                            cout << "**************** EXITED PROJECT TRACKING SYSTEM *****************" << endl;
                            return 0;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                            break;
                    }
                }
            }
            else
            {
                Member member(username, password);
                while(true)
                {
                    cout << "1. Update Project Status" << endl;
                    cout << "2. Update Task Progress" << endl;
                    cout << "3. Add Issue" << endl;
                    cout << "4. Update Issue Status" << endl;
                    cout << "5. Access Tracker and Track Project" << endl;
                    cout << "6. Exit\n" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;
                    cin.ignore();
                    cout << endl;
                    switch (choice)
                    {
                        case 1:
                            member.updateProjectStatus();
                            break;
                        case 2:
                            member.updateTaskProgress();
                            break;
                        case 3:
                            member.addIssue();
                            break;
                        case 4:
                            member.updateIssueStatusOrDescription();
                            break;
                        case 5:
                            member.accessTrackerAndTrackProject();
                            break;
                        case 6:
                            cout << "**************** EXITED PROJECT TRACKING SYSTEM *****************" << endl;
                            return 0;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                            break;
                    }
                }
            }
        }
        catch (const exception& e)
        {
            cerr << "An error occurred: " << e.what() << endl;
            return 1;
        }
        catch (...)
        {
            cerr << "An error occurred." << endl;
            return 1;
        }

    return 0;
}
