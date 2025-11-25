#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m'

echo -e "${CYAN}================================${NC}"
echo -e "${CYAN}  Building Ardus Project  ${NC}"
echo -e "${CYAN}================================${NC}"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

cd "$PROJECT_ROOT" || exit 1

echo -e "${YELLOW}[1/3] Preparing build directory...${NC}"
if [ ! -d "build" ]; then
	mkdir build
fi

cd build || exit 1

echo -e "${YELLOW}[2/3] Generating CMake project...${NC}"
if cmake .. -G "Visual Studio 18 2026" -A x64; then
	echo -e "${GREEN}CMake generation successful${NC}"
else
	echo -e "${RED}CMake generation failed${NC}"
	cd ..
	exit 1
fi

echo ""

echo -e "${YELLOW}[3/3] Building project (Release)...${NC}"
if cmake --build . --config Release; then
	echo -e "${GREEN}================================${NC}"
	echo -e "${GREEN}Build successful${NC}"
else
	echo -e "${RED}================================${NC}"
	echo -e "${RED}Build failed${NC}"
	cd ..
	exit 1
fi

EXE_PATH="Release/Ardus.exe"
if [ -f "$EXE_PATH" ]; then
	echo -e "${GREEN}Executable: $EXE_PATH ${NC}"
	echo -e "${GREEN}================================${NC}"
else
	echo -e "${RED}Executable not found${NC}"
	echo -e "${RED}================================${NC}"
	cd ..
	exit 1
fi

cd ..
