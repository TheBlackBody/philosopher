# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MAKEFILE                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfernand <sfernand@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/07 16:28:13 by sfernand          #+#    #+#              #
#    Updated: 2023/08/13 14:23:55 by sfernand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosopher

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
AR = ar rcs
RM = rm -f

FILES = main \
		activity \
		thread \
		parsing \
		utils_philo \
		utils_libs \

SRCS_DIR = ./sources/
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./sources/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	gcc $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(OBJS)
	
re: clean all


.PHONY: all clean fclean re