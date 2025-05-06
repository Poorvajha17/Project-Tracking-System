#ifndef ISSUE_H
#define ISSUE_H
#include<iostream>
#include<string>

using namespace std;

class Issue
{
    string issueID;
    string description;
    string status;
    string projectID;
public:
    Issue();
    Issue(const string& ID,const string& desc,const string& stat,const string& proID);
    Issue(const Issue& obj);
    string getIssueID()const;
    string getDescription()const;
    string getStatus() const;
    string getProjectID() const;
    void setIssueID(const string& ID);
    void setDescription(const string& desc);
    void setStatus(const string& stat);
    void setProjectID(const string& proID);
    void display() const;
    void appendToIssuesFile() const;
    void readFromIssuesFile();
    friend ostream& operator<<(ostream& out, const Issue& issue);
    friend istream& operator>>(istream& in, Issue& issue);
    ~Issue();

};
#endif // ISSUE_H

