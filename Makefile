COMPILER := gcc

# SRC Files
SRC := ./src/svm.c ./src/memory.c ./src/opcode.c ./src/register.c ./src/utils.c ./src/win.c

# Include Files
INCLUDE := -I ./include/
# Build exe

build:
	@echo Building...
	@$(COMPILER) $(SRC) -I ./include/ -o bin/svm.exe

run:
	@echo Running...
	@./bin/svm.exe ./obj/2048.obj

vm:
	@make build
	@echo Running 2048.obj
	@./bin/svm.exe ./obj/2048.obj
