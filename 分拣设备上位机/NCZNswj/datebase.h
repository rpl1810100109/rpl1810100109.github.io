#ifndef DATEBASE_H
#define DATEBASE_H

#include <QWidget>

namespace Ui {
class DateBase;
}

class DateBase : public QWidget
{
    Q_OBJECT

public:
    explicit DateBase(QWidget *parent = nullptr);
    ~DateBase();

private:
    Ui::DateBase *ui;
};

#endif // DATEBASE_H
