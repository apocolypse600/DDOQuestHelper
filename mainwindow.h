#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QtSql>
#include "comboboxdelegate.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void updateColumnVisibility(QString column, bool value);
    void on_checkBoxQuestName_toggled(bool checked);
    void on_checkBoxExtremeChallenge_toggled(bool checked);
    void on_checkBoxPatron_toggled(bool checked);
    void on_checkBoxBaseXP_toggled(bool checked);
    void on_checkBoxQuestLevel_toggled(bool checked);
    void on_checkBoxTotalFavour_toggled(bool checked);
    void on_checkBoxAquiredAt_toggled(bool checked);
    void on_checkBoxBestowedBy_toggled(bool checked);
    void on_checkBoxSolo_toggled(bool checked);
    void on_checkBoxCasualAvailable_toggled(bool checked);
    void on_checkBoxRaid_toggled(bool checked);
    void on_checkBoxAdventurePack_toggled(bool checked);
    void on_checkBoxDifficultyCompleted_toggled(bool checked);

    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionOpen_triggered();
    void on_actionNew_triggered();

    void updateFilters();

    void on_checkBoxHideExtremeChallengeFilter_toggled(bool checked);

    void on_checkBoxHideRaidsFilter_toggled(bool checked);

    void on_checkBoxHideCompletedQuestsFilter_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel *tableModel;
    comboBoxDelegate *delegate;
    QSettings* settings;
    QString filename = "";
    const QString VERSION = "0.1.0";



    int columnIndex(QString name);
};

#endif // MAINWINDOW_H