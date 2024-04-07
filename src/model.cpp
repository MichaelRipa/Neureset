/* Model class (following the MVC paradigm) */

#include "model.h"


int Model::handleEventsFrequency = 100;


Model::Model()
    : handleEventsTimer(new QTimer(this))
{

    // Set up callback connections
    connect(handleEventsTimer, SIGNAL(timeout()), this, SLOT(handleEvents()));

    handleEventsTimer->start(handleEventsFrequency);
}


Model::~Model()
{
}


void Model::handleEvents()
{
    qDebug("Handling events.");
}
