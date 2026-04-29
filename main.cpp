#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include <vector>
#include <string>

#include "models/Member.h"
#include "models/Trainer.h"
#include "models/Admin.h"
#include "models/Owner.h"
#include "models/Equipment.h"
#include "models/Payment.h"
#include "models/MembershipPlan.h"

#include "utils/FileManager.h"

#include "ui/LoginScreen.h"
#include "ui/MemberDashboard.h"
#include "ui/TrainerDashboard.h"
#include "ui/AdminDashboard.h"
#include "ui/OwnerDashboard.h"

int main() {
    std::string basePath = "data/";
    std::vector<Member> members;
    std::vector<Trainer> trainers;
    std::vector<Admin> admins;
    std::vector<Owner> owners;
    std::vector<Equipment> equipment;
    std::vector<Payment> payments;
    std::vector<MembershipPlan> plans;

    FileManager::loadMembers(members, basePath + "members.txt");
    FileManager::loadTrainers(trainers, basePath + "trainers.txt");
    FileManager::loadAdmins(admins, basePath + "admins.txt");
    FileManager::loadOwners(owners, basePath + "owners.txt");
    FileManager::loadEquipment(equipment, basePath + "equipment.txt");
    FileManager::loadPayments(payments, basePath + "payments.txt");
    FileManager::loadMembershipPlans(plans, basePath + "plans.txt");

    // Default admin and owner if empty
    if (admins.empty()) admins.push_back(Admin("A1", "admin", "admin", "Default Admin"));
    if (owners.empty()) owners.push_back(Owner("O1", "owner", "owner", "Default Owner"));
    if (plans.empty()) {
        plans.push_back(MembershipPlan("PL1", "Basic", 50.0, 1));
        plans.push_back(MembershipPlan("PL2", "Gold", 120.0, 3));
        plans.push_back(MembershipPlan("PL3", "Platinum", 400.0, 12));
    }

    sf::RenderWindow window(sf::VideoMode(1024, 768), "Gym Management System");
    window.setFramerateLimit(60);
    
    if (!ImGui::SFML::Init(window)) return -1;
    ImGui::StyleColorsDark();

    LoginScreen loginScreen;
    MemberDashboard memberDash;
    TrainerDashboard trainerDash;
    AdminDashboard adminDash;
    OwnerDashboard ownerDash;

    bool isLoggedIn = false;
    std::string activeRole = "";
    std::string activeUserId = "";
    bool logoutRequested = false;

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        if (logoutRequested) {
            // Save state immediately on logout before resetting
            FileManager::saveMembers(members, basePath + "members.txt");
            FileManager::saveTrainers(trainers, basePath + "trainers.txt");
            FileManager::saveAdmins(admins, basePath + "admins.txt");
            FileManager::saveOwners(owners, basePath + "owners.txt");
            FileManager::saveEquipment(equipment, basePath + "equipment.txt");
            FileManager::savePayments(payments, basePath + "payments.txt");
            FileManager::saveMembershipPlans(plans, basePath + "plans.txt");

            isLoggedIn = false;
            activeRole = "";
            activeUserId = "";
            logoutRequested = false;
        }

        if (!isLoggedIn) {
            // Center login screen
            ImGui::SetNextWindowPos(ImVec2(window.getSize().x / 2.0f, window.getSize().y / 2.0f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
            isLoggedIn = loginScreen.render(members, trainers, admins, owners, activeRole, activeUserId);
        } else {
            // Setup Fullscreen window for Dashboards
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImVec2((float)window.getSize().x, (float)window.getSize().y));

            if (activeRole == "Member") {
                for (auto& m : members) {
                    if (m.getId() == activeUserId) {
                        memberDash.render(m, trainers, payments, logoutRequested);
                        break;
                    }
                }
            } else if (activeRole == "Trainer") {
                for (auto& t : trainers) {
                    if (t.getId() == activeUserId) {
                        trainerDash.render(t, members, logoutRequested);
                        break;
                    }
                }
            } else if (activeRole == "Admin") {
                for (auto& a : admins) {
                    if (a.getId() == activeUserId) {
                        adminDash.render(a, members, trainers, equipment, payments, plans, logoutRequested);
                        break;
                    }
                }
            } else if (activeRole == "Owner") {
                for (auto& o : owners) {
                    if (o.getId() == activeUserId) {
                        ownerDash.render(o, members, trainers, equipment, payments, admins, plans, logoutRequested);
                        break;
                    }
                }
            }
        }

        window.clear(sf::Color(30, 30, 30));
        ImGui::SFML::Render(window);
        window.display();
    }

    // Save Data before exit
    FileManager::saveMembers(members, basePath + "members.txt");
    FileManager::saveTrainers(trainers, basePath + "trainers.txt");
    FileManager::saveAdmins(admins, basePath + "admins.txt");
    FileManager::saveOwners(owners, basePath + "owners.txt");
    FileManager::saveEquipment(equipment, basePath + "equipment.txt");
    FileManager::savePayments(payments, basePath + "payments.txt");
    FileManager::saveMembershipPlans(plans, basePath + "plans.txt");

    ImGui::SFML::Shutdown();
    return 0;
}
