# Command to detect the OS
UNAME := $(shell uname)

# Compiler and source files
CXX := g++
SRC := $(wildcard src/*.cpp)
OUT := main


# Platform-specific flags
ifeq ($(UNAME), Linux)
    INCLUDES := $(shell sdl2-config --cflags)
	LIBS := -lSDL2 -lSDL2_image
else
	# Assume Windows (MinGW)
    INCLUDES := -Iinclude -Iinclude/sdl -Iinclude/headers -Llib
	LIBS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
endif

all:
	$(CXX) $(INCLUDES) -o $(OUT) $(SRC) $(LIBS)
