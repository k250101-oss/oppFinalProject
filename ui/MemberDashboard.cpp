#include "MemberDashboard.h"
#include "imgui.h"
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <sstream>

static std::string getCurrentDate() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    struct tm* parts = std::localtime(&now_c);
    std::stringstream ss;
    ss << 1900 + parts->tm_year << "-" << std::setfill('0') << std::setw(2) << 1 + parts->tm_mon << "-" << std::setfill('0') << std::setw(2) << parts->tm_mday;
    return ss.str();
}

void MemberDashboard::render(Member& currentMember, const std::vector<Trainer>& trainers, std::vector<Payment>& payments, bool& logout) {
    ImGui::Begin("Member Dashboard", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);

    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Account")) {
            if (ImGui::MenuItem("Logout")) {
                logout = true;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    if (ImGui::BeginTabBar("MemberTabs")) {
        if (ImGui::BeginTabItem("Personal Info")) {
            ImGui::Text("Name: %s", currentMember.getName().c_str());
            ImGui::Text("ID: %s", currentMember.getId().c_str());
            ImGui::Separator();
            
            ImGui::Text("Membership Type: %s", currentMember.getMembership().getType().c_str());
            ImGui::Text("Expiry Date: %s", currentMember.getMembership().getExpiryDate().c_str());

            std::string trainerName = "None";
            for (const auto& t : trainers) {
                if (t.getId() == currentMember.getAssignedTrainerId()) {
                    trainerName = t.getName();
                    break;
                }
            }
            ImGui::Text("Assigned Trainer: %s", trainerName.c_str());

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Workout Plan")) {
            ImGui::Text("Plan Name: %s", currentMember.getWorkoutPlan().getPlanName().c_str());
            ImGui::Text("Duration: %d weeks", currentMember.getWorkoutPlan().getDurationWeeks());
            ImGui::Separator();
            ImGui::TextWrapped("Details:\n%s", currentMember.getWorkoutPlan().getDetails().c_str());
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Attendance")) {
            ImGui::Text("Total Days Attended: %d", currentMember.getAttendanceCount());
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Payments")) {
            if (ImGui::Button("Pay Dues ($50.00)", ImVec2(150, 0))) {
                std::string payId = "PAY" + std::to_string(payments.size() + 1);
                payments.push_back(Payment(payId, currentMember.getId(), 50.0, getCurrentDate(), "Paid"));
            }
            ImGui::Separator();
            
            if (ImGui::BeginTable("PaymentHistory", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
                ImGui::TableSetupColumn("Payment ID");
                ImGui::TableSetupColumn("Date");
                ImGui::TableSetupColumn("Amount");
                ImGui::TableSetupColumn("Status");
                ImGui::TableHeadersRow();

                for (const auto& p : payments) {
                    if (p.getMemberId() == currentMember.getId()) {
                        ImGui::TableNextRow();
                        ImGui::TableSetColumnIndex(0); ImGui::Text("%s", p.getId().c_str());
                        ImGui::TableSetColumnIndex(1); ImGui::Text("%s", p.getDate().c_str());
                        ImGui::TableSetColumnIndex(2); ImGui::Text("$%.2f", p.getAmount());
                        ImGui::TableSetColumnIndex(3); ImGui::Text("%s", p.getStatus().c_str());
                    }
                }
                ImGui::EndTable();
            }
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}
