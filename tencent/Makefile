all: huge tool

huge: hugesort.c
	gcc -g $^ -o $@ -Wall -pedantic -std=c99

tool: tool.c
	gcc -g $^ -o $@ -Wall -pedantic -std=c99

clean:
	rm -f huge tool out.dat
