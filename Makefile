all: sdku-gen.c

sdku-gen.c:
	cc -ggdb -Wall -Wextra -Werror $< $@
clean:
	rm sdku-gen 
