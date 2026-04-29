#pragma once
#include "../models/Member.h"
#include "../models/Trainer.h"
#include "../models/Payment.h"
#include <vector>
#include <string>

class MemberDashboard {
public:
    void render(Member& currentMember, const std::vector<Trainer>& trainers, std::vector<Payment>& payments, bool& logout);
};
