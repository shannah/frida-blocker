package ca.weblite.fridablocker;

import android.os.Handler;
import android.os.Looper;

/**
 * FridaDetector provides methods to detect Frida instrumentation framework.
 * This class uses JNI to call native C++ code for detection.
 */
public class FridaDetector {
    
    static {
        System.loadLibrary("fridablocker");
    }
    
    /**
     * Performs a comprehensive Frida detection check.
     * @return true if Frida is detected, false otherwise
     */
    public static native boolean nativeDetectFrida();
    
    /**
     * Gets detailed detection results for all checks.
     * @return DetectionResult object with detailed information
     */
    public static native DetectionResult nativeGetDetailedDetection();
    
    /**
     * Performs a comprehensive Frida detection check with debug logging.
     * @param debug if true, enables detailed debug logging for each test
     * @return true if Frida is detected, false otherwise
     */
    public static native boolean nativeDetectFridaWithDebug(boolean debug);
    
    /**
     * Gets detailed detection results for all checks with debug logging.
     * @param debug if true, enables detailed debug logging for each test
     * @return DetectionResult object with detailed information
     */
    public static native DetectionResult nativeGetDetailedDetectionWithDebug(boolean debug);
    
    /**
     * Checks for Frida processes running on the system.
     * @return true if Frida processes are detected
     */
    public static native boolean nativeCheckProcesses();
    
    /**
     * Checks for Frida on common network ports.
     * @return true if Frida ports are detected
     */
    public static native boolean nativeCheckPorts();
    
    /**
     * Checks for Frida libraries loaded in memory.
     * @return true if Frida libraries are detected
     */
    public static native boolean nativeCheckLibraries();
    
    /**
     * Checks for Frida files on the filesystem.
     * @return true if Frida files are detected
     */
    public static native boolean nativeCheckFiles();
    
    /**
     * Checks for Frida environment variables.
     * @return true if Frida environment variables are detected
     */
    public static native boolean nativeCheckEnvironment();
    
    /**
     * High-level method to detect Frida using all available methods.
     * @return true if Frida is detected by any method
     */
    public static boolean detectFrida() {
        return nativeDetectFrida();
    }
    
    /**
     * High-level method to detect Frida using all available methods with debug logging.
     * @param debug if true, enables detailed debug logging for each test
     * @return true if Frida is detected by any method
     */
    public static boolean detectFrida(boolean debug) {
        return nativeDetectFridaWithDebug(debug);
    }
    
    /**
     * Gets comprehensive detection results.
     * @return DetectionResult with detailed breakdown of all checks
     */
    public static DetectionResult getDetailedDetection() {
        return nativeGetDetailedDetection();
    }
    
    /**
     * Gets comprehensive detection results with debug logging.
     * @param debug if true, enables detailed debug logging for each test
     * @return DetectionResult with detailed breakdown of all checks
     */
    public static DetectionResult getDetailedDetection(boolean debug) {
        return nativeGetDetailedDetectionWithDebug(debug);
    }

    public static void detectAndExit() {
        detectAndExit(false);
    }

    public static void detectAndExit(boolean debug) {
        // Detect if frida exists, and exit if it does
        if (detectFrida(debug)) {
            new Handler(Looper.getMainLooper()).postDelayed(() -> {
                throw new RuntimeException("Unexpected error occurred.");
            }, (long)(Math.random() * 5000 + 2000)); // 2-7 sec delay
        }
    }
}