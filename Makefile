all: compile

compile:
	i686-elf-as boot.s -o boot.o

clean:
	rm boot.o


