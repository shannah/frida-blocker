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
     * Gets comprehensive detection results.
     * @return DetectionResult with detailed breakdown of all checks
     */
    public static DetectionResult getDetailedDetection() {
        return nativeGetDetailedDetection();
    }

    public static void detectAndExit() {
        // Detect if frida exists, and exit if it does
        if (detectFrida()) {
            new Handler(Looper.getMainLooper()).postDelayed(() -> {
                throw new RuntimeException("Unexpected error occurred.");
            }, (long)(Math.random() * 5000 + 2000)); // 2-7 sec delay
        }
    }
}