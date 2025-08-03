# Release Guide

This guide explains how to publish new versions of FridaBlocker to Maven Central.

## Prerequisites

### One-time Setup

1. **Create Maven Central Account**
   - Sign up at [Maven Central Portal](https://central.sonatype.com/)
   - Verify your namespace (`ca.weblite`)

2. **Generate GPG Key**
   ```bash
   # Generate new key
   gpg --gen-key
   
   # Export private key (base64 encoded)
   gpg --export-secret-keys YOUR_KEY_ID | base64 | tr -d '\n'
   
   # Export public key to keyserver
   gpg --keyserver keyserver.ubuntu.com --send-keys YOUR_KEY_ID
   ```

3. **Set GitHub Secrets**
   In your GitHub repository settings, add these secrets:
   - `MAVEN_CENTRAL_USERNAME` - Your Maven Central Portal username
   - `MAVEN_CENTRAL_PASSWORD` - Your Maven Central Portal token
   - `SIGNING_KEY` - Your GPG private key (base64 encoded from step 2)
   - `SIGNING_PASSWORD` - Your GPG key passphrase

## Release Process

### Option 1: GitHub Release (Recommended)

1. **Update Version**
   - Edit `app/build.gradle` and update `ext.libVersion`
   - Commit and push the version change

2. **Create GitHub Release**
   - Go to GitHub Releases
   - Click "Create a new release"
   - Create a new tag (e.g., `v1.0.1`)
   - Set release title and description
   - Click "Publish release"

3. **Automatic Publishing**
   - GitHub Actions will automatically trigger
   - Library will be built, tested, and published to Maven Central
   - Check the Actions tab for progress

### Option 2: Manual Trigger

1. **Update Version**
   - Edit `app/build.gradle` and update `ext.libVersion`
   - Commit and push

2. **Trigger Workflow**
   - Go to GitHub Actions
   - Select "Publish to Maven Central" workflow
   - Click "Run workflow"
   - Enter the version number
   - Click "Run workflow"

### Option 3: Local Publishing

For testing or emergency releases:

```bash
# Set environment variables
export MAVEN_CENTRAL_USERNAME="your-username"
export MAVEN_CENTRAL_PASSWORD="your-token"
export SIGNING_KEY="your-base64-private-key"
export SIGNING_PASSWORD="your-key-password"

# Update version in app/build.gradle
# Then publish
./gradlew publishReleasePublicationToCentralRepository
```

## Post-Release

1. **Verify Publication**
   - Check [Maven Central Search](https://search.maven.org/search?q=g:ca.weblite%20AND%20a:fridablocker)
   - It may take a few minutes to appear

2. **Update Documentation**
   - Update version numbers in README.md
   - Update USAGE.md if needed
   - Update CLAUDE.md if needed

3. **Test Integration**
   - Create a test project
   - Add the new version as a dependency
   - Verify it works correctly

## Troubleshooting

### Build Failures
- Check that all tests pass: `./gradlew test`
- Verify NDK is properly installed
- Ensure Java 21 is being used

### Publishing Failures
- Verify all GitHub secrets are set correctly
- Check that GPG key is valid and uploaded to keyserver
- Ensure Maven Central credentials are correct
- Check that the version number is unique

### Signing Issues
- Verify SIGNING_KEY is base64 encoded correctly
- Check that SIGNING_PASSWORD matches your GPG key
- Ensure GPG key hasn't expired

## Version Numbering

Follow semantic versioning (SemVer):
- **Major** (1.0.0 → 2.0.0): Breaking changes
- **Minor** (1.0.0 → 1.1.0): New features, backward compatible
- **Patch** (1.0.0 → 1.0.1): Bug fixes, backward compatible

## Testing Before Release

```bash
# Run all tests
./gradlew test

# Build release version
./gradlew assembleRelease

# Test with different Android API levels
./gradlew connectedAndroidTest

# Check for any lint issues
./gradlew lint
```

## Emergency Releases

For critical security fixes:

1. Create hotfix branch from main
2. Make minimal necessary changes
3. Test thoroughly
4. Use manual publishing option
5. Create GitHub release immediately after
6. Merge hotfix back to main and develop branches