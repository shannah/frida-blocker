package ca.weblite.fridablocker;

/**
 * DetectionResult holds the results of Frida detection checks.
 * Each field represents a different detection method.
 */
public class DetectionResult {
    
    /** Overall result - true if any detection method found Frida */
    public final boolean fridaDetected;
    
    /** True if Frida processes were detected */
    public final boolean processDetection;
    
    /** True if Frida network ports were detected */
    public final boolean portDetection;
    
    /** True if Frida libraries were detected in memory */
    public final boolean libraryDetection;
    
    /** True if Frida files were detected on filesystem */
    public final boolean fileDetection;
    
    /** True if Frida environment variables were detected */
    public final boolean environmentDetection;
    
    /**
     * Constructor for DetectionResult.
     * @param fridaDetected Overall detection result
     * @param processDetection Process detection result
     * @param portDetection Port detection result
     * @param libraryDetection Library detection result
     * @param fileDetection File detection result
     * @param environmentDetection Environment detection result
     */
    public DetectionResult(boolean fridaDetected, boolean processDetection, 
                          boolean portDetection, boolean libraryDetection,
                          boolean fileDetection, boolean environmentDetection) {
        this.fridaDetected = fridaDetected;
        this.processDetection = processDetection;
        this.portDetection = portDetection;
        this.libraryDetection = libraryDetection;
        this.fileDetection = fileDetection;
        this.environmentDetection = environmentDetection;
    }
    
    /**
     * Returns a summary of which detection methods found Frida.
     * @return String describing active detections
     */
    public String getSummary() {
        if (!fridaDetected) {
            return "No Frida detected";
        }
        
        StringBuilder summary = new StringBuilder("Frida detected via: ");
        boolean first = true;
        
        if (processDetection) {
            if (!first) summary.append(", ");
            summary.append("processes");
            first = false;
        }
        if (portDetection) {
            if (!first) summary.append(", ");
            summary.append("ports");
            first = false;
        }
        if (libraryDetection) {
            if (!first) summary.append(", ");
            summary.append("libraries");
            first = false;
        }
        if (fileDetection) {
            if (!first) summary.append(", ");
            summary.append("files");
            first = false;
        }
        if (environmentDetection) {
            if (!first) summary.append(", ");
            summary.append("environment");
            first = false;
        }
        
        return summary.toString();
    }
    
    @Override
    public String toString() {
        return String.format(
            "DetectionResult{fridaDetected=%b, process=%b, port=%b, library=%b, file=%b, env=%b}",
            fridaDetected, processDetection, portDetection, libraryDetection, 
            fileDetection, environmentDetection
        );
    }
}