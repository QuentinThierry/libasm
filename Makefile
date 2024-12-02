AS= nasm
ASFLAGS= -g -f elf64
LD=ld

SRCS_DIR=	srcs/
SRCS_LIST=	ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s\
			ft_strdup.s ft_atoi_base.s ft_list_push_front.s ft_list_size.s\
			ft_list_sort.s
SRCS=	$(addprefix $(SRCS_DIR), $(SRCS_LIST))

NAME= libasm.a
NAME_TEST= libasm.out

OBJ_DIR=	obj/
OBJ_LIST= ${SRCS_LIST:.s=.o}
OBJ=	$(addprefix $(OBJ_DIR), $(OBJ_LIST))

${OBJ_DIR}%.o: ${SRCS_DIR}%.s
	$(AS) $(ASFLAGS) -o $@ $<

all: $(NAME)

bonus: all

$(NAME): $(OBJ_DIR) $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJ_DIR):
	mkdir -p obj/

test: $(NAME_TEST)
	./$(NAME_TEST)

valgrind_test: $(NAME_TEST)
	valgrind ./$(NAME_TEST)

$(NAME_TEST): $(NAME) main.c utils.c
	cc -Wall -Wextra main.c utils.c -g -L. -lasm -o $(NAME_TEST)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re test
