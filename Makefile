WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 

SRCS = main.c hw04.c
OBJS = $(SRCS:%.c=%.o)

hw04: $(OBJS) 
	$(GCC) $(OBJS) -o hw04

.c.o: 
	$(GCC) -c $*.c 

testall: test1 test2

test1: hw04
	./hw04 inputs/presorted_list.bin output1.bin 
	diff output1.bin expected/expected1.bin

show1: test1
	hexdump -C inputs/presorted_list.bin > presorted_list_hex.txt
	hexdump -C output1.bin > output1_hex.txt
	hexdump -C expected/expected1.bin > expected1_hex.txt

test2: hw04
	./hw04 inputs/short_list.bin output2.bin 
	diff output2.bin expected/expected2.bin

show2: test2
	hexdump -C inputs/short_list.bin > short_list_hex.txt
	hexdump -C output2.bin > output2_hex.txt
	hexdump -C expected/expected2.bin > expected2_hex.txt

clean: # remove all machine generated files
	rm -f hw04 *.o *.txt output*