#include "toolsubclass.h"

ToolSubClass::ToolSubClass()
{

}
char ToolSubClass::getId() const
{
    return id;
}

void ToolSubClass::setId(char value)
{
    id = value;
}
QString ToolSubClass::getName() const
{
    return name;
}

void ToolSubClass::setName(const QString &value)
{
    name = value;
}



