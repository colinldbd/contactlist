#include "contact_list.h"

CContact_list::CContact_list()
{
    listcount=0;
}

void CContact_list::AddStuff(CStuffInfo *stuff)
{
    contactlist[listcount++]=*stuff;
}

void CContact_list::DeleteStuff(QString tname)
{
    for(int i=0;i<listcount;i++){
        if(contactlist[i].ShowName()==tname){
            listcount--;
            for(int j=i;j<listcount;j++)
                contactlist[j]=contactlist[j+1];
        }
        if(contactlist[i].ShowName()==tname)//处理连续出现要删除的联系人名的情况
            i--;
    }
}

int CContact_list::CountList()
{
    return listcount;
}


//点击新建，产生新的空白联系人，输入联系人名等信息，点击保存就会保存并跟新item，或者点击item以外，也会保存，保存的方式是先AddStuff，然后写文件，修改？改写文本框（检测文本框修改情况），然后将对应的数组成员的数据更新，然后重写入文件
