#pragma once
#include "Person.h"
#include "Membership.h"
#include "WorkoutPlan.h"
#include <string>
#include <iostream>

class Member : public Person {
private:
    Membership membership;
    WorkoutPlan workoutPlan;
    std::string assignedTrainerId;
    int attendanceCount;

public:
    Member(const std::string& id, const std::string& username, const std::string& password, const std::string& name,
           const Membership& membership = Membership(), const WorkoutPlan& workoutPlan = WorkoutPlan(),
           const std::string& assignedTrainerId = "", int attendanceCount = 0);

    Membership getMembership() const;
    WorkoutPlan getWorkoutPlan() const;
    std::string getAssignedTrainerId() const;
    int getAttendanceCount() const;

    void setMembership(const Membership& membership);
    void setWorkoutPlan(const WorkoutPlan& workoutPlan);
    void setAssignedTrainerId(const std::string& assignedTrainerId);
    void setAttendanceCount(int attendanceCount);
    void incrementAttendance();

    bool login(const std::string& inputUsername, const std::string& inputPassword) const override;
    void display() const override;
};
