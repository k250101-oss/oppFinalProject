#pragma once
#include <string>
#include <iostream>

class Person {
private:
    std::string id;
    std::string username;
    std::string password;
    std::string name;
    std::string role;

public:
    Person(const std::string& id, const std::string& username, const std::string& password, const std::string& name, const std::string& role);
    virtual ~Person() = default;

    // Getters
    std::string getId() const;
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getName() const;
    std::string getRole() const;

    // Setters
    void setId(const std::string& id);
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setName(const std::string& name);
    void setRole(const std::string& role);

    virtual bool login(const std::string& inputUsername, const std::string& inputPassword) const = 0;
    virtual void display() const = 0;
};
