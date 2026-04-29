#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

static std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    // Handle empty last token specifically for trailing commas
    if (!str.empty() && str.back() == delimiter) {
        tokens.push_back("");
    }
    return tokens;
}

static std::string join(const std::vector<std::string>& vec, char delimiter) {
    if (vec.empty()) return "";
    std::string result = vec[0];
    for (size_t i = 1; i < vec.size(); ++i) {
        result += delimiter + vec[i];
    }
    return result;
}

void FileManager::loadMembers(std::vector<Member>& members, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::vector<std::string> parts = split(line, ',');
        if (parts.size() >= 12) {
            Membership mem(parts[4], parts[5], parts[6]);
            WorkoutPlan wp(parts[7], parts[8], parts[9].empty() ? 0 : std::stoi(parts[9]));
            Member member(parts[0], parts[1], parts[2], parts[3], mem, wp, parts[10], parts[11].empty() ? 0 : std::stoi(parts[11]));
            members.push_back(member);
        }
    }
}

void FileManager::saveMembers(const std::vector<Member>& members, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& m : members) {
        file << m.getId() << "," << m.getUsername() << "," << m.getPassword() << "," << m.getName() << ","
             << m.getMembership().getType() << "," << m.getMembership().getStartDate() << "," << m.getMembership().getExpiryDate() << ","
             << m.getWorkoutPlan().getPlanName() << "," << m.getWorkoutPlan().getDetails() << "," << m.getWorkoutPlan().getDurationWeeks() << ","
             << m.getAssignedTrainerId() << "," << m.getAttendanceCount() << "\n";
    }
}

void FileManager::loadTrainers(std::vector<Trainer>& trainers, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::vector<std::string> parts = split(line, ',');
        if (parts.size() >= 6) {
            Trainer trainer(parts[0], parts[1], parts[2], parts[3], parts[4], parts[5].empty() ? 0.0 : std::stod(parts[5]));
            if (parts.size() >= 7 && !parts[6].empty()) {
                std::vector<std::string> memIds = split(parts[6], ';');
                trainer.setAssignedMemberIds(memIds);
            }
            trainers.push_back(trainer);
        }
    }
}

void FileManager::saveTrainers(const std::vector<Trainer>& trainers, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& t : trainers) {
        file << t.getId() << "," << t.getUsername() << "," << t.getPassword() << "," << t.getName() << ","
             << t.getSchedule() << "," << t.getSalary() << ","
             << join(t.getAssignedMemberIds(), ';') << "\n";
    }
}

void FileManager::loadAdmins(std::vector<Admin>& admins, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::vector<std::string> parts = split(line, ',');
        if (parts.size() >= 4) {
            admins.push_back(Admin(parts[0], parts[1], parts[2], parts[3]));
        }
    }
}

void FileManager::saveAdmins(const std::vector<Admin>& admins, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& a : admins) {
        file << a.getId() << "," << a.getUsername() << "," << a.getPassword() << "," << a.getName() << "\n";
    }
}

void FileManager::loadOwners(std::vector<Owner>& owners, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::vector<std::string> parts = split(line, ',');
        if (parts.size() >= 4) {
            owners.push_back(Owner(parts[0], parts[1], parts[2], parts[3]));
        }
    }
}

void FileManager::saveOwners(const std::vector<Owner>& owners, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& o : owners) {
        file << o.getId() << "," << o.getUsername() << "," << o.getPassword() << "," << o.getName() << "\n";
    }
}

void FileManager::loadEquipment(std::vector<Equipment>& eqList, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::vector<std::string> parts = split(line, ',');
        if (parts.size() >= 4) {
            eqList.push_back(Equipment(parts[0], parts[1], parts[2], parts[3]));
        } else if (parts.size() >= 3) {
            eqList.push_back(Equipment(parts[0], parts[1], "Uncategorized", parts[2]));
        }
    }
}

void FileManager::saveEquipment(const std::vector<Equipment>& eqList, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& eq : eqList) {
        file << eq.getId() << "," << eq.getName() << "," << eq.getCategory() << "," << eq.getCondition() << "\n";
    }
}

void FileManager::loadPayments(std::vector<Payment>& payments, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::vector<std::string> parts = split(line, ',');
        if (parts.size() >= 5) {
            payments.push_back(Payment(parts[0], parts[1], parts[2].empty() ? 0.0 : std::stod(parts[2]), parts[3], parts[4]));
        }
    }
}

void FileManager::savePayments(const std::vector<Payment>& payments, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& p : payments) {
        file << p.getId() << "," << p.getMemberId() << "," << p.getAmount() << "," << p.getDate() << "," << p.getStatus() << "\n";
    }
}

void FileManager::loadMembershipPlans(std::vector<MembershipPlan>& plans, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::vector<std::string> parts = split(line, ',');
        if (parts.size() >= 4) {
            plans.push_back(MembershipPlan(parts[0], parts[1], parts[2].empty() ? 0.0 : std::stod(parts[2]), parts[3].empty() ? 0 : std::stoi(parts[3])));
        }
    }
}

void FileManager::saveMembershipPlans(const std::vector<MembershipPlan>& plans, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& p : plans) {
        file << p.getId() << "," << p.getName() << "," << p.getPrice() << "," << p.getDurationMonths() << "\n";
    }
}
