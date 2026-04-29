#pragma once
#include <string>

class Payment {
private:
    std::string id;
    std::string memberId;
    double amount;
    std::string date;
    std::string status; // Paid, Pending

public:
    Payment(const std::string& id, const std::string& memberId, double amount, const std::string& date, const std::string& status);

    std::string getId() const;
    std::string getMemberId() const;
    double getAmount() const;
    std::string getDate() const;
    std::string getStatus() const;

    void setId(const std::string& id);
    void setMemberId(const std::string& memberId);
    void setAmount(double amount);
    void setDate(const std::string& date);
    void setStatus(const std::string& status);
};
