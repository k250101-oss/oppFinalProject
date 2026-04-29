#include "Payment.h"

Payment::Payment(const std::string& id, const std::string& memberId, double amount, const std::string& date, const std::string& status)
    : id(id), memberId(memberId), amount(amount), date(date), status(status) {}

std::string Payment::getId() const { return id; }
std::string Payment::getMemberId() const { return memberId; }
double Payment::getAmount() const { return amount; }
std::string Payment::getDate() const { return date; }
std::string Payment::getStatus() const { return status; }

void Payment::setId(const std::string& id) { this->id = id; }
void Payment::setMemberId(const std::string& memberId) { this->memberId = memberId; }
void Payment::setAmount(double amount) { this->amount = amount; }
void Payment::setDate(const std::string& date) { this->date = date; }
void Payment::setStatus(const std::string& status) { this->status = status; }
