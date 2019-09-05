.PHONY:all
all:client server

client:client.c common.c
	gcc $^ -o $@
server:server.c common.c
	gcc $^ -o $@

.PHONY:clean
clean:
	rm server client
