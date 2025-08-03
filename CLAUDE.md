# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

FridaBlocker is an Android application project designed as a defensive security tool. The project uses modern Android development practices with Gradle build system and follows standard Android project structure.

**Package Name**: `ca.weblite.fridablocker`
**Min SDK**: 16 (Android 4.1)
**Target SDK**: 35 (Android 15)
**Java Version**: 11

## Build Commands

### Building the Project
```bash
./gradlew build
```

### Running Tests
```bash
# Run unit tests
./gradlew test

# Run instrumented tests (requires connected device/emulator)
./gradlew connectedAndroidTest

# Run all tests
./gradlew check
```

### Installing the App
```bash
# Install debug build
./gradlew installDebug

# Install release build
./gradlew installRelease
```

### Cleaning the Project
```bash
./gradlew clean
```

### Assembling APKs
```bash
# Build debug APK
./gradlew assembleDebug

# Build release APK
./gradlew assembleRelease
```

## Project Architecture

### Module Structure
- **app/**: Main application module containing all source code and resources
- **gradle/**: Gradle configuration including version catalogs (`libs.versions.toml`)

### Source Organization
- **Main source**: `app/src/main/java/ca/weblite/fridablocker/`
- **Unit tests**: `app/src/test/java/ca/weblite/fridablocker/`
- **Instrumented tests**: `app/src/androidTest/java/ca/weblite/fridablocker/`
- **Resources**: `app/src/main/res/`
- **Manifest**: `app/src/main/AndroidManifest.xml`

### Key Configuration Files
- **Root build.gradle**: Top-level build configuration
- **app/build.gradle**: App module build configuration with dependencies and Android settings
- **gradle/libs.versions.toml**: Centralized dependency version management
- **settings.gradle**: Project structure and repository configuration

### Dependencies
The project uses modern Android libraries:
- AndroidX AppCompat for backward compatibility
- Material Design Components
- JUnit for unit testing
- Espresso for UI testing

## JNI Native Library

This project includes a native C++ library for Frida detection that compiles to `libfridablocker.so`.

### Native Library Features
- **Frida Process Detection**: Scans for frida-server and related processes
- **Port Detection**: Checks for Frida on common network ports (27042-27045)
- **Library Detection**: Scans memory maps for loaded Frida libraries
- **File Detection**: Checks filesystem for Frida binaries and libraries
- **Environment Detection**: Scans for Frida-related environment variables

### JNI Interface
The native code is accessible through Java via the `FridaDetector` class:
```java
// Simple detection
boolean detected = FridaDetector.detectFrida();

// Detailed detection with breakdown
DetectionResult result = FridaDetector.getDetailedDetection();
```

### Build Requirements
- **Java**: Requires Java 17+ (tested with Java 21)
- **NDK**: Android NDK is automatically downloaded during build
- **CMake**: Version 3.22.1 (automatically installed)
- **Min SDK**: 21 (required for NDK compatibility)

### Native Build Commands
```bash
# Build native library with Java 21
JAVA_HOME=/Users/shannah/Library/Java/JavaVirtualMachines/azul-21.0.6/Contents/Home ./gradlew build

# Clean native build
./gradlew clean

# Build only native components
./gradlew externalNativeBuild
```

### Library Output
The build generates `libfridablocker.so` for all target architectures:
- `arm64-v8a` (64-bit ARM)
- `armeabi-v7a` (32-bit ARM) 
- `x86` (32-bit Intel)
- `x86_64` (64-bit Intel)

## Library Distribution

### Publishing Commands
```bash
# Publish to local Maven repository (~/.m2/repository)
JAVA_HOME=/Users/shannah/Library/Java/JavaVirtualMachines/azul-21.0.6/Contents/Home ./gradlew publishToMavenLocal

# Publish to project's local repository (build/repo)
JAVA_HOME=/Users/shannah/Library/Java/JavaVirtualMachines/azul-21.0.6/Contents/Home ./gradlew publishReleasePublicationToLocalRepository
```

### Integration in Other Projects
Add to consuming app's `build.gradle`:
```gradle
dependencies {
    implementation 'ca.weblite:fridablocker:1.0.0'
}
```

See `USAGE.md` for detailed integration instructions.

### Important Notes
- Project is configured as Android library module (generates .aar files)
- Native library is automatically included in APK builds
- Build configuration supports ProGuard for release builds but minification is currently disabled
- Project uses Gradle Version Catalogs for dependency management
- C++ code uses Android logging for debug output (check logcat with tag "FridaDetector")
- Published artifacts include native libraries for all Android architectures