# FridaBlocker Library Usage Guide

This guide explains how to include the FridaBlocker library in your Android applications as a Gradle dependency.

## Integration Methods

### Method 1: Maven Central (Recommended)

The easiest way to include FridaBlocker in your project:

```gradle
dependencies {
    implementation 'ca.weblite:fridablocker:1.0.0'
}
```

That's it! The library and its dependencies will be automatically downloaded.

### Method 2: Local Maven Repository (For Development)

If you have the FridaBlocker project locally, you can publish it to your local Maven repository:

1. **Build and publish the library:**
   ```bash
   cd /path/to/FridaBlocker
   JAVA_HOME=/path/to/java21 ./gradlew publishToMavenLocal
   ```

2. **Add to your app's `build.gradle`:**
   ```gradle
   dependencies {
       implementation 'ca.weblite:fridablocker:1.0.0'
   }
   ```

### Method 3: Local Project Repository

1. **Copy the published AAR to your project:**
   ```bash
   # After building FridaBlocker
   cp FridaBlocker/build/repo/ca/weblite/fridablocker/1.0.0/fridablocker-1.0.0.aar your-project/libs/
   ```

2. **Add to your app's `build.gradle`:**
   ```gradle
   dependencies {
       implementation files('libs/fridablocker-1.0.0.aar')
       
       // Required dependencies
       implementation 'androidx.appcompat:appcompat:1.7.1'
   }
   ```

### Method 4: Local Maven Repository in Project

1. **Copy the entire Maven repository to your project:**
   ```bash
   cp -r FridaBlocker/build/repo your-project/local-repo
   ```

2. **Add repository to your project's `build.gradle` (project level):**
   ```gradle
   allprojects {
       repositories {
           google()
           mavenCentral()
           maven { url "local-repo" }  // Add this line
       }
   }
   ```

3. **Add dependency to your app's `build.gradle`:**
   ```gradle
   dependencies {
       implementation 'ca.weblite:fridablocker:1.0.0'
   }
   ```

## Library Usage

### Basic Detection

```java
import ca.weblite.fridablocker.FridaDetector;

public class MainActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        // Simple Frida detection
        boolean fridaDetected = FridaDetector.detectFrida();
        
        if (fridaDetected) {
            // Handle Frida detection - terminate app, show warning, etc.
            Log.w("Security", "Frida instrumentation detected!");
            finish();
        } else {
            Log.i("Security", "No Frida detected, app is secure");
        }
    }
}
```

### Detailed Detection

```java
import ca.weblite.fridablocker.FridaDetector;
import ca.weblite.fridablocker.DetectionResult;

public class SecurityChecker {
    
    public static void performSecurityCheck() {
        DetectionResult result = FridaDetector.getDetailedDetection();
        
        if (result.fridaDetected) {
            Log.w("Security", "Frida detected: " + result.getSummary());
            
            // Check specific detection methods
            if (result.processDetection) {
                Log.w("Security", "Frida processes detected");
            }
            if (result.portDetection) {
                Log.w("Security", "Frida network ports detected");
            }
            if (result.libraryDetection) {
                Log.w("Security", "Frida libraries detected in memory");
            }
            if (result.fileDetection) {
                Log.w("Security", "Frida files detected on filesystem");
            }
            if (result.environmentDetection) {
                Log.w("Security", "Frida environment variables detected");
            }
            
            // Take appropriate action
            handleFridaDetection();
        }
    }
    
    private static void handleFridaDetection() {
        // Implement your security response
        // Examples: terminate app, clear sensitive data, notify server, etc.
    }
}
```

### Individual Detection Methods

```java
// Check specific detection methods individually
boolean processDetected = FridaDetector.nativeCheckProcesses();
boolean portDetected = FridaDetector.nativeCheckPorts();
boolean libraryDetected = FridaDetector.nativeCheckLibraries();
boolean fileDetected = FridaDetector.nativeCheckFiles();
boolean envDetected = FridaDetector.nativeCheckEnvironment();
```

## Requirements

- **Min SDK:** 21 (Android 5.0)
- **Target SDK:** 35 (Android 15)
- **Java:** Compatible with Java 8+
- **Native Libraries:** Includes native libraries for ARM64, ARM32, x86, and x86_64

## Dependencies

The library has minimal dependencies:
- `androidx.appcompat:appcompat` (for Android compatibility)

## Security Considerations

1. **Obfuscation:** Consider obfuscating your app and the FridaBlocker calls to make them harder to bypass.

2. **Multiple Checks:** Perform detection checks at multiple points in your app lifecycle, not just at startup.

3. **Response Strategy:** Don't just terminate the app - consider logging to analytics, clearing sensitive data, or implementing a graceful degradation.

4. **Anti-Tampering:** The native library makes it harder to hook detection methods, but determined attackers may still find ways to bypass detection.

## Example Anti-Tampering Implementation

```java
public class SecurityManager {
    private static final String TAG = "SecurityManager";
    
    public static boolean isAppSecure() {
        try {
            // Perform detection
            DetectionResult result = FridaDetector.getDetailedDetection();
            
            if (result.fridaDetected) {
                // Log to analytics service
                Analytics.logSecurityEvent("frida_detected", result.getSummary());
                
                // Clear sensitive data
                clearSensitiveData();
                
                return false;
            }
            
            return true;
        } catch (Exception e) {
            // If detection fails, assume compromise
            Log.e(TAG, "Security check failed", e);
            return false;
        }
    }
    
    private static void clearSensitiveData() {
        // Clear tokens, credentials, cached data, etc.
    }
}
```

## Building from Source

If you need to modify the library:

1. **Clone and build:**
   ```bash
   git clone <repo-url>
   cd FridaBlocker
   JAVA_HOME=/path/to/java21 ./gradlew build
   ```

2. **Publish locally:**
   ```bash
   JAVA_HOME=/path/to/java21 ./gradlew publishToMavenLocal
   ```

3. **Customize detection logic** in `app/src/main/cpp/frida_detector.cpp`

## Troubleshooting

### Build Issues
- Ensure you're using Java 17+ for building
- Make sure Android NDK is installed
- Check that CMake 3.22.1+ is available

### Runtime Issues
- Verify your app's minSdk is at least 21
- Check that the native library is included in your APK
- Enable logging to see detection details in logcat

### False Positives
- Test on various devices and Android versions
- Consider adjusting detection thresholds if needed
- Some development tools may trigger false positives