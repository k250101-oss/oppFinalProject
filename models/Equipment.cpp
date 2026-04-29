#include "Equipment.h"

Equipment::Equipment(const std::string& id, const std::string& name, const std::string& category, const std::string& condition)
    : id(id), name(name), category(category), condition(condition) {}

std::string Equipment::getId() const { return id; }
std::string Equipment::getName() const { return name; }
std::string Equipment::getCategory() const { return category; }
std::string Equipment::getCondition() const { return condition; }

void Equipment::setId(const std::string& id) { this->id = id; }
void Equipment::setName(const std::string& name) { this->name = name; }
void Equipment::setCategory(const std::string& category) { this->category = category; }
void Equipment::setCondition(const std::string& condition) { this->condition = condition; }
