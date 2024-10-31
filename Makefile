CFLAGS = -Wall -Werror -Wextra
CPPFLAGS =  -MMD

.PHONY: all
all: Trie

-include main.d rbtree.d trie.d

Trie: main.o librbtree.a
	gcc  $(CFLAGS) $^ -o $@
	rm main.o;
	rm main.d;
	rm rbtree.o;
	rm rbtree.d ;
	rm trie.o;
	rm trie.d

main.o: main.c
	gcc -c $(CFLAGS) $(CPPFLAGS) $< -o $@

librbtree.a: rbtree.o trie.o
	ar rcs $@ $^

rbtree.o: rbtree.c
	gcc -c $(FLAGS) $(CPPFLAGS) $< -o $@

trie.o: trie.c
	gcc -c $(FLAGS) $(CPPFLAGS) $< -o $@

.PHONY: clean
clean:
	rm main.o;
	rm main.d;
	rm rbtree.o;
	rm rbtree.d ;