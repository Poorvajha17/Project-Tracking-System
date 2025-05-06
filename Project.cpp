#include "Project.h"
#include "Person.h"
#include <iomanip>
#include <fstream>
#include <sstream>

Project::Project()
{
    projectID = "";
    projectName = "";
    startDate = "";
    endDate = "";
    status ="";
    description = "";
}

Project :: Project(const string& id,const string& name,const string& startDate,string endDate,string status,const string& description)
{
    projectID=id;
    projectName=name;
    this -> startDate=startDate;
    this -> endDate=endDate;
    this -> status=status;
    this -> description=description;
}

void Project :: assignPerson(const Person& person)
{
    assigned_persons.push_back(person);
}

void Project::display() const
{
    cout << "---------------------------------------------------------------------------------------------\n" << endl;
    cout << left << setw(15) << "Project ID";
    cout << left << setw(15) << "Project Name";
    cout << left << setw(15) << "Start Date";
    cout << left << setw(15) << "End Date";
    cout << left << setw(15) << "Status";
    cout << left << setw(15) << "Description" << endl;
    cout << "---------------------------------------------------------------------------------------------\n" << endl;

    cout << left << setw(15) << projectID;
    cout << left << setw(15) << projectName;
    cout << left << setw(15) << startDate;
    cout << left << setw(15) << endDate;
    cout << left << setw(15) << status;
    cout << left << setw(15) << description << endl;

    cout << "Assigned Persons:" << endl;
    cout << left << setw(15) << "ID";
    cout << left << setw(15) << "Name";
    cout << left << setw(15) << "Role";
    cout << left << setw(15) << "Assigned to Project" << endl;

    for (const auto& person : assigned_persons)
    {
        cout << left << setw(15) << person.getID();
        cout << left << setw(15) << person.getName();
        cout << left << setw(15) << person.getRole();
        cout << left << setw(15) << (person.isAssignedToProject() ? "Yes" : "No") << endl;
    }
    cout << "---------------------------------------------------------------------------------------------\n" << endl;

}

string Project :: getID() const
{
    return projectID;
}

string Project :: getProjectName() const
{
    return projectName;
}

string Project :: getStartDate() const
{
    return startDate;
}

string Project :: getEndDate() const
{
    return endDate;
}

string Project :: getStatus() const
{
    return status;
}

string Project :: getDescription() const
{
    return description;
}

vector<Person> Project::getAssignedPersons() const
{
    return assigned_persons;
}

void Project :: setID(const string& id)
{
    projectID = id;
}

void Project :: setProjectName(const string& name)
{
    projectName = name;
}

void Project :: setStartDate(const string& startDate)
{
    this -> startDate = startDate;
}

void Project :: setEndDate(string endDate)
{
    this -> endDate = endDate;
}

void Project :: setStatus(const string& status)
{
    this -> status = status;
}

void Project :: setDescription(const string& description)
{
    this -> description = description;
}


istream& operator>>(istream& in, Project& project)
{
    cout << "Enter Project ID: ";
    getline(in, project.projectID);
    cout << "Enter Project Name: ";
    getline(in, project.projectName);
    cout << "Enter Start Date: ";
    getline(in, project.startDate);
    cout << "Enter End Date: ";
    getline(in, project.endDate);
    project.setStatus("Incomplete");
    cout << "Enter Description: ";
    getline(in, project.description);

    int numPersons;
    cout << "Enter the number of persons to be assigned: ";
    in >> numPersons;
    in.ignore();

    for (int i = 0; i < numPersons; ++i)
    {
        Person person;
        string id;
        cout << "Enter Person " << i + 1 << " ID: ";
        getline(cin, id);
        person.loadPersonFromFile(id);
        if (person.isAssignedToProject())
        {
            cout << "Person with ID " << id << " is already assigned to a project. Please choose another person." << endl;
            i--;
            continue;
        }
        person.setAssignedToProject("Yes");
        project.assignPerson(person);
        person.updateStatus(true);
    }

    return in;
}

ostream& operator<<(ostream& out, const Project& project)
{
    out << "Project ID: " << project.projectID << endl;
    out << "Project Name: " << project.projectName << endl;
    out << "Start Date: " << project.startDate << endl;
    out << "End Date: " << project.endDate << endl;
    out << "Status: " << project.status << endl;
    out << "Description: " << project.description << endl;

    return out;
}


void Project::saveToFile() const
{
    ofstream file("projects.txt", ios::app);
    if (file.is_open())
    {
        file << left << setw(15) << projectID;
        file << left << setw(15) << projectName;
        file << left << setw(15) << startDate;
        file << left << setw(15) << endDate;
        file << left << setw(15) << status;
        file << left << setw(15) << description;
        file << endl;
        for (const auto& person : assigned_persons)
        {
            file << left << setw(15) << person.getID();
            file << left << setw(15) << person.getName();
            file << left << setw(15) << person.getRole();
            file << left << setw(15) << (person.isAssignedToProject() ? "Yes" : "No") << endl;
        }
        file << endl;
        file.close();
    }
    else
    {
        cout << "Unable to open file for appending." << endl;
    }
}

void Project :: loadFromFile()
{
    ifstream file("projects.txt");
    if (file.is_open())
    {
        vector<vector<string>> projectData;
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string id, name, startDate, endDate, status, description;
            ss >> id >> name >> startDate >> endDate >> status;
            getline(ss, description);
            vector<string> rowData = {id, name, startDate, endDate, status, description};
            projectData.push_back(rowData);
        }

        vector<int> columnWidths(6, 0);
        for (const auto& rowData : projectData)
        {
            for (size_t i = 0; i < rowData.size(); ++i)
            {
                columnWidths[i] = max(columnWidths[i], static_cast<int>(rowData[i].length()));
            }
        }

        cout << left;
        cout << "-----------------------------------------------------------------------------------------" << endl;
        for (const auto& rowData : projectData)
        {
            for (size_t i = 0; i < rowData.size(); ++i)
            {
                cout << setw(columnWidths[i] + 5) << rowData[i];
            }
            cout << endl;
        }
        cout << "-----------------------------------------------------------------------------------------" << endl;

        file.close();
    }
    else
    {
        cout << "Unable to open projects file for reading." << endl;
    }
}

bool Project::loadProjectFromFile(const string& projectID)
{
    ifstream file("projects.txt");
    if (!file.is_open())
    {
        cerr << "Unable to open projects file for reading." << endl;
        return false;
    }

    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string id, name, startDate, endDate, status, description;
        iss >> id >> name >> startDate >> endDate >> status;
        getline(iss, description);

        if (id == projectID)
        {

            this->projectID = id;
            this->projectName = name;
            this->startDate = startDate;
            this->endDate = endDate;
            this->status = status;
            this->description = description;

            file.close();
            return true;
        }
    }

    cerr << "Project with ID " << projectID << " not found." << endl;
    file.close();
    return false;
}

void Project::displayProject() const
{
    cout << "----------------------------------------------------------------------------------------\n" << endl;
    cout << left << setw(15) << "Project ID";
    cout << left << setw(15) << "Project Name";
    cout << left << setw(15) << "Start Date";
    cout << left << setw(15) << "End Date";
    cout << left << setw(15) << "Status";
    cout << left << setw(15) << "Description" << endl;
    cout << "----------------------------------------------------------------------------------------\n" << endl;

    cout << left << setw(15) << projectID;
    cout << left << setw(15) << projectName;
    cout << left << setw(15) << startDate;
    cout << left << setw(15) << endDate;
    cout << left << setw(15) << status;
    cout << left << setw(15) << description << endl;
    cout << "----------------------------------------------------------------------------------------\n" << endl;
}
