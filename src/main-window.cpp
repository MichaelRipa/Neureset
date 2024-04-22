/* Controller class (following the MVC paradigm) */

#include "main-window.h"
#include "ui_main-window.h"
#include "globals.h"
#include "session-log.h"
#include <QGraphicsOpacityEffect>
#include <QDebug>
#include <QDate>
#include <QTime>
#include <QFile>
#include <vector>

bool deleteFile(const QString& filePath) {
    // Helper file which removes the session logs file from previous runs of the program
    QFile file(filePath);
    if (!file.exists()) {
        qDebug() << "File does not exist:" << filePath;
        return false;
    }

    if (file.remove()) {
        qDebug() << "File deleted successfully:" << filePath;
        return true;
    } else {
        qDebug() << "Failed to delete file:" << filePath;
        return false;
    }
}

// Function to extract site index from string format "Site i"
int extractSiteIndex(const QString& siteStr) {
    QRegularExpression re("Site (\\d+)");
    QRegularExpressionMatch match = re.match(siteStr);
    if (match.hasMatch()) {
        return match.captured(1).toInt(); // captured(1) is the first capture group (\d+)
    }
    return -1; // Return -1 or any other invalid index if parsing fails
}

int MainWindow::extractSiteIndexPC() {
  QString selectedSite = ui->computerSelectSiteDropdown->currentText();
  QStringList parts = selectedSite.split(" ");  // Splits at space
  int siteNumber = 1;

  if (parts.size() == 2) {
    bool ok;
    siteNumber = parts.at(1).toInt(&ok);  // Converts the second part to integer
    if (ok) {
      qDebug() << "Site number is:" << siteNumber;
      return siteNumber;
    } else {
      qDebug() << "Conversion failed";
      return -1;
    }
  } else {
    qDebug() << "Unexpected format";
    return -1;
  }
}

void MainWindow::populateBaselinesPC(int siteNumber, int logID) {
  std::vector<SessionLog> logs = model->getNeuresetDevice()->getPCInterface()->loadAllSessionLogs();
  ui->computerBaselineFrequencyBefore->clear();
  ui->computerBaselineFrequencyAfter->clear();
  if (siteNumber - 1 < logs[logID].beforeFrequencies.size() && siteNumber - 1 < logs[logID].afterFrequencies.size()) {
  // Safe to access the first log and its frequency data
      float beforeFrequency = logs[logID].beforeFrequencies[siteNumber - 1];
      float afterFrequency = logs[logID].afterFrequencies[siteNumber - 1];
      // Populate the UI elements
      ui->computerBaselineFrequencyBefore->setText(QString::number(beforeFrequency, 'f', 2));
      ui->computerBaselineFrequencyAfter->setText(QString::number(afterFrequency, 'f', 2));
    } else {
      // Handle cases where there are no logs or siteNumber is out of bounds
      ui->computerBaselineFrequencyBefore->setText("N/A");
      ui->computerBaselineFrequencyAfter->setText("N/A");
      qDebug() << "No available data for the first log or site number out of bounds.";
    }
}

void plotData(const std::vector<std::vector<float>>& waveData, QGraphicsScene* scene) {
    //QGraphicsView* view = new QGraphicsView(scene);
    //view->scale(1000, 1000);



    QPen pen(Qt::blue, 1); // Customize color and line thickness
    scene->setBackgroundBrush(QBrush(Qt::lightGray));  // Light gray background might help in visibility

    for (vector<float> innerData: waveData) {
        for (float ele: innerData) {
            //qDebug() << ele;
        }
       // qDebug() << innerData.size();
    }

  //  exit(0);
    /*qDebug() << "Clearing scene and adding new items";*/
    scene->clear();

    int itemCount = 0; // To count how many lines are added

    // We need at least two points to start drawing lines
    /*
    if (waveData.size() < 2) {
        qDebug() << "Not enough data to plot lines. Need at least two points.";
        return;
    }

    // Ensure each wave data has exactly two floats
    for (size_t i = 0; i < waveData.size(); i++) {
        if (waveData[i].size() != 2) {
            qDebug() << "Skipping wave with incorrect length:" << waveData[i].size();
            continue;
        }
    }
    */
    // Draw lines between consecutive waves
    for (int i = 1; i < waveData.size() / 2; ++i) {
        float x1 =  i - 1; // waveData[i - 1][0];
        float y1 = waveData[i - 1][1] * 300;
        float x2 = i; // waveData[i][0];
        float y2 = waveData[i][1] * 300;

        if (i == 1) {  // Additional debug for first line
            //qDebug() << "Drawing first line from (" << x1 << "," << y1 << ") to (" << x2 << "," << y2 << ")";
        }

        scene->addLine(x1, y1, x2, y2, pen);
        itemCount++;
    }

    /*qDebug() << "Items added to scene:" << itemCount;
    if (itemCount > 0) {
        scene->setSceneRect(scene->itemsBoundingRect());  // Update scene rect to encompass all items
        qDebug() << "Scene rect after update:" << scene->sceneRect();
    } else {
        qDebug() << "No lines were added to the scene.";
    }
    */
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      opacityEffectContactLED(new QGraphicsOpacityEffect(NULL)),
      opacityEffectContactLostLED(new QGraphicsOpacityEffect(NULL)),
      opacityEffectTreatmentSignalLED(new QGraphicsOpacityEffect(NULL))
{
    model = Model::Instance();

    ui->setupUi(this);
    initializeComboBoxes();
    deleteFile(PC_FILENAME);
    renderPC();
    

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

    connect(ui->chargeBatteryButton, SIGNAL(released()), this, SLOT(handleChargeBatteryButtonPressed()));
    connect(ui->connectButton, SIGNAL(released()), this, SLOT(handleConnectButtonPressed()));
    connect(ui->disconnectButton, SIGNAL(released()), this, SLOT(handleDisconnectButtonPressed()));
    connect(ui->waveSettingsBandRangeDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(handleWaveSettingsBandRangeSelectedChanged()));
    connect(ui->waveSettingsSiteDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(handleWaveSettingsSiteSelectedChanged()));

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
    renderAdminPanel();
    //renderPC();



}

void MainWindow::renderNeuresetDevice()
{
    NeuresetDevice* neuresetDevice = model->getNeuresetDevice();

    // Neureset device screen. Order of pages set in UI to match order of NeuresetDevice::Screen enum.
    //qDebug("k: %d",neuresetDevice->getCurrentScreen());
    ui->neuresetDeviceScreen->setCurrentIndex((int)neuresetDevice->getCurrentScreen());

    // Battery
    ui->batteryLevelBar->setValue(neuresetDevice->getBatteryLevel());

    // LED
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
    // No specifics needed
    else if (neuresetDevice->getCurrentScreen() == NeuresetDevice::Screen::SessionCompleted) {

    }
    else if (neuresetDevice->getCurrentScreen() == NeuresetDevice::Screen::SessionErased) {

    }
    else if (neuresetDevice->getCurrentScreen() == NeuresetDevice::Screen::SessionLogs) {

    }
    else if (neuresetDevice->getCurrentScreen() == NeuresetDevice::Screen::DateAndTime) {

    }


}

void MainWindow::renderAdminPanel() {
    EEGHeadset* eegHeadset = model->getEEGHeadset();
    QString siteStr = ui->waveSettingsSiteDropdown->currentText();
    QString bandStr = ui->waveSettingsBandRangeDropdown->currentText();
    Band band = stringToBand(bandStr);
    int siteIndex = extractSiteIndex(siteStr);

    if (!ui->wavePlot->scene()) {
        ui->wavePlot->setScene(new QGraphicsScene(this));
    }

    auto data = eegHeadset->getSignal(siteIndex - 1, band);
    // Adjust these based on your data's typical range
        float horizontalScale = 1.0;  // Adjust this based on the time range or desired horizontal stretch
        float verticalScale = 1.0;    // Adjust this based on the amplitude range

        for (auto& wave : data) {
            for (size_t i = 0; i < wave.size(); i++) {
                if (i % 2 == 0) {  // Even index: x-coordinate (time)
                    wave[i] *= horizontalScale;
                } else {           // Odd index: y-coordinate (amplitude)
                    wave[i] *= verticalScale;
                }
            }
        }
    if (data.empty() || (data.size() > 0 && data[0].empty())) {
        qDebug() << "No data to plot. Data vector is empty or first vector is empty.";
        return;
    }

  /*
    qDebug() << "Data points to plot:" << data.size();
    if (!data.empty()) {
        qDebug() << "Sample data point:" << data[0][0] << "," << data[0][1];
    }
  */

    plotData(data, ui->wavePlot->scene());
    ui->wavePlot->scene()->setSceneRect(ui->wavePlot->scene()->itemsBoundingRect());
    ui->wavePlot->fitInView(ui->wavePlot->scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
    ui->wavePlot->viewport()->update();
    ui->label_5->hide();  // Ensure label is hidden

}

void MainWindow::renderPC()
{
  handleComputerSiteSelectedChanged();
}

void MainWindow::handleStartSessionButtonPressed()
{
  model->getNeuresetDevice()->startSession();
  render();
}

void MainWindow::handleSessionLogsButtonPressed()
{
  model->getNeuresetDevice()->setCurrentScreen(NeuresetDevice::Screen::SessionLogs);
  ui->sessionLogsList->clear();
  std::vector<Session*> allSessions = model->getNeuresetDevice()->getAllSessions();
  if (!allSessions.empty()) {
    // Populate screen with all Sessions stored on NeuresetDevice
    for (size_t i = 0; i < allSessions.size(); ++i) {
      QString formattedDate = allSessions[i]->getStartTime().toString("yyyy-MM-dd.hh:mm");
      QString listItem = QString::number(i+1) + ". " + formattedDate;
      // TODO: Check wherther the frequencies ar estored here
      ui->sessionLogsList->addItem(listItem);
    }
  }
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
  model->getNeuresetDevice()->userStopSession();
  render();
}

void MainWindow::handleSessionCompleteBackButtonPressed()
{
  model->getNeuresetDevice()->setCurrentScreen(NeuresetDevice::Screen::MainMenu);
  render();
  qDebug() << "TODO: Verify MainWindow::handleSessionCompleteBackButtonPressed() doesn't need to perform any additional steps asides from changing screen state and rendering.";
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

  model->getNeuresetDevice()->clearAllSessions();
  ui->sessionLogsList->clear();
  //qDebug() << "TODO: Finish implementing MainWindow::handleSessionLogsClearAllButtonPressed()";
  //qDebug() << "Currently, it clears the sessions directly from NeuresetDevice, it still needs to reflect the changes to the UI";
}

void MainWindow::handleSessionLogsUploadAllButtonPressed() {
qDebug() << "Uploading sessions: (num sessions) - " << model->getNeuresetDevice()->getAllSessions().size();
  model->getNeuresetDevice()->uploadAllSessions();
  handleComputerSiteSelectedChanged();
  handleSessionLogsButtonPressed();
  // Call the handler for displaying the PC logs
  //qDebug() << "TODO: Finish implementing MainWindow::handleSessionLogsUploadAllButtonPressed()";

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
    NeuresetDevice* neuresetDevice = model->getNeuresetDevice();
    // TODO: Check if screen on/off, if on set to off (and vice versa)
    // TODO: There might be other things to check for (e.g. if a session is running, if so stop it etc.)
    // TODO: Also, the battery shouldn't be draining when the device is off and the light should be off
    if (neuresetDevice->isOn())
        neuresetDevice->turnOff();
    else
        neuresetDevice->turnOn();
    render();
}

void MainWindow::handleComputerSessionSelectedChanged() {
    QList<QListWidgetItem*> selectedItems = ui->computerSessionsList->selectedItems();
    if (!selectedItems.isEmpty()) {
        // Get the first selected item
        QListWidgetItem* selectedItem = selectedItems.first();

        // Get the index of the selected item
        int logID = ui->computerSessionsList->row(selectedItem);

        qDebug() << "Selected item index:" << logID;
        int siteNumber = extractSiteIndexPC();
        populateBaselinesPC(siteNumber, logID);
        } else {
            qDebug() << "No item is selected.";
        }
}

void MainWindow::handleComputerSiteSelectedChanged()
{
  int siteNumber = extractSiteIndexPC();

  std::vector<SessionLog> logs = model->getNeuresetDevice()->getPCInterface()->loadAllSessionLogs();
  qDebug() << "Current size of session logs: " << logs.size();
  ui->computerSessionsList->clear();
  ui->computerBaselineFrequencyBefore->clear();
  ui->computerBaselineFrequencyAfter->clear();

  if (!logs.empty()) {
    for (const auto& log : logs) {
      QString formattedDate = log.startTime.toString("yyyy-MM-dd.hh:mm");
      qDebug() << "Extracted date: " << formattedDate;
      QString listItem = QString::number(log.id) + ". " + formattedDate;
      ui->computerSessionsList->addItem(listItem);
    }

    if (siteNumber - 1 < logs[0].beforeFrequencies.size() && siteNumber - 1 < logs[0].afterFrequencies.size()) {
      // Safe to access the first log and its frequency data
      float beforeFrequency = logs[0].beforeFrequencies[siteNumber - 1];
      float afterFrequency = logs[0].afterFrequencies[siteNumber - 1];
      // Populate the UI elements
      ui->computerBaselineFrequencyBefore->setText(QString::number(beforeFrequency, 'f', 2));
      ui->computerBaselineFrequencyAfter->setText(QString::number(afterFrequency, 'f', 2));
    } else {
      // Handle cases where there are no logs or siteNumber is out of bounds
      ui->computerBaselineFrequencyBefore->setText("N/A");
      ui->computerBaselineFrequencyAfter->setText("N/A");
      qDebug() << "No available data for the first log or site number out of bounds.";
    }
  }
  else {
    qDebug() << "No logs to display";
  }

}

void MainWindow::handleChargeBatteryButtonPressed()
{
    model->getNeuresetDevice()->setBatteryLevel(100);
    render();
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
  NeuresetDevice::SessionStatus status = model->getNeuresetDevice()->getCurrentSessionStatus();
  if ((status == NeuresetDevice::SessionStatus::InProgress)) {
    renderAdminPanel();
  }
}

void MainWindow::handleWaveSettingsSiteSelectedChanged()
{
  NeuresetDevice::SessionStatus status = model->getNeuresetDevice()->getCurrentSessionStatus();
  if ((status == NeuresetDevice::SessionStatus::InProgress)) {
   renderAdminPanel();
  }
}

void MainWindow::initializeComboBoxes() {
  // Populate waveSettingsSiteDropdown
  ui->waveSettingsSiteDropdown->clear(); //Clear existing items
  ui->computerSelectSiteDropdown->clear();
  for (int i = 0; i < NUM_SITES; ++i) {
    ui->waveSettingsSiteDropdown->addItem(QString("Site %1").arg(i+1));
    ui->computerSelectSiteDropdown->addItem(QString("Site %1").arg(i+1));
  }

  ui->waveSettingsBandRangeDropdown->clear();

  for (int band = 0; band < static_cast<int>(Band::NUM_BANDS); ++band) {
    ui->waveSettingsBandRangeDropdown->addItem(QString::fromStdString(bandMap(static_cast<Band>(band))));
  }

}



