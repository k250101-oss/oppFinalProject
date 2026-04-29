#include "Membership.h"

Membership::Membership() : type("Basic"), startDate(""), expiryDate("") {}

Membership::Membership(const std::string& type, const std::string& startDate, const std::string& expiryDate)
    : type(type), startDate(startDate), expiryDate(expiryDate) {}

std::string Membership::getType() const { return type; }
std::string Membership::getStartDate() const { return startDate; }
std::string Membership::getExpiryDate() const { return expiryDate; }

void Membership::setType(const std::string& type) { this->type = type; }
void Membership::setStartDate(const std::string& startDate) { this->startDate = startDate; }
void Membership::setExpiryDate(const std::string& expiryDate) { this->expiryDate = expiryDate; }

bool Membership::isValid() const {
    // Simple verification (in a real app we'd parse this)
    return !expiryDate.empty();
}
