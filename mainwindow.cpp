#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlTableModel>
#include <QtCore>
#include <QtGui>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("DDO Quest Helper " + VERSION);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("ddoQuestDatabase.db");

    //TODO handle this better
    if (!db.open())
    {
        qDebug() << "error opening DB";
    }
    else
    {
        qDebug() <<"opened db";
    }

    tableModel = new QSqlTableModel(this,db);
    tableModel->setTable("questList");
    tableModel->setEditStrategy(QSqlTableModel::OnFieldChange);

    tableModel->select();
    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableView->setSortingEnabled(true);

    ui->tableView->setModel(tableModel);

    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //center the tabs in the tab widget
    ui->tabWidget->setStyleSheet("QTabWidget::tab-bar{alignment:center;}");

    settings = new QSettings("ddoQuestHelper.ini", QSettings::IniFormat);

    //Read the bools from the config, hide columns that need to be hidden
    //Setting the checked status also triggers the signal to hide the columns as needed
    if (!settings->value("Columns/questNameVisible").toBool()) { ui->checkBoxQuestName->setChecked(false); }
    if (!settings->value("Columns/baseXPVisible").toBool()) { ui->checkBoxBaseXP->setChecked(false); }
    if (!settings->value("Columns/questLevelVisible").toBool()) { ui->checkBoxQuestLevel->setChecked(false); }
    if (!settings->value("Columns/totalFavourVisible").toBool()) { ui->checkBoxTotalFavour->setChecked(false); }
    if (!settings->value("Columns/patronVisible").toBool()) { ui->checkBoxPatron->setChecked(false); }
    if (!settings->value("Columns/aquiredAtVisible").toBool()) { ui->checkBoxAquiredAt->setChecked(false); }
    if (!settings->value("Columns/bestowedByVisible").toBool()) { ui->checkBoxBestowedBy->setChecked(false); }
    if (!settings->value("Columns/soloVisible").toBool()) { ui->checkBoxSolo->setChecked(false); }
    if (!settings->value("Columns/casualAvailableVisible").toBool() ) { ui->checkBoxCasualAvailable->setChecked(false); }
    if (!settings->value("Columns/raidVisible").toBool() ) { ui->checkBoxRaid->setChecked(false); }
    if (!settings->value("Columns/extemeChallengeVisible").toBool()) {ui->checkBoxExtremeChallenge->setChecked(false); }
    if (!settings->value("Columns/adventurePackVisible").toBool()) { ui->checkBoxAdventurePack->setChecked(false); }
    if (!settings->value("Columns/difficultyCompletedVisible").toBool()) { ui->checkBoxDifficultyCompleted->setChecked(false); }

    ui->checkBoxHideExtremeChallengeFilter->setChecked(settings->value("Misc/hideExtremeChallenge").toBool());
    ui->checkBoxHideRaidsFilter->setChecked(settings->value("Misc/hideRaids").toBool());
    ui->checkBoxHideCompletedQuestsFilter->setChecked(settings->value("Misc/hideCompleted").toBool());
    updateFilters();

    delegate = new comboBoxDelegate(this);
    //TODO fix the 12 when moved to an enum
    ui->tableView->setItemDelegateForColumn(12, delegate);

    connect(ui->spinBoxMaxLevel, SIGNAL(valueChanged(int)),this,SLOT(updateFilters()));
    connect(ui->spinBoxMinLevel, SIGNAL(valueChanged(int)),this,SLOT(updateFilters()));
    connect(ui->checkBoxHideCompletedQuestsFilter, SIGNAL(clicked(bool)),this,SLOT(updateFilters()));
    connect(ui->checkBoxHideRaidsFilter, SIGNAL(clicked(bool)),this,SLOT(updateFilters()));
    connect(ui->checkBoxHideExtremeChallengeFilter, SIGNAL(clicked(bool)),this,SLOT(updateFilters()));
    connect(ui->lineEditNameFilter, SIGNAL(textChanged(QString)),this,SLOT(updateFilters()));

    /*for ( int i = 0; i < tableModel->rowCount(); ++i )
    {
        //TODO fix the 12 when moved to an enum
        ui->tableView->openPersistentEditor( tableModel->index(i, 12, QModelIndex()) );
    }*/

    //TODO This needs to check if the path is actually valid before loading it
    //The data is cached into the database since the last run
    if(settings->value("Recent/recentFile1").toString() != "")
    {
        filename=settings->value("Recent/recentFile1").toString();
        setWindowTitle("DDO Quest Helper " + VERSION + " - " + filename);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateColumnVisibility(QString column, bool value)
{
    settings->setValue("Columns/" + column + "visible", value);

    if (value)
    {
        ui->tableView->showColumn(columnIndex(column));
    }
    else
    {
        ui->tableView->hideColumn(columnIndex(column));
    }

}

//TODO Replace this total mess with a proper enum
int MainWindow::columnIndex(QString name)
{
    //Can't use a case statement because it's a string
    if ( name == "questName" )
    {
        return 0;
    }
    else if ( name  == "baseXP" )
    {
        return 1;
    }
    else if ( name  == "questLevel" )
    {
        return 2;
    }
    else if ( name == "totalFavour" )
    {
        return 3;
    }
    else if ( name == "patron" )
    {
        return 4;
    }
    else if ( name == "aquiredAt" )
    {
        return 5;
    }
    else if ( name == "bestowedBy" )
    {
        return 6;
    }
    else if ( name == "solo" )
    {
        return 7;
    }
    else if ( name == "casualAvailable" )
    {
        return 8;
    }
    else if ( name == "raid" )
    {
        return 9;
    }
    else if ( name == "extremeChallenge")
    {
        return 10;
    }
    else if (name == "adventurePack")
    {
        return 11;
    }
    else if (name == "difficultyCompleted" )
    {
        return 12;
    }
    else
    {
        return -1;
    }

}

//TODO make this cleaner. There has to be a better way to pass the name of the column into the function.
void MainWindow::on_checkBoxQuestName_toggled(bool checked)
{
    updateColumnVisibility("questName",checked);
}

void MainWindow::on_checkBoxBaseXP_toggled(bool checked)
{
    updateColumnVisibility("baseXP",checked);
}

void MainWindow::on_checkBoxQuestLevel_toggled(bool checked)
{
    updateColumnVisibility("questLevel",checked);
}

void MainWindow::on_checkBoxTotalFavour_toggled(bool checked)
{
    updateColumnVisibility("totalFavour",checked);
}

void MainWindow::on_checkBoxPatron_toggled(bool checked)
{
    updateColumnVisibility("patron",checked);
}

void MainWindow::on_checkBoxAquiredAt_toggled(bool checked)
{
    updateColumnVisibility("aquiredAt",checked);
}

void MainWindow::on_checkBoxBestowedBy_toggled(bool checked)
{
    updateColumnVisibility("bestowedBy",checked);
}

void MainWindow::on_checkBoxSolo_toggled(bool checked)
{
    updateColumnVisibility("solo",checked);
}

void MainWindow::on_checkBoxCasualAvailable_toggled(bool checked)
{
    updateColumnVisibility("casualAvailable",checked);
}

void MainWindow::on_checkBoxRaid_toggled(bool checked)
{
    updateColumnVisibility("raid",checked);
}

void MainWindow::on_checkBoxExtremeChallenge_toggled(bool checked)
{
    updateColumnVisibility("extremeChallenge",checked);
}

void MainWindow::on_checkBoxAdventurePack_toggled(bool checked)
{
    updateColumnVisibility("adventurePack",checked);
}

void MainWindow::on_checkBoxDifficultyCompleted_toggled(bool checked)
{
    updateColumnVisibility("difficultyCompleted",checked);
}

void MainWindow::on_actionSave_triggered()
{
    if(filename != "")
    {

        QFile sFile(filename);
        if(sFile.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream out(&sFile);

            for ( int i = 0; i < tableModel->rowCount(); ++i )
            {
                //TODO More magic numbers
                //Output name of quest, and completion state
                out <<  tableModel->index(i,0,QModelIndex()).data().toString() << '\n'
                    <<  tableModel->index(i,12,QModelIndex()).data().toString() << '\n';
            }


            sFile.flush();
            sFile.close();

        }

        //TODO write a nice wrapper to save 5 or so previous files
        settings->setValue("Recent/recentFile1",filename);
        setWindowTitle("DDO Quest Helper " + VERSION);

    }
    else
    {
        on_actionSave_As_triggered();
    }

}

void MainWindow::on_actionSave_As_triggered()
{
    QString readFilename = QFileDialog::getSaveFileName(this,"Save as");

    if(!readFilename.isEmpty())
    {
        filename = readFilename;
        on_actionSave_triggered();
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString readFilename = QFileDialog::getOpenFileName(this,"Open a file");

    if(!readFilename.isEmpty())
    {
        QFile sFile(readFilename);
        if(sFile.open(QFile::ReadOnly | QFile::Text))
        {
            filename = readFilename;

            QTextStream in(&sFile);

            //Start the transaction with the database. If we do all the edits in one transaction it goes much, much faster
            db.transaction();

            for ( int i = 0; i < tableModel->rowCount(); ++i )
            {
                //TODO More magic numbers
                //Read in name of quest, and completion state

                QString questName = in.readLine();
                QString difficultyCompleted = in.readLine();

                QString query = "UPDATE questList SET DifficultyCompleted='" + difficultyCompleted + "' WHERE Name='" + questName + "'";

                qDebug() << query;
                db.exec(query);
            }

            db.commit();


            sFile.close();
        }

    }

    //update the view
    tableModel->select();

    setWindowTitle("DDO Quest Helper " + VERSION + " - " + filename);

    //TODO write a nice wrapper to save 5 or so previous files
    settings->setValue("Recent/recentFile1",filename);
}

void MainWindow::on_actionNew_triggered()
{
    filename = "";
    setWindowTitle("DDO Quest Helper " + VERSION);

    db.exec("UPDATE questList SET DifficultyCompleted='Not Completed'");

    tableModel->select();
}

void MainWindow::updateFilters()
{
    QString filter = "Name LIKE '%" + ui->lineEditNameFilter->text() + "%' AND Level<='" + QString::number(ui->spinBoxMaxLevel->value()) + "'" + "AND Level>='" + QString::number(ui->spinBoxMinLevel->value()) + "'";

    if (ui->checkBoxHideCompletedQuestsFilter->isChecked())
    {
        filter += " AND DifficultyCompleted<>'Elite' AND DifficultyCompleted<>'Solo'";
    }

    if ( ui->checkBoxHideExtremeChallengeFilter->isChecked())
    {
        filter += " AND ExtremeChallenge<>1";
    }

    if ( ui->checkBoxHideRaidsFilter->isChecked())
    {
        filter += " AND Raid<>1";
    }

    qDebug() <<"New Filter:" << filter;
    tableModel->setFilter(filter);
    //tableModel->select();
}

void MainWindow::on_checkBoxHideExtremeChallengeFilter_toggled(bool checked)
{
    settings->setValue("Misc/hideExtremeChallenge",checked);
}

void MainWindow::on_checkBoxHideRaidsFilter_toggled(bool checked)
{
    settings->setValue("Misc/hideRaids",checked);
}

void MainWindow::on_checkBoxHideCompletedQuestsFilter_toggled(bool checked)
{
    settings->setValue("Misc/hideCompleted",checked);
}
