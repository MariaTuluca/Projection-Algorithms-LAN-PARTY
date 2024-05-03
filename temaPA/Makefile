
all: lanParty

lanParty.out: lanParty.c
	gcc -o lanParty lanParty.c

compile: lanParty
	./lanParty d.in r.out

clean:
	rm -f lanParty
