#include "OwnerDashboard.h"
#include "imgui.h"
#include <map>
#include <string>

void OwnerDashboard::renderPlansTab(std::vector<MembershipPlan>& plans) {
    if (ImGui::Button("Add New Plan")) {
        ImGui::OpenPopup("Add Plan");
    }

    if (ImGui::BeginPopupModal("Add Plan", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::InputText("Plan Name", planNameInput, IM_ARRAYSIZE(planNameInput));
        ImGui::InputDouble("Price", &planPriceInput);
        ImGui::InputInt("Duration (Months)", &planDurationInput);

        if (ImGui::Button("Save", ImVec2(120, 0))) {
            std::string id = "PL" + std::to_string(plans.size() + 1);
            plans.push_back(MembershipPlan(id, planNameInput, planPriceInput, planDurationInput));
            ImGui::CloseCurrentPopup();
            planNameInput[0] = '\0';
            planPriceInput = 0.0;
            planDurationInput = 1;
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(120, 0))) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    ImGui::Separator();

    if (ImGui::BeginTable("PlansTable", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Price");
        ImGui::TableSetupColumn("Duration (Mo)");
        ImGui::TableSetupColumn("Actions");
        ImGui::TableHeadersRow();

        int removeIdx = -1;
        for (size_t i = 0; i < plans.size(); ++i) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0); ImGui::Text("%s", plans[i].getId().c_str());
            ImGui::TableSetColumnIndex(1); ImGui::Text("%s", plans[i].getName().c_str());
            ImGui::TableSetColumnIndex(2); ImGui::Text("$%.2f", plans[i].getPrice());
            ImGui::TableSetColumnIndex(3); ImGui::Text("%d", plans[i].getDurationMonths());
            
            ImGui::TableSetColumnIndex(4);
            std::string delBtn = "Remove##PL" + std::to_string(i);
            if (ImGui::Button(delBtn.c_str())) {
                removeIdx = i;
            }
        }
        if (removeIdx != -1) {
            plans.erase(plans.begin() + removeIdx);
        }
        ImGui::EndTable();
    }
}

void OwnerDashboard::renderFinancialReport(const std::vector<Payment>& payments, const std::vector<Member>& members, const std::vector<Trainer>& trainers, const std::vector<Admin>& admins, const std::vector<MembershipPlan>& plans) {
    double totalRevenue = 0;
    std::map<std::string, double> revenueByPlan;

    for (const auto& p : payments) {
        if (p.getStatus() == "Paid") {
            totalRevenue += p.getAmount();

            // Find member to identify their plan type
            std::string planType = "Unknown/Custom";
            for(const auto& m : members) {
                if(m.getId() == p.getMemberId()) {
                    planType = m.getMembership().getType();
                    break;
                }
            }
            revenueByPlan[planType] += p.getAmount();
        }
    }

    ImGui::Text("Total Members: %zu", members.size());
    ImGui::Text("Total Trainers: %zu", trainers.size());
    ImGui::Text("Total Admins: %zu", admins.size());
    ImGui::Separator();
    
    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Total Revenue: $%.2f", totalRevenue);
    ImGui::Separator();

    ImGui::Text("Revenue Breakdown by Plan:");
    if (ImGui::BeginTable("RevenueTable", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
        ImGui::TableSetupColumn("Plan Type");
        ImGui::TableSetupColumn("Revenue");
        ImGui::TableHeadersRow();

        for (const auto& kv : revenueByPlan) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0); ImGui::Text("%s", kv.first.c_str());
            ImGui::TableSetColumnIndex(1); ImGui::Text("$%.2f", kv.second);
        }
        ImGui::EndTable();
    }

    ImGui::Separator();
    ImGui::Text("Recent Payments Log:");
    if (ImGui::BeginTable("PaymentsLogTableOwner", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
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
}

void OwnerDashboard::render(Owner& currentOwner, std::vector<Member>& members, std::vector<Trainer>& trainers, std::vector<Equipment>& equipment, std::vector<Payment>& payments, std::vector<Admin>& admins, std::vector<MembershipPlan>& plans, bool& logout) {
    ImGui::Begin("Owner Dashboard", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);

    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Account")) {
            if (ImGui::MenuItem("Logout")) {
                logout = true;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::Text("Welcome, %s (Owner)", currentOwner.getName().c_str());
    ImGui::Separator();

    if (ImGui::BeginTabBar("OwnerTabs")) {
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
        if (ImGui::BeginTabItem("Manage Plans")) {
            renderPlansTab(plans);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Financial Report")) {
            renderFinancialReport(payments, members, trainers, admins, plans);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("My Profile")) {
            renderProfileTab(currentOwner);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    ImGui::End();
}
