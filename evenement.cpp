#include "evenement.h"
#include "ui_evenement.h"
#include <QMessageBox>
#include <QDateTime>
#include <QDebug>
#include <entite_evenment.h>
#include <QRegularExpression>

//Entite_evenment::Entite_evenment(){}
Evenement::Evenement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Evenement)
{
    ui->setupUi(this);
    ui->tableView->setModel(ev.afficher());
    ui->titre_modif->setEnabled(false);
    ui->date_modif->setEnabled(false);
    ui->description_modif->setEnabled(false);
    ui->category_modif->setEnabled(false);
}

Evenement::~Evenement()
{
    delete ui;
}
// ajouter
void Evenement::on_ajouter_button_clicked()
{
    //int id = ui->id->text().toInt();

    int id =NULL;
    QString titre = ui->titre->text();
    QString category = ui->category->text();
    QString description = ui->description->toPlainText();
    QDateTime date = ui->date->dateTime();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString specialChars = "@#$%&'()*+,-./=<>\±×÷€£¥$@§©®™°^_~₽₹฿";

    if(titre.isEmpty() && category.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champs obligatoires"),
                             QObject::tr("Veuillez saisir un titre et une category."),QMessageBox::Cancel);
        return;
    }
    bool containsSpecialChars = false;

    for (const QChar& ch : titre) {
        if (specialChars.contains(ch)) {
            containsSpecialChars = true;
            break;
        }
    }
    if(containsSpecialChars)
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ non valid"),
                             QObject::tr("veuillez saisir un titre qui ne contient pas des characteres speciaux"),QMessageBox::Cancel);
        return;
    }
    if(titre.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir un titre."),QMessageBox::Cancel);
        return;
    }
    if(category.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir une category."),QMessageBox::Cancel);
        return;
    }
    if (date < currentDateTime) {
        QMessageBox::warning(nullptr, QObject::tr("Champ invalid"),
                             QObject::tr("La date que vous avez saisir est revolue"),QMessageBox::Cancel);
        return;
     }
    Entite_evenment ev (id, titre, category,date, description);
    bool test = ev.ajouter();
    if(test) {
       // ui->id->clear();
        ui->titre->clear();
        ui->description->clear();
        ui->category->clear();
        ui->date->clear();
        ui->tableView->setModel(ev.afficher());
        QMessageBox::information(nullptr,QObject::tr("insertion"),
                               QObject::tr("insertion avec success.\n"),QMessageBox::Cancel);
    }
    else {
        QMessageBox::critical(nullptr,QObject::tr("insertion"),
                               QObject::tr("insertion echoue.\n"),QMessageBox::Cancel);
    }
}
// supprimer
void Evenement::on_supprimer_button_clicked()
{
    int id = ui->id_supprime->text().toInt();
       Entite_evenment ev;  // Declare the object
       ev = ev.rechercher(id);
        if (ev.getId()==-1){
            QMessageBox::critical(nullptr,QObject::tr("delete"),
                                   QObject::tr("delete failed : you must use a an exist id.\n"),QMessageBox::Cancel);
        }
        else {
              bool test = ev.supprimer(id);

                if(test) {
                     ui->tableView->setModel(ev.afficher());
                    QMessageBox::information(nullptr,QObject::tr("suppression"),
                                       QObject::tr("delete succesful.\n"),QMessageBox::Cancel);
                         }
                else {
                        QMessageBox::critical(nullptr,QObject::tr("delete"),
                                       QObject::tr("delete failed.\n"),QMessageBox::Cancel);
                }
        }

}
 //modifier
void Evenement::on_modifier_button_clicked()
{
    int id = ui->id_modif->text().toInt();
    QString titre = ui->titre_modif->text();
    QString category = ui->category_modif->text();
    QDateTime date = ui->date_modif->dateTime();
    QString description = ui->description_modif->toPlainText();
    Entite_evenment em (id, titre, category,date,description);
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString specialChars = "@#$%&'()*+,-./=<>\±×÷€£¥$@§©®™°^_~₽₹฿";
     bool containsSpecialChars = false;
    // controle de saisie
    if(titre.isEmpty() && category.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champs obligatoires"),
                             QObject::tr("Veuillez saisir un titre et une category."),QMessageBox::Cancel);
        return;
    }
    if(titre.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir un titre."),QMessageBox::Cancel);
        return;
    }


    for (const QChar& ch : titre) {
        if (specialChars.contains(ch)) {
            containsSpecialChars = true;
            break;
        }
    }
    if(containsSpecialChars)
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ non valid"),
                             QObject::tr("veuillez saisir un titre qui ne contient pas des characteres speciaux"),QMessageBox::Cancel);
        return;
    }
    if(category.isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Champ obligatoire"),
                             QObject::tr("Veuillez saisir une category."),QMessageBox::Cancel);
        return;
    }
    if (date < currentDateTime) {
        QMessageBox::warning(nullptr, QObject::tr("Champ invalid"),
                             QObject::tr("La date que vous avez saisir est revolue"),QMessageBox::Cancel);
        return;
     }
    bool test = em.modifier();
    if(test) {
        ui->tableView->setModel(ev.afficher());
        //ce block du code pour update affichage ui
        ui->id_modif->setEnabled(true);
        ui->titre_modif->setEnabled(false);
        ui->category_modif->setEnabled(false);
        ui->date_modif->setEnabled(false);
        ui->description_modif->setEnabled(false);
        //fin du code update l affichage ui
        //code pour vider les champs saisie
        ui->id_modif->clear();
        ui->titre_modif->clear();
        ui->description_modif->clear();
        ui->category_modif->clear();
        ui->date_modif->clear();
        // fin du code de vider les champs
        QMessageBox::information(nullptr,QObject::tr("insertion"),
                               QObject::tr("modification avec success.\n"),QMessageBox::Cancel);

    }
    else {
        QMessageBox::critical(nullptr,QObject::tr("insertion"),
                               QObject::tr("modification echoue.\n"),QMessageBox::Cancel);
    }
}

void Evenement::on_Rechercher_button_clicked()
{
    int id = ui->id_modif->text().toInt();
    Entite_evenment ev ;
    ev = ev.rechercher(id);
    if(ev.getId()==-1)
    {
        // handle error
        QMessageBox::critical(nullptr,QObject::tr("Error"),
                               QObject::tr("Vous devez inserer un id existant.\n"),QMessageBox::Cancel);
    }
    else {
        // i will enable the inputs
        ui->titre_modif->setEnabled(true);
        ui->date_modif->setEnabled(true);
        ui->description_modif->setEnabled(true);
        ui->category_modif->setEnabled(true);
        // update the inputs with the data getted from the database
        ui->id_modif->setEnabled(false);
        ui->titre_modif->setText(ev.getTitre());
        ui->date_modif->setDateTime(ev.getDate());
        ui->description_modif->setText(ev.getDescription());
        ui->category_modif->setText(ev.getCategory());

    }

}
