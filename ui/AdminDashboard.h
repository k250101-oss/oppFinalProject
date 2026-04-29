#pragma once
#include "../models/Admin.h"
#include "../models/Member.h"
#include "../models/Trainer.h"
#include "../models/Equipment.h"
#include "../models/Payment.h"
#include "../models/MembershipPlan.h"
#include <vector>

class AdminDashboard {
protected:
    char nameInput[128] = "";
    char usernameInput[128] = "";
    char passwordInput[128] = "";
    char eqNameInput[128] = "";
    char eqCategoryInput[128] = "";
    int eqConditionIndex = 0; // 0: Good, 1: Needs Servicing
    int membershipTypeIndex = 0;

    // Profile Edit
    char profileUsername[128] = "";
    char profilePassword[128] = "";
    bool profileInputsInitialized = false;

    // Edit Workout
    std::string memberIdForWorkout = "";
    char workoutNameInput[128] = "";
    char workoutDetailsInput[512] = "";
    int workoutDurationInput = 4;

    // Assign Trainer
    int assignTrainerIndex = 0;
    std::string memberIdForAssign = "";

    void renderMembersTab(std::vector<Member>& members, std::vector<MembershipPlan>& plans, std::vector<Payment>& payments, std::vector<Trainer>& trainers);
    void renderTrainersTab(std::vector<Trainer>& trainers);
    void renderEquipmentTab(std::vector<Equipment>& equipment);
    void renderProfileTab(Admin& currentAdmin);

public:
    virtual void render(Admin& currentAdmin, std::vector<Member>& members, std::vector<Trainer>& trainers, std::vector<Equipment>& equipment, std::vector<Payment>& payments, std::vector<MembershipPlan>& plans, bool& logout);
    virtual ~AdminDashboard() = default;
};
