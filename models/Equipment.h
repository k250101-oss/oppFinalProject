#pragma once
#include <string>

class Equipment {
private:
    std::string id;
    std::string name;
    std::string category;
    std::string condition;

public:
    Equipment(const std::string& id, const std::string& name, const std::string& category, const std::string& condition);

    std::string getId() const;
    std::string getName() const;
    std::string getCategory() const;
    std::string getCondition() const;

    void setId(const std::string& id);
    void setName(const std::string& name);
    void setCategory(const std::string& category);
    void setCondition(const std::string& condition);
};
