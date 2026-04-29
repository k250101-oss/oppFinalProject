#include "Admin.h"

Admin::Admin(const std::string& id, const std::string& username, const std::string& password, const std::string& name, const std::string& role)
    : Person(id, username, password, name, role) {}

bool Admin::login(const std::string& inputUsername, const std::string& inputPassword) const {
    return (getUsername() == inputUsername && getPassword() == inputPassword);
}

void Admin::display() const {
    std::cout << getRole() << ": " << getName() << " (ID: " << getId() << ")\n";
}
