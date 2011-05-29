CC = gcc
CF = -Wall -Wextra -g
SRC = problema4
TREE = kdtree

build: $(SRC).o $(TREE).o
	$(CC) $(SRC).o $(TREE).o -lm -o $(SRC) 

$(SRC).o: $(SRC).c $(TREE).h
	$(CC) $(CF) -c $(SRC).c

$(TREE).o: $(TREE).c $(TREE).h
	$(CC) $(CF) -c $(TREE).c

clean:
	rm *.o $(SRC)

.PHONY: clean build
