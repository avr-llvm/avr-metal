# AVR on-target test suite

These tests are built using LLVM and executed on real AVR hardware.

## Prerequisites

* LLVM
* Arduino UNO

## Setup

```bash
# Grab LLVM
git clone https://github.com/llvm-mirror/llvm.git
cd llvm

# Grab the AVRLIT testing tool
cd tools
git clone https://github.com/avr-llvm/avrlit.git

# Grab the metal test suite
cd ../projects
git clone https://github.com/avr-llvm/avr-metal.git

# Build LLVM
cd ../../ && mkdir llvm-build
cmake ../llvm -DLLVM_EXPERIMENTAL_TARGETS_TO_BUILD=AVR
make

# Configure the board setup
export AVRLIT_PORT=/dev/cu.usbserial-A9OFZL9T
export AVRLIT_BOARD=uno

# Run the tests
./bin/llvm-lit ../llvm/projects/avr-metal
```
