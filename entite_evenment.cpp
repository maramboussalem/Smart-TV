#include "entite_evenment.h"
#include "QDate"
Entite_evenment::Entite_evenment(){
    this->id =-1;
}
Entite_evenment::Entite_evenment(int id,QString titre , QString category,QDateTime date,QString description)
{
    this->id = id;
    this->date =date;
    this->titre =titre;
    this->description =description;
    this->category =category;
};
bool Entite_evenment::ajouter(){
    // todo
    QSqlQuery query ;
    QString res = QString::number(id);
    query.prepare("insert into EVENEMENTS (TITRE,CATEGORY,DESCRIPTION,DATE_EV) values (:titre,:category,:description,:date)");
   // query.bindValue(":id",res);
   // query.bindValue(":date",QDate(date));
    query.bindValue(":titre",titre);
    query.bindValue(":category",category);
    query.bindValue(":description",description);
    query.bindValue(":date",QDateTime(date));
    return query.exec();
};
bool Entite_evenment::supprimer(int id){
    // todo
    QSqlQuery query ;
    QString res = QString::number(id);
    query.prepare("DELETE from EVENEMENTS WHERE ID_EVENMENT =:id");
    query.bindValue(":id",res);
    return query.exec();

};
QSqlQueryModel * Entite_evenment::afficher()
{
    // todo
    QSqlQueryModel * model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM EVENEMENTS");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TITRE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("CATEGORY"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("DESCRIPTION"));
    return model ;
};
bool Entite_evenment::modifier(){
    // todo
    QSqlQuery query ;
    QString res = QString::number(id);
   query.prepare("UPDATE EVENEMENTS SET TITRE = :titre, CATEGORY = :category, DESCRIPTION = :description, DATE_EV=:date  WHERE ID_EVENMENT = :id");
    query.bindValue(":id",res);
    //query.bindValue(":date",QDate(date));
    query.bindValue(":date",date);
    query.bindValue(":titre",titre);
   // query.bindValue(":langue",langue);
    query.bindValue(":category",category);
    query.bindValue(":description",description);
  //  query.bindValue(":horraire",horraire);

    return query.exec();
};
Entite_evenment Entite_evenment::rechercher(int id)
{    QSqlQuery query;
     query.prepare("SELECT * FROM EVENEMENTS WHERE ID_EVENMENT = :id_ev");
     query.bindValue(":id_ev", id);
     query.exec();
     if(query.next())
           {
               int id = query.value(0).toInt();
               QString titre = query.value(1).toString();
               QString description = query.value(2).toString();
               QDateTime date = query.value(3).toDateTime();
               QString category = query.value(4).toString();
               Entite_evenment evenment(id, titre, category, date ,description);
               return evenment;
           }
           // Si aucune émission correspondante n'est trouvée, retourner un objet Emissions vide
     return Entite_evenment();
}

