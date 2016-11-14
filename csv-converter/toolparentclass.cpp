#include "toolparentclass.h"

ToolParentClass::ToolParentClass()
{

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
vector<ToolSubClass> ToolParentClass::getSubclasses() const
{
    return subclasses;
}

void ToolParentClass::setSubclasses(const vector<ToolSubClass> &value)
{
    subclasses = value;
}




