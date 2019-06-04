#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secondwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Login, SIGNAL(released()), this,SLOT(on_pushButton_Login_clicked()));
    connect(ui->reg, SIGNAL(released()), this,SLOT(on_pushButton_reg_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool login(QString username, QString password){
    QFile file("C:\\Users\\TALGAT PC\\Documents\\loogiin\\database.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(nullptr, "OSHIBKA!!!", file.errorString());
    }
    QTextStream in(&file);
    QString data = username+":"+password;

    while(!in.atEnd()) {
        QString line = in.readLine();
        if(line==data){
            return true;
        }
    }
    return false;
};

void MainWindow::on_Login_clicked()
{
    QString username = ui->username->text();
    QString password = ui->password->text();
    bool auth = login(username, password);


    if(auth) {
        hide();
        SecondWindow *s=new SecondWindow();
        s->show();
    }
    else {
        QMessageBox::warning(this,"Login", "Not correct");
    }
}

void MainWindow::on_reg_clicked()
{
    hide();
    Registration *r = new Registration();
    r->show();
}

void MainWindow::on_password_textEdited(const QString &arg1)
{
    ui->password->setEchoMode(QLineEdit::Password);
}

void MainWindow::on_radioButton_clicked(bool checked)
{
    if(checked == true){
        ui->password->setEchoMode(QLineEdit::Normal);
    }else {
        ui->password->setEchoMode(QLineEdit::Password);
    }
}

