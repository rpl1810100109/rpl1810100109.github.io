#ifndef DATEDEAL_H
#define DATEDEAL_H

#include <QWidget>

namespace Ui {
class dateDeal;
}

class dateDeal : public QWidget
{
    Q_OBJECT

public:
    explicit dateDeal(QWidget *parent = nullptr);
    ~dateDeal();

private:
    Ui::dateDeal *ui;
};

#endif // DATEDEAL_H
