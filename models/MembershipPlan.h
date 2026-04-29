#pragma once
#include <string>

class MembershipPlan {
private:
    std::string id;
    std::string name;
    double price;
    int durationMonths;

public:
    MembershipPlan(const std::string& id, const std::string& name, double price, int durationMonths);

    std::string getId() const;
    std::string getName() const;
    double getPrice() const;
    int getDurationMonths() const;

    void setId(const std::string& id);
    void setName(const std::string& name);
    void setPrice(double price);
    void setDurationMonths(int durationMonths);
};
