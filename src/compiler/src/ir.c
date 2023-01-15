#include <math.h>
#include <stdint.h>

#include "ir.h"
#include "limits.h"
#include "node.h"
#include "symbol.h"
#include "type.h"
#include "util/flexstr.h"

/* ir_section() -- create a new list of IR instructions
 *      args: first instruction of the list, last instruction of the list
 *      rets: the new list
 *
 * Note: An IR section is just a list of ir instructions. Each node in the AST has a section
 * associated with it if there are any instructions for that node. If there aren't, it will simply
 * be NULL.
 */
static struct ir_section *ir_section(struct ir_instruction *first, struct ir_instruction *last)
{
    struct ir_section *code;
    code = smalloc(sizeof(struct ir_section));

    code->first = first;
    code->last = last;
    code->size = 1;
    return code;
}

/* ir_duplicate() -- duplicates an existing IR section
 *      args: original section
 *      rets: new section
 */
static struct ir_section *ir_duplicate(struct ir_section *original)
{
    return ir_section(original->first, original->last);
}

/* ir_join() -- joins two IR sections together to form a new IR section
 *      args: first section, second section
 *      rets: new section
 */
static struct ir_section *ir_join(struct ir_section *first, struct ir_section *second)
{
    if (first == NULL)
        return second;

    /* Link the sections together */
    first->last->next = second->first;
    second->first->prev = first->last;

    struct ir_section *section = ir_section(first->first, second->last);
    section->size = first->size + second->size;
    return section;
}

/* ir_append() -- appends an IR instruction onto an IR section
 *      args: first section, the instruction
 *      rets: new section
 */
static struct ir_section *ir_append(struct ir_section *section, struct ir_instruction *instruction)
{
    /* section is empty */
    if (section == NULL)
        section = ir_section(instruction, instruction);
    else if (section->first == NULL && section->last == NULL) {
        section->first = instruction;
        section->last = instruction;
        section->size++;

        instruction->prev = NULL;
        instruction->next = NULL;
    } else {
        instruction->next = section->last->next;
        if (instruction->next != NULL)
            instruction->next->prev = instruction;
        section->last->next = instruction;

        instruction->prev = section->last;
        section->last = instruction;
        section->size++;
    }

    return section;
}

/* ir_instruction() -- creates a new ir_instruction
 *      args: none
 *      rets: new ir instruction
 */
static struct ir_instruction *ir_instruction()
{
    struct ir_instruction *instruction = smalloc(sizeof(struct ir_instruction));

    instruction->next = NULL;
    instruction->prev = NULL;

    return instruction;
}

/* ir_instruction_ABC() -- creates a new ir_instruction with a given operation code and registers
 *      args: operation code, a register, b register, and c register
 *      rets: new ir instruction
 */
static struct ir_instruction *ir_instruction_ABC(enum opcode op, uint8_t a, uint8_t b, uint8_t c)
{
    struct ir_instruction *instruction = ir_instruction();

    /* Set IR instruction */
    instruction->value = (uint32_t)op | (a << 8) | (b << 16) | (c << 24);

    instruction->mode = iABC;

    return instruction;
}

/* ir_instruction_AD() -- creates a new ir_instruction with a given operation code and registers
 *      args: operation code, a register, d register
 *      rets: new ir instruction
 */
static struct ir_instruction *ir_instruction_AD(enum opcode op, uint8_t a, int16_t d)
{
    struct ir_instruction *instruction = ir_instruction();

    /* Set IR operands */
    instruction->value = (uint32_t)op | (a << 8) | ((uint16_t)d << 16);

    instruction->mode = iAD;

    return instruction;
}

/* ir_instruction_ADu() -- creates a new ir_instruction with a given operation code and registers
 *      args: operation code, a register, du register
 *      rets: new ir instruction
 */
static struct ir_instruction *ir_instruction_ADu(enum opcode op, uint8_t a, uint16_t du)
{
    struct ir_instruction *instruction = ir_instruction();

    /* Set IR operands */
    instruction->value = (uint32_t)op | (a << 8) | ((int16_t)du << 16);

    instruction->mode = iADu;

    return instruction;
}

/* ir_instruction_E() -- creates a new ir_instruction with a given operation code and registers
 *      args: operation code, e register
 *      rets: new ir instruction
 */
static struct ir_instruction *ir_instruction_E(enum opcode op, int32_t e)
{
    struct ir_instruction *instruction = ir_instruction();

    /* Set IR operands */
    instruction->value = (uint32_t)op | ((uint32_t)e << 8);

    instruction->mode = iE;

    return instruction;
}

/* ir_instruction_sub() -- creates a new sub instruction, whose purpose is to store a 32-bit value
 *      args: value
 *      rets: new ir instruction
 */
static struct ir_instruction *ir_instruction_sub(unsigned int value)
{
    struct ir_instruction *instruction = ir_instruction();

    /* Set IR operands */
    instruction->value = value;

    instruction->mode = SUB;

    return instruction;
}

/* ir_allocate_register() -- 'allocates' a certain amount of registers based on the counter. In
 * reality it just checks if the counter exceeds the maximum and updates the max register counter.
 *      args: ir_context, ir proto, register count
 *      rets: first register available
 */
static unsigned char ir_allocate_register(struct ir_context *context, struct ir_proto *proto,
                                          unsigned char count)
{
    unsigned char top = proto->top_register;

    /* Can not exceed max byte size */
    if (proto->top_register + count > UCHAR_MAX) {
        unhandled_compiler_error("out of registers when trying to allocate %d registers", count);
        context->error_count++;
    }

    proto->top_register += count;

    if (proto->top_register > proto->max_stack_size)
        proto->max_stack_size = proto->top_register;

    return top;
}

/* ir_free_register() -- 'deallocates' a certain amount of registers based on the counter.
 *      args: ir context, ir proto, register count
 *      rets: none
 */
static void ir_free_register(struct ir_context *context, struct ir_proto *proto,
                             unsigned char count)
{
    if (proto->top_register - count < 0) {
        unhandled_compiler_error(
            "attempt to free %d registers setting the stack size below the minimum of 0", count);
        context->error_count++;
    }

    proto->top_register -= count;
}

/* ir_constant_list() -- allocate memory for a new IR constant list
 *      args: first constant, last constant
 *      rets: new list;
 */
static struct ir_constant_list *ir_constant_list(struct ir_constant *first,
                                                 struct ir_constant *last)
{
    struct ir_constant_list *list = smalloc(sizeof(struct ir_constant_list));

    /* Set members */
    list->first = first;
    list->last = last;

    return list;
}

/* ir_constant_list_add() -- add a new constant to a given constant list
 *      args: list of constants, constant
 *      rets: none;
 */
static void ir_constant_list_add(struct ir_constant_list *list, struct ir_constant *constant)
{
    if (list == NULL)
        list = ir_constant_list(constant, constant);
    else if (list->first == NULL && list->last == NULL) {
        list->first = constant;
        list->last = constant;

        constant->prev = NULL;
        constant->next = NULL;
    } else {
        constant->next = list->last->next;
        if (constant->next != NULL)
            constant->next->prev = constant;
        list->last->next = constant;

        constant->prev = list->last;
        list->last = constant;
    }
}

/* ir_constant() -- allocate memory for a new IR constant
 *      args: type of constant
 *      rets: constant
 */
static struct ir_constant *ir_constant(constant_t type)
{
    struct ir_constant *c = smalloc(sizeof(struct ir_constant));

    c->type = type;

    c->prev = NULL;
    c->next = NULL;

    return c;
}

static unsigned int ir_find_symbol_constant(struct ir_constant_list *list, struct symbol *symbol,
                                            constant_t type)
{
    int index = 0;

    for (struct ir_constant *iter = list->first; iter != NULL; iter = iter->next) {
        if (iter->type == type && iter->data.symbol.symbol_id == symbol->id)
            return index;
        ++index;
    }

    return -1;
}

static unsigned int ir_find_number_constant(struct ir_constant_list *list, double number)
{
    int index = 0;

    for (struct ir_constant *iter = list->first; iter != NULL; iter = iter->next) {
        if (iter->type == CONSTANT_NUMBER && iter->data.number.value == number)
            return index;
        ++index;
    }

    return -1;
}

static unsigned int ir_find_env_constant(struct ir_constant_list *list, unsigned int id)
{
    int index = 0;

    for (struct ir_constant *iter = list->first; iter != NULL; iter = iter->next) {
        if (iter->type == CONSTANT_ENVIRONMENT && iter->data.env.index == index)
            return index;
        ++index;
    }

    return -1;
}

/* ir_constant_symbol() -- allocate memory for a new constant using the symbol value
 *      args: proto, symbol, constant type
 *      rets: index in constant list
 */
static unsigned int ir_constant_symbol(struct ir_proto *proto, struct symbol *symbol,
                                       constant_t type)
{
    unsigned int index;
    if ((index = ir_find_symbol_constant(proto->constant_list, symbol, type)) == -1) {

        // We were unable to find an existing constant
        struct ir_constant *c = ir_constant(type);
        c->data.symbol.symbol_id = symbol->id;

        ir_constant_list_add(proto->constant_list, c);

        return proto->constant_list->size++;
    } else
        return index;
}

/* ir_constant_string() -- allocate memory for a new IR constant string
 *      args: proto, symbol
 *      rets: index in constant list
 */
static unsigned int ir_constant_string(struct ir_proto *proto, struct symbol *symbol)
{
    return ir_constant_symbol(proto, symbol, CONSTANT_STRING);
}

/* ir_constant_number() -- allocate memory for a new IR constant number
 *      args: number value
 *      rets: constant
 */
static unsigned int ir_constant_number(struct ir_proto *proto, double value)
{
    unsigned int index;
    if ((index = ir_find_number_constant(proto->constant_list, value)) == -1) {
        // We were unable to find an existing number constant
        struct ir_constant *c = ir_constant(CONSTANT_NUMBER);

        c->data.number.value = value;
        ir_constant_list_add(proto->constant_list, c);

        return proto->constant_list->size++;
    } else
        return index;
}

/* ir_constant_env() -- allocate memory for a new global constant
 *      args: proto, symbol
 *      rets: constant
 */
static unsigned int ir_constant_env(struct ir_proto *proto, struct symbol *symbol)
{
    unsigned int id = ir_constant_symbol(proto, symbol, CONSTANT_STRING);

    unsigned int index;
    if ((index = ir_find_env_constant(proto->constant_list, id)) == -1) {

        // We were unable to find an existing constant
        struct ir_constant *c = ir_constant(CONSTANT_ENVIRONMENT);
        c->data.env.index = id;

        ir_constant_list_add(proto->constant_list, c);

        return proto->constant_list->size++;
    } else
        return index;
}

static int32_t ir_get_constant_number(struct ir_proto *proto, struct node *node)
{
    if (node->type != NODE_NUMBER)
        return -1;

    return ir_constant_number(proto, node->data.number.value);
}

/* ir_constant_number() -- allocate memory for a new function prototype list
 *      args: first proto, last proto
 *      rets: new list
 */
static struct ir_proto_list *ir_proto_list(struct ir_proto *first, struct ir_proto *last)
{
    struct ir_proto_list *list = smalloc(sizeof(struct ir_proto_list));

    list->first = first;
    list->last = last;

    list->size = 1;

    return list;
}

/* ir_proto() -- allocate memory for a new empty IR function prototype
 *      args: number value
 *      rets: constant
 */
static struct ir_proto *ir_proto()
{
    struct ir_proto *p = smalloc(sizeof(struct ir_proto));

    p->constant_list = ir_constant_list(NULL, NULL);
    p->is_vararg = false;
    p->max_stack_size = 0;
    p->parameters_size = 0;
    p->top_register = 0;
    p->upvalues_size = 0;

    p->protos = ir_proto_list(NULL, NULL);

    p->prev = NULL;
    p->next = NULL;
}

/* ir_proto_append() -- appends a new function prototype to the proto list
 *      args: list of function prototypes, the function prototype.
 *      rets: list of protos
 */
static struct ir_proto_list *ir_proto_append(struct ir_proto_list *list, struct ir_proto *proto)
{
    if (list == NULL)
        list = ir_proto_list(proto, proto);
    else if (list->first == NULL && list->last == NULL) {
        list->first = proto;
        list->last = proto;
        list->size++;
        proto->prev = NULL;
        proto->next = NULL;
    } else {
        proto->next = list->last->next;
        if (proto->next != NULL)
            proto->next->prev = proto;
        list->last->next = proto;
        list->size++;
        proto->prev = list->last;
        list->last = proto;
    }

    return list;
}

static enum opcode get_arith_opcode(enum node_binary_operation op, bool is_k)
{
    switch (op) {
        case BINOP_ADD:
            return is_k ? OP_ADDK : OP_ADD;
        case BINOP_SUB:
            return is_k ? OP_SUBK : OP_SUB;
        case BINOP_MUL:
            return is_k ? OP_MULK : OP_MUL;
        case BINOP_DIV:
            return is_k ? OP_DIVK : OP_DIV;
        case BINOP_POW:
            return is_k ? OP_POWK : OP_POW;
        case BINOP_MOD:
            return is_k ? OP_MODK : OP_MOD;
    }

    return 0;
}

/* ir_join() -- joins two IR proto lists together to shape a new list of protos
 *      args: first proto, second proto
 *      rets: new proto list
 */
static struct ir_proto_list *ir_proto_join(struct ir_proto_list *first,
                                           struct ir_proto_list *second)
{
    if (first == NULL)
        return second;

    /* Link the sections together */
    first->last->next = second->first;
    second->first->prev = first->last;

    struct ir_proto_list *proto_list = ir_proto_list(first->first, second->last);
    proto_list->size = first->size + second->size;

    return proto_list;
}

/* ir_init() -- initializes the member variables of the IR context
 *      args: context
 *      rets: none
 */
void ir_init(struct ir_context *context) { context->main_proto = ir_proto(); }

struct ir_proto *ir_build_proto(struct ir_context *context, struct ir_proto *proto,
                                struct node *node)
{
    if (!node)
        return NULL;

    switch (node->type) {
        case NODE_EXPRESSION_STATEMENT: {
            ir_build_proto(context, proto, node->data.expression_statement.expression);
            break;
        }
        case NODE_CALL: {
            struct ir_instruction *instruction;
            struct node *function = node->data.call.prefix_expression;
            struct node *args = node->data.call.args;

            int size = 0;

            /* Set the size of the args list */
            if (args)
                if (args->type != NODE_EXPRESSION_LIST)
                    size = 1;
                else
                    size = args->data.expression_list.size;

            /* Save the old register for later use */
            int old = proto->top_register;

            ir_build_proto(context, proto, function);
            ir_build_proto(context, proto, args);

            instruction = ir_instruction_ABC(OP_CALL, old, size + 1, 1);

            ir_free_register(context, proto, size + 1);

            ir_append(proto->code, instruction);
            break;
        }
        case NODE_BINARY_OPERATION: {
            /* ir build proto will alloc */
            uint8_t target = proto->top_register;

            /* Determine operation code for binary operation */
            switch (node->data.binary_operation.operation) {
                case BINOP_ADD:
                case BINOP_SUB:
                case BINOP_MUL:
                case BINOP_DIV:
                case BINOP_POW:
                case BINOP_MOD: {
                    const int32_t constant =
                        ir_get_constant_number(proto, node->data.binary_operation.right);

                    if (constant >= 0 && constant <= 255) {
                        enum opcode code =
                            get_arith_opcode(node->data.binary_operation.operation, true);

                        ir_build_proto(context, proto, node->data.binary_operation.left);

                        struct ir_instruction *instruction =
                            ir_instruction_ABC(code, target, target, constant);

                        ir_append(proto->code, instruction);
                    } else {
                        enum opcode code =
                            get_arith_opcode(node->data.binary_operation.operation, false);

                        ir_build_proto(context, proto, node->data.binary_operation.left);
                        ir_build_proto(context, proto, node->data.binary_operation.right);

                        struct ir_instruction *instruction =
                            ir_instruction_ABC(code, target, target, target + 1);

                        /* Pop the two expressions off the stack */
                        ir_free_register(context, proto, 1);

                        ir_append(proto->code, instruction);
                    }
                    break;
                }
                case BINOP_CONCAT: {
                    ir_build_proto(context, proto, node->data.binary_operation.left);
                    ir_build_proto(context, proto, node->data.binary_operation.right);

                    /* top_register contains the next availible register so -1 to get previous */
                    const uint8_t end = proto->top_register - 1;

                    struct ir_instruction *instruction =
                        ir_instruction_ABC(OP_CONCAT, target, target, end);

                    /* Pop all experssions from the stack */
                    ir_free_register(context, proto, end - target);

                    ir_append(proto->code, instruction);
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case NODE_STRING: {
            struct ir_instruction *instruction;
            unsigned int index = ir_constant_string(proto, node->data.string.s);

            instruction =
                ir_instruction_AD(OP_LOADK, ir_allocate_register(context, proto, 1), index);

            ir_append(proto->code, instruction);
            break;
        }
        case NODE_NAME_REFERENCE: {
            ir_build_proto(context, proto, node->data.name_reference.identifier);
            break;
        }
        case NODE_NUMBER: {
            struct ir_instruction *instruction, *sub;

            if (node->data.number.value <= USHRT_MAX && node->data.number.value >= -USHRT_MAX &&
                floor(node->data.number.value) == node->data.number.value) {
                /* Determine whether we have a negative or positive value */
                const bool is_positive = node->data.number.value >= 0;

                /* We have a whole number that is large enough to fit in the Du operand */
                instruction = ir_instruction_ADu(is_positive ? OP_LOADPN : OP_LOADNN,
                                                 ir_allocate_register(context, proto, 1),
                                                 node->data.number.value);
                ir_append(proto->code, instruction);
                break;
            }

            uint32_t index = ir_constant_number(proto, node->data.number.value);
            /* Each Lua++ instruction (like Lua) must strictly be 32-bits in size, so we need to
             * account for extremely large programs with massive constant pools */
            if (index <= UINT16_MAX) {
                instruction =
                    ir_instruction_AD(OP_LOADK, ir_allocate_register(context, proto, 1), index);

                ir_append(proto->code, instruction);
                break;
            } else {
                /* Here we use a sub instruction. An operation less instruction that simply stores a
                 * singular value */
                instruction =
                    ir_instruction_AD(OP_LOADKX, ir_allocate_register(context, proto, 1), 0);
                sub = ir_instruction_sub(index);

                ir_append(proto->code, instruction);
                ir_append(proto->code, sub);
                break;
            }
        }
        case NODE_BOOLEAN: {
            struct ir_instruction *instruction = ir_instruction_ABC(OP_LOADBOOL, ir_allocate_register(context, proto, 1), 
                                                                    node->data.boolean.value, 0);
            
            ir_append(proto->code, instruction);
            break;
        }
        case NODE_IDENTIFIER: {
            struct ir_instruction *instruction;

            if (node->data.identifier.is_global) {
                unsigned int index = ir_constant_env(proto, node->data.identifier.s);

                instruction =
                    ir_instruction_AD(OP_GETENV, ir_allocate_register(context, proto, 1), index);
            }

            ir_append(proto->code, instruction);
            break;
        }
        case NODE_BLOCK: {
            struct ir_instruction *vararg_instr, *return_instr;
            struct node *init = node->data.block.init;
            struct node *statement = node->data.block.statement;

            if (statement == NULL)
                ir_build_proto(context, proto, init);
            else {
                ir_build_proto(context, proto, init);
                ir_build_proto(context, proto, statement);
            }
            break;
        }
        case NODE_FUNCTION_BODY: {
            struct node *params = node->data.function_body.exprlist;
            struct node *namelist = params->data.parameter_list.namelist;

            struct ir_proto *p = ir_proto();
            p->is_vararg = params->data.parameter_list.vararg != NULL;
            p->parameters_size = namelist->data.name_list.size;

            struct ir_instruction *arg_instr = ir_instruction_ABC(
                OP_VARARGPREP, (namelist != NULL ? namelist->data.name_list.size : 0), 0, 0);

            struct ir_section *section = ir_section(arg_instr, arg_instr);

            ir_build_proto(context, proto, node->data.function_body.body);

            struct ir_instruction *return_instr = ir_instruction_ABC(OP_RETURN, 0, 1, 0);
            ir_append(proto->code, return_instr);

            ir_proto_append(proto->protos, p);

            struct ir_instruction *closure = ir_instruction_AD(
                OP_CLOSURE, ir_allocate_register(context, proto, 1), proto->protos->size - 1);
            ir_append(proto->code, closure);
            break;
        }
        case NODE_EXPRESSION_LIST: {
            struct node *init = node->data.expression_list.init;
            struct node *expression = node->data.expression_list.expression;

            if (expression == NULL)
                ir_build_proto(context, proto, init);
            else {
                ir_build_proto(context, proto, init);
                ir_build_proto(context, proto, expression);
            }
            break;
        }
    }
}

/* ir_build() -- will build a new IR proto based on an AST
 *      args: context, AST node
 *      rets: new ir section
 */
struct ir_proto *ir_build(struct ir_context *context, struct node *node)
{
    struct ir_proto *proto = ir_proto();

    /* Mark this function as a vararg function */
    proto->is_vararg = true;

    /* Build the initial argument preparation instruction */
    struct ir_instruction *instruction = ir_instruction_ABC(OP_VARARGPREP, 0, 0, 0);
    proto->code = ir_append(proto->code, instruction);

    /* Build the content of the main block */
    ir_build_proto(context, proto, node->data.function_body.body);

    /* Build the function exit instruction (return) */
    instruction = ir_instruction_ABC(OP_RETURN, 0, 1, 0);
    proto->code = ir_append(proto->code, instruction);

    return proto;
}

/* ir_collect_protos() -- will collect all protos and shove them into a list
 *      args: main/core proto
 *      rets: new ir proto list
 */
struct ir_proto_list *ir_collect_protos(struct ir_proto *main)
{
    struct ir_proto_list *list = NULL;

    /* recursively reach all function prototypes */
    for (struct ir_proto *iter = main->protos->first; iter != NULL; iter = iter->next)
        list = ir_proto_join(list, ir_collect_protos(iter));

    if (!list)
        return ir_proto_list(main, main);

    return ir_proto_append(list, main);
}

static void ir_print_instruction(FILE *output, struct ir_instruction *instruction)
{
    if (instruction->mode == SUB)
        fprintf(output, "%-10s", " ");
    else
        fprintf(output, "%-10s", opcode_names[GET_OPCODE(instruction->value)]);

    switch (instruction->mode) {
        case iABC:
            fprintf(output, "%10d %d %d", GETARG_A(instruction->value),
                    GETARG_B(instruction->value), GETARG_C(instruction->value));
            break;
        case iAD:
            fprintf(output, "%10d %hu", GETARG_A(instruction->value), GETARG_D(instruction->value));
            break;
        case iADu:
            fprintf(output, "%10d %hu", GETARG_A(instruction->value),
                    GETARG_Du(instruction->value));
            break;
        case iE:
            fprintf(output, "%10d", GETARG_E(instruction->value));
            break;
        default:
            fprintf(output, "%10d", instruction->value);
            break;
    }
}

/* ir_print_proto() -- will an IR function prototype to the console
 *      args: output, proto
 *      rets: none
 */
void ir_print_proto(FILE *output, struct ir_proto *proto)
{
    fprintf(output, "----------------------------------------------------------------\n");

    /* Dump the function prototype information */
    fprintf(output, "proto->is_vararg       %7s\n", proto->is_vararg ? "true" : "false");
    fprintf(output, "proto->parameters_size %7d\n", proto->parameters_size);
    fprintf(output, "proto->max_stack_size  %7d\n", proto->max_stack_size);
    fprintf(output, "proto->upvalues_size   %7d\n", proto->upvalues_size);

    /* Spacing... lol */
    fputc('\n', output);

    /* Dump all of the instructions */
    int count = 1;
    for (struct ir_instruction *iter = proto->code->first; iter != NULL; iter = iter->next) {
        fprintf(output, "[%04d]     ", count++);
        ir_print_instruction(output, iter);
        fputc('\n', output);
    }

    fputc('\n', output);

    /* Dump all constants */
    fprintf(output, "constants:\n");

    int id = 0;
    for (struct ir_constant *iter = proto->constant_list->first; iter != NULL; iter = iter->next) {
        /* Dump individual constants */
        switch (iter->type) {
            case CONSTANT_STRING:
                fprintf(output, "[%d]   string      { %d }\n", id++, iter->data.symbol.symbol_id);
                break;
            case CONSTANT_ENVIRONMENT:
                fprintf(output, "[%d]   environment { k(%d) }\n", id++, iter->data.env.index);
                break;
            case CONSTANT_NUMBER:
                fprintf(output, "[%d]   number      { %f }\n", id++, iter->data.number.value);
                break;
        }
    }

    fprintf(output, "----------------------------------------------------------------\n");

    /* Dump all protos within the current one (if any) */
    for (struct ir_proto *iter = proto->protos->first; iter != NULL; iter = iter->next)
        ir_print_proto(output, iter);
}

/* ir_print_context() -- will print all of the contents of the IR context
 *      args: output, context
 *      rets: none
 */
void ir_print_context(FILE *output, struct ir_context *context)
{
    /* Dump the symbol table */
    symbol_print_table(output, context->table);

    /* Dump the main function prototype */
    ir_print_proto(output, context->main_proto);
}