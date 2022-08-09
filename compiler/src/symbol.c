#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compiler.h"
#include "util/flexstr.h"
#include "node.h"
#include "symbol.h"

/* symbol_initialize_table() -- initializes the symbol table
 *      args: table that we will init
 *      returns: none
 */
void symbol_initialize_table(struct symbol_table *table) { table->variables = NULL; }

/* symbol_get() -- get a symbol from the symbol table
 *      args: table, the name of the symbol
 *      returns: new symbol
 */
static struct symbol *symbol_get(struct symbol_table *table, char *name)
{
    struct symbol_list *iter;
    for (iter = table->variables; NULL != iter; iter = iter->next) {
        if (!strcmp(name, iter->symbol.name)) {
            return &iter->symbol;
        }
    }
    return NULL;
}

/* symbol_put() -- add a symbol to the symbol table
 *      args: table, the name of the symbol
 *      returns: new symbol
 */
static struct symbol *symbol_put(struct symbol_table *table, char *name)
{
    struct symbol *s;
    if ((s = symbol_get(table, name)))
        return s;

    struct symbol_list *symbol_list;

    symbol_list = smalloc(sizeof(struct symbol_list));

    symbol_list->symbol.name = strdup(name);
    symbol_list->symbol.id = nextSymbolId++;

    symbol_list->next = table->variables;
    table->variables = symbol_list;

    return &symbol_list->symbol;
}

/* symbol_ast_traversal() -- traverse through the AST and build symbol tree
 *      args: context, and AST
 *      returns: none
 */
void symbol_ast_traversal(struct symbol_context *context, struct node *node)
{
    if (!node)
        return;

    /* We have to have a context and table */
    assert(context);
    assert(context->table);

    switch (node->type) {
        case NODE_IDENTIFIER:
            node->data.identifier.s = symbol_put(context->table, node->data.identifier.name);
            break;
        case NODE_STRING:
            node->data.string.s = symbol_put(context->table, node->data.string.value);
            break;
        case NODE_BLOCK:
            symbol_ast_traversal(context, node->data.block.init);
            symbol_ast_traversal(context, node->data.block.statement);
            break;
        case NODE_TYPE_ANNOTATION:
            symbol_ast_traversal(context, node->data.type_annotation.identifier);
            symbol_ast_traversal(context, node->data.type_annotation.type);
            break;
        case NODE_BINARY_OPERATION:
            symbol_ast_traversal(context, node->data.binary_operation.left);
            symbol_ast_traversal(context, node->data.binary_operation.right);
            break;
        case NODE_UNARY_OPERATION:
            symbol_ast_traversal(context, node->data.unary_operation.expression);
            break;
        case NODE_EXPRESSION_LIST:
            symbol_ast_traversal(context, node->data.expression_list.expression);
            symbol_ast_traversal(context, node->data.expression_list.init);
            break;
        case NODE_NAME_LIST:
            symbol_ast_traversal(context, node->data.name_list.init);
            symbol_ast_traversal(context, node->data.name_list.name);
            break;
        case NODE_VARIABLE_LIST:
            symbol_ast_traversal(context, node->data.variable_list.init);
            symbol_ast_traversal(context, node->data.variable_list.variable);
            break;
        case NODE_PARAMETER_LIST:
            symbol_ast_traversal(context, node->data.parameter_list.namelist);
            symbol_ast_traversal(context, node->data.parameter_list.vararg);
            break;
        case NODE_CALL:
            symbol_ast_traversal(context, node->data.call.args);
            symbol_ast_traversal(context, node->data.call.prefix_expression);
            break;
        case NODE_EXPRESSION_GROUP:
            symbol_ast_traversal(context, node->data.expression_group.expression);
            break;
        case NODE_NAME_INDEX:
            symbol_ast_traversal(context, node->data.name_index.expression);
            symbol_ast_traversal(context, node->data.name_index.index);
            break;
        case NODE_EXPRESSION_INDEX:
            symbol_ast_traversal(context, node->data.expression_index.expression);
            symbol_ast_traversal(context, node->data.expression_index.index);
            break;
        case NODE_EXPRESSION_STATEMENT:
            symbol_ast_traversal(context, node->data.expression_statement.expression);
            break;
        case NODE_ASSIGNMENT:
            symbol_ast_traversal(context, node->data.assignment.values);
            symbol_ast_traversal(context, node->data.assignment.variables);
            break;
        case NODE_WHILELOOP:
            symbol_ast_traversal(context, node->data.while_loop.body);
            symbol_ast_traversal(context, node->data.while_loop.condition);
            break;
        case NODE_REPEATLOOP:
            symbol_ast_traversal(context, node->data.repeat_loop.body);
            symbol_ast_traversal(context, node->data.repeat_loop.condition);
            break;
        case NODE_IF:
            symbol_ast_traversal(context, node->data.if_statement.body);
            symbol_ast_traversal(context, node->data.if_statement.condition);
            symbol_ast_traversal(context, node->data.if_statement.else_body);
            break;
        case NODE_NUMERICFORLOOP:
            symbol_ast_traversal(context, node->data.numerical_for_loop.body);
            symbol_ast_traversal(context, node->data.numerical_for_loop.increment);
            symbol_ast_traversal(context, node->data.numerical_for_loop.init);
            break;
        case NODE_GENERICFORLOOP:
            symbol_ast_traversal(context, node->data.generic_for_loop.body);
            symbol_ast_traversal(context, node->data.generic_for_loop.local);
            break;
        case NODE_LOCAL:
            symbol_ast_traversal(context, node->data.local.exprlist);
            symbol_ast_traversal(context, node->data.local.namelist);
            break;
        case NODE_RETURN:
            symbol_ast_traversal(context, node->data.return_statement.exprlist);
            break;
        case NODE_FUNCTION_BODY:
            symbol_ast_traversal(context, node->data.function_body.body);
            symbol_ast_traversal(context, node->data.function_body.exprlist);
            symbol_ast_traversal(context, node->data.function_body.type_list);
            break;
        case NODE_NAME_REFERENCE:
            symbol_ast_traversal(context, node->data.name_reference.identifier);
            break;
        case NODE_KEY_VALUE_PAIR:
            symbol_ast_traversal(context, node->data.key_value_pair.key);
            symbol_ast_traversal(context, node->data.key_value_pair.value);
            break;
    }
}

/* symbol_print_table() -- dumps all the contents of the symbol table to the screen
 *      args: output stream, symbol table
 *      returns: none
 */
void symbol_print_table(FILE *output, struct symbol_table *table)
{
    struct symbol_list *iter;

    fputs("symbol table:\n", output);

    for (iter = table->variables; NULL != iter; iter = iter->next) {
        fprintf(output, "  variable: %s /* %u */\n", iter->symbol.name, iter->symbol.id);
    }

    fputs("\n", output);
}