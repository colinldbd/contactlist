#ifndef CONTACT_LIST_H
#define CONTACT_LIST_H
#include "cstuffinfo.h"

class CContact_list
{
public:
    CContact_list();
    void AddStuff(CStuffInfo *);
    void DeleteStuff(QString);
    int CountList();
    CStuffInfo &operator [](int idx){
        return contactlist[idx];
    }

private:
    CStuffInfo contactlist[200];
    int listcount;
};

#endif // CONTACT_LIST_H
