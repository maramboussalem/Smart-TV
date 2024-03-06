#ifndef EMISSION_H
#define EMISSION_H
#include "entite_emission.h"
#include <QDialog>

namespace Ui {
class Emission;
}

class Emission : public QDialog
{
    Q_OBJECT

public:
    explicit Emission(QWidget *parent = nullptr);
    ~Emission();

private slots:
    void on_pushButton_9_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::Emission *ui;
    Entite_emission em;
};

#endif // EMISSION_H
