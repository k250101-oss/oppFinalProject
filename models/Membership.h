#pragma once
#include <string>

class Membership {
private:
    std::string type; // Basic, Gold, Platinum
    std::string startDate;
    std::string expiryDate;

public:
    Membership();
    Membership(const std::string& type, const std::string& startDate, const std::string& expiryDate);

    std::string getType() const;
    std::string getStartDate() const;
    std::string getExpiryDate() const;

    void setType(const std::string& type);
    void setStartDate(const std::string& startDate);
    void setExpiryDate(const std::string& expiryDate);

    bool isValid() const;
};
