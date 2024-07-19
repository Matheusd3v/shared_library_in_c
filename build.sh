#!/bin/sh

install_apk_packages() {
    apk add --no-cache gcc g++ make
}

install_apt_packages() {
    apt-get update
    apt-get install -y gcc g++ make
}

if command -v apt-get > /dev/null; then
    echo "Detected Debian-based distribution. Installing packages with apt-get..."
    install_apt_packages
elif command -v apk > /dev/null; then
    echo "Detected Alpine Linux. Installing packages with apk..."
    install_apk_packages
else
    echo "Unsupported package manager. Please install gcc, g++, and make manually."
    exit 1
fi

make shared-library
