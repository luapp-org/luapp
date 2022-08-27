%.yy.c : %.l
	flex --header-file=$(subst .yy.c,.yy.h,$@) -o $@ $<

%.tab.c : %.y
	bison -d $< 

	mv parser.tab.h  src/
	mv parser.tab.c  src/

OBJS = src/main.c src/lexer.yy.c src/parser.tab.c src/compiler.c src/node.c src/util/flexstr.c src/util/hashmap.c src/type.c src/symbol.c src/ir.c src/codegen.c

# Builds all of the files and stores the out file in bin/
make: $(OBJS)
	gcc -o src/bin/luappc $^ -lm