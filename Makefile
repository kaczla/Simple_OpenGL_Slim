SOURCE_DIR = ./src/
MAIN = $(SOURCE_DIR)main.cpp
CXXFLAGS = -std=c++11
CXXFLAGS += -O3

ifeq ($(OS),Windows_NT)
CXXFLAGS += -m32 -D_hypot=hypot
LFLAGS = -lmingw32 -lSDL2main -lSDL2 -mwindows -lopengl32 -lglew32 -lglu32  -lDevIL -lILU -lassimp
else
LFLAGS = -lSDL2 -lGL -lGLU -lGLEW -lIL -lILU -lassimp
endif

ifeq ($(OS),Windows_NT)
APP_NAME = game.exe
else
APP_NAME = game.app
endif

all:
	@echo ' '
	@echo ' '
	@echo 'Building application $(APP_NAME)'
	@echo ' '
	$(CXX) $(CXXFLAGS) $(MAIN) -o $(APP_NAME) $(LFLAGS)
	@echo ' '
	@echo 'Finished building application $(APP_NAME)'
	@echo ' '
	@echo ' '

clear: clean
clean:
	echo ' '
	@echo 'Cleaning'
	$(RM) $(APP_NAME)
	@echo 'Cleaned'
	@echo ' '
