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
    /* Link the sections together */
    first->last->next = second->first;
    second->first->prev = first->last;

    return ir_section(first->first, second->last);
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

        instruction->prev = NULL;
        instruction->next = NULL;
    } else {
        instruction->next = section->last->next;
        if (instruction->next == NULL)
            instruction->next->prev = instruction;
        section->last->next = instruction;

        instruction->prev = section->last;
        section->last = instruction;
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

/* ir_allocate_register() -- 'allocates' a certain amount of registers based on the counter. In
 * reality it just checks if the counter exceeds the maximum and updates the max register counter.
 *      args: ir context, register count
 *      rets: first register available
 */
static unsigned char ir_allocate_register(struct ir_context *context, unsigned char count)
{
    unsigned char top = context->top_register;

    /* Can not exceed max byte size */
    if (context->top_register + count > UCHAR_MAX) {
        unhandled_compiler_error("out of registers when trying to allocate %d registers", count);
        context->error_count++;
    }

    context->top_register += count;

    if (context->top_register > context->stack_size)
        context->stack_size = context->top_register;

    return top;
}

/* ir_free_register() -- 'deallocates' a certain amount of registers based on the counter.
 *      args: ir context, register count
 *      rets: none
 */
static void ir_free_register(struct ir_context *context, unsigned char count)
{
    if (context->top_register - count < 0) {
        unhandled_compiler_error(
            "attempt to free %d registers setting the stack size below the minimum of 0", count);
        context->error_count++;
    }

    context->top_register -= count;
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
        if (constant->next == NULL)
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

/* ir_constant_string() -- allocate memory for a new IR constant string
 *      args: context, symbol
 *      rets: index in constant list
 */
static unsigned int ir_constant_string(struct ir_context *context, struct symbol *symbol)
{
    struct ir_constant *c = ir_constant(CONSTANT_STRING);

    c->data.string.symbol_id = symbol->id;
    ir_constant_list_add(context->constant_list, c);

    return context->constants++;
}

/* ir_constant_number() -- allocate memory for a new IR constant number
 *      args: number value
 *      rets: constant
 */
static unsigned int ir_constant_number(struct ir_context *context, double value)
{
    struct ir_constant *c = ir_constant(CONSTANT_NUMBER);

    c->data.number.value = value;
    ir_constant_list_add(context->constant_list, c);

    return context->constants++;
}
/* ir_init() -- initializes the member variables of the IR context
 *      args: context
 *      rets: none
 */

void ir_init(struct ir_context *context)
{
    context->constant_list = ir_constant_list(NULL, NULL);
    context->constants = 0;

    context->stack_size = 0;
    context->top_register = 0;
}

/* ir_build() -- will build a new IR section based on an AST node
 *      args: context, AST node
 *      rets: new ir section
 */
struct ir_section *ir_build(struct ir_context *context, struct node *node)
{
    if (!node)
        return NULL;

    switch (node->type) {
        case NODE_EXPRESSION_STATEMENT: {
            ir_build(context, node->data.expression_statement.expression);

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
            int old = context->top_register;

            ir_build(context, function);
            ir_build(context, args);

            instruction = ir_instruction_ABC(IR_CALL, old, size + 1, 1);

            // node->ir = ir_join(function->ir, args->ir);
            // ir_append(node->ir, instruction);
            node->ir = ir_section(instruction, instruction);
            break;
        }
        case NODE_STRING: {
            
            ir_constant_string(context, node->data.string.s);
            printf("adadad\n");
        }
        case NODE_BLOCK: {
            struct node *init = node->data.block.init;
            struct node *statement = node->data.block.statement;

            if (statement == NULL) {
                ir_build(context, init);
                node->ir = init->ir;
            } else {
                ir_build(context, init);
                ir_build(context, statement);
                node->ir = ir_join(init->ir, statement->ir);
            }
            break;
        }
        case NODE_EXPRESSION_LIST: {
            struct node *init = node->data.expression_list.init;
            struct node *expression = node->data.expression_list.expression;

            if (expression == NULL) {
                ir_build(context, init);
                node->ir = init->ir;
            } else {
                ir_build(context, init);
                ir_build(context, expression);
                node->ir = ir_join(init->ir, expression->ir);
            }
            break;
        }
    }

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
        fprintf(output, "%5s", " ");
    else
        fprintf(output, "%5s", opcode_names[instruction->op]);

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