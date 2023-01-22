%.yy.c : %.l
	flex --header-file=$(subst .yy.c,.yy.h,$@) -o $@ $<

%.tab.c : %.y
	bison -d $< 

	mv parser.tab.h  compiler/src
	mv parser.tab.c  compiler/src

COMPILER_CORE = compiler/src/lexer.yy.c compiler/src/parser.tab.c compiler/src/compiler.c compiler/src/node.c compiler/src/util/flexstr.c compiler/src/util/hashmap.c compiler/src/type.c compiler/src/symbol.c compiler/src/ir.c compiler/src/codegen.c common/opcodes.c

COMPILER_OBJS = compiler/src/main.c ${COMPILER_CORE}
VM_OBJS = vm/src/*.c vm/src/lua/*.c common/opcodes.c
INTERPRETER_OBJS = interpreter/main.c ${COMPILER_CORE} vm/src/load.c vm/src/execute.c vm/src/lua/*.c

compiler: $(COMPILER_OBJS)
	gcc -o bin/luappc $^ -lm

# runtime -> vm
runtime: $(VM_OBJS)
	gcc -o bin/luappvm $^ -lm

interpreter: $(INTERPRETER_OBJS)
	gcc -o bin/luapp $^ -lm

.PHONY: interpreter runtime compiler