/* Controller class (following the MVC paradigm) */

#include "main-window.h"
#include "ui_main-window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    model = new Model();

    ui->setupUi(this);

    // ---- Connections ----

    // Testing
    connect(ui->helloWorldButton, SIGNAL(released()), this, SLOT(helloWorld()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

// Testing
void MainWindow::helloWorld() {
    qDebug("Hello world!");
}
