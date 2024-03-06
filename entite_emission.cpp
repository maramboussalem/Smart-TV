#include "entite_emission.h"
#include<QDate>

Entite_emission::Entite_emission(int id,QString titre , QString category,QString realisateur,QString date,QString duree,QString description ,QString horraire)
{
  this->id = id;
  this->titre = titre;
  this->category = category;
  this->realisateur = realisateur;
   // this->langue = langue;
    this->date = date;
    this->duree = duree;
    this->description = description ;
    this->horraire = horraire ;
};
bool Entite_emission::ajouter(){
    // todo
    QSqlQuery query ;
    QString res = QString::number(id);
    query.prepare("insert into EMISSIONS (ID_EMISSION,TITRE,CATEGORIE,DURE,REALISATEUR,DESCRIPTION) values (:id,:titre,:category,:duree,:realisateur,:description)");
    query.bindValue(":id",res);
   // query.bindValue(":date",QDate(date));
    query.bindValue(":titre",titre);
   // query.bindValue(":langue",langue);
    query.bindValue(":realisateur",realisateur);
    query.bindValue(":category",category);
    query.bindValue(":description",description);
  //  query.bindValue(":horraire",horraire);

    return query.exec();
};
bool Entite_emission::supprimer(int id){
    // todo
    QSqlQuery query ;
    QString res = QString::number(id);
    query.prepare("DELETE from EMISSIONS WHERE ID_EMISSION =:id");
    query.bindValue(":id",res);
    return query.exec();

};
QSqlQueryModel * Entite_emission::afficher()
{
    // todo
    QSqlQueryModel * model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM EMISSIONS");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("TITRE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("CATEGORY"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("DURE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("REALISATEUR"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("DESCRIPTION"));
    return model ;
};
bool Entite_emission::modifier(){
    // todo
    QSqlQuery query ;
    QString res = QString::number(id);
   query.prepare("UPDATE EMISSIONS SET TITRE = :titre, CATEGORIE = :category, DURE = :duree, REALISATEUR = :realisateur, DESCRIPTION = :description WHERE ID_EMISSION = :id");
    query.bindValue(":id",res);
   // query.bindValue(":date",QDate(date));
    query.bindValue(":titre",titre);
   // query.bindValue(":langue",langue);
    query.bindValue(":realisateur",realisateur);
    query.bindValue(":category",category);
    query.bindValue(":description",description);
  //  query.bindValue(":horraire",horraire);

    return query.exec();
};
