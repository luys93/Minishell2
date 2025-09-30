NAME = libft.a
TITLE = libft

BROWN = \033[1;38;2;101;67;33m

CC = cc 
RM = rm -f
AR = ar rcs
CFLAGS = -Wall -Werror -Wextra -I. -Iincludes

SRCS = lib/ft_isalnum.c \
	   lib/ft_isdigit.c \
	   lib/ft_isalpha.c \
	   lib/ft_isprint.c \
	   lib/ft_strlen.c  \
	   lib/ft_toupper.c \
	   lib/ft_tolower.c \
	   lib/ft_atoi.c    \
	   lib/ft_memset.c  \
	   lib/ft_strrchr.c \
	   lib/ft_strlcat.c \
	   lib/ft_strncmp.c \
	   lib/ft_memmove.c \
	   lib/ft_memcmp.c  \
	   lib/ft_bzero.c   \
	   lib/ft_isascii.c \
	   lib/ft_strchr.c  \
	   lib/ft_memcpy.c  \
	   lib/ft_strdup.c  \
	   lib/ft_strdup.c  \
	   lib/ft_strlcpy.c \
	   lib/ft_calloc.c  \
	   lib/ft_memchr.c  \
	   lib/ft_substr.c  \
	   lib/ft_strnstr.c \
	   lib/ft_strjoin.c \
	   lib/ft_strtrim.c \
	   lib/ft_strndup.c \
	   lib/ft_strcmp.c 	\
	   lib/ft_split.c	\
	   lib/ft_putchar_fd.c	\
	   lib/ft_putstr_fd.c 	\
	   lib/ft_putendl_fd.c	\
	   lib/ft_putnbr_fd.c 	\
	   lib/ft_itoa.c	  	\
	   lib/ft_strmapi.c	  	\
	   lib/ft_striteri.c	\
	   lib/ft_lstnew.c 		\
	   lib/ft_lstmap.c 		\
	   lib/ft_lstiter.c 	\
	   lib/ft_lstsize.c 	\
	   lib/ft_lstlast.c 	\
	   lib/ft_lstclear.c 	\
	   lib/ft_lstdelone.c 	\
	   lib/ft_lstadd_back.c \
	   lib/ft_lstadd_front.c\
	   gnl/get_next_line.c 	\
	   gnl/get_next_line_utils.c 	\
	   ft_printf/ft_printf.c 		\
	   ft_printf/utils.c			\
	   ft_printf/utils2.c 			\


OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	@$(AR) $@ $^
	@printf "\n\033[1A\033[K"
	@printf "$(BROWN)$(TITLE) compiled OK!\n"
	@printf "\033[0;37m"

%.o: %.c
	@printf "\033[0;37m Generating $(TITLE) objects... %-33.33s\r" $@
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

bonus: all

clean:
	@$(RM) $(OBJS)

	
fclean: clean
	@$(RM) $(NAME)


re: fclean all

.PHONY: all clean fclean re bonus