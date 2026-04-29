#include "AdminDashboard.h"
#include "imgui.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <algorithm>

static std::string getCurrentDate() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}

static std::string getExpiryDate(int monthsToAdd) {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    tm.tm_mon += monthsToAdd;
    std::mktime(&tm);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}

void AdminDashboard::renderProfileTab(Admin& currentAdmin) {
    if (!profileInputsInitialized) {
        std::strncpy(profileUsername, currentAdmin.getUsername().c_str(), sizeof(profileUsername));
        std::strncpy(profilePassword, currentAdmin.getPassword().c_str(), sizeof(profilePassword));
        profileInputsInitialized = true;
    }

    ImGui::Text("Edit Profile Data:");
    ImGui::InputText("Username", profileUsername, IM_ARRAYSIZE(profileUsername));
    ImGui::InputText("Password", profilePassword, IM_ARRAYSIZE(profilePassword));

    if (ImGui::Button("Save Changes", ImVec2(120, 0))) {
        currentAdmin.setUsername(std::string(profileUsername));
        currentAdmin.setPassword(std::string(profilePassword));
        ImGui::TextColored(ImVec4(0, 1, 0, 1), "Profile updated successfully!");
    }
}

void AdminDashboard::renderMembersTab(std::vector<Member>& members, std::vector<MembershipPlan>& plans, std::vector<Payment>& payments, std::vector<Trainer>& trainers) {
    if (ImGui::Button("Add New Member")) {
        ImGui::OpenPopup("Add Member");
    }

    if (ImGui::BeginPopupModal("Add Member", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::InputText("Name", nameInput, IM_ARRAYSIZE(nameInput));
        ImGui::InputText("Username", usernameInput, IM_ARRAYSIZE(usernameInput));
        ImGui::InputText("Password", passwordInput, IM_ARRAYSIZE(passwordInput));

        std::vector<const char*> planNames;
        for (const auto& p : plans) {
            planNames.push_back(p.getName().c_str());
        }

        if (plans.empty()) {
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "Please add Membership Plans first in Owner Menu!");
        } else {
            ImGui::Combo("Membership Type", &membershipTypeIndex, planNames.data(), planNames.size());
        }

        if (ImGui::Button("Save", ImVec2(120, 0))) {
            if (!plans.empty()) {
                std::string id = "M" + std::to_string(members.size() + 1);
                auto& selPlan = plans[membershipTypeIndex];
                
                Membership mem(selPlan.getName(), getCurrentDate(), getExpiryDate(selPlan.getDurationMonths()));
                WorkoutPlan wp("None", "No plan assigned", 0);
                members.push_back(Member(id, usernameInput, passwordInput, nameInput, mem, wp, "", 0));
                
                // Add an initial payment
                std::string payId = "P" + std::to_string(payments.size() + 1);
                payments.push_back(Payment(payId, id, selPlan.getPrice(), getCurrentDate(), "Paid"));

                ImGui::CloseCurrentPopup();
                nameInput[0] = '\0'; usernameInput[0] = '\0'; passwordInput[0] = '\0';
                membershipTypeIndex = 0;
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(120, 0))) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    if (ImGui::BeginPopupModal("Assign Trainer", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        std::vector<const char*> trNames;
        for (const auto& tr : trainers) trNames.push_back(tr.getName().c_str());
        
        if (trainers.empty()) {
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "No trainers available!");
        } else {
            ImGui::Combo("Select Trainer", &assignTrainerIndex, trNames.data(), trNames.size());
        }

        if (ImGui::Button("Save##T", ImVec2(120, 0))) {
            if (!trainers.empty() && !memberIdForAssign.empty()) {
                auto sit = std::find_if(members.begin(), members.end(), [&](Member& m){ return m.getId() == memberIdForAssign; });
                if (sit != members.end()) {
                    std::string oldTrainerId = sit->getAssignedTrainerId();
                    if (!oldTrainerId.empty()) {
                        auto oldTr = std::find_if(trainers.begin(), trainers.end(), [&](Trainer& t) { return t.getId() == oldTrainerId; });
                        if (oldTr != trainers.end()) oldTr->removeAssignedMemberId(memberIdForAssign);
                    }
                    std::string newTrainerId = trainers[assignTrainerIndex].getId();
                    sit->setAssignedTrainerId(newTrainerId);
                    trainers[assignTrainerIndex].addAssignedMemberId(memberIdForAssign);
                }
            }
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel##T", ImVec2(120, 0))) ImGui::CloseCurrentPopup();
        ImGui::EndPopup();
    }

    if (ImGui::BeginPopupModal("Edit Workout", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::InputText("Workout Name", workoutNameInput, IM_ARRAYSIZE(workoutNameInput));
        ImGui::InputTextMultiline("Details", workoutDetailsInput, IM_ARRAYSIZE(workoutDetailsInput));
        ImGui::InputInt("Duration (Weeks)", &workoutDurationInput);
        
        if (ImGui::Button("Save##W", ImVec2(120, 0))) {
            auto sit = std::find_if(members.begin(), members.end(), [&](Member& m){ return m.getId() == memberIdForWorkout; });
            if (sit != members.end()) {
                sit->setWorkoutPlan(WorkoutPlan(workoutNameInput, workoutDetailsInput, workoutDurationInput));
            }
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel##W", ImVec2(120, 0))) ImGui::CloseCurrentPopup();
        ImGui::EndPopup();
    }

    ImGui::Separator();

    if (ImGui::BeginTable("MembersTable", 6, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Membership");
        ImGui::TableSetupColumn("Trainer");
        ImGui::TableSetupColumn("Workout");
        ImGui::TableSetupColumn("Actions");
        ImGui::TableHeadersRow();

        int removeIdx = -1;
        bool openAssignTrainer = false;
        bool openEditWorkout = false;

        for (size_t i = 0; i < members.size(); ++i) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0); ImGui::Text("%s", members[i].getId().c_str());
            ImGui::TableSetColumnIndex(1); ImGui::Text("%s\n(%s)", members[i].getName().c_str(), members[i].getUsername().c_str());
            ImGui::TableSetColumnIndex(2); ImGui::Text("%s", members[i].getMembership().getType().c_str());
            
            ImGui::TableSetColumnIndex(3);
            std::string tName = "None";
            std::string tId = members[i].getAssignedTrainerId();
            if(!tId.empty()) {
                for (auto& t : trainers) { if(t.getId() == tId) tName = t.getName(); }
            }
            ImGui::Text("%s", tName.c_str());

            ImGui::TableSetColumnIndex(4);
            ImGui::Text("%s (%d wks)", members[i].getWorkoutPlan().getPlanName().c_str(), members[i].getWorkoutPlan().getDurationWeeks());

            ImGui::TableSetColumnIndex(5);
            std::string assBtn = "Assign Trainer##" + members[i].getId();
            if (ImGui::Button(assBtn.c_str())) {
                memberIdForAssign = members[i].getId();
                openAssignTrainer = true;
            }
            ImGui::SameLine();
            std::string wrkBtn = "Edit Workout##" + members[i].getId();
            if (ImGui::Button(wrkBtn.c_str())) {
                memberIdForWorkout = members[i].getId();
                std::strncpy(workoutNameInput, members[i].getWorkoutPlan().getPlanName().c_str(), sizeof(workoutNameInput));
                std::strncpy(workoutDetailsInput, members[i].getWorkoutPlan().getDetails().c_str(), sizeof(workoutDetailsInput));
                workoutDurationInput = members[i].getWorkoutPlan().getDurationWeeks();
                openEditWorkout = true;
            }
            ImGui::SameLine();
            std::string delBtn = "Remove##M" + std::to_string(i);
            if (ImGui::Button(delBtn.c_str())) {
                removeIdx = i;
            }
        }
        if (removeIdx != -1) {
            std::string rTid = members[removeIdx].getAssignedTrainerId();
            if (!rTid.empty()) {
                auto tIt = std::find_if(trainers.begin(), trainers.end(), [&](Trainer& t) { return t.getId() == rTid; });
                if (tIt != trainers.end()) tIt->removeAssignedMemberId(members[removeIdx].getId());
            }
            members.erase(members.begin() + removeIdx);
        }
        ImGui::EndTable();

        if (openAssignTrainer) ImGui::OpenPopup("Assign Trainer");
        if (openEditWorkout) ImGui::OpenPopup("Edit Workout");
    }
}

void AdminDashboard::renderTrainersTab(std::vector<Trainer>& trainers) {
    if (ImGui::Button("Add New Trainer")) {
        ImGui::OpenPopup("Add Trainer");
    }

    if (ImGui::BeginPopupModal("Add Trainer", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::InputText("Name", nameInput, IM_ARRAYSIZE(nameInput));
        ImGui::InputText("Username", usernameInput, IM_ARRAYSIZE(usernameInput));
        ImGui::InputText("Password", passwordInput, IM_ARRAYSIZE(passwordInput));

        if (ImGui::Button("Save", ImVec2(120, 0))) {
            std::string id = "T" + std::to_string(trainers.size() + 1);
            trainers.push_back(Trainer(id, usernameInput, passwordInput, nameInput, "9AM - 5PM", 2000.0));
            ImGui::CloseCurrentPopup();
            nameInput[0] = '\0'; usernameInput[0] = '\0'; passwordInput[0] = '\0';
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(120, 0))) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    ImGui::Separator();

    if (ImGui::BeginTable("TrainersTable", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Username");
        ImGui::TableSetupColumn("Actions");
        ImGui::TableHeadersRow();

        int removeIdx = -1;
        for (size_t i = 0; i < trainers.size(); ++i) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0); ImGui::Text("%s", trainers[i].getId().c_str());
            ImGui::TableSetColumnIndex(1); ImGui::Text("%s", trainers[i].getName().c_str());
            ImGui::TableSetColumnIndex(2); ImGui::Text("%s", trainers[i].getUsername().c_str());
            
            ImGui::TableSetColumnIndex(3);
            std::string delBtn = "Remove##T" + std::to_string(i);
            if (ImGui::Button(delBtn.c_str())) {
                removeIdx = i;
            }
        }
        if (removeIdx != -1) {
            trainers.erase(trainers.begin() + removeIdx);
        }
        ImGui::EndTable();
    }
}

void AdminDashboard::renderEquipmentTab(std::vector<Equipment>& equipment) {
    if (ImGui::Button("Add Equipment")) {
        ImGui::OpenPopup("Add Eq");
    }

    if (ImGui::BeginPopupModal("Add Eq", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::InputText("Name", eqNameInput, IM_ARRAYSIZE(eqNameInput));
        ImGui::InputText("Category", eqCategoryInput, IM_ARRAYSIZE(eqCategoryInput));
        const char* conds[] = {"Good", "Needs Servicing"};
        ImGui::Combo("Condition", &eqConditionIndex, conds, IM_ARRAYSIZE(conds));

        if (ImGui::Button("Save", ImVec2(120, 0))) {
            std::string id = "EQ" + std::to_string(equipment.size() + 1);
            std::string condStr = (eqConditionIndex == 0) ? "Good" : "Needs Servicing";
            equipment.push_back(Equipment(id, eqNameInput, std::string(eqCategoryInput), condStr));
            ImGui::CloseCurrentPopup();
            eqNameInput[0] = '\0';
            eqCategoryInput[0] = '\0';
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(120, 0))) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    ImGui::Separator();

    if (ImGui::BeginTable("EqTable", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Category");
        ImGui::TableSetupColumn("Condition");
        ImGui::TableSetupColumn("Actions");
        ImGui::TableHeadersRow();

        for (auto& eq : equipment) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0); ImGui::Text("%s", eq.getId().c_str());
            ImGui::TableSetColumnIndex(1); ImGui::Text("%s", eq.getName().c_str());
            ImGui::TableSetColumnIndex(2); ImGui::Text("%s", eq.getCategory().c_str());
            ImGui::TableSetColumnIndex(3); 
            if (eq.getCondition() == "Needs Servicing") {
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%s", eq.getCondition().c_str());
            } else {
                ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "%s", eq.getCondition().c_str());
            }

            ImGui::TableSetColumnIndex(4);
            std::string btnStr = (eq.getCondition() == "Good") ? "Mark Broken##" + eq.getId() : "Mark Fixed##" + eq.getId();
            if (ImGui::Button(btnStr.c_str())) {
                eq.setCondition(eq.getCondition() == "Good" ? "Needs Servicing" : "Good");
            }
        }
        ImGui::EndTable();
    }
}

void AdminDashboard::render(Admin& currentAdmin, std::vector<Member>& members, std::vector<Trainer>& trainers, std::vector<Equipment>& equipment, std::vector<Payment>& payments, std::vector<MembershipPlan>& plans, bool& logout) {
    ImGui::Begin("Admin Dashboard", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);

    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Account")) {
            if (ImGui::MenuItem("Logout")) {
                logout = true;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::Text("Welcome, %s (Admin)", currentAdmin.getName().c_str());
    ImGui::Separator();

    if (ImGui::BeginTabBar("AdminTabs")) {
        if (ImGui::BeginTabItem("Manage Members")) {
            renderMembersTab(members, plans, payments, trainers);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Manage Trainers")) {
            renderTrainersTab(trainers);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Manage Equipment")) {
            renderEquipmentTab(equipment);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Payments Log")) {
            if (ImGui::BeginTable("PaymentsLogTable", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
                ImGui::TableSetupColumn("Payment ID");
                ImGui::TableSetupColumn("Member ID");
                ImGui::TableSetupColumn("Amount");
                ImGui::TableSetupColumn("Date");
                ImGui::TableSetupColumn("Status");
                ImGui::TableHeadersRow();

                for (const auto& p : payments) {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0); ImGui::Text("%s", p.getId().c_str());
                    ImGui::TableSetColumnIndex(1); ImGui::Text("%s", p.getMemberId().c_str());
                    ImGui::TableSetColumnIndex(2); ImGui::Text("$%.2f", p.getAmount());
                    ImGui::TableSetColumnIndex(3); ImGui::Text("%s", p.getDate().c_str());
                    ImGui::TableSetColumnIndex(4); ImGui::Text("%s", p.getStatus().c_str());
                }
                ImGui::EndTable();
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("My Profile")) {
            renderProfileTab(currentAdmin);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    ImGui::End();
}
