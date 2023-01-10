SHELL = /bin/sh

NAME := decoder
OBJDIR := objdir

COMAND_IPC_DIR = ../../lib/comand_ipc
COMAND_IPC = $(COMAND_IPC_DIR)/libcomand_ipc.a

CFLAGS += $(INCLUDE) -Wall -Wextra -g
LDLIBS += -lcomand_ipc
LDFLAGS += -L$(COMAND_IPC_DIR)
INCLUDE = -I$(COMAND_IPC_DIR)

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

$(NAME): $(OBJS) $(COMAND_IPC)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

$(COMAND_IPC):
	$(MAKE) -C $(COMAND_IPC_DIR) --no-print-directory

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $@

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(COMAND_IPC_DIR) --no-print-directory

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(COMAND_IPC_DIR) --no-print-directory

re: fclean all

.PHONY: all re
