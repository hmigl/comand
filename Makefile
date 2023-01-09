SHELL = /bin/sh

all: encoder decoder

encoder:
	$(MAKE) -C ./src/encoder --no-print-directory

decoder:
	$(MAKE) -C ./src/decoder --no-print-directory

fclean:
	$(MAKE) fclean -C ./src/encoder --no-print-directory
	$(MAKE) fclean -C ./src/decoder --no-print-directory
