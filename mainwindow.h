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

    void save();
    void saveAs();
    void open();
    void loadFile(QString filepath);
    void newFile();
    void openRecentFile();

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

    QMenu *fileMenu;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;
    QAction *separatorAct;
    void updateRecentFiles();
    void updateRecentFileActions();
    QString stripName(const QString fullFilePath);


    //const int MAX_RECENT_FILES = 5;
    enum { MAX_RECENT_FILES = 5 };
    QAction *recentFileActs[MAX_RECENT_FILES];

    QString filename = "";
    const QString VERSION = "0.1.0";


    void createActions();
    void createMenus();
    int columnIndex(QString name);
};

#endif // MAINWINDOW_H
