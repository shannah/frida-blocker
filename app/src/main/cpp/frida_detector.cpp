#include "frida_detector.h"
#include <string>
#include <vector>
#include <fstream>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <android/log.h>

#define LOG_TAG "FridaDetector"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

namespace FridaDetector {

bool checkFridaProcesses() {
    const std::vector<std::string> fridaProcessNames = {
        "frida-server",
        "frida-agent",
        "frida-gadget",
        "frida-portal"
    };
    
    DIR* procDir = opendir("/proc");
    if (!procDir) {
        LOGE("Failed to open /proc directory");
        return false;
    }
    
    struct dirent* entry;
    while ((entry = readdir(procDir)) != nullptr) {
        if (entry->d_type == DT_DIR) {
            std::string pid = entry->d_name;
            if (pid != "." && pid != ".." && isdigit(pid[0])) {
                std::string cmdlinePath = "/proc/" + pid + "/cmdline";
                std::ifstream cmdlineFile(cmdlinePath);
                if (cmdlineFile.is_open()) {
                    std::string cmdline;
                    std::getline(cmdlineFile, cmdline);
                    cmdlineFile.close();
                    
                    for (const auto& fridaProcess : fridaProcessNames) {
                        if (cmdline.find(fridaProcess) != std::string::npos) {
                            LOGD("Detected Frida process: %s", cmdline.c_str());
                            closedir(procDir);
                            return true;
                        }
                    }
                }
            }
        }
    }
    closedir(procDir);
    return false;
}

bool checkFridaPorts() {
    const std::vector<int> commonFridaPorts = {27042, 27043, 27044, 27045};
    
    std::ifstream netFile("/proc/net/tcp");
    if (!netFile.is_open()) {
        LOGE("Failed to open /proc/net/tcp");
        return false;
    }
    
    std::string line;
    while (std::getline(netFile, line)) {
        for (int port : commonFridaPorts) {
            char hexPort[16];
            snprintf(hexPort, sizeof(hexPort), ":%04X ", port);
            if (line.find(hexPort) != std::string::npos) {
                LOGD("Detected Frida on port: %d", port);
                netFile.close();
                return true;
            }
        }
    }
    netFile.close();
    return false;
}

bool checkFridaLibraries() {
    const std::vector<std::string> fridaLibraries = {
        "frida-agent",
        "frida-gadget",
        "libfrida",
        "frida.so"
    };
    
    std::ifstream mapsFile("/proc/self/maps");
    if (!mapsFile.is_open()) {
        LOGE("Failed to open /proc/self/maps");
        return false;
    }
    
    std::string line;
    while (std::getline(mapsFile, line)) {
        for (const auto& lib : fridaLibraries) {
            if (line.find(lib) != std::string::npos) {
                LOGD("Detected Frida library in memory: %s", line.c_str());
                mapsFile.close();
                return true;
            }
        }
    }
    mapsFile.close();
    return false;
}

bool checkFridaFiles() {
    const std::vector<std::string> fridaFiles = {
        "/data/local/tmp/frida-server",
        "/data/local/tmp/frida-agent",
        "/system/bin/frida-server",
        "/system/lib/frida-gadget.so",
        "/system/lib64/frida-gadget.so"
    };
    
    for (const auto& file : fridaFiles) {
        struct stat buffer;
        if (stat(file.c_str(), &buffer) == 0) {
            LOGD("Detected Frida file: %s", file.c_str());
            return true;
        }
    }
    return false;
}

bool checkFridaEnvironment() {
    const char* fridaEnvVars[] = {
        "FRIDA_AGENT_PATH",
        "FRIDA_SCRIPT_RUNTIME",
        "FRIDA_TARGET_PID"
    };
    
    for (const char* envVar : fridaEnvVars) {
        if (getenv(envVar) != nullptr) {
            LOGD("Detected Frida environment variable: %s", envVar);
            return true;
        }
    }
    return false;
}

DetectionResult performDetection(bool debug) {
    DetectionResult result = {};
    
    if (debug) {
        LOGD("Starting Frida detection with debug logging...");
    } else {
        LOGD("Starting Frida detection...");
    }
    
    result.processDetection = checkFridaProcesses();
    if (debug && result.processDetection) {
        LOGD("DEBUG: Process detection returned POSITIVE");
    }
    
    result.portDetection = checkFridaPorts();
    if (debug && result.portDetection) {
        LOGD("DEBUG: Port detection returned POSITIVE");
    }
    
    result.libraryDetection = checkFridaLibraries();
    if (debug && result.libraryDetection) {
        LOGD("DEBUG: Library detection returned POSITIVE");
    }
    
    result.fileDetection = checkFridaFiles();
    if (debug && result.fileDetection) {
        LOGD("DEBUG: File detection returned POSITIVE");
    }
    
    result.environmentDetection = checkFridaEnvironment();
    if (debug && result.environmentDetection) {
        LOGD("DEBUG: Environment detection returned POSITIVE");
    }
    
    result.fridaDetected = result.processDetection || 
                          result.portDetection || 
                          result.libraryDetection || 
                          result.fileDetection || 
                          result.environmentDetection;
    
    if (debug) {
        LOGD("DEBUG: Final results - Process: %s, Port: %s, Library: %s, File: %s, Environment: %s",
             result.processDetection ? "POSITIVE" : "NEGATIVE",
             result.portDetection ? "POSITIVE" : "NEGATIVE", 
             result.libraryDetection ? "POSITIVE" : "NEGATIVE",
             result.fileDetection ? "POSITIVE" : "NEGATIVE",
             result.environmentDetection ? "POSITIVE" : "NEGATIVE");
    }
    
    if (result.fridaDetected) {
        LOGD("Frida detection: POSITIVE");
    } else {
        LOGD("Frida detection: NEGATIVE");
    }
    
    return result;
}

} // namespace FridaDetector