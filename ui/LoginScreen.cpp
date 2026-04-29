#include "LoginScreen.h"
#include "imgui.h"

LoginScreen::LoginScreen() {}

bool LoginScreen::render(const std::vector<Member>& members,
                         const std::vector<Trainer>& trainers,
                         const std::vector<Admin>& admins,
                         const std::vector<Owner>& owners,
                         std::string& activeRole, 
                         std::string& activeUserId) {
    bool loggedIn = false;

    ImGui::Begin("Gym Management System - Login", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);

    const char* roles[] = { "Member", "Trainer", "Admin", "Owner" };
    ImGui::Combo("Role", &roleIndex, roles, IM_ARRAYSIZE(roles));

    ImGui::InputText("Username", usernameInput, IM_ARRAYSIZE(usernameInput));
    ImGui::InputText("Password", passwordInput, IM_ARRAYSIZE(passwordInput), ImGuiInputTextFlags_Password);

    if (ImGui::Button("Login", ImVec2(120, 0))) {
        std::string u(usernameInput);
        std::string p(passwordInput);
        bool found = false;

        if (roleIndex == 0) {
            for (const auto& m : members) {
                if (m.login(u, p)) {
                    activeRole = "Member";
                    activeUserId = m.getId();
                    loggedIn = true;
                    found = true;
                    break;
                }
            }
        } else if (roleIndex == 1) {
            for (const auto& t : trainers) {
                if (t.login(u, p)) {
                    activeRole = "Trainer";
                    activeUserId = t.getId();
                    loggedIn = true;
                    found = true;
                    break;
                }
            }
        } else if (roleIndex == 2) {
            for (const auto& a : admins) {
                if (a.login(u, p)) {
                    activeRole = "Admin";
                    activeUserId = a.getId();
                    loggedIn = true;
                    found = true;
                    break;
                }
            }
        } else if (roleIndex == 3) {
            for (const auto& o : owners) {
                if (o.login(u, p)) {
                    activeRole = "Owner";
                    activeUserId = o.getId();
                    loggedIn = true;
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            errorMessage = "Invalid username or password!";
        } else {
            errorMessage = ""; // clear error on success
            // clear inputs
            usernameInput[0] = '\0';
            passwordInput[0] = '\0';
        }
    }

    if (!errorMessage.empty()) {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%s", errorMessage.c_str());
    }

    ImGui::End();

    return loggedIn;
}
