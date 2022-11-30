OBJS = src/*.c src/lua/*.c

# Builds all of the files and stores the out file in bin/
make: $(OBJS)
	gcc -o src/bin/luappvm $^ -lm