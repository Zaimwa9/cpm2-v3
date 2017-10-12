NAME = CPM2
CC = gcc
DEST = ./bin/
EXE = $(addprefix $(DEST), cpm2.exe)

INC_PATH = ./includes/
SRC_DIR = ./src/
SRC_NAMES = CPM2.c daemon_kill.c pathvalidator.c daemonprog.c name_extract.c \
						list_processes.c control_processes.c pathcreator.c

SRC = $(addprefix $(SRC_DIR),$(SRC_NAMES)) 

OBJ_DIR = ./obj/
OBJ_NAMES = $(SRC_NAMES:.c=.o)
OBJ = $(addprefix $(OBJ_DIR),$(OBJ_NAMES))
INC = $(addprefix -I,$(INC_PATH))

all: $(NAME)

$(NAME):				makedirs $(OBJ)
								$(CC) $(CFLAGS) -o $(EXE) $(OBJ)
								@echo "cpm2 ready to be used"

makedirs:
								@mkdir $(OBJ_DIR) 2> /dev/null || echo "" 2> /dev/null
								@mkdir ./bin 2> /dev/null || echo "" 2> /dev/null

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c					
								$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean: 
								rm -rf $(OBJ_DIR)

fclean:
								rm -rf $(OBJ_DIR)
								rm -rf ./bin/cpm2.exe

re: 						fclean all