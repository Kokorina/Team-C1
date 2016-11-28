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
QString Tool::getKontext() const
{
    return kontext;
}

void Tool::setKontext(const QString &value)
{
    kontext = value;
}



