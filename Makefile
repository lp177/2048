NAME = game_2048
SRC = main.c
OBJ = $(SRC:.c=.o)
FLG = -Wall -Wextra -Werror -g3
INC = -I libft/includes/
RED = \033[0;31m
GREEN = \033[1;32m
BLUE = \033[0;34m
CYAN = \033[0;36m
CYAN_L = \033[1;36m
NC = \033[0m
HOME = "`echo $HOME`"
VALGRIND = "$(HOME)/valgrind/bin/valgrind --leak-check=full --tool=memcheck --dsymutil=yes --show-leak-kinds=all"
LIBS= -L libft/ -lft 

$(NAME): $(OBJ)
	@echo "$(GREEN)== Make ==$(PURPLE)"
	make -C libft
	gcc $(FLG) $(INC) -c $(SRC)
	gcc -o $(NAME) $(OBJ) $(LIBS)
	@echo "$(GREEN)== End of compilation ==$(NC)"

all: $(NAME)

$(OBJ): $(SRC)
	gcc $(FLG) $(INC) -c $(SRC)

clean:
	@echo "\n    $(GREEN)== Clean ==$(CYAN)"
	@echo "      - rm all libft/.o"
	@make -C libft clean
	@rm -f $(OBJ)
	@echo "      - rm all .o"
	@echo "    $(GREEN)== End of clean ==$(NC)"

fclean:
	@echo "\n$(GREEN)== Fclean ==$(CYAN_L)"
	make clean
	@echo "$(CYAN_L)"
	make -C libft fclean
	@rm -rf libft.a
	rm -f $(NAME)
	@echo "$(GREEN)== End of fclean ==$(NC)\n"

re: fclean all

debug: fclean
	@echo "\n$(GREEN)== Debug ==$(PURPLE)"
	make -C libft give
	cc $(FLG) $(INC) -c -g $(SRC)
	cc -o $(NAME) $(OBJ) $(LIBS)
	@echo "$(GREEN)== End of compilation ==$(NC)\n"

leacks:
	while (test 42) do clear; leaks $(NAME); sleep 5; done

mn:
ifeq ($(N),)
	@echo "\n\n$(RED)Give me a N guy!   (make mn N=42)$(NC)\n"
else
	@echo "\n$(GREEN)Load main$(N).z$(NC)"
	rm -f main.c; cp main$(N).z main.c
	make debug
endif

thread:
ifeq ($(T),)
	@echo "\n\n$(RED)Give me a T guy!   (make thread T=42)$(NC)\n"
else
ifeq ($(P),)
	@echo "\n\n$(RED)Give me a P guy!   (make thread T=42 P=/Applications)$(NC)\n"
else
	@echo "\n$(GREEN)Iniatialisation du thread $(T)$(PURPLE)"
	make mn N=1 && cp $(NAME) $(NAME)_$(T) && sleep 1 && clear
	@echo "$(GREEN)== End of compilation ==$(NC)"
	./$(NAME)_$(T) -laR $(P)
	rm -f $(NAME)_$(T)
	make fclean
endif
endif

leacksn:
ifeq ($(N),)
	@echo "\n\n$(RED)Give me a N guy!   (make leacksn N=42)$(NC)\n"
else
	while (test 42) do clear; leaks $(NAME)_$(N); sleep 5; done
endif

moulinator:
	make mn N=1
	make -C ../moulitest-master sh1

.PHONY: all NAME debug clean fclean re
