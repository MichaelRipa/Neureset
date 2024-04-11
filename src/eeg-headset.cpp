#include "eeg-headset.h"

EEGHeadset::EEGHeadset() : contactStatus(false) {}

EEGHeadset::~EEGHeadset() {}

bool EEGHeadset::isConnected() const {
    return contactStatus;
}

std::vector<double> EEGHeadset::getSignal(int siteIndex) {
    // Placeholder implementation
    return std::vector<double>();
}
