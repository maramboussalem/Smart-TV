#include "menu.h"
#include "ui_menu.h"

#include "employee.h"
#include "emission.h"
#include "evenement.h"
#include "publicite.h"
#include "sponsors.h"
#include "equipement.h"

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_pushButtonEmployee_clicked()
{
Employee employeeDialog;
employeeDialog.exec();
}

void Menu::on_pushButtonEmission_clicked()
{
Emission emissionDialog;
emissionDialog.exec();
}

void Menu::on_pushButtonEvenement_clicked()
{
Evenement evenementDialog;
evenementDialog.exec();
}

void Menu::on_pushButtonPublicite_clicked()
{
 Publicite publiciteDialog;
 publiciteDialog.exec();
}

void Menu::on_pushButtonSponsors_clicked()
{
Sponsors sponsorsDialog;
sponsorsDialog.exec();
}

void Menu::on_pushButtonEquipement_clicked()
{
Equipement equipementDialog;
equipementDialog.exec();
}
