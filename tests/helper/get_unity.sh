#!/bin/bash

# Define variables
UNITY_REPO_URL="https://github.com/ThrowTheSwitch/Unity.git"
TEMP_DIR="temp_unity"
TARGET_DIR="tests/helper/unity"

# Create a temporary directory
mkdir -p $TEMP_DIR

# Clone the Unity repository into the temporary directory
git clone --depth=1 $UNITY_REPO_URL $TEMP_DIR

# Create the target directory
mkdir -p $TARGET_DIR

# Move only the src folder content from Unity to the target directory
mv $TEMP_DIR/src/* $TARGET_DIR

# Remove the temporary directory
rm -rf $TEMP_DIR

echo "Unity framework's src folder has been successfully moved to $TARGET_DIR"
