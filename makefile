all:
	gcc -Wall -pedantic-errors -Werror -Wno-long-long -Wno-format -Wno-format-extra-args -g -o connectfour connectfour.c
    
clean:
	rm -f connectfour
