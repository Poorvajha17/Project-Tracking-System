#include "Person.h"
#include<iomanip>
#include<sstream>

Person :: Person()
{
    ID='\0';
    name='\0';
    role='\0';
    assignedToProject=false;
}

Person :: Person(const string& ID, const string& name, string role,bool assignedToProject)
{
    this -> ID=ID;
    this -> name=name;
    this -> role=role;
    this -> assignedToProject = assignedToProject;
}

void Person :: display() const
{
    cout << "ID: " << ID << endl;
    cout << "Name: " << name << endl;
    cout << "role: " << role << endl;
    cout << "Assigned to project: " << assignedToProject << endl;
}

string Person :: getName() const
{
    return name;
}

void Person :: setName(const string& newName)
{
    name = newName;
}

string Person :: getID() const
{
    return ID;
}

void Person :: setID(const string& newID)
{
    ID = newID;
}

string Person :: getRole() const
{
    return role;
}

void Person :: setRole(string newrole)
{
    role = newrole;
}

void Person::setAssignedToProject(bool assigned)
{
    assignedToProject = assigned;
}

bool Person::isAssignedToProject() const
{
    return assignedToProject;
}


void Person::loadFromFile()
{
    ifstream file("persons.txt");
    string id, name, role;
    string assignedStr;

    cout << "---------------------------------------------------------------------" << endl;
    if (file.is_open()) {
        cout << left << setw(15) << "ID";
        cout << left << setw(15) << "Name";
        cout << left << setw(15) << "Role";
        cout << left << setw(15) << "Assigned to Project" << endl << endl;
        cout << "--------------------------------------------------------------------" << endl;


        while (file >> id >> name >> role >> assignedStr)
        {
            bool assigned = (assignedStr == "Yes" ? true : false);
            cout << left << setw(15) << id;
            cout << left << setw(15) << name;
            cout << left << setw(15) << role;
            cout << left << setw(15) << (assigned ? "Yes" : "No") << endl;
        }
        cout << "--------------------------------------------------------------------" << endl;
        file.close();
        cout << endl;
    }
    else
    {
        cout << "Unable to open persons file for reading." << endl;
    }
}


void Person::addToFile() const
{
    ofstream file("persons.txt", ios::app);
    if (file.is_open())
    {
        file << left << setw(15) << ID;
        file << left << setw(15) << name;
        file << left << setw(15) << role;
        file << left << setw(15) << (assignedToProject ? "Yes" : "No") << endl;
        file.close();
    }
    else
    {
        cout << "Unable to open persons file for appending." << endl;
    }
}

bool Person::loadPersonFromFile(const string& personID)
{
    ifstream file("persons.txt");
    if (!file.is_open())
    {
        cerr << "Unable to open persons file for reading." << endl;
        return false;
    }

    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string id, name, role, assignedStr;
        iss >> id >> name >> role >> assignedStr;

        if (id == personID)
        {
            this->ID = id;
            this->name = name;
            this->role = role;
            this->assignedToProject = (assignedStr == "Yes");
            file.close();
            return true;
        }
    }

    cerr << "Person with ID " << personID << " not found." << endl;
    file.close();
    return false;
}

void Person::updateStatus(bool assigned)
{
    assignedToProject = assigned;

    ifstream inFile("persons.txt");
    ofstream tempFile("temp.txt");

    if (!inFile.is_open() || !tempFile.is_open())
    {
        cerr << "Unable to open file for updating." << endl;
        return;
    }

    string line;
    while (getline(inFile, line))
    {
        istringstream iss(line);
        string id, name, role, assignedStr;
        iss >> id >> name >> role >> assignedStr;

        if (id == ID)
        {
            tempFile << left << setw(15) << ID;
            tempFile << left << setw(15) << name;
            tempFile << left << setw(15) << role;
            tempFile << left << setw(15) << (assigned ? "Yes" : "No") << endl;
        }
        else
        {
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    remove("persons.txt");
    rename("temp.txt", "persons.txt");
}


istream& operator>>(istream& in, Person& person)
{
    cout << "Enter ID: ";
    getline(in, person.ID);
    cout << "Enter Name: ";
    getline(in, person.name);
    cout << "Enter Role: ";
    getline(in, person.role);
    person.setAssignedToProject(false);

    return in;
}
