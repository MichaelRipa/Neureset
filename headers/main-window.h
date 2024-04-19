/*
mainwindow.h:
Serves as the controller in the MVC paradigm between the model (business logic)
and UI. It connects to GUI interactions and other events, tells the underlying model
to update itself, and rerenders.
*/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"
#include <QGraphicsEffect>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Model* model;

    // Opacity effects for turned off neureset LEDs
    // Note: cannot be shared so 3 instances required
    float opacity = 0.25;
    QGraphicsOpacityEffect* opacityEffectContactLED;
    QGraphicsOpacityEffect* opacityEffectContactLostLED;
    QGraphicsOpacityEffect* opacityEffectTreatmentSignalLED;



private slots:

    void helloWorld();
    void init_render(); // Handles any render specific initialization
    void render();
    void renderNeuresetDevice();
    void renderAdminPanel();
    void renderPC();

    // --- Neureset device ---
    void handleStartSessionButtonPressed();
    void handleSessionLogsButtonPressed();
    void handleTimeAndDateButtonPressed();

    void handleInSessionPauseButtonPressed();
    void handleInSessionStartButtonPressed();
    void handleInSessionStopButtonPressed();

    void handleSessionCompleteBackButtonPressed();
    void handleSessionIncompleteBackButtonPressed();


    void handleSessionLogsBackButtonPressed();
    void handleSessionLogsClearAllButtonPressed();
    void handleSessionLogsUploadAllButtonPressed();

    void handleSaveDateAndTimeChangesButtonPressed();
    void handleDateAndTimeBackButtonPressed();

    void handlePowerButtonPressed();

    // --- Computer ---
    void handleComputerSessionSelectedChanged();
    void handleComputerSiteSelectedChanged();


    // --- Admin panel ---
    void handleChargeBatteryButtonPressed();
    void handleConnectButtonPressed();
    void handleDisconnectButtonPressed();

    void handleWaveSettingsBandRangeSelectedChanged();
    void handleWaveSettingsSiteSelectedChanged();
    void initializeComboBoxes();


};
#endif // MAINWINDOW_H
