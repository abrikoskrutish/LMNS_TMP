#ifndef DATABASE_H
#define DATABASE_H
#include <QByteArray>
#include <QString>

class databese
{
public:
    databese();
    static QByteArray sendQuerry(QString text);
};

#endif // DATABASE_H
