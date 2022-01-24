#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <assert.h>
#include <time.h>

#include "lexer.h"

static void print_summary(char *pass, int error_count, clock_t start) {
    double sec = ((clock() - start) * 1000);

    printf("\n%s encountered %d %s, elapsed time: %lf second(s).\n", 
            pass, error_count, (error_count == 1 ? "error" : "errors"), (sec / 1000000) / 1000);
}

/*
* Entrypoint for the compiler.
*
* luapp -s [lexer|parser|symbol|type|ir|codgen] -o [outputfile] [inputfile]
*
* -s : indicates the name of the stage to stop after.
*      Defaults to the last stage.
* -o : name of the output file. Defaults to "output.s"
*
* You should pass the name of the file to compile.
*/
int main(int argc, char **argv) {
    int opt, error_count;
    char *stage, *dot;
    FILE *input, *output;
    yyscan_t lexer;
    time_t start;

    stage = "codegen";
    output = stdout;
    while ((opt = getopt(argc, argv, "o:s:")) != -1) {
        switch (opt) {
            case 'o':
                output = fopen(optarg, "w");
                break;
            case 's':
                stage = optarg;
                break;
        }
    }

    if (optind == argc - 1) {
        /* check if the input file is a .lpp or .lua file */
        dot = strrchr(argv[optind], '.');

        if (dot && !strcmp(dot, ".lpp") || !strcmp(dot, ".lua")) {
            lex_init(&lexer, fopen(argv[optind], "r"));
        } else {
            printf("Incorrect file type.\n");
            return 1;
        }
    } else {
        printf("Expected 1 input file, found %d.\n", argc - optind);
        return 1;
    }

    if (!strcmp(stage, "lexer")) {
        error_count = 0;
        start = clock();
        lex_print(lexer, &error_count, output);
        lex_destroy(&lexer);

        print_summary("Lexer", error_count, start);
        return (error_count > 0) ? 1 : 0;
    }
}