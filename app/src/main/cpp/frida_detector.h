#ifndef FRIDA_DETECTOR_H
#define FRIDA_DETECTOR_H

namespace FridaDetector {

struct DetectionResult {
    bool fridaDetected;
    bool processDetection;
    bool portDetection;
    bool libraryDetection;
    bool fileDetection;
    bool environmentDetection;
};

// Individual detection methods
bool checkFridaProcesses();
bool checkFridaPorts();
bool checkFridaLibraries();
bool checkFridaFiles();
bool checkFridaEnvironment();

// Main detection function
DetectionResult performDetection();

// Debug logging control
void setDebugLogging(bool enabled);
bool isDebugLoggingEnabled();

} // namespace FridaDetector

#endif // FRIDA_DETECTOR_H