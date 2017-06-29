all: huge tool

huge: hugesort.c
	gcc -g $^ -o $@ -Wall -pedantic -std=c99

tool: tool.c
	gcc -g $^ -o $@ -Wall -pedantic -std=c99

gen: 
	./tool -z out.dat

clean:
	rm -f huge tool out.dat 
