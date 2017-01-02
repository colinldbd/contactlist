#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QListWidgetItem>
#include "contact_list.h"
#include <QTextCodec>
#include <QDebug>
#include <QDataStream>
#include <QFile>
#include <QMessageBox>
#include <QAction>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    BuildListWidGet();
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    //this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    this->setFixedSize( this->width (),this->height ());
    this->setWindowTitle(tr("通讯录"));
    ui->stufflist->setStyleSheet("border:1px solid gray;background:lightyellow");
    ui->lineEdit_1->setStyleSheet("border :none ;border-bottom:1px solid gray;background : transparent");
    ui->lineEdit_2->setStyleSheet("border :none ;border-bottom:1px solid gray;background : transparent");
    ui->lineEdit_3->setStyleSheet("border :none ;border-bottom:1px solid gray;background : transparent");
    ui->lineEdit_4->setStyleSheet("border :none ;border-bottom:1px solid gray;background : transparent");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load("./background.jpg");
    pix.scaled(this->size());
    painter.drawPixmap(this->rect(),pix);
}

void MainWindow::BuildListWidGet()
{
    loadfile(tr("contactbook.dat"));

    if(list.CountList()!=0){
        for(int i=0;i<list.CountList();i++){
            ui->stufflist->addItem(list[i].ShowName());
        }
        ui->stufflist->setCurrentRow(0);
        SetTextInfo();
    }
    else{
        ui->lineEdit_1->setFocusPolicy(Qt::NoFocus);
        ui->lineEdit_2->setFocusPolicy(Qt::NoFocus);
        ui->lineEdit_3->setFocusPolicy(Qt::NoFocus);
        ui->lineEdit_4->setFocusPolicy(Qt::NoFocus);

    }
}

void MainWindow::GetStuffInfo()
{
    CStuffInfo *stuff=new CStuffInfo;

    //不能引用右值,text()返回的是右值
    stuff->GetName(ui->lineEdit_1->text());
    stuff->GetPhoneNumber(ui->lineEdit_2->text());
    stuff->GetAddress(ui->lineEdit_3->text());
    stuff->GetEmail(ui->lineEdit_4->text());

    bool found=false;

    for(int i=0;i<list.CountList();i++){
        if(ui->stufflist->currentItem()->text()==list[i].ShowName()){
            found=true;
            list[i]=*stuff;
            break;
        }

    }

    if(found==false){
        list.AddStuff(stuff);
    }
}

bool MainWindow::TextIsModified()
{
    if(ui->lineEdit_1->isModified()||ui->lineEdit_2->isModified()||ui->lineEdit_3->isModified()||ui->lineEdit_4->isModified())
        return true;
    else
        return false;
}

void MainWindow::SetTextModified(bool bool_type)
{
    ui->lineEdit_1->setModified(bool_type);
    ui->lineEdit_2->setModified(bool_type);
    ui->lineEdit_3->setModified(bool_type);
    ui->lineEdit_4->setModified(bool_type);
}

void MainWindow::savefile(QString fileName)
{
    QFile file(fileName);

    //文本只写方式打开文件
    if(!file.open(QFile::WriteOnly)){
        //.arg()用来表示参数
        QMessageBox::warning(this,tr("通讯录"),
                             tr("无法写入文件%1:/n%2")
                             .arg(fileName).arg(file.errorString()));

        return;
    }

    QDataStream out(&file);

    for(int i=0;i<list.CountList();i++){
        out<<list[i].ShowName()<<list[i].ShowPhoneNumber()<<list[i].ShowAddress()<<list[i].ShowEmail();
    }

    file.close();
}

void MainWindow::loadfile(QString fileName)
{
    QFile file(fileName);
    CStuffInfo * stuff=new CStuffInfo;
    QString name,phone,address,email;

    if(!file.open(QFile::ReadOnly)){
        //.arg()用来表示参数
        QMessageBox::warning(this,tr("通讯录"),
                             tr("无法读取文件%1:/n%2")
                             .arg(fileName).arg(file.errorString()));

        return;
    }

    QDataStream in(&file);

    while(1){
        if(file.atEnd())
            break;
        in>>name>>phone>>address>>email;
        stuff->GetName(name);
        stuff->GetPhoneNumber(phone);
        stuff->GetEmail(email);
        stuff->GetAddress(address);
        list.AddStuff(stuff);
   }

    file.close();
}

void MainWindow::SetTextInfo()
{
    bool found=false;

//使用previous和current
    for(int i=0;i<list.CountList();i++){
        if(ui->stufflist->currentItem()->text()==list[i].ShowName()){
            ui->lineEdit_1->setText(list[i].ShowName());
            ui->lineEdit_2->setText(list[i].ShowPhoneNumber());
            ui->lineEdit_3->setText(list[i].ShowAddress());
            ui->lineEdit_4->setText(list[i].ShowEmail());
            found=true;
            break;
        }

    }
    if(found==false){
        ui->lineEdit_1->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        SetTextModified(false);
    }
}

//用count把最后的移动到最前
void MainWindow::on_actoin_N_triggered()
{
    ui->lineEdit_1->setFocusPolicy(Qt::StrongFocus);
    ui->lineEdit_2->setFocusPolicy(Qt::StrongFocus);
    ui->lineEdit_3->setFocusPolicy(Qt::StrongFocus);
    ui->lineEdit_4->setFocusPolicy(Qt::StrongFocus);
    ui->stufflist->addItem(tr("空白联系人"));
    qDebug()<<ui->stufflist->count();
    QListWidgetItem *newitem=ui->stufflist->takeItem(ui->stufflist->count()-1);
    ui->stufflist->insertItem(0,newitem);
    ui->stufflist->setCurrentRow(0);
}

void MainWindow::on_action_S_triggered()
{
    if(ui->stufflist->count()==0)
        return;
    ui->stufflist->currentItem()->setText(ui->lineEdit_1->text());
    GetStuffInfo();
    savefile(tr("contactbook.dat"));
    SetTextModified(false);
}

void MainWindow::on_stufflist_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(current==NULL)
        return;
    if(!previous==NULL){
        if(TextIsModified()){
            previous->setText(ui->lineEdit_1->text());
            GetStuffInfo();
            savefile(tr("contactbook.dat"));
            SetTextModified(false);
        }
        qDebug()<<ui->stufflist->currentItem()->text();
        SetTextInfo();
    }
}

void MainWindow::on_action_D_triggered()
{
    if(list.CountList()==0)
        return;
        QListWidgetItem *current=ui->stufflist->takeItem(ui->stufflist->currentRow());
        list.DeleteStuff(current->text());
        delete current;
        SetTextInfo();
        savefile(tr("contactbook.dat"));
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *listmenu=new QMenu(ui->stufflist);

    QAction *action1=new QAction(tr("新建"),ui->stufflist);
    QAction *action2=new QAction(tr("删除"),ui->stufflist);

    listmenu->addAction(action1);
    listmenu->addAction(action2);

    connect(action1,SIGNAL(triggered()),this,SLOT(on_actoin_N_triggered()));
    connect(action2,SIGNAL(triggered()),this,SLOT(on_action_D_triggered()));

    listmenu->move(cursor().pos());

    listmenu->show();
}
