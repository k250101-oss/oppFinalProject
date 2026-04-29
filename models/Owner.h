#pragma once
#include "Admin.h"
#include <string>

class Owner : public Admin {
public:
    Owner(const std::string& id, const std::string& username, const std::string& password, const std::string& name);

    void display() const override;
};
