%.yy.c : %.l
	flex --header-file=$(subst .yy.c,.yy.h,$@) -o $@ $<

%.tab.c : %.y
	bison -d $<

OBJS = luapp.c lexer.yy.c parser.tab.c compiler.c node.c
luapp: $(OBJS)
	gcc -o $@ $^ 