/* Controller class (following the MVC paradigm) */

#include "main-window.h"
#include "ui_main-window.h"
#include "globals.h"
#include <QGraphicsOpacityEffect>
#include <QDebug>
#include <QDate>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      opacityEffectContactLED(new QGraphicsOpacityEffect(NULL)),
      opacityEffectContactLostLED(new QGraphicsOpacityEffect(NULL)),
      opacityEffectTreatmentSignalLED(new QGraphicsOpacityEffect(NULL))
{
    model = Model::Instance();

    ui->setupUi(this);

    // ---- Non-GUI connections ----
    connect(model, SIGNAL(modelChanged()), this, SLOT(render()));

    // --- GUI connections ---
    connect(ui->startSessionButton, SIGNAL(released()), this, SLOT(handleStartSessionButtonPressed()));
    connect(ui->sessionLogsButton, SIGNAL(released()), this, SLOT(handleSessionLogsButtonPressed()));
    connect(ui->timeAndDateButton, SIGNAL(released()), this, SLOT(handleTimeAndDateButtonPressed()));
    connect(ui->inSessionPauseButton, SIGNAL(released()), this, SLOT(handleInSessionPauseButtonPressed()));
    connect(ui->inSessionStartButton, SIGNAL(released()), this, SLOT(handleInSessionStartButtonPressed()));
    connect(ui->inSessionStopButton, SIGNAL(released()), this, SLOT(handleInSessionStopButtonPressed()));
    connect(ui->sessionCompleteBackButton, SIGNAL(released()), this, SLOT(handleSessionCompleteBackButtonPressed()));
    connect(ui->sessionIncompleteBackButton, SIGNAL(released()), this, SLOT(handleSessionIncompleteBackButtonPressed()));
    connect(ui->sessionLogsBackButton, SIGNAL(released()), this, SLOT(handleSessionLogsBackButtonPressed()));
    connect(ui->sessionLogsClearAllButton, SIGNAL(released()), this, SLOT(handleSessionLogsClearAllButtonPressed()));
    connect(ui->sessionLogsUploadAllButton, SIGNAL(released()), this, SLOT(handleSessionLogsUploadAllButtonPressed()));
    connect(ui->saveDateAndTimeChangesButton, SIGNAL(released()), this, SLOT(handleSaveDateAndTimeChangesButtonPressed()));
    connect(ui->dateAndTimeBackButton, SIGNAL(released()), this, SLOT(handleDateAndTimeBackButtonPressed()));
    connect(ui->powerButton, SIGNAL(released()), this, SLOT(handlePowerButtonPressed()));

    connect(ui->computerSessionsList, SIGNAL(itemSelectionChanged()), this, SLOT(handleComputerSessionSelectedChanged()));
    connect(ui->computerSelectSiteDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(handleComputerSiteSelectedChanged()));

    connect(ui->applyBandRangeToAllSitesButton, SIGNAL(released()), this, SLOT(handleApplyBandRangeToAllSitesButtonPressed()));
    connect(ui->chargeBatteryButton, SIGNAL(released()), this, SLOT(handleChargeBatteryButtonPressed()));
    connect(ui->connectButton, SIGNAL(released()), this, SLOT(handleConnectButtonPressed()));
    connect(ui->disconnectButton, SIGNAL(released()), this, SLOT(handleDisconnectButtonPressed()));
    connect(ui->waveSettingsBandRangeDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(handleWaveSettingsBandRangeSelectedChanged()));
    connect(ui->waveSettingsSiteDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(handleWaveSettingsSiteSelectedChanged()));

    // --- Debugging-only connections (delete later) ---
    connect(ui->helloWorldButton, SIGNAL(released()), this, SLOT(helloWorld()));

    init_render();
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::init_render() {
    qDebug("init render.");
    opacityEffectContactLED->setOpacity(opacity);
    opacityEffectContactLostLED->setOpacity(opacity);
    opacityEffectTreatmentSignalLED->setOpacity(opacity);

    ui->contactLED->setGraphicsEffect(opacityEffectContactLED);
    ui->contactLostLED->setGraphicsEffect(opacityEffectContactLostLED);
    ui->treatmentSignalLED->setGraphicsEffect(opacityEffectTreatmentSignalLED);

    render();
}


void MainWindow::render() {
    //qDebug("Rendering.");
    renderNeuresetDevice();
   // renderAdminPanel();
    //renderPC();



}

void MainWindow::renderNeuresetDevice()
{
    NeuresetDevice* neuresetDevice = model->getNeuresetDevice();
    // Neureset device screen. Order of pages set in UI to match order of NeuresetDevice::Screen enum.
    //qDebug("k: %d",neuresetDevice->getCurrentScreen());
    ui->neuresetDeviceScreen->setCurrentIndex((int)neuresetDevice->getCurrentScreen());

    ui->contactLED->graphicsEffect()->setEnabled(true);
    ui->contactLostLED->graphicsEffect()->setEnabled(true);
    ui->treatmentSignalLED->graphicsEffect()->setEnabled(true);

    if (neuresetDevice->getCurrentConnectionStatus() == NeuresetDevice::ConnectionStatus::Contact)
        ui->contactLED->graphicsEffect()->setEnabled(false);
    else if (neuresetDevice->getCurrentConnectionStatus() == NeuresetDevice::ConnectionStatus::ContactLost)
        ui->contactLostLED->graphicsEffect()->setEnabled(false);
    else if (neuresetDevice->getCurrentConnectionStatus() == NeuresetDevice::ConnectionStatus::Treatment)
        ui->treatmentSignalLED->graphicsEffect()->setEnabled(false);

    // Rendering based on current screen (only for screens that need coding logic)
    if (neuresetDevice->getCurrentScreen() == NeuresetDevice::Screen::MainMenu) {
        ui->startSessionButton->setEnabled(neuresetDevice->isConnected());
    }
    else if (neuresetDevice->getCurrentScreen() == NeuresetDevice::Screen::InSession) {
        // Session time elapsed
        //qDebug("%d",neuresetDevice->getCurrentSession()->getElapsedTime());
        int timeInMS = neuresetDevice->getCurrentSession()->getElapsedTime();
        int timeInSEC = timeInMS / 1000;
        ui->sessionTimeLabel->setText(QString("%0").arg(timeInSEC));


        // Progress bar

        // Buttons not clickable


    }
    else if (neuresetDevice->getCurrentScreen() == NeuresetDevice::Screen::SessionCompleted) {

    }
    else if (neuresetDevice->getCurrentScreen() == NeuresetDevice::Screen::SessionErased) {

    }
    else if (neuresetDevice->getCurrentScreen() == NeuresetDevice::Screen::SessionLogs) {

    }
    else if (neuresetDevice->getCurrentScreen() == NeuresetDevice::Screen::DateAndTime) {

    }


}

void MainWindow::renderAdminPanel()
{
    EEGHeadset* eegHeadset = model->getEEGHeadset();

}

void MainWindow::renderPC()
{

}

void MainWindow::handleStartSessionButtonPressed()
{
  model->getNeuresetDevice()->startSession();
  render();
}

void MainWindow::handleSessionLogsButtonPressed()
{
  model->getNeuresetDevice()->setCurrentScreen(NeuresetDevice::Screen::SessionLogs);
  render();
}

void MainWindow::handleTimeAndDateButtonPressed()
{
  model->getNeuresetDevice()->setCurrentScreen(NeuresetDevice::Screen::DateAndTime);
  render();
}

void MainWindow::handleInSessionPauseButtonPressed()
{
    model->getNeuresetDevice()->userPauseSession();
    render();

}

void MainWindow::handleInSessionStartButtonPressed()
{
    model->getNeuresetDevice()->userUnpauseSession();
    render();
}

void MainWindow::handleInSessionStopButtonPressed()
{
  model->getNeuresetDevice()->stopSession();
  render();
}

void MainWindow::handleSessionCompleteBackButtonPressed()
{
  // TODO: Define the steps which ocuur after a Session is completed
  qDebug() << "TODO: Implement MainWindow::handleSessionCompleteBackButtonPressed()";
}

void MainWindow::handleSessionIncompleteBackButtonPressed()
{
  model->getNeuresetDevice()->setCurrentScreen(NeuresetDevice::Screen::MainMenu);
  render();
}

void MainWindow::handleSessionLogsBackButtonPressed()
{
  model->getNeuresetDevice()->setCurrentScreen(NeuresetDevice::Screen::MainMenu);
  render();
}

void MainWindow::handleSessionLogsClearAllButtonPressed()
{
  qDebug() << "TODO: Implement MainWindow::handleSessionLogsClearAllButtonPressed()";
}

void MainWindow::handleSessionLogsUploadAllButtonPressed()
{
  qDebug() << "TODO: Implement MainWindow::handleSessionLogsUploadAllButtonPressed()";
}

void MainWindow::handleSaveDateAndTimeChangesButtonPressed()
{
  // Extract the time and date from the UI elements
  QTime time = ui->timeEdit->time();
  QDate date = ui->dateEdit->date();
  QDateTime dateTime(date, time);

  // Update the devices DateTime.
  model->getNeuresetDevice()->setCurrentDateTime(dateTime);

  qDebug() << "New DateTime:" << dateTime.toString("yyyy-MM-dd hh:mm:ss");
}

void MainWindow::handleDateAndTimeBackButtonPressed()
{
  model->getNeuresetDevice()->setCurrentScreen(NeuresetDevice::Screen::MainMenu);
  render();
}

void MainWindow::handlePowerButtonPressed()
{
  // TODO: Check if screen on/off, if on set to off (and vice versa)
  // TODO: There might be other things to check for (e.g. if a session is running, if so stop it etc.)
  // TODO: Also, the battery shouldn't be draining when the device is off and the light should be off 
  qDebug() << "TODO: Implement MainWindow::handlePowerButtonPressed()";
}

void MainWindow::handleComputerSessionSelectedChanged()
{
  qDebug() << "TODO: Implement MainWindow::handleComputerSessionSelectedChanged()";
}

void MainWindow::handleComputerSiteSelectedChanged()
{
  // TODO: I don't think there is anything keeping track of the selected site yet.
  qDebug() << "TODO: Implement MainWindow::handleComputerSiteSelectedChanged()";

}

void MainWindow::handleApplyBandRangeToAllSitesButtonPressed()
{
  qDebug() << "TODO: Implement MainWindow::handleApplyBandRangeToAllSitesButtonPressed()";
}

void MainWindow::handleChargeBatteryButtonPressed()
{
  qDebug() << "TODO: Implement MainWindow::handleChargeBatteryButtonPressed()";
}

void MainWindow::handleConnectButtonPressed()
{
    model->getEEGHeadset()->connect();
    render();
}

void MainWindow::handleDisconnectButtonPressed()
{
    model->getEEGHeadset()->disconnect();
    render();
}

void MainWindow::handleWaveSettingsBandRangeSelectedChanged()
{
  qDebug() << "TODO: Implement MainWindow::handleWaveSettingsBandRangeSelectedChanged()";
}

void MainWindow::handleWaveSettingsSiteSelectedChanged()
{
  qDebug() << "TODO: Implement MainWindow::handleWaveSettingsSiteSelectedChanged()";

}


// Testing
void MainWindow::helloWorld() {
    qDebug("Hello world!");
}


