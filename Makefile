# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emcnab <emcnab@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/21 10:30:50 by emcnab            #+#    #+#              #
#    Updated: 2022/11/29 16:28:08 by emcnab           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ==============================================================================
# 										DISPLAY
# ==============================================================================

# colors
BLACK   = \033[0;30m
GRAY    = \033[1;30m
RED     = \033[0;31m
LRED    = \033[1;31m
GREEN   = \033[0;32m
LGREEN  = \033[1;32m
ORANGE  = \033[0;33m
YELLOW  = \033[1;33m
BLUE    = \033[0;34m
LBLUE   = \033[1;34m
PURPLE  = \033[0;35m
LPURPLE = \033[1;35m
CYAN    = \033[0;36m
LCYAN   = \033[1;36m
LGRAY   = \033[0;37m
WHITE   = \033[1;37m

define SEPERATOR
$(WHITE).....................................................................
endef

export SEPERATOR

# ==============================================================================
# 									COMPILATION
# ==============================================================================

# mandatory files
define MAND_FILES
	get_next_line.c get_next_line_utils.c	test.c
endef

# bonus files
define BONUS_FILES
endef
 
# this is where all object files are compiled to
ODIR   = objs/

# object files
OFILES = $(patsubst %.c, $(ODIR)%.o, $(MAND_FILES))\
		 $(patsubst %.c, $(ODIR)%.o, $(BONUS_FILES))

# C compiler
CC     = clang
CMODE  = debug hard
OPT    = -O0
CFLAGS = -Wall -Wextra -Werror $(OPT) -D BUFFER_SIZE=1

# compilation modes
# debug    : debug mode
# fsanitize: uses fsanitize option for compilation
# hard     : stricter compilation rules and error checking
ifneq ($(filter debug, $(CMODE)),)
	CFLAGS += -g
endif
ifneq ($(filter fsanitize, $(CMODE)),)
	CFLAGS += -fsanitize=address
endif
ifneq ($(filter hard, $(CMODE)),)
	CFLAGS += -Weverything
	# -Wno-cast-qual -Wno-missing-noreturn -Wno-disabled-macro-expansion
	# -Wno-reserved-id-macro
endif

# libft
LIBFT_REPO = https://github.com/eliot-mcnab/libft.git
LIBFT_DIR  = libft

# dependencies
DEPS = libft/libft.a

# program name
BINARY = gnl

# by default, compiles binary
all: $(ODIR) $(BINARY) Makefile

# creates the object directory if it does not exist
$(ODIR):
	@mkdir $(ODIR)
	@echo "${GREEN} created directory ${LGREEN}${@}${LGRAY}"

# for binary to be compiled, all related object files must have been compiled
$(BINARY): $(OFILES) $(DEPS)
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "$$SEPERATOR"
	@echo "${LGREEN} ${WHITE}${BINARY} ${LGREEN}built successfully!${LGRAY}"

# for any object file to be compiled, the corresponding c file must exist
$(ODIR)%.o:%.c
	@$(CC) $(CFLAGS) -c -o $@ $^
	@echo "${LGRAY}${@} ${GREEN}built successfully!${LGRAY}"

# updates libft
update: $(LIBFT_DIR)
	@(cd libft && git pull)
	@(cd libft && make all)
	@cp libft/libft.h ./
	@echo "${PURPLE}  udpdated ${LPURPLE}libft${LGRAY}"

# clones git repo if it does not exist
$(LIBFT_DIR):
	@git clone $(LIBFT_REPO)
	@echo "${PURPLE}  cloned ${LPURPLE}libft${LGRAY}"

# removes all objects
clean:
	@rm -f $(OFILES)
	@echo "${RED} removed all object files${LGRAY}"

# removes all objects and the binary
fclean: clean
	@rm -f $(BINARY)
	@echo "${RED}|${LGRAY}"
	@echo "${LRED} removed ${WHITE}${BINARY}${LGRAY}"
	@echo "$$SEPERATOR"

# removes all objecst, the binary and rebuilds the binary
re: fclean
	@make all

# displays debug information
debug:
	@echo $(filter debug, $(CMODE))

.PHONY: all update clean fclean re debug
