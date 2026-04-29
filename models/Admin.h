#pragma once
#include "Person.h"
#include <string>
#include <iostream>

class Admin : public Person {
public:
    Admin(const std::string& id, const std::string& username, const std::string& password, const std::string& name, const std::string& role = "Admin");

    bool login(const std::string& inputUsername, const std::string& inputPassword) const override;
    void display() const override;
};
