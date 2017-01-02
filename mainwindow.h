#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "contact_list.h"
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    CContact_list list;
protected:
    void paintEvent(QPaintEvent *);
    void BuildListWidGet();
    void GetStuffInfo();
    bool TextIsModified();
    void SetTextModified(bool);
    void savefile(QString);
    void loadfile(QString);
private slots:
    void on_actoin_N_triggered();
    void on_action_S_triggered();
    void SetTextInfo();
    void on_stufflist_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_action_D_triggered();
    void contextMenuEvent(QContextMenuEvent *event);
};

#endif // MAINWINDOW_H
