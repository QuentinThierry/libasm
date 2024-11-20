AS= nasm
ASFLAGS= -g -f elf64
LD=ld

SRCS_DIR=	srcs/
SRCS_LIST=	ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s
SRCS=	$(addprefix $(SRCS_DIR), $(SRCS_LIST))

NAME= libasm.a

OBJ_DIR=	obj/
OBJ_LIST= ${SRCS_LIST:.s=.o}
OBJ=	$(addprefix $(OBJ_DIR), $(OBJ_LIST))

${OBJ_DIR}%.o: ${SRCS_DIR}%.s
	$(AS) $(ASFLAGS) -o $@ $<

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJ_DIR):
	mkdir -p obj/

test:
	make && cc -Wall -Wextra main.c -g -L. -lasm && ./a.out

bonus: all

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re test
