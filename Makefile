NAME = libasm.a
NASM = nasm
NASMFLAGS = -f elf64 -w+all
AR = ar rcs
RM = rm -f
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s
OBJS = $(SRCS:.s=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.s
	$(NASM) $(NASMFLAGS) $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) test

re: fclean all

test: re
	$(CC) $(CFLAGS) main.c -g -L. -lasm -o test
