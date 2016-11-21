#include "toolsubclass.h"

ToolSubClass::ToolSubClass()
{

}

ToolSubClass::ToolSubClass(QString id, QString name)
{
    this->id=id;
    this->name=name;
}

QString ToolSubClass::getId() const
{
    return id;
}

void ToolSubClass::setId(QString value)
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
vector<Tool> ToolSubClass::getTools() const
{
    return tools;
}

void ToolSubClass::setTools(const vector<Tool> &value)
{
    tools = value;
}




