#include "cstuffinfo.h"

CStuffInfo::CStuffInfo()
{
}

void CStuffInfo::GetName(QString tname)
{
    name=tname;
}

void CStuffInfo::GetPhoneNumber(QString tno)
{
    phonenumber=tno;
}

void CStuffInfo::GetAddress(QString adrs)
{
    address=adrs;
}

void CStuffInfo::GetEmail(QString temail)
{
    email=temail;
}

const QString CStuffInfo::ShowName()
{
    return name;
}

const QString CStuffInfo::ShowPhoneNumber()
{
    return phonenumber;
}

const QString CStuffInfo::ShowAddress()
{
    return address;
}

const QString CStuffInfo::ShowEmail()
{
    return email;
}

