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
        if(contactlist[i].ShowName()==tname)//������������Ҫɾ������ϵ���������
            i--;
    }
}

int CContact_list::CountList()
{
    return listcount;
}


//����½��������µĿհ���ϵ�ˣ�������ϵ��������Ϣ���������ͻᱣ�沢����item�����ߵ��item���⣬Ҳ�ᱣ�棬����ķ�ʽ����AddStuff��Ȼ��д�ļ����޸ģ���д�ı��򣨼���ı����޸��������Ȼ�󽫶�Ӧ�������Ա�����ݸ��£�Ȼ����д���ļ�
