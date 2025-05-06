#ifndef USER_H
#define USER_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class User
{
private:
    string username;
    string password;

public:
    User(const string& username, const string& password);

    string getUsername() const;

    static bool userExists(const string& username);

    bool authenticateUser(const string& inputUsername, const string& inputPassword) const ;

    string addUserToFile(const string &username, const string &password) const;

};

#endif // USER_H



