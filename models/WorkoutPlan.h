#pragma once
#include <string>

class WorkoutPlan {
private:
    std::string planName;
    std::string details;
    int durationWeeks;

public:
    WorkoutPlan();
    WorkoutPlan(const std::string& planName, const std::string& details, int durationWeeks);

    std::string getPlanName() const;
    std::string getDetails() const;
    int getDurationWeeks() const;

    void setPlanName(const std::string& planName);
    void setDetails(const std::string& details);
    void setDurationWeeks(int durationWeeks);
};
