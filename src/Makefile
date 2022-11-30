%.yy.c : %.l
	flex --header-file=$(subst .yy.c,.yy.h,$@) -o $@ $<

%.tab.c : %.y
	bison -d $< 

	mv parser.tab.h  compiler/src
	mv parser.tab.c  compiler/src

COMPILER_OBJS = compiler/src/main.c compiler/src/lexer.yy.c compiler/src/parser.tab.c compiler/src/compiler.c compiler/src/node.c compiler/src/util/flexstr.c compiler/src/util/hashmap.c compiler/src/type.c compiler/src/symbol.c compiler/src/ir.c compiler/src/codegen.c common/opcodes.c


# Builds all of the files and stores the out file in bin/
make compiler: $(COMPILER_OBJS)
	gcc -o bin/luappc $^ -lm