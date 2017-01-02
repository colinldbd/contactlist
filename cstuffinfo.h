#ifndef CSTUFFINFO_H
#define CSTUFFINFO_H
#include <QString>

using namespace std;

class CStuffInfo
{
public:
    CStuffInfo();
    void GetName(QString);
    void GetPhoneNumber(QString);
    void GetAddress(QString);
    void GetEmail(QString);
    const QString ShowName();
    const QString ShowPhoneNumber();
    const QString ShowAddress();
    const QString ShowEmail();
private:
    QString name;
    QString phonenumber;
    QString address;
    QString email;
};

#endif // CSTUFFINFO_H
