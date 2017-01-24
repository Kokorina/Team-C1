#include "toolparentclass.h"
#include <numeric>
#include <utility>

ToolParentClass::ToolParentClass()
{

}

ToolParentClass::ToolParentClass(int id, QString name)
{
    this->id=id;
    this->name=name;

}

int ToolParentClass::getId() const
{
    return id;
}

void ToolParentClass::setId(int value)
{
    id = value;
}
QString ToolParentClass::getName() const
{
    return name;
}

void ToolParentClass::setName(const QString &value)
{
    name = value;
}
map<QString, ToolSubClass> ToolParentClass::getSubclasses() const
{
    return subclasses;
}

void ToolParentClass::setSubclasses(const map<QString, ToolSubClass> &value)
{
    subclasses = value;
}

int ToolParentClass::getTotalWords() {
	return totalWords;
}
void ToolParentClass::calculateTotalWords() {
	totalWords = accumulate(begin(BoW), std::end(BoW), 0, [](const int previous, const std::pair<QString, int>& p) { return previous + p.second; });
}


