# Command to detect the OS
UNAME := $(shell uname)

# Compiler and source files
CXX := g++
SRC := $(wildcard src/*.cpp)
OUT := output/main


# Platform-specific flags
ifeq ($(UNAME), Linux)
    INCLUDES := $(shell sdl2-config --cflags) -Iinclude
	LIBS := -lSDL2 -lSDL2_image
else
	# Assume Windows (MinGW)
    INCLUDES := -Llib -Iinclude
	LIBS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
endif

all:
	$(CXX) $(INCLUDES) -o $(OUT) $(SRC) $(LIBS)