%.yy.c : %.l
	flex --header-file=$(subst .yy.c,.yy.h,$@) -o $@ $<

	mv lexer.yy.h  src/
	mv lexer.yy.c  src/

%.tab.c : %.y
	bison -d $< 

	mv parser.tab.h  src/
	mv parser.tab.c  src/

OBJS = src/luapp.c src/lexer.yy.c src/parser.tab.c src/compiler.c src/node.c src/util/flexstr.c src/type.c

# Builds all of the files and stores the out file in bin/
make: $(OBJS)
	gcc -o src/bin/luapp $^