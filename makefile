EXECUTABLE = election.out
COMPILER = g++
CPP_FILES = $(wildcard .src/**/*.cpp)
O_FILES = $(patsubst %.cpp, %.o, $(CPP_FILES))
CPP_VERSION = -std=c++17
FLAGS = -Wall -g 
OBJ_DIR = objects

YELLOW = "\033[1;33m"
RED = "\033[1;31m" 
CYAN = "\033[1;36m"
PURPLE = "\033[1;35m"
RESET_COLOR = "\033[0m"

all: $(EXECUTABLE)

$(EXECUTABLE): create_directories $(O_FILES)
	@echo $(YELLOW)
	@echo Creating executable file...
	@$(COMPILER) -o $@ $(OBJ_DIR)/$^
	@echo $(RESET_COLOR)

create_directories:
	@echo $(PURPLE)
	@echo Creating and organizing directories...
	@mkdir $(OBJ_DIR)
	@echo $(RESET_COLOR)

main.o: main.cpp
	@echo $(YELLOW)
	@echo Compilling main.cpp...
	@$(COMPILER) $(CPP_VERSION) -c $^ $(FLAGS)
	@mv $@ ./$(OBJ_DIR)
	@echo $(RESET_COLOR)

%.o: $(CPP_FILES)
	@echo $(YELLOW)
	@echo Compilling $(CPP_FILES) files...
	@$(COMPILER) $(CPP_VERSION) -c $^ $(FLAGS)
	@mv ./src/**/$(O_FILES) $(OBJ_DIR)
	@echo $(RESET_COLOR)

runfederal: $(EXECUTABLE)
	@echo $(CYAN)
	@echo Running federal analysis...
	@./$(EXECUTAVEL) --federal candidatos.csv votacao.csv 02/10/2022
	@echo (RESET_COLOR)

runestadual: $(EXECUTABLE)
	@echo $(CYAN)
	@echo Running estadual analysis...
	@./$(EXECUTAVEL) --estadual candidatos.csv votacao.csv 02/10/2022
	@echo (RESET_COLOR)

clean: 
	@echo $(RED)
	@echo Removing temporary files and executable...
	@rm -rf $(EXECUTABLE) $(OBJ_DIR)
	@clear
	@echo $(RESET_COLOR)
