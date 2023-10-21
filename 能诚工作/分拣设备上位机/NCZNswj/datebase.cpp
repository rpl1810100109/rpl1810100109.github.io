#include "datebase.h"
#include "ui_datebase.h"

DateBase::DateBase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DateBase)
{
    ui->setupUi(this);
}

DateBase::~DateBase()
{
    delete ui;
}
