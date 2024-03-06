#ifndef ENTITE_EMISSION_H
#define ENTITE_EMISSION_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class Entite_emission
{
private:
    int id;
    QString titre, category, duree, realisateur, date, description, horraire;

public:
    Entite_emission();
    Entite_emission(int,QString,QString,QString,QString,QString,QString, QString);
    // Getters
//    QString getTitre() const { return titre; }
//    QString getCategory() const { return category; }
//    QString getDuree() const { return duree; }
//    QString getLangue() const { return langue; }
//    QString getRealisateur() const { return realisateur; }
//    QString getDate() const { return date; }
//    int getId() const { return id; }

//    // Setters
//    void setTitre( QString t) { this->titre = t; }
//    void setCategory(QString c) {this->category = c; }
//    void setDuree( QString d) { this->duree = d; }
//    void setLangue(QString l) { this->langue = l; }
//    void setRealisateur( QString &r) { this->realisateur = r; }
//    void setDate(const QString d) { this->date = d; }
    // CRUD functionality
    bool ajouter();
    bool supprimer(int);
    QSqlQueryModel *afficher();
    bool modifier ();
};
#endif
