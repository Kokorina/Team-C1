#ifndef TOOL_H
#define TOOL_H

#include <QString>

class Tool
{
public:
    Tool();

    QString getName() const;
    void setName(const QString &value);

private:
    QString name;
};

#endif // TOOL_H
