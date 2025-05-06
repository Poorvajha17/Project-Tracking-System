#include"Issue.h"
#include<string>
#include<fstream>
#include<iomanip>
#include<sstream>

Issue::Issue():Issue("","","",""){}
Issue::Issue(const string& ID,const string& desc,const string& stat,const string& proID)
{
    issueID=ID;
    description=desc;
    status=stat;
    projectID=proID;
}
Issue::Issue(const Issue& obj)
{
    issueID=obj.issueID;
    description=obj.description;
    status=obj.status;
    projectID=obj.projectID;
}
string Issue::getIssueID()const
{
    return issueID;
}
string Issue::getDescription()const
{
    return description;
}
string Issue::getStatus() const
{
    return status;
}
string Issue::getProjectID() const
{
    return projectID;
}
void Issue::setIssueID(const string& ID)
{
    issueID=ID;
}
void Issue::setDescription(const string& desc)
{
    description=desc;
}
void Issue::setStatus(const string& stat)
{
    status=stat;
}
void Issue::setProjectID(const string& proID)
{
    projectID=proID;
}
void Issue::appendToIssuesFile() const
{
    ofstream file("issues.txt", ios::app);
    if (file.is_open())
    {
        file << left << setw(15) << issueID;
        file << left << setw(15) << description;
        file << left << setw(15) << status;
        file << left << setw(15) << projectID << endl;
        file.close();
    }
    else
    {
        cout << " Unable to open issues file for appending." << endl;
    }
}
void Issue::readFromIssuesFile()
{
    ifstream file("issues.txt");
    string line;

    if (file.is_open())
    {
        cout << left << setw(15) << "Issue ID";
        cout << left << setw(20) << "Description";
        cout << left << setw(20) << "Status";
        cout << left << setw(15) << "Project ID" << endl;

        while (getline(file, line))
        {
            istringstream iss(line);
            string field;

            while (getline(iss, field, ','))
            {
                cout << left << setw(16) << field;
            }
            cout << endl;
        }
        file.close();
    }
    else
    {
        cout << " Unable to open issues file for reading." << endl;
    }
}

void Issue::display() const
{
    ifstream file("issues.txt");
    string fileIssueID, description, status, projectID;
    bool found = false;

    if (file.is_open())
    {
        while (file >> fileIssueID >> description >> status >> projectID)
        {
            if (fileIssueID == issueID)
            {
                cout << left << setw(15) << fileIssueID;
                cout << left << setw(20) << description;
                cout << left << setw(20) << status;
                cout << left << setw(15) << projectID << endl;
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "Issue with ID " << issueID << " not found." << endl;
        }

        file.close();
    }
    else
    {
        cout << "Error: Unable to open issues file for reading." << endl;
    }
}
ostream& operator<<(ostream& out, const Issue& issue)
{
    out << "Issue ID: " << issue.issueID << endl;
    out << "Description: " << issue.description << endl;
    out << "Status: " << issue.status << endl;
    out << "Project ID: " << issue.projectID << endl;
    return out;
}
istream& operator>>(istream& in, Issue& issue)
{
    string temp;
    cout << "Enter issue ID: ";
    getline(in, temp);
    issue.setIssueID(temp);

    cout << "Enter description: ";
    getline(in, temp);
    issue.setDescription(temp);

    cout << "Enter status: ";
    getline(in, temp);
    issue.setStatus(temp);

    cout << "Enter project ID: ";
    getline(in, temp);
    issue.setProjectID(temp);

    return in;
}

Issue::~Issue(){}

