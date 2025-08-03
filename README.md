# FridaBlocker

[![CI](https://github.com/shannah/FridaBlocker/actions/workflows/ci.yml/badge.svg)](https://github.com/shannah/FridaBlocker/actions/workflows/ci.yml)
[![Maven Central](https://img.shields.io/maven-central/v/ca.weblite/fridablocker.svg?label=Maven%20Central)](https://search.maven.org/search?q=g:%22ca.weblite%22%20AND%20a:%22fridablocker%22)

An Android native library for detecting Frida instrumentation framework. This defensive security library helps protect Android applications from dynamic analysis and runtime manipulation.

## Features

- **Native C++ Implementation** - Harder to bypass than Java-only solutions
- **Multi-layer Detection** - Comprehensive detection across multiple vectors
- **Cross-platform** - Supports all Android architectures (ARM64, ARM32, x86, x86_64)
- **Easy Integration** - Simple Gradle dependency with minimal setup
- **Zero Dependencies** - Only requires androidx.appcompat

## Detection Methods

- **Process Detection** - Scans for frida-server and related processes
- **Port Detection** - Checks for Frida on common network ports (27042-27045)
- **Library Detection** - Scans memory maps for loaded Frida libraries
- **File Detection** - Checks filesystem for Frida binaries and libraries
- **Environment Detection** - Scans for Frida-related environment variables

## Installation

### Maven Central (Recommended)

Add to your app's `build.gradle`:

```gradle
dependencies {
    implementation 'ca.weblite:fridablocker:1.0.0'
}
```

### Local Development

For local development or custom builds:

```gradle
dependencies {
    implementation files('libs/fridablocker-1.0.0.aar')
    implementation 'androidx.appcompat:appcompat:1.7.1'
}
```

## Usage

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
            // Handle security threat
            Log.w("Security", "Frida instrumentation detected!");
            handleSecurityThreat();
        }
    }
    
    private void handleSecurityThreat() {
        // Implement your security response:
        // - Clear sensitive data
        // - Log to analytics
        // - Graceful degradation
        // - App termination (if appropriate)
    }
}
```

### Detailed Detection

```java
import ca.weblite.fridablocker.DetectionResult;

DetectionResult result = FridaDetector.getDetailedDetection();

if (result.fridaDetected) {
    Log.w("Security", result.getSummary());
    
    // Check specific detection methods
    if (result.processDetection) {
        Log.w("Security", "Frida processes detected");
    }
    if (result.libraryDetection) {
        Log.w("Security", "Frida libraries detected in memory");
    }
    // ... handle other detection types
}
```

### Individual Detection Methods

```java
// Test specific detection methods
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
- **Native:** ARM64, ARM32, x86, x86_64 support

## Security Considerations

1. **Obfuscation:** Consider obfuscating detection calls to make them harder to identify
2. **Multiple Checks:** Perform detection at various points in your app lifecycle
3. **Graceful Response:** Don't just terminate - consider logging and data protection
4. **Defense in Depth:** Use alongside other security measures

## Building from Source

### Prerequisites

- Java 17+ (Java 21 recommended)
- Android Studio or Android SDK
- NDK (automatically downloaded)
- CMake 3.22.1+ (automatically installed)

### Build Commands

```bash
# Build the library
JAVA_HOME=/path/to/java21 ./gradlew build

# Run tests
./gradlew test

# Publish to local Maven repository
./gradlew publishToMavenLocal
```

### GitHub Actions

This repository includes automated CI/CD workflows:

- **CI Workflow** - Runs tests on every push/PR
- **Publish Workflow** - Publishes to Maven Central on releases

## Publishing to Maven Central

The library is automatically published to Maven Central via GitHub Actions when a new release is created.

### Required Secrets

Set these secrets in your GitHub repository:

- `MAVEN_CENTRAL_USERNAME` - Your Maven Central Portal username
- `MAVEN_CENTRAL_PASSWORD` - Your Maven Central Portal token
- `SIGNING_KEY` - Your GPG private key (base64 encoded)
- `SIGNING_PASSWORD` - Your GPG key passphrase

### Manual Publishing

```bash
# Set environment variables
export MAVEN_CENTRAL_USERNAME="your-username"
export MAVEN_CENTRAL_PASSWORD="your-token"
export SIGNING_KEY="your-base64-encoded-private-key"
export SIGNING_PASSWORD="your-key-password"

# Publish
./gradlew publishReleasePublicationToCentralRepository
```

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests if applicable
5. Submit a pull request

## License

This project is licensed under the Apache License 2.0 - see the [LICENSE](LICENSE) file for details.

## Disclaimer

This library is intended for defensive security purposes only. It should be used to protect legitimate applications from unauthorized analysis and manipulation. The authors are not responsible for any misuse of this software.

## Support

- Report issues on [GitHub Issues](https://github.com/shannah/FridaBlocker/issues)
- For security vulnerabilities, please email steve@weblite.ca

## Acknowledgments

- Built for the Android security community
- Uses modern Android NDK and CMake
- Follows Maven Central publishing best practices