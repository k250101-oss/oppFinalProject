#pragma once
#include "../models/Trainer.h"
#include "../models/Member.h"
#include <vector>

class TrainerDashboard {
private:
    char wpNameInput[128] = "";
    char wpDetailsInput[512] = "";
    int wpDurationInput = 4;
    std::string selectedMemberId = "";

public:
    void render(Trainer& currentTrainer, std::vector<Member>& members, bool& logout);
};
