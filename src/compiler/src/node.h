#ifndef _NODE_H
#define _NODE_H

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void *yyscan_t;
#endif

#include <assert.h>
#include <float.h>
#include <stdbool.h>

#include "compiler.h"
#include "symbol.h"

struct type;

enum node_type {
    NODE_NUMBER,
    NODE_IDENTIFIER,
    NODE_STRING,
    NODE_BOOLEAN,
    NODE_NIL,
    NODE_TYPE_ANNOTATION,
    NODE_BINARY_OPERATION,
    NODE_UNARY_OPERATION,
    NODE_EXPRESSION_LIST,
    NODE_NAME_LIST,
    NODE_VARIABLE_LIST,
    NODE_PARAMETER_LIST,
    NODE_CALL,
    NODE_EXPRESSION_GROUP,
    NODE_NAME_INDEX,
    NODE_EXPRESSION_INDEX,
    NODE_EXPRESSION_STATEMENT,
    NODE_BLOCK,
    NODE_ASSIGNMENT,
    NODE_WHILELOOP,
    NODE_REPEATLOOP,
    NODE_IF,
    NODE_NUMERICFORLOOP,
    NODE_GENERICFORLOOP,
    NODE_LOCAL,
    NODE_RETURN,
    NODE_BREAK,
    NODE_FUNCTION_BODY,
    NODE_VARARG,
    NODE_TYPE_LIST,
    NODE_TYPE,
    NODE_TYPE_ARRAY,
    NODE_TYPE_TABLE,
    NODE_TYPE_FUNCTION,
    NODE_NAME_REFERENCE,
    NODE_ARRAY_CONSTRUCTOR, /* local a: Array<number> = { 1, 2, 3, 4 } */
    NODE_KEY_VALUE_PAIR,
    NODE_TABLE_CONSTRUCTOR,
};

#define NODE_SIZE (int32_t) NODE_TABLE_CONSTRUCTOR + 1

extern const char *const node_names[NODE_SIZE + 1];

/* Binary operations */
enum node_binary_operation {
    /* Arithmetic operations */
    BINOP_MUL,
    BINOP_DIV,
    BINOP_ADD,
    BINOP_SUB,
    BINOP_POW,
    BINOP_MOD,
    BINOP_CONCAT,
    /* Comparative */
    BINOP_GT,
    BINOP_LT,
    BINOP_GE,
    BINOP_LE,
    BINOP_EQ,
    BINOP_NE,
    BINOP_AND,
    BINOP_OR
};

/* Unary operations (-, not, #) */
enum node_unary_operation { UNOP_NEG, UNOP_NOT, UNOP_LEN };

/* Assignment types */
enum node_assignment_type {
    ASSIGN,
    ASSIGN_MUL,
    ASSIGN_DIV,
    ASSIGN_ADD,
    ASSIGN_SUB,
    ASSIGN_POW,
    ASSIGN_MOD,
    ASSIGN_CON
};

/* Node struct with data unions */
struct node {
    enum node_type type;
    struct type *node_type;
    struct YYLTYPE location;
    struct ir_section *ir;
    union {
        struct {
            double value;
            bool overflow; /* Indicates double overflow */
        } number;
        struct {
            char *name;
            struct symbol *s;
            bool is_global;
        } identifier;
        struct {
            char *value;
            struct symbol *s;
        } string;
        struct {
            bool value;
        } boolean;
        struct {
            struct node *identifier;
            struct node *type;
        } type_annotation;
        struct {
            enum node_binary_operation operation;
            struct node *left;  /* Left operand */
            struct node *right; /* Right operand */
        } binary_operation;
        struct {
            enum node_unary_operation operation;
            struct node *expression; /* Operand */
        } unary_operation;
        struct {
            struct node *init;       /* First expression */
            struct node *expression; /* Next expression */
            int size;
        } expression_list;
        struct {
            struct node *init; /* First expression */
            struct node *name; /* Next expression */
            int size;
        } name_list;
        struct {
            struct node *init;     /* First expression */
            struct node *variable; /* Next expression */
            int size;
        } variable_list;
        struct {
            struct node *namelist;
            struct node *vararg;
            int size;
        } parameter_list;
        struct {
            struct node *expression;
        } expression_statement;
        struct {
            struct node *prefix_expression;
            struct node *args;
            bool self_call; // Depricated: self syntax only for tables. Class methods force the
        } call;             // creation of the self variable.
        struct {
            struct node *expression;
        } expression_group;
        struct {
            struct node *expression;
            struct node *index;
            bool self_index; /* prefixexp `:´ Name  ->  only in self-calls */
        } name_index;
        struct {
            struct node *expression;
            struct node *index;
        } expression_index;
        struct {
            struct node *init;      /* First statement */
            struct node *statement; /* Next statement */
        } block;
        struct {
            struct node *variables;
            enum node_assignment_type type;
            struct node *values;
        } assignment;
        struct {
            struct node *condition;
            struct node *body; /* Usually block */
        } while_loop;
        struct {
            struct node *body; /* Usually block */
            struct node *condition;
        } repeat_loop;
        struct {
            struct node *condition;
            struct node *body;
            struct node *else_body;
        } if_statement;
        struct {
            struct node *init;
            struct node *target;    /* Max/min value - depends on forloop type */
            struct node *increment; /* Increment/decrement - depends on forloop type */
            struct node *body;
        } numerical_for_loop;
        struct {
            struct node *local;
            struct node *body;
        } generic_for_loop;
        struct {
            struct node *namelist;
            struct node *exprlist;
        } local;
        struct {
            struct node *exprlist;
        } return_statement;
        struct {
            struct node *exprlist;
            struct node *type_list;
            struct node *body;
        } function_body;
        struct {
            struct node *init;
            struct node *type;
            int size;
        } type_list;
        struct {
            struct node *identifier;
        } name_reference;
        struct {
            struct node *exprlist;
        } array_constructor;
        struct {
            struct node *key;
            struct node *value;
        } key_value_pair;
        struct {
            struct node *pairlist;
        } table_constructor;
    } data;
};

/* binary_operations -- the string values of all binary operations */
static const char *binary_operations[] = {"*", "/",  "+",  "-",  "^",  "%",   "..", ">",
                                          "<", ">=", "<=", "==", "~=", "and", "or", NULL};

/* unary_operations -- the string values of all unary operations */
static const char *unary_operations[] = {"-", "not", "#", NULL};

/* assignment_types -- the string values of all assignment types */
static const char *assignment_types[] = {"=", "+=", "-=", "*=", "/=", "%=", "^=", "..=", NULL};

/* Node create method constructor */
static struct node *node_create(YYLTYPE location, enum node_type type);

/* Node expression constructors */
struct node *node_number(YYLTYPE location, char *value);
struct node *node_identifier(YYLTYPE location, char *value);
struct node *node_string(YYLTYPE location, char *value);
struct node *node_boolean(YYLTYPE location, bool value);
struct node *node_nil(YYLTYPE location);
struct node *node_type_annotation(YYLTYPE location, struct node *identifier, struct node *type);
struct node *node_type_list(YYLTYPE location, struct node *init, struct node *type);
struct node *node_type(YYLTYPE location, struct type *type);
struct node *node_type_array(YYLTYPE location, struct node *type);
struct node *node_type_table(YYLTYPE location, struct node *left, struct node *right);
struct node *node_type_function(YYLTYPE location, struct node *args, struct node *rets);
struct node *node_binary_operation(YYLTYPE location, enum node_binary_operation operation,
                                   struct node *left, struct node *right);
struct node *node_unary_operation(YYLTYPE location, enum node_unary_operation operation,
                                  struct node *expression);
struct node *node_expression_list(YYLTYPE location, struct node *init, struct node *expression);
struct node *node_parameter_list(YYLTYPE location, struct node *namelist, struct node *vararg);
struct node *node_name_list(YYLTYPE location, struct node *init, struct node *name);
struct node *node_variable_list(YYLTYPE location, struct node *init, struct node *variable);
struct node *node_call(YYLTYPE location, struct node *prefix_expression, struct node *args,
                       bool self_call);
struct node *node_expression_group(YYLTYPE location, struct node *expression);
struct node *node_name_index(YYLTYPE location, struct node *expression, struct node *index,
                             bool self_index);
struct node *node_expression_index(YYLTYPE location, struct node *expression, struct node *index);
struct node *node_function_body(YYLTYPE location, struct node *exprlist, struct node *type_list,
                                struct node *body);
struct node *node_vararg(YYLTYPE location);
struct node *node_name_reference(YYLTYPE location, struct node *nameref);
struct node *node_array_constructor(YYLTYPE location, struct node *exprlist);
struct node *node_key_value_pair(YYLTYPE location, struct node *key, struct node *value);
struct node *node_table_constructor(YYLTYPE location, struct node *pairlist);

/* Node statement constructors */
struct node *node_expression_statement(YYLTYPE location, struct node *expression);
struct node *node_block(YYLTYPE location, struct node *init, struct node *statement);
struct node *node_assignment(YYLTYPE location, struct node *variables,
                             enum node_assignment_type type, struct node *values);
struct node *node_while_loop(YYLTYPE location, struct node *condition, struct node *body);
struct node *node_repeat_loop(YYLTYPE location, struct node *body, struct node *condition);
struct node *node_if_statement(YYLTYPE location, struct node *condition, struct node *body,
                               struct node *else_body);
struct node *node_numerical_for_loop(YYLTYPE location, struct node *init, struct node *target,
                                     struct node *increment, struct node *body);
struct node *node_generic_for_loop(YYLTYPE location, struct node *local, struct node *body);
struct node *node_local(YYLTYPE location, struct node *namelist, struct node *exprlist);
struct node *node_return(YYLTYPE location, struct node *exprlist);
struct node *node_break(YYLTYPE location);

/* Graphviz generation methods */
void write_node(FILE *output, char *name, bool higlight);
void write_parentless_node(FILE *output, char *name, bool higlight);
char *format_node(struct node *node);
void print_ast(FILE *output, struct node *node, bool first);

/* Helper functions used in other code */
char *node_to_string(struct node *node);
int node_get_size(struct node *node);

#endif