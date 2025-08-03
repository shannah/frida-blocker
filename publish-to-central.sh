#!/bin/bash

# Script to publish FridaBlocker to Maven Central Portal
# This script creates a bundle that can be uploaded manually or automatically

set -e

echo "🚀 Publishing FridaBlocker to Maven Central Portal..."

# Set Java home
export JAVA_HOME=/Users/shannah/Library/Java/JavaVirtualMachines/azul-21.0.6/Contents/Home

# Load environment variables for credentials
if [ -f .env ]; then
    source .env
    echo "✅ Loaded credentials from .env"
else
    echo "⚠️  No .env file found - using system credentials"
fi

# Automated publish to Maven Central Portal (like mvn deploy)
echo "📦 Building and publishing to Maven Central Portal..."
./gradlew publishAggregationToCentralPortal

if [ $? -eq 0 ]; then
    echo "✅ Successfully published to Maven Central Portal!"
    echo ""
    echo "📋 Your library will be available at:"
    echo "   ca.weblite:fridablocker:1.0.0"
    echo ""
    echo "🔍 Check status at: https://central.sonatype.com/publishing"
    echo "📦 Once published, developers can use:"
    echo "   implementation 'ca.weblite:fridablocker:1.0.0'"
else
    echo "❌ Failed to publish to Maven Central Portal"
    echo "Check the error messages above for details"
    exit 1
fi