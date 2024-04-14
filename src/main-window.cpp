/* Controller class (following the MVC paradigm) */

#include "main-window.h"
#include "ui_main-window.h"
#include "globals.h"
#include <QGraphicsOpacityEffect>

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

    if (neuresetDevice->getCurrentLight() == NeuresetDevice::Light::Blue)
        ui->contactLED->graphicsEffect()->setEnabled(false);
    else if (neuresetDevice->getCurrentLight() == NeuresetDevice::Light::Red)
        ui->contactLostLED->graphicsEffect()->setEnabled(false);
    else if (neuresetDevice->getCurrentLight() == NeuresetDevice::Light::Green)
        ui->treatmentSignalLED->graphicsEffect()->setEnabled(false);

    // Rendering based on current screen (only for screens that need coding logic)
    if (neuresetDevice->getCurrentScreen() == NeuresetDevice::Screen::MainMenu) {
        ui->startSessionButton->setEnabled(neuresetDevice->isConnected());
    }
    else if (neuresetDevice->getCurrentScreen() == NeuresetDevice::Screen::InSession) {


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
    model->getEEGHeadset()->setConnected(true);
    render();
}

void MainWindow::handleDisconnectButtonPressed()
{
    model->getEEGHeadset()->setConnected(false);
    render();
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


