CC = gcc
CF = -Wall -Wextra -g
SRC = main
OUT = nns
TREE = kdtree

build: $(SRC).o $(TREE).o
	$(CC) $(SRC).o $(TREE).o -lm -o $(OUT) 

$(SRC).o: $(SRC).c $(TREE).h
	$(CC) $(CF) -c $(SRC).c

$(TREE).o: $(TREE).c $(TREE).h
	$(CC) $(CF) -c $(TREE).c

clean:
	rm *.o $(OUT)

.PHONY: clean build
