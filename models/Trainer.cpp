#include "Trainer.h"
#include <algorithm>

Trainer::Trainer(const std::string& id, const std::string& username, const std::string& password, const std::string& name,
                 const std::string& schedule, double salary)
    : Person(id, username, password, name, "Trainer"), schedule(schedule), salary(salary) {}

std::vector<std::string> Trainer::getAssignedMemberIds() const { return assignedMemberIds; }
std::string Trainer::getSchedule() const { return schedule; }
double Trainer::getSalary() const { return salary; }

void Trainer::setAssignedMemberIds(const std::vector<std::string>& ids) {
    assignedMemberIds = ids;
}

void Trainer::addAssignedMemberId(const std::string& memberId) {
    if (std::find(assignedMemberIds.begin(), assignedMemberIds.end(), memberId) == assignedMemberIds.end()) {
        assignedMemberIds.push_back(memberId);
    }
}

void Trainer::removeAssignedMemberId(const std::string& memberId) {
    assignedMemberIds.erase(std::remove(assignedMemberIds.begin(), assignedMemberIds.end(), memberId), assignedMemberIds.end());
}

void Trainer::setSchedule(const std::string& schedule) { this->schedule = schedule; }
void Trainer::setSalary(double salary) { this->salary = salary; }

bool Trainer::login(const std::string& inputUsername, const std::string& inputPassword) const {
    return (getUsername() == inputUsername && getPassword() == inputPassword);
}

void Trainer::display() const {
    std::cout << "Trainer: " << getName() << " (ID: " << getId() << ")\n";
    std::cout << "Schedule: " << schedule << "\n";
    std::cout << "Assigned Members Count: " << assignedMemberIds.size() << "\n";
}
