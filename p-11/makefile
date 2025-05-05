CC = gcc
CFLAGS = -Wall -ansi -pedantic

.PHONY: palindrome clean
.PHONY: countZeros clean
palindrome: palindrome.c
	$(CC) $(CFLAGS) -o $@ $<

countZeros: count_zero_bits.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f palindrome
