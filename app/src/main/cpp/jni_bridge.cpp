#include <jni.h>
#include "frida_detector.h"
#include <android/log.h>

#define LOG_TAG "FridaBlockerJNI"

#define LOGD(...) do { \
    if (FridaDetector::isDebugLoggingEnabled()) { \
        __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__); \
    } \
} while(0)

extern "C" {

JNIEXPORT jboolean JNICALL
Java_ca_weblite_fridablocker_FridaDetector_nativeDetectFrida(JNIEnv *env, jclass clazz) {
    LOGD("Native Frida detection called");
    FridaDetector::DetectionResult result = FridaDetector::performDetection();
    return static_cast<jboolean>(result.fridaDetected);
}

JNIEXPORT jobject JNICALL
Java_ca_weblite_fridablocker_FridaDetector_nativeGetDetailedDetection(JNIEnv *env, jclass clazz) {
    LOGD("Native detailed Frida detection called");
    
    FridaDetector::DetectionResult result = FridaDetector::performDetection();
    
    // Find the DetectionResult class
    jclass detectionResultClass = env->FindClass("ca/weblite/fridablocker/DetectionResult");
    if (detectionResultClass == nullptr) {
        LOGD("Failed to find DetectionResult class");
        return nullptr;
    }
    
    // Get the constructor
    jmethodID constructor = env->GetMethodID(detectionResultClass, "<init>", "(ZZZZZZ)V");
    if (constructor == nullptr) {
        LOGD("Failed to find DetectionResult constructor");
        return nullptr;
    }
    
    // Create the Java object
    jobject detectionResultObj = env->NewObject(detectionResultClass, constructor,
        static_cast<jboolean>(result.fridaDetected),
        static_cast<jboolean>(result.processDetection),
        static_cast<jboolean>(result.portDetection),
        static_cast<jboolean>(result.libraryDetection),
        static_cast<jboolean>(result.fileDetection),
        static_cast<jboolean>(result.environmentDetection)
    );
    
    return detectionResultObj;
}

JNIEXPORT jboolean JNICALL
Java_ca_weblite_fridablocker_FridaDetector_nativeCheckProcesses(JNIEnv *env, jclass clazz) {
    return static_cast<jboolean>(FridaDetector::checkFridaProcesses());
}

JNIEXPORT jboolean JNICALL
Java_ca_weblite_fridablocker_FridaDetector_nativeCheckPorts(JNIEnv *env, jclass clazz) {
    return static_cast<jboolean>(FridaDetector::checkFridaPorts());
}

JNIEXPORT jboolean JNICALL
Java_ca_weblite_fridablocker_FridaDetector_nativeCheckLibraries(JNIEnv *env, jclass clazz) {
    return static_cast<jboolean>(FridaDetector::checkFridaLibraries());
}

JNIEXPORT jboolean JNICALL
Java_ca_weblite_fridablocker_FridaDetector_nativeCheckFiles(JNIEnv *env, jclass clazz) {
    return static_cast<jboolean>(FridaDetector::checkFridaFiles());
}

JNIEXPORT jboolean JNICALL
Java_ca_weblite_fridablocker_FridaDetector_nativeCheckEnvironment(JNIEnv *env, jclass clazz) {
    return static_cast<jboolean>(FridaDetector::checkFridaEnvironment());
}

JNIEXPORT void JNICALL
Java_ca_weblite_fridablocker_FridaDetector_nativeSetDebugLogging(JNIEnv *env, jclass clazz, jboolean enabled) {
    FridaDetector::setDebugLogging(static_cast<bool>(enabled));
}

} // extern "C"