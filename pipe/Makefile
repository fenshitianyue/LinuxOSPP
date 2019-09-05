.PHONY:all
all:clientPipe serverPipe

serverPage:serverPage.c
	gcc $^ -o $@

clientPipe:clientPipe.c
	gcc $^ -o $@

clean:
	rm serverPipe clientPipe
