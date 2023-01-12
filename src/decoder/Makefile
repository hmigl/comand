SHELL = /bin/sh

NAME := decoder
OBJDIR := objdir

COMAND_IPC_DIR = ../../lib/comand_ipc
COMAND_IPC = $(COMAND_IPC_DIR)/libcomand_ipc.a

HUFFMAN_DIR = ../../lib/huffman
HUFFMAN = $(HUFFMAN_DIR)/libhuff.a

CFLAGS += $(INCLUDE) -Wall -Wextra -g
LDLIBS += -lcomand_ipc -lhuff
LDFLAGS += -L$(COMAND_IPC_DIR) -L$(HUFFMAN_DIR)
INCLUDE = -I$(COMAND_IPC_DIR) -I$(HUFFMAN_DIR)

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

$(NAME): $(OBJS) $(COMAND_IPC) $(HUFFMAN)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

$(COMAND_IPC):
	$(MAKE) -C $(COMAND_IPC_DIR) --no-print-directory

$(HUFFMAN):
	$(MAKE) -C $(HUFFMAN_DIR) --no-print-directory

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $@

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(COMAND_IPC_DIR) --no-print-directory
	$(MAKE) clean -C $(HUFFMAN_DIR) --no-print-directory

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(COMAND_IPC_DIR) --no-print-directory
	$(MAKE) fclean -C $(HUFFMAN_DIR) --no-print-directory

re: fclean all

.PHONY: all re
