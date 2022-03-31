#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "necessiteux.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <ActiveQt/qaxobject.h>
#include <ActiveQt/qaxbase.h>
#include <QMessageBox>
#include <QIntValidator>
#include "excelexporthelper.h"
#include <QFile>
#include <stdexcept>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->age->setValidator(new QIntValidator(0, 9999999, this));
    ui->id->setValidator(new QIntValidator(0, 9999999, this));
    ui->tel->setValidator(new QIntValidator(0, 9999999, this));
    ui->tableView->setModel(nes.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_4_clicked()
{
    QString id=ui->id->text();
    QString nom=ui->nom->text();
    QString sexe=ui->sexe->text();
    QString age=ui->age->text();
    QString tel=ui->tel->text();
    QString adresse=ui->adresse->text();
    QString besoin=ui->besoin->text();
    QString mbr=ui->mbr->text();
    QString date=ui->date->text();

    NECESSITEUX e(id,nom,sexe,age,tel,adresse,besoin,mbr,date);
    if (nom.isEmpty()||adresse.isEmpty()||id==0)
    {
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                 QObject::tr("Case Obligatoire!\n"),QMessageBox::Cancel );
    }
    else
        if(!(nom.contains(QRegExp("^[A-Za-z]+$"))))
                {

                    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                             QObject::tr("Veuillez entrer une chaine!\n"
                                                         "Click Cancel to exit. "),QMessageBox::Cancel);

                }
        else
            if(sexe != "femme" && sexe !="homme")
                    {

                        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                                 QObject::tr("Veuillez entrer homme ou femme!\n"
                                                             "Click Cancel to exit. "),QMessageBox::Cancel);

                    }
    else
        {
            e.ajouter();
            ui->tableView->setModel(nes.afficher());

        }

}










void MainWindow::on_pushButton_7_clicked()
{

    QString id=ui->lineEdit_supp->text();
    NECESSITEUX e ;
    e.supprimer(id);

    ui->tableView->setModel(nes.afficher());
}


void MainWindow::on_pushButton_2_clicked()
{
    QString id=ui->lineEdit->text();
    QString nom=ui->lineEdit_2->text();
    QString sexe=ui->lineEdit_3->text();
    QString age=ui->lineEdit_4->text();
    QString tel=ui->lineEdit_5->text();
    QString adresse=ui->lineEdit_6->text();
    QString besoin=ui->lineEdit_7->text();
    QString mbr=ui->spinBox->text();

    QString date=ui->dateEdit->text();

    NECESSITEUX e(id,nom,sexe,age,tel,adresse,besoin,mbr,date);
    ui->age->setValidator(new QIntValidator(0, 9999999, this));
    ui->id->setValidator(new QIntValidator(0, 9999999, this));
    ui->tel->setValidator(new QIntValidator(0, 9999999, this));

        if(!(nom.contains(QRegExp("^[A-Za-z]+$||nom.isEmpty()"))))
                {

                    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                             QObject::tr("Veuillez entrer une chaine!\n"
                                                         "Click Cancel to exit. "),QMessageBox::Cancel);

                }
        else
            if(sexe != "femme" && sexe !="homme")
                    {

                        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                                 QObject::tr("Veuillez entrer homme ou femme!\n"
                                                             "Click Cancel to exit. "),QMessageBox::Cancel);

                    }
        else{
            bool test = e.modifier(id);
            if (test)
            {
               ui->tableView->setModel(nes.afficher());
               QMessageBox::information(nullptr,QObject::tr("OK"),
                                        QObject::tr("Edit done"),QMessageBox::Cancel );
            }
            else
            {
                QMessageBox::critical(nullptr , QObject::tr("OK"),
                                      QObject::tr("Edit impossible") , QMessageBox::Cancel );
            }
        }

        }


void MainWindow::on_pushButton_8_clicked()
{
    QString nom =ui->lineEdit_9->text();


    if (nom!="")
        ui->tableView->setModel(nes.rechercher(nom));
    else
        ui->tableView->setModel(nes.afficher());

}

void MainWindow::on_pushButton_clicked()
{
     QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM NECESSITEUX ORDER BY MBR_FAMILLE ASC ;");
             ui->tableView->setModel(model);
}

void MainWindow::on_excel_clicked()
{
    try
            {
                const QString fileName = "c:\\test.xlsx";

                ExcelExportHelper helper;
    int l=2;
                QSqlQuery q;
                if(q.exec("SELECT * FROM membres"))
                {
    helper.SetCellValue(1,1,"ID");
    helper.SetCellValue(1,2,"NOM");
    helper.SetCellValue(1,3,"PRENOM");
    helper.SetCellValue(1,4,"USERNAME");
    helper.SetCellValue(1,5,"EMAIL");
    helper.SetCellValue(1,6,"MDP");
    helper.SetCellValue(1,7,"NBPOINTS");
    helper.SetCellValue(1,8,"BRANCHE");
                    while (q.next())
                    {

                helper.SetCellValue(l,1,q.value(0).toString());
                helper.SetCellValue(l,2,q.value(1).toString());
                helper.SetCellValue(l,3,q.value(2).toString());
                helper.SetCellValue(l,4,q.value(3).toString());
                helper.SetCellValue(l,5,q.value(4).toString());
                helper.SetCellValue(l,6,q.value(5).toString());
                helper.SetCellValue(l,7,q.value(6).toString());
                helper.SetCellValue(l,8,q.value(7).toString());
    l++;

                    }
                helper.SaveAs(fileName);
            }}
            catch (const exception& e)
            {
                QMessageBox::critical(this, "Error - Demo", e.what());
            }
}
