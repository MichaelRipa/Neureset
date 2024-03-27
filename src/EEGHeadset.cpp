#include "EEGHeadset.h"

EEGHeadset::EEGHeadset() : contactStatus(false) {}

EEGHeadset::~EEGHeadset() {}

bool EEGHeadset::checkContact() const {
    return contactStatus;
}

double EEGHeadset::getSignal() {
    // Placeholder implementation
    return 0.0;
}
