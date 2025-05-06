#ifndef MEMBER_H
#define MEMBER_H

#include "User.h"
#include <iostream>
#include <string>
#include "Issue.h"

using namespace std;

class Member : public User
{
public:
    Member(const string& username, const string& password);

    string getRole() const ;

    void updateProjectStatus();

    void updateIssueStatusOrDescription();

    void accessTrackerAndTrackProject() const;

    void updateTaskProgress();

    void addIssue();

};

#endif // MEMBER_H

