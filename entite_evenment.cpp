#include "entite_evenment.h"
#include "QDate"
#include "QDebug"
//#include <QtCharts>

Entite_evenment::Entite_evenment(){
    this->id =-1;
}
Entite_evenment::Entite_evenment(int id,QString titre , QString category,QDateTime date,QString description,QString location)
{
    this->id = id;
    this->date =date;
    this->titre =titre;
    this->description =description;
    this->category =category;
    this->location = location;
};
bool Entite_evenment::ajouter(){
    // todo
    QSqlQuery query ;
  //  QString res = QString::number(id);
    query.prepare("insert into EVENEMENTS (TITRE,CATEGORY,DESCRIPTION,DATE_EV) values (:titre,:category,:description,:date)");
   // query.bindValue(":id",res);
   // query.bindValue(":date",QDate(date));
//     query.bindValue(":id",3);
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
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DESCRIPTION"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("CATEGORY"));
    return model ;
};
QSqlQueryModel * Entite_evenment::afficher_selon_titre(QString title)
{
    // todo
    QSqlQueryModel * model = new QSqlQueryModel;
    QSqlQuery query ;
    query.prepare("SELECT * FROM EVENEMENTS WHERE TITRE LIKE '%' || :title || '%'");
    query.bindValue(":title",title);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TITRE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DESCRIPTION"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("CATEGORY"));
    return model ;
};
QSqlQueryModel * Entite_evenment::afficher_Tri(QString category)
{
    // todo
    QSqlQueryModel * model = new QSqlQueryModel;
    QSqlQuery query ;
    query.prepare("SELECT * FROM EVENEMENTS WHERE CATEGORY =:category");
    query.bindValue(":category",category);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TITRE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DESCRIPTION"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("CATEGORY"));
    return model ;
};
// affichage selon date
QSqlQueryModel * Entite_evenment::afficher_Selon_Date(QDate date)
{
    // todo
    QSqlQueryModel * model = new QSqlQueryModel;
    QSqlQuery query ;
    query.prepare("SELECT * FROM EVENEMENTS WHERE DATE_EV =:date");
    query.bindValue(":date",date);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TITRE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DESCRIPTION"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("CATEGORY"));
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
               QString location = query.value(5).toString();
               Entite_evenment evenment(id, titre, category, date ,description,location);
               return evenment;
           }
           // Si aucune émission correspondante n'est trouvée, retourner un objet Emissions vide
     return Entite_evenment();
}
QSqlQueryModel *Entite_evenment::afficher_Selon_Asc(){
    QSqlQueryModel * model = new QSqlQueryModel;
    QSqlQuery query ;
        query.prepare("SELECT * FROM EVENEMENTS ORDER BY DATE_EV ASC");
        query.exec();
        model->setQuery(query);
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("TITRE"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("DESCRIPTION"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("CATEGORY"));
        return model ;
}
QSqlQueryModel *Entite_evenment::afficher_Selon_Desc(){
    QSqlQueryModel * model = new QSqlQueryModel;
    QSqlQuery query ;

        query.prepare("SELECT * FROM EVENEMENTS ORDER BY DATE_EV DESC");
        query.exec();
        model->setQuery(query);
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("TITRE"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("DESCRIPTION"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("CATEGORY"));
        return model ;
}
//QString Entite_evenment::locationById(int id){
//    QSqlQuery query;
//         query.prepare("SELECT LOCATION FROM EVENEMENTS WHERE ID_EVENMENT = :id_ev");
//         query.bindValue(":id_ev", id);
//         query.exec();
//         if(query.next()){
//             QString location = query.value(0).toString();
//             return location;
//         }
//}
// statistique
//void Entite_evenment::statistique(){
//    QSqlQuery query("SELECT categorie, COUNT(*) FROM emissions GROUP BY categorie");
//            QtCharts::QBarSeries *series = new QtCharts::QBarSeries();

//            while (query.next())
//            {
//                QString categorie = query.value(0).toString();
//                int count = query.value(1).toInt();

//                QtCharts::QBarSet *set = new QtCharts::QBarSet(categorie); // Utilisez la catégorie comme libellé
//                *set << count;

//                series->append(set);
//            }

//            QtCharts::QChart *chart = new QtCharts::QChart();
//            chart->addSeries(series);
//            chart->setTitle("Nombre d'émissions par catégorie");
//            chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

//            QStringList categories;
//            categories << "Catégories"; // Ajoutez les noms de vos catégories ici

//            QtCharts::QBarCategoryAxis *axis = new QtCharts::QBarCategoryAxis();
//            axis->append(categories);
//            chart->createDefaultAxes();
//            chart->setAxisX(axis, series);
//            chart->legend()->setVisible(true);

//            QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
//            chartView->resize(900, 600);
//            chartView->show();

//}
//void displayStatistics() {

//        QSqlQuery query("SELECT category, COUNT(*) AS count FROM events GROUP BY category");

//        // Prepare data for chart
//        QBarSet *set = new QBarSet("Count");
//        while (query.next()) {
//            *set << query.value("count").toInt();
//            categories << query.value("category").toString();
//        }

//        // Create bar series
//        QBarSeries *series = new QBarSeries();
//        series->append(set);

//        // Create chart
//        QChart *chart = new QChart();
//        chart->addSeries(series);
//        chart->setTitle("Event Statistics by Category");

//        // Create categories axis
//        QBarCategoryAxis *axisX = new QBarCategoryAxis();
//        axisX->append(categories);
//        chart->createDefaultAxes();
//        chart->setAxisX(axisX, series);

//        // Create chart view and set it as central widget
//        QChartView *chartView = new QChartView(chart);
//        setCentralWidget(chartView);
//    }


