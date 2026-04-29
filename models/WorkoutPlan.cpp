#include "WorkoutPlan.h"

WorkoutPlan::WorkoutPlan() : planName(""), details(""), durationWeeks(0) {}

WorkoutPlan::WorkoutPlan(const std::string& planName, const std::string& details, int durationWeeks)
    : planName(planName), details(details), durationWeeks(durationWeeks) {}

std::string WorkoutPlan::getPlanName() const { return planName; }
std::string WorkoutPlan::getDetails() const { return details; }
int WorkoutPlan::getDurationWeeks() const { return durationWeeks; }

void WorkoutPlan::setPlanName(const std::string& planName) { this->planName = planName; }
void WorkoutPlan::setDetails(const std::string& details) { this->details = details; }
void WorkoutPlan::setDurationWeeks(int durationWeeks) { this->durationWeeks = durationWeeks; }
