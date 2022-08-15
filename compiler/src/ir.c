#include "ir.h"
#include "limits.h"
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
    struct ir_instruction *instruction;
    instruction = smalloc(sizeof(struct ir_instruction));

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
    instruction->operands[0].type = OPERAND_A;
    instruction->operands[0].data.A = A;
    instruction->operands[1].type = OPERAND_A;
    instruction->operands[1].data.A = B;
    instruction->operands[2].type = OPERAND_A;
    instruction->operands[2].data.A = C;

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
    instruction->operands[0].type = OPERAND_A;
    instruction->operands[0].data.A = A;
    instruction->operands[1].type = OPERAND_B;
    instruction->operands[1].data.B = Bx;

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
    instruction->operands[0].type = OPERAND_A;
    instruction->operands[0].data.A = A;
    instruction->operands[1].type = OPERAND_C;
    instruction->operands[1].data.C = sBx;

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

struct ir_section *ir_build(struct ir_context *context, struct node *node) {}