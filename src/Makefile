%.yy.c : %.l
	flex --header-file=$(subst .yy.c,.yy.h,$@) -o $@ $<

%.tab.c : %.y
	bison -d $<

OBJS = luapp.c lexer.yy.c parser.tab.c compiler.c node.c

# Builds all of the files and stores the out file in bin/
make: $(OBJS)
	gcc -o bin/luapp $^ 