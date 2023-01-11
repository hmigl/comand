NAME := libhuff.a
OBJDIR := objdir

CFLAGS += -Wall -Wextra -Werror

OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
SRC = $(wildcard *.c)

$(OBJDIR)/%.o: %.c
	@$(COMPILE.c) $(OUTPUT_OPTION) $<

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	@mkdir $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean
