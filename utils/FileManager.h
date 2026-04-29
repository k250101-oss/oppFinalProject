#pragma once
#include <vector>
#include <string>
#include "../models/Member.h"
#include "../models/Trainer.h"
#include "../models/Admin.h"
#include "../models/Owner.h"
#include "../models/Equipment.h"
#include "../models/Payment.h"
#include "../models/MembershipPlan.h"

class FileManager {
public:
    static void loadMembers(std::vector<Member>& members, const std::string& filename);
    static void saveMembers(const std::vector<Member>& members, const std::string& filename);

    static void loadTrainers(std::vector<Trainer>& trainers, const std::string& filename);
    static void saveTrainers(const std::vector<Trainer>& trainers, const std::string& filename);

    static void loadAdmins(std::vector<Admin>& admins, const std::string& filename);
    static void saveAdmins(const std::vector<Admin>& admins, const std::string& filename);

    static void loadOwners(std::vector<Owner>& owners, const std::string& filename);
    static void saveOwners(const std::vector<Owner>& owners, const std::string& filename);

    static void loadEquipment(std::vector<Equipment>& eqList, const std::string& filename);
    static void saveEquipment(const std::vector<Equipment>& eqList, const std::string& filename);

    static void loadPayments(std::vector<Payment>& payments, const std::string& filename);
    static void savePayments(const std::vector<Payment>& payments, const std::string& filename);

    static void loadMembershipPlans(std::vector<MembershipPlan>& plans, const std::string& filename);
    static void saveMembershipPlans(const std::vector<MembershipPlan>& plans, const std::string& filename);
};
