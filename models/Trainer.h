#pragma once
#include "Person.h"
#include <string>
#include <vector>
#include <iostream>

class Trainer : public Person {
private:
    std::vector<std::string> assignedMemberIds;
    std::string schedule;
    double salary;

public:
    Trainer(const std::string& id, const std::string& username, const std::string& password, const std::string& name,
            const std::string& schedule = "", double salary = 0.0);

    std::vector<std::string> getAssignedMemberIds() const;
    std::string getSchedule() const;
    double getSalary() const;

    void setAssignedMemberIds(const std::vector<std::string>& ids);
    void addAssignedMemberId(const std::string& memberId);
    void removeAssignedMemberId(const std::string& memberId);
    void setSchedule(const std::string& schedule);
    void setSalary(double salary);

    bool login(const std::string& inputUsername, const std::string& inputPassword) const override;
    void display() const override;
};
