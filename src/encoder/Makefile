SHELL = /bin/sh

NAME := decoder
OBJDIR := objdir

CFLAGS += -Wall -Wextra -g
LDLIBS +=
LDFLAGS +=
INCLUDE =

OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

SRC = $(wildcard *.c)

$(OBJDIR)/%.o: %.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

all: $(NAME)

options:
	@echo "$(NAME) build options:"
	@echo "CFLAGS        = $(CFLAGS)"
	@echo "LDLIBS        = $(LDLIBS)"
	@echo "LDFLAGS       = $(LDFLAGS)"
	@echo "CC            = $(CC)"

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $@

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re
