EXE ?= SSSimpler

USE_LIBNUMA ?= off
NUMA_FLAGS :=
ifeq ($(USE_LIBNUMA),on)
    NUMA_FLAGS := -DUSE_LIBNUMA -lnuma
endif

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

CXXFLAGS =  -O3 -std=c++2a $(MARCH_FLAG) -pthread -fno-exceptions -fno-rtti -DNDEBUG -ffast-math -funroll-loops $(NUMA_FLAGS)


all:
	rm -f $(EXE) $(EXE)_pgo $(EXE).profdata default.profraw
	clang++ $(CXXFLAGS) -fprofile-instr-generate code/main.cpp -o $(EXE)_pgo
	LLVM_PROFILE_FILE="default.profraw" ./$(EXE)_pgo bench
	llvm-profdata merge -o $(EXE).profdata default.profraw
	clang++ $(CXXFLAGS) -fprofile-instr-use=$(EXE).profdata code/main.cpp -o $(EXE)
	rm -f $(EXE)_pgo default.profraw

.PHONY: all
