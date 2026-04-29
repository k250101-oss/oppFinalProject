#include "Person.h"

Person::Person(const std::string& id, const std::string& username, const std::string& password, const std::string& name, const std::string& role) 
    : id(id), username(username), password(password), name(name), role(role) {}

std::string Person::getId() const { return id; }
std::string Person::getUsername() const { return username; }
std::string Person::getPassword() const { return password; }
std::string Person::getName() const { return name; }
std::string Person::getRole() const { return role; }

void Person::setId(const std::string& id) { this->id = id; }
void Person::setUsername(const std::string& username) { this->username = username; }
void Person::setPassword(const std::string& password) { this->password = password; }
void Person::setName(const std::string& name) { this->name = name; }
void Person::setRole(const std::string& role) { this->role = role; }
