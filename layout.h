#ifndef LAYOUT_H
#define LAYOUT_H

#include <QDialog>

namespace Ui {
class Layout;
}

class Layout : public QDialog
{
    Q_OBJECT
    
public:
    explicit Layout(QWidget *parent = 0);
    ~Layout();
    
private:
    Ui::Layout *ui;
};

#endif // LAYOUT_H
