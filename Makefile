EXE ?= Simpler
CXX ?= clang++

ARCH := $(shell uname -m)

# Set march flags based on architecture
ifeq ($(ARCH),aarch64)
    # ARM 64-bit
    MARCH_FLAG := -mcpu=native
else ifeq ($(ARCH),armv7l)
    # ARM 32-bit
    MARCH_FLAG := -mcpu=native
else
    # x86_64
    MARCH_FLAG := -march=native

endif
all:
	clang++ code/main.cpp -o $(EXE) -O3 -std=c++2a $(MARCH_FLAG) -pthread -flto -fno-exceptions -fno-rtti -DNDEBUG -ffast-math -funroll-loops

