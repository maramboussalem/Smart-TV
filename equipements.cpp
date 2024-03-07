#include "equipements.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

equipements::equipements()
{
    id_equipement = 0;
    reference = "";
    type = "";
    quantite = "";
    prix = "";
}

equipements::equipements(int id_equipement, QString reference, QString type, QString quantite, QString prix)
{
    this->id_equipement = id_equipement;
    this->reference = reference;
    this->type = type;
    this->quantite = quantite;
    this->prix = prix;
}
//get
int equipements::getID_equipement(){return id_equipement;}
QString equipements::getRefrence(){return reference;}
QString equipements::getType(){return type;}
QString equipements::getQuantite(){return quantite;}
QString equipements::getPrix(){return prix;}

//set
void equipements::setID_equipement(int id){id_equipement=id;}
void equipements::setRefrence(QString ref){reference=ref;}
void equipements::setType(QString tp){type=tp;}
void equipements::setQuantite(QString quant){quantite=quant;}
void equipements::setPrix(QString pr){prix=pr;}

bool equipements::ajouter()
{
    // Vérification des champs obligatoires
     if (reference.isEmpty() || type.isEmpty() || quantite.isEmpty() || prix.isEmpty()) {
         qDebug() << "Erreur : Tous les champs doivent être renseignés.";
         return false;
     }
    QSqlQuery query;
        QString res = QString::number(id_equipement);

        query.prepare("insert into equipements (id_equipement, reference, type, quantite, prix) "
                      "values (:id_equipement, :reference, :type, :quantite, :prix)");

        query.bindValue(":id_equipement", id_equipement);  // Use the integer directly
        query.bindValue(":reference", reference);
        query.bindValue(":type", type);
        query.bindValue(":quantite", quantite);
        query.bindValue(":prix", prix);

        return query.exec();
}

bool equipements::supprimer(int id_equipement)
{ // Vérification de l'ID
    if (id_equipement <= 0) {
        qDebug() << "Erreur : L'ID de l'équipement doit être un entier positif.";
        return false;
    }

    QSqlQuery query;
        QString res = QString::number(id_equipement);

        query.prepare("delete from equipements where id_equipement = :id_equipement");

        query.bindValue(":id_equipement", res);  // Corrected the parameter name

        return query.exec();
}

QSqlQueryModel * equipements::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from equipements");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_equipement"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("reference"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("quantite"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));

    return model;
}

bool equipements::modifier(int id_equipement, QString reference, QString type, QString quantite, QString prix)
{
    // Vérification des champs obligatoires
     if (reference.isEmpty() || type.isEmpty() || quantite.isEmpty() || prix.isEmpty()) {
         qDebug() << "Erreur : Tous les champs doivent être renseignés.";
         return false;
     }


    QSqlQuery query;
    query.prepare("UPDATE equipements SET reference = :reference, type = :type, quantite = :quantite, prix = :prix WHERE id_equipement = :id_equipement");
    query.bindValue(":id_equipement", id_equipement);
    query.bindValue(":reference", reference);
    query.bindValue(":type", type);
    query.bindValue(":quantite", quantite);
    query.bindValue(":prix", prix);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Erreur lors de la modification :" << query.lastError().text();
        return false;
    }
}


equipements equipements::rechercherEquipement(int id_equipement)
{
    QSqlQuery query;
       query.prepare("SELECT * FROM equipements WHERE id_equipement = :id_equipement");
       query.bindValue(":id_equipement", id_equipement);
       query.exec();

       if (query.next())
       {
           int id = query.value(0).toInt();
           QString reference = query.value(1).toString();
           QString type = query.value(2).toString();
           QString quantite = query.value(3).toString();
           QString prix = query.value(4).toString();

           qDebug() << "ID:" << id << "Reference:" << reference << "Type:" << type << "Quantite:" << quantite << "Prix:" << prix;

           equipements e(id, reference, type, quantite, prix);
           return e;
       }

       qDebug() << "Equipement non trouvé avec l'ID:" << id_equipement;
       return equipements();
}