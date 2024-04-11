/* Controller class (following the MVC paradigm) */

#include "main-window.h"
#include "ui_main-window.h"
#include "globals.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    model = new Model(NUM_SITES);

    ui->setupUi(this);

    // ---- Connections ----
    connect(model, SIGNAL(modelChanged()), this, SLOT(render()));


    // Testing
    connect(ui->helloWorldButton, SIGNAL(released()), this, SLOT(helloWorld()));

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::render() {

}

void MainWindow::handleStartSessionButtonPressed()
{

}

void MainWindow::handleSessionLogsButtonPressed()
{

}

void MainWindow::handleTimeAndDateButtonPressed()
{

}

void MainWindow::handleInSessionPauseButtonPressed()
{

}

void MainWindow::handleInSessionStartButtonPressed()
{

}

void MainWindow::handleInSessionStopButtonPressed()
{

}

void MainWindow::handleSessionCompleteBackButtonPressed()
{

}

void MainWindow::handleSessionIncompleteBackButtonPressed()
{

}

void MainWindow::handleSessionLogsBackButtonPressed()
{

}

void MainWindow::handleSessionLogsClearAllButtonPressed()
{

}

void MainWindow::handleSessionLogsUploadAllButtonPressed()
{

}

void MainWindow::handleSaveDateAndTimeChangesButtonPressed()
{

}

void MainWindow::handleDateAndTimeBackButtonPressed()
{

}

void MainWindow::handlePowerButtonPressed()
{

}

void MainWindow::handleComputerSessionSelectedChanged()
{

}

void MainWindow::handleComputerSiteSelectedChanged()
{

}

void MainWindow::handleApplyBandRangeToAllSitesButtonPressed()
{

}

void MainWindow::handleChargeBatteryButtonPressed()
{

}

void MainWindow::handleConnectButtonPressed()
{

}

void MainWindow::handleDisconnectButtonPressed()
{

}

void MainWindow::handleWaveSettingsBandRangeSelectedChanged()
{

}

void MainWindow::handleWaveSettingsSiteSelectedChanged()
{

}


// Testing
void MainWindow::helloWorld() {
    qDebug("Hello world!");
}


