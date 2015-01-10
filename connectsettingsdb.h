#ifndef CONNECTSETTINGSDB_H
#define CONNECTSETTINGSDB_H

#include <QDialog>

namespace Ui {
class ConnectSettingsDB;
}

class ConnectSettingsDB : public QDialog
{
    Q_OBJECT
    
public:
    explicit ConnectSettingsDB(QWidget *parent = 0);
    ~ConnectSettingsDB();
    
private:
 //   Ui::ConnectSettingsDB *ui;
};

#endif // CONNECTSETTINGSDB_H
