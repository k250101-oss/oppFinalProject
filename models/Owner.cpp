#include "Owner.h"
#include <iostream>

Owner::Owner(const std::string& id, const std::string& username, const std::string& password, const std::string& name)
    : Admin(id, username, password, name, "Owner") {}

void Owner::display() const {
    std::cout << "Owner: " << getName() << " (ID: " << getId() << ")\n";
    std::cout << "Special Privileges: Financial Reports, Manage Admins\n";
}
