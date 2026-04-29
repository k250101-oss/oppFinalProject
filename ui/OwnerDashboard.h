#pragma once
#include "AdminDashboard.h"
#include "../models/Owner.h"
#include <vector>

class OwnerDashboard : public AdminDashboard {
private:
    char planNameInput[128] = "";
    double planPriceInput = 0.0;
    int planDurationInput = 1;

    void renderPlansTab(std::vector<MembershipPlan>& plans);
    void renderFinancialReport(const std::vector<Payment>& payments, const std::vector<Member>& members, const std::vector<Trainer>& trainers, const std::vector<Admin>& admins, const std::vector<MembershipPlan>& plans);

public:
    void render(Owner& currentOwner, std::vector<Member>& members, std::vector<Trainer>& trainers, std::vector<Equipment>& equipment, std::vector<Payment>& payments, std::vector<Admin>& admins, std::vector<MembershipPlan>& plans, bool& logout);
};
