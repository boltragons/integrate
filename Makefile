all: app

app: main.o integrate.o
	@gcc obj/main.o obj/integrate.o -lm -o bin/integrate

main.o:
	@gcc -lm -Wall -Iinc -c src/main.c -o obj/main.o

integrate.o:
	@gcc -lm -Wall -Iinc -c src/integrate.c -o obj/integrate.o

clean:
	@rm -rf bin/*
	@rm -rf obj/*