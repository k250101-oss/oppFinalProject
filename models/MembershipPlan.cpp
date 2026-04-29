#include "MembershipPlan.h"

MembershipPlan::MembershipPlan(const std::string& id, const std::string& name, double price, int durationMonths)
    : id(id), name(name), price(price), durationMonths(durationMonths) {}

std::string MembershipPlan::getId() const { return id; }
std::string MembershipPlan::getName() const { return name; }
double MembershipPlan::getPrice() const { return price; }
int MembershipPlan::getDurationMonths() const { return durationMonths; }

void MembershipPlan::setId(const std::string& id) { this->id = id; }
void MembershipPlan::setName(const std::string& name) { this->name = name; }
void MembershipPlan::setPrice(double price) { this->price = price; }
void MembershipPlan::setDurationMonths(int durationMonths) { this->durationMonths = durationMonths; }
