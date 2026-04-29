#include "Member.h"

Member::Member(const std::string& id, const std::string& username, const std::string& password, const std::string& name,
               const Membership& membership, const WorkoutPlan& workoutPlan,
               const std::string& assignedTrainerId, int attendanceCount)
    : Person(id, username, password, name, "Member"), 
      membership(membership), workoutPlan(workoutPlan), 
      assignedTrainerId(assignedTrainerId), attendanceCount(attendanceCount) {}

Membership Member::getMembership() const { return membership; }
WorkoutPlan Member::getWorkoutPlan() const { return workoutPlan; }
std::string Member::getAssignedTrainerId() const { return assignedTrainerId; }
int Member::getAttendanceCount() const { return attendanceCount; }

void Member::setMembership(const Membership& membership) { this->membership = membership; }
void Member::setWorkoutPlan(const WorkoutPlan& workoutPlan) { this->workoutPlan = workoutPlan; }
void Member::setAssignedTrainerId(const std::string& assignedTrainerId) { this->assignedTrainerId = assignedTrainerId; }
void Member::setAttendanceCount(int attendanceCount) { this->attendanceCount = attendanceCount; }
void Member::incrementAttendance() { attendanceCount++; }

bool Member::login(const std::string& inputUsername, const std::string& inputPassword) const {
    return (getUsername() == inputUsername && getPassword() == inputPassword);
}

void Member::display() const {
    std::cout << "Member: " << getName() << " (ID: " << getId() << ")\n";
    std::cout << "Membership Type: " << membership.getType() << "\n";
    std::cout << "Trainer ID: " << assignedTrainerId << "\n";
}
