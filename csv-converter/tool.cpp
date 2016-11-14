#include "tool.h"

Tool::Tool()
{

}
QString Tool::getName() const
{
    return name;
}

void Tool::setName(const QString &value)
{
    name = value;
}


