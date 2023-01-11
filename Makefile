SHELL = /bin/sh

all: encoder decoder

encoder:
	$(MAKE) -C ./src/encoder --no-print-directory

decoder:
	$(MAKE) -C ./src/decoder --no-print-directory

clean:
	$(MAKE) clean -C ./src/encoder --no-print-directory
	$(MAKE) clean -C ./src/decoder --no-print-directory

fclean: clean
	$(MAKE) fclean -C ./src/encoder --no-print-directory
	$(MAKE) fclean -C ./src/decoder --no-print-directory

re: fclean all
