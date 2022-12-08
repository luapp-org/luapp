%.yy.c : %.l
	flex --header-file=$(subst .yy.c,.yy.h,$@) -o $@ $<

%.tab.c : %.y
	bison -d $< 

	mv parser.tab.h  compiler/src
	mv parser.tab.c  compiler/src

COMPILER_OBJS = compiler/src/main.c compiler/src/lexer.yy.c compiler/src/parser.tab.c compiler/src/compiler.c compiler/src/node.c compiler/src/util/flexstr.c compiler/src/util/hashmap.c compiler/src/type.c compiler/src/symbol.c compiler/src/ir.c compiler/src/codegen.c common/opcodes.c
VM_OBJS = vm/src/*.c vm/src/lua/*.c common/opcodes.c

compiler: $(COMPILER_OBJS)
	gcc -o bin/luappc $^ -lm

# runtime -> vm
runtime: $(VM_OBJS)
	gcc -o bin/luappvm $^ -lm