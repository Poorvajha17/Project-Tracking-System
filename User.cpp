#include "User.h"

User::User(const string& username, const string& password) : username(username), password(password)
{
    addUserToFile(username, password);
}
string User::getUsername() const
{
    return username;
}

bool User::userExists(const string& username)
{
    ifstream userFile("users.txt");
    if (!userFile)
    {
        cerr << " Unable to open users file." << endl;
        return false;
    }

    string fileUsername;
    while (userFile >> fileUsername)
    {
        if (fileUsername == username)
        {
            userFile.close();
            return true;
        }
    }

    userFile.close();
    return false;
}

bool User::authenticateUser(const string& inputUsername, const string& inputPassword) const
{
    ifstream userFile("users.txt");
    if (!userFile)
    {
        cerr << " Unable to open users file." << endl;
        return false;
    }

    string fileUsername, filePassword;
    while (userFile >> fileUsername >> filePassword)
    {
        if (fileUsername == inputUsername && filePassword == inputPassword)
        {
            userFile.close();
            return true;
        }
    }

    userFile.close();
    return false;
}


string User::addUserToFile(const string &username, const string &password) const
{
    if (userExists(username))
    {
        return "already_exists";
    }

    ofstream userFile("users.txt", ios::app);
    if (!userFile)
    {
        cerr << "Error: Unable to open users file for appending." << endl;
        return "error";
    }

    userFile << username << " " << password << endl;

    userFile.close();

    return "success";
}
