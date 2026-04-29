#include "TrainerDashboard.h"
#include "imgui.h"

void TrainerDashboard::render(Trainer& currentTrainer, std::vector<Member>& members, bool& logout) {
    ImGui::Begin("Trainer Dashboard", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);

    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Account")) {
            if (ImGui::MenuItem("Logout")) {
                logout = true;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    if (ImGui::BeginTabBar("TrainerTabs")) {
        if (ImGui::BeginTabItem("My Schedule")) {
            ImGui::Text("Name: %s", currentTrainer.getName().c_str());
            ImGui::Text("Schedule: %s", currentTrainer.getSchedule().c_str());
            ImGui::Text("Salary: $%.2f", currentTrainer.getSalary());
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Assigned Members")) {
            if (ImGui::BeginTable("AssignedMembersTable", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable)) {
                ImGui::TableSetupColumn("ID");
                ImGui::TableSetupColumn("Name");
                ImGui::TableSetupColumn("Attendance");
                ImGui::TableSetupColumn("Workout Plan");
                ImGui::TableSetupColumn("Actions");
                ImGui::TableHeadersRow();

                bool openEditWorkout = false;

                for (auto& m : members) {
                    if (m.getAssignedTrainerId() == currentTrainer.getId()) {
                        ImGui::TableNextRow();
                        ImGui::TableSetColumnIndex(0); ImGui::Text("%s", m.getId().c_str());
                        ImGui::TableSetColumnIndex(1); ImGui::Text("%s", m.getName().c_str());
                        ImGui::TableSetColumnIndex(2); ImGui::Text("%d", m.getAttendanceCount());
                        ImGui::TableSetColumnIndex(3); ImGui::Text("%s", m.getWorkoutPlan().getPlanName().c_str());
                        
                        ImGui::TableSetColumnIndex(4);
                        std::string attId = "Mark Att##" + m.getId();
                        if (ImGui::Button(attId.c_str())) {
                            m.incrementAttendance();
                        }
                        ImGui::SameLine();
                        std::string wpId = "Edit WP##" + m.getId();
                        if (ImGui::Button(wpId.c_str())) {
                            selectedMemberId = m.getId();
                            snprintf(wpNameInput, sizeof(wpNameInput), "%s", m.getWorkoutPlan().getPlanName().c_str());
                            snprintf(wpDetailsInput, sizeof(wpDetailsInput), "%s", m.getWorkoutPlan().getDetails().c_str());
                            wpDurationInput = m.getWorkoutPlan().getDurationWeeks();
                            openEditWorkout = true;
                        }
                    }
                }
                ImGui::EndTable();
                
                if (openEditWorkout) {
                    ImGui::OpenPopup("Edit Workout Plan");
                }
            }
            
            if (ImGui::BeginPopupModal("Edit Workout Plan", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                ImGui::InputText("Plan Name", wpNameInput, IM_ARRAYSIZE(wpNameInput));
                ImGui::InputTextMultiline("Details", wpDetailsInput, IM_ARRAYSIZE(wpDetailsInput), ImVec2(300, 100));
                ImGui::InputInt("Duration (Weeks)", &wpDurationInput);

                if (ImGui::Button("Save", ImVec2(120, 0))) {
                    for (auto& m : members) {
                        if (m.getId() == selectedMemberId) {
                            WorkoutPlan newWp(wpNameInput, wpDetailsInput, wpDurationInput);
                            m.setWorkoutPlan(newWp);
                            break;
                        }
                    }
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SetItemDefaultFocus();
                ImGui::SameLine();
                if (ImGui::Button("Cancel", ImVec2(120, 0))) {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}
