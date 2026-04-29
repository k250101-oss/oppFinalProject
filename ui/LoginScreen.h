#pragma once
#include <string>
#include <vector>
#include "../models/Member.h"
#include "../models/Trainer.h"
#include "../models/Admin.h"
#include "../models/Owner.h"

class LoginScreen {
private:
    char usernameInput[128] = "";
    char passwordInput[128] = "";
    int roleIndex = 0; // 0: Member, 1: Trainer, 2: Admin, 3: Owner
    std::string errorMessage;

public:
    LoginScreen();
    
    bool render(const std::vector<Member>& members,
                const std::vector<Trainer>& trainers,
                const std::vector<Admin>& admins,
                const std::vector<Owner>& owners,
                std::string& activeRole, 
                std::string& activeUserId);
};
