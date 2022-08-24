#include "datedeal.h"
#include "ui_datedeal.h"

dateDeal::dateDeal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dateDeal)
{
    ui->setupUi(this);
}

dateDeal::~dateDeal()
{
    delete ui;
}
