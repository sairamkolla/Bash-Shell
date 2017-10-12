HEADERS = headers/everything.h headers/execution.h headers/refresh.h headers/tokenize.h

default: shell

shell: execution.c main.c tokenize.c refresh.c $(HEADERS)
	    gcc -g execution.c main.c tokenize.c refresh.c -o shell
clean:
	-rm -f shell
