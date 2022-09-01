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

/* ir_instruction() -- creates a new ir_instruction with a given operation code
 *      args: operation code
 *      rets: new ir instruction
 */
static struct ir_instruction *ir_instruction(enum ir_opcode op)
{
    struct ir_instruction *instruction = smalloc(sizeof(struct ir_instruction));

    instruction->op = op;

    instruction->next = NULL;
    instruction->prev = NULL;

    return instruction;
}

/* ir_instruction_ABC() -- creates a new ir_instruction with a given operation code and registers
 *      args: operation code, a register, b register, and c register
 *      rets: new ir instruction
 */
static struct ir_instruction *ir_instruction_ABC(enum ir_opcode op, int A, int B, int C)
{
    struct ir_instruction *instruction = ir_instruction(op);

    /* Set IR operands */
    instruction->A = A;
    instruction->B = B;
    instruction->C = C;

    instruction->mode = iABC;

    return instruction;
}

/* ir_instruction_ABx() -- creates a new ir_instruction with a given operation code and registers
 *      args: operation code, a register, bx register
 *      rets: new ir instruction
 */
static struct ir_instruction *ir_instruction_ABx(enum ir_opcode op, int A, unsigned short Bx)
{
    struct ir_instruction *instruction = ir_instruction(op);

    /* Set IR operands */
    instruction->A = A;
    instruction->Bx = Bx;

    instruction->mode = iABx;

    return instruction;
}

/* ir_instruction_AsBx() -- creates a new ir_instruction with a given operation code and registers
 *      args: operation code, a register, sbx register
 *      rets: new ir instruction
 */
static struct ir_instruction *ir_instruction_AsBx(enum ir_opcode op, int A, short sBx)
{
    struct ir_instruction *instruction = ir_instruction(op);

    /* Set IR operands */
    instruction->A = A;
    instruction->sBx = sBx;

    instruction->mode = iAsBx;

    return instruction;
}

/* ir_instruction_sub() -- creates a new sub instruction, whose purpose is to store a 32-bit value
 *      args: value
 *      rets: new ir instruction
 */
static struct ir_instruction *ir_instruction_sub(unsigned int value)
{
    struct ir_instruction *instruction = smalloc(sizeof(struct ir_instruction));

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
static struct ir_constant *ir_constant(enum ir_constant_type type)
{
    struct ir_constant *c = smalloc(sizeof(struct ir_constant));

    c->type = type;

    c->prev = NULL;
    c->next = NULL;

    return c;
}

static unsigned int ir_find_string_constant(struct ir_constant_list *list, struct symbol *symbol)
{
    int index = 0;

    for (struct ir_constant *iter = list->first; iter != NULL; iter = iter->next) {
        if (iter->type == CONSTANT_STRING && iter->data.string.symbol_id == symbol->id)
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

/* ir_constant_string() -- allocate memory for a new IR constant string
 *      args: proto, symbol
 *      rets: index in constant list
 */
static unsigned int ir_constant_string(struct ir_proto *proto, struct symbol *symbol)
{
    unsigned int index;
    if ((index = ir_find_string_constant(proto->constant_list, symbol)) == -1) {
        // We were unable to find an existing constant
        struct ir_constant *c = ir_constant(CONSTANT_STRING);
        c->data.string.symbol_id = symbol->id;

        ir_constant_list_add(proto->constant_list, c);

        return proto->constant_list->size++;
    } else
        return index;
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

/* ir_new_proto() -- allocate memory for a new empty IR function prototype
 *      args: number value
 *      rets: constant
 */
static struct ir_proto *ir_proto()
{
    struct ir_proto *p = smalloc(sizeof(struct ir_proto));

    p->constant_list = NULL;
    p->is_vararg = false;
    p->max_stack_size = 0;
    p->parameters_size = 0;
    p->top_register = 0;

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
        list = ir_constant_list(proto, proto);
    else if (list->first == NULL && list->last == NULL) {
        list->first = proto;
        list->last = proto;

        proto->prev = NULL;
        proto->next = NULL;
    } else {
        proto->next = list->last->next;
        if (proto->next != NULL)
            proto->next->prev = proto;
        list->last->next = proto;

        proto->prev = list->last;
        list->last = proto;
    }
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

            node->ir = ir_duplicate(node->data.expression_statement.expression->ir);
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

            instruction = ir_instruction_ABC(IR_CALL, old, size + 1, 1);

            ir_free_register(context, proto, size + 1);

            node->ir = ir_join(function->ir, args->ir);
            ir_append(node->ir, instruction);
            break;
        }
        case NODE_STRING: {
            struct ir_instruction *instruction;
            unsigned int index = ir_constant_string(context, node->data.string.s);

            instruction = ir_instruction_ABx(IR_LOADK, ir_allocate_register(context, proto, 1), index);

            node->ir = ir_section(instruction, instruction);
            break;
        }
        case NODE_NAME_REFERENCE: {
            node->ir = ir_build(context, node->data.name_reference.identifier, false);
            break;
        }
        case NODE_NUMBER: {
            struct ir_instruction *instruction, *sub;

            if (node->data.number.value <= SHRT_MAX && node->data.number.value >= SHRT_MIN &&
                floor(node->data.number.value) == node->data.number.value) {
                // We have a whole number that is large enough to fit in the sBx operand
                instruction = ir_instruction_AsBx(IR_LOADI, ir_allocate_register(context, proto, 1),
                                                  node->data.number.value);
                node->ir = ir_section(instruction, instruction);
                break;
            }

            unsigned int index = ir_constant_number(context, node->data.number.value);
            /* Each Lua++ instruction (like Lua) must strictly be 32-bits in size, so we need to
             * account for extremely large programs with massive constant pools */
            if (index <= UINT16_MAX) {
                instruction = ir_instruction_ABx(IR_LOADK, ir_allocate_register(context, proto, 1), index);

                node->ir = ir_section(instruction, instruction);
                break;
            } else {
                /* Here we use a sub instruction. An operation less instruction that simply stores a
                 * singular value */
                instruction = ir_instruction_ABx(IR_LOADKX, ir_allocate_register(context, proto, 1), 0);
                sub = ir_instruction_sub(index);

                node->ir = ir_section(instruction, sub);
                break;
            }
        }
        case NODE_IDENTIFIER: {
            struct ir_instruction *instruction;

            if (node->data.identifier.is_global) {
                unsigned int index = ir_constant_string(context, node->data.identifier.s);

                instruction =
                    ir_instruction_ABx(IR_GETGLOBAL, ir_allocate_register(context, proto, 1), index);
            }

            node->ir = ir_section(instruction, instruction);
            break;
        }
        case NODE_BLOCK: {
            struct ir_instruction *vararg_instr, *return_instr;
            struct node *init = node->data.block.init;
            struct node *statement = node->data.block.statement;

            if (statement == NULL) {
                ir_build_proto(context, proto, init);
                node->ir = ir_join(node->ir, init->ir);
            } else {
                ir_build_proto(context, proto, init);
                ir_build_proto(context, proto, statement);
                node->ir = ir_join(node->ir, ir_join(init->ir, statement->ir));
            }
            break;
        }
        case NODE_FUNCTION_BODY: {
            struct node *params = node->data.function_body.exprlist;
            struct node *namelist = params->data.parameter_list.namelist;

            struct ir_proto *p = ir_proto();
            p->is_vararg = params->data.parameter_list.vararg != NULL;
            p->parameters_size = namelist->data.name_list.size;

            struct ir_section *section;
            struct ir_instruction *arg_instr, *return_instr;

            if (namelist) {
                arg_instr =
                    ir_instruction_ABC(IR_ARGPREP + (params->data.parameter_list.vararg != NULL),
                                       namelist->data.name_list.size, 0, 0);
            } else {
                arg_instr = ir_instruction_ABC(
                    IR_ARGPREP + (params->data.parameter_list.vararg != NULL), 0, 0, 0);
            }
            section = ir_section(arg_instr, arg_instr);

            ir_build(context, node->data.function_body.body, false);
            section = ir_join(node->ir, node->data.function_body.body->ir);

            return_instr = ir_instruction_ABC(IR_RETURN, 0, 1, 0);
            section = ir_append(node->ir, return_instr);

            p->code = section;
            proto->protos = ir_proto_append(proto->protos, p);

            struct ir_instruction *closure = ir_instruction_ABx(
                IR_CLOSURE, ir_allocate_register(context, proto, 1), proto->protos->size - 1);
            node->ir = ir_section(closure, closure);
            break;
        }
        case NODE_EXPRESSION_LIST: {
            struct node *init = node->data.expression_list.init;
            struct node *expression = node->data.expression_list.expression;

            if (expression == NULL) {
                ir_build_proto(context, proto, init);
                node->ir = init->ir;
            } else {
                ir_build_proto(context, proto, init);
                ir_build_proto(context, proto, expression);
                node->ir = ir_join(init->ir, expression->ir);
            }
            break;
        }
    }
}

/* ir_build() -- will build a new IR section based on an AST node
 *      args: context, AST node
 *      rets: new ir section
 */
struct ir_section *ir_build(struct ir_context *context, struct node *node, bool main)
{

    return node->ir;
}

/* ir_print_context() -- will print all of the contents of the IR context
 *      args: output, context
 *      rets: none
 */
void ir_print_context(FILE *output, struct ir_context *context) {}

static void ir_print_instruction(FILE *output, struct ir_instruction *instruction)
{
    if (instruction->mode == SUB)
        fprintf(output, "%-10s", " ");
    else
        fprintf(output, "%-10s", opcode_names[instruction->op]);

    switch (instruction->mode) {
        case iABC:
            fprintf(output, "%10d %d %d", instruction->A, instruction->B, instruction->C);
            break;
        case iABx:
            fprintf(output, "%10d %hu", instruction->A, instruction->Bx);
            break;
        case iAsBx:
            fprintf(output, "%10d %d", instruction->A, instruction->sBx);
            break;
        default:
            fprintf(output, "%10d", instruction->value);
            break;
    }
}

/* ir_print_section() -- will an IR section to the console
 *      args: output, section
 *      rets: none
 */
void ir_print_section(FILE *output, struct ir_section *section)
{
    int count = 1;
    for (struct ir_instruction *iter = section->first; iter != NULL; iter = iter->next) {
        fprintf(output, "[%04d]     ", count++);
        ir_print_instruction(output, iter);
        fputc('\n', output);
    }
}