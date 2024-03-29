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
    code->size = first && last ? 1 : 0;
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
    instruction->value = CREATE_iABC(op, a, b, c);

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
    instruction->value = CREATE_iAD(op, a, d);

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
    instruction->value = CREATE_iADu(op, a, du);

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
    instruction->value = CREATE_iE(op, e);

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
    if (proto->target_register > -1)
        return proto->target_register;

    unsigned char top = proto->top_register;

    /* Can not exceed max byte size */
    if (proto->top_register + count > UCHAR_MAX) {
        lcompiler_error("out of registers when trying to allocate %d registers", count);
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
        lcompiler_error(
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

    list->size = first && last ? 1 : 0;

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

static int ir_find_env_constant(struct ir_constant_list *list, unsigned int id)
{
    int index = 0;

    for (struct ir_constant *iter = list->first; iter != NULL; iter = iter->next) {
        if (iter->type == CONSTANT_ENVIRONMENT && iter->data.env.index == id)
            return index;
        ++index;
    }

    return -1;
}

static struct node *ir_create_array_constant(struct ir_constant_list *list, struct node *n)
{
    /* TODO: #7 Add array constant for arrays that consist of constant literals. */
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
        // printf("ADDING SYMBOL %u\n", symbol->id);
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

    int index;
    if ((index = ir_find_env_constant(proto->constant_list, id)) == -1) {
        // printf("ADDING CONSTANT ENV (%u)\n", id);
        // We were unable to find an existing constant
        struct ir_constant *c = ir_constant(CONSTANT_ENVIRONMENT);
        c->data.env.index = id;

        ir_constant_list_add(proto->constant_list, c);

        return proto->constant_list->size++;
    } else
        return index;
}

/* ir_constant_array() -- allocate memory for a new array constant
 *       args: array constructor
 *       rets: constant index
 */
static uint32_t ir_constant_array(struct ir_proto *p, struct node *n) {}

static int32_t ir_get_constant_number(struct ir_proto *proto, struct node *node)
{
    if (node->type != NODE_NUMBER)
        return -1;

    return ir_constant_number(proto, node->data.number.value);
}

typedef struct register_data {
    int32_t reg;
} register_data_t;

static int32_t ir_get_local_register(struct ir_context *context, char *name)
{
    register_data_t *data;

    if (hashmap_get(context->local_map, name, (void **)(&data)) == MAP_OK)
        return data->reg;

    return -1;
}

static void ir_set_local_register(struct ir_context *context, char *name, uint8_t reg)
{
    register_data_t *data = malloc(sizeof(register_data_t));
    data->reg = reg;

    assert(hashmap_put(context->local_map, name, data) == MAP_OK);
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

    list->size = first && last ? 1 : 0;

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
    p->target_register = -1;
    p->upvalues_size = 0;
    p->proto_size = 0;
    p->code = ir_section(NULL, NULL);
    p->mult_ret = true;

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

static enum opcode get_compare_opcode(enum node_binary_operation op)
{
    switch (op) {
        case BINOP_NE:
            return OP_NEJMP;
        case BINOP_EQ:
            return OP_EQJMP;
        case BINOP_GE:
        case BINOP_LE:
            return OP_LEJMP;
        case BINOP_GT:
        case BINOP_LT:
            return OP_LTJMP;
        default:
            break;
    }
}

static enum opcode get_unary_opcode(enum node_unary_operation op)
{
    switch (op) {
        case UNOP_NOT:
            return OP_NOT;
        case UNOP_NEG:
            return OP_UNM;
        case UNOP_LEN:
            return OP_LEN;
        default:
            return OP_NOP;
    }
}

static void ir_load_function_args(struct ir_context *c, struct ir_proto *p, struct node *args)
{
    assert(args->type == NODE_NAME_LIST);

    for (struct node *iter = args; iter; iter = iter->data.name_list.init) {
        /* Get name */
        struct node *name = iter->type == NODE_NAME_LIST ? iter->data.name_list.name : iter;
        const uint8_t reg = ir_allocate_register(c, p, 1);

        if (name->type == NODE_TYPE_ANNOTATION)
            ir_set_local_register(c, name->data.type_annotation.identifier->data.identifier.name,
                                  reg);
        else /* assert NODE_IDENTIFIER */
            ir_set_local_register(c, name->data.identifier.name, reg);

        if (iter->type != NODE_NAME_LIST)
            break;
    }
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
void ir_init(struct ir_context *context)
{
    context->protos = ir_proto_list(NULL, NULL);
    context->local_map = hashmap_new();
}

/* ir_destroy() -- destroys the IR context. Must be called if initialized.
 *      args: context
 *      rets: none
 */
void ir_destroy(struct ir_context *context)
{
    if (context->local_map)
        hashmap_free(context->local_map);
}

uint8_t ir_target_register(struct ir_proto *proto)
{
    const uint8_t result =
        proto->target_register == -1 ? proto->top_register : proto->target_register;

    /* Reset target register for future instructions */
    proto->target_register = -1;

    return result;
}

uint8_t ir_get_name_register(struct ir_context *context, struct ir_proto *proto, struct node *node)
{
    int32_t reg;

    if (node->type == NODE_NAME_REFERENCE &&
        node->data.name_reference.identifier->type == NODE_IDENTIFIER) {

        node = node->data.name_reference.identifier;
        if ((reg = ir_get_local_register(context, node->data.identifier.name)) > -1)
            return reg;
    }

    reg = proto->top_register;
    ir_build_proto(context, proto, node);

    return reg;
}

void ir_build_assignment(struct ir_context *context, struct ir_proto *proto,
                         struct node *expression, const uint8_t value)
{
    const uint8_t target = proto->top_register;

    switch (expression->type) {
        case NODE_EXPRESSION_INDEX: {
            const uint8_t target =
                ir_get_name_register(context, proto, expression->data.expression_index.expression);

            const uint8_t index = proto->top_register;
            ir_build_proto(context, proto, expression->data.expression_index.index);

            ir_append(proto->code, ir_instruction_ABC(OP_SETTABLE, target, index, value));
            break;
        }
        default:
            break;
    }
}

struct ir_proto *ir_build_proto(struct ir_context *context, struct ir_proto *proto,
                                struct node *node)
{
    if (!node)
        return NULL;
    //printf("NODE %s\n", node_names[node->type]);
    switch (node->type) {
        case NODE_EXPRESSION_STATEMENT: {
            proto->mult_ret = false;
            ir_build_proto(context, proto, node->data.expression_statement.expression);
            break;
        }
        case NODE_ARRAY_CONSTRUCTOR: {
            const uint8_t top = ir_allocate_register(context, proto, 1);
            const size_t size = node->data.array_constructor.exprlist->data.expression_list.size;

            ir_append(proto->code, ir_instruction_ABC(OP_NEWTABLE, top, size, 0));

            if (size) {
                ir_build_proto(context, proto, node->data.array_constructor.exprlist);
                ir_append(proto->code, ir_instruction_ABC(OP_SETLIST, top, size, 1));
            }
            break;
        }
        case NODE_TABLE_CONSTRUCTOR: {
            const uint8_t top = ir_allocate_register(context, proto, 1);

            struct node *expr = node->data.table_constructor.pairlist;
            const uint8_t size =
                expr->type == NODE_EXPRESSION_LIST ? expr->data.expression_list.size : 1;

            ir_append(proto->code, ir_instruction_ABC(OP_NEWTABLE, top, size, 0));

            if (size) {
                for (expr; expr != NULL; expr = expr->data.expression_list.init) {

                    struct node *n = expr->type == NODE_EXPRESSION_LIST
                                         ? expr->data.expression_list.expression
                                         : expr;

                    const uint8_t key = proto->top_register;
                    ir_build_proto(context, proto, n->data.key_value_pair.key);

                    const uint8_t value = proto->top_register;
                    ir_build_proto(context, proto, n->data.key_value_pair.value);

                    ir_append(proto->code, ir_instruction_ABC(OP_SETTABLE, top, key, value));

                    ir_free_register(context, proto, value - key + 1);
                    if (expr->type != NODE_EXPRESSION_LIST)
                        break;
                }
            }
            break;
        }
        case NODE_EXPRESSION_INDEX: {
            const uint8_t target = ir_allocate_register(context, proto, 1);

            struct node *expression = node->data.expression_index.expression;
            int32_t var = ir_get_name_register(context, proto, expression);

            struct node *index = node->data.expression_index.index;

            if (index->type == NODE_NUMBER) {
                double number = index->data.number.value;

                if (number >= 1 && number <= 256) {
                    ir_append(proto->code, ir_instruction_ABC(OP_GETTABLEN, target, var, number));
                    break;
                }
            }

            const uint8_t idx = proto->top_register;
            ir_build_proto(context, proto, index);

            ir_append(proto->code, ir_instruction_ABC(OP_GETTABLE, target, var, idx));
            break;
        }
        case NODE_CALL: {
            struct ir_instruction *instruction;
            struct node *function = node->data.call.prefix_expression;
            struct node *args = node->data.call.args;

            uint8_t c = !proto->mult_ret;

            if (!proto->mult_ret)
                proto->mult_ret = true;

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

            uint8_t b = node_expression_list_contains(args, NODE_CALL) ? 0 : size + 1;

            instruction = ir_instruction_ABC(OP_CALL, old, b, c);

            ir_free_register(context, proto, b);

            ir_append(proto->code, instruction);
            break;
        }
        case NODE_IF: {
            struct node *condition = node->data.if_statement.condition;
            const uint8_t top = ir_get_name_register(context, proto, condition);

            /* jump will be overriden later */
            struct ir_instruction *jump = ir_instruction_AD(OP_JMPIFNOT, top, 0);
            ir_append(proto->code, jump);

            /* cache old program counter for jump calculation */
            const uint32_t old_pc = proto->code->size;

            ir_build_proto(context, proto, node->data.if_statement.body);

            /* jump out instruction */
            struct ir_instruction *jump_out = ir_instruction_E(OP_JMPBACK, proto->code->size);
            ir_append(proto->code, jump_out);

            /* calculate jump size */
            jump->value = CREATE_iAD(OP_JMPIFNOT, top, proto->code->size - old_pc);

            ir_build_proto(context, proto, node->data.if_statement.else_body);

            jump_out->value =
                CREATE_iE(OP_JMPBACK, proto->code->size - GETARG_E(jump_out->value) - 1);
            break;
        }
        case NODE_ASSIGNMENT: {
            struct node *exprlist = node->data.assignment.values;
            struct node *namelist = node->data.assignment.variables;

            while (true) {
                struct node *name = NULL;
                struct node *expr = NULL;

                if (namelist->type == NODE_NAME_LIST) {
                    name = namelist->data.name_list.name->data.name_reference.identifier;
                    expr = exprlist->data.expression_list.expression;
                } else {
                    name = namelist->data.name_reference.identifier;
                    expr = exprlist;
                }

                /* top register will now be local's register */
                uint8_t target = proto->top_register;
                if (name->type == NODE_IDENTIFIER)
                    target = ir_get_local_register(context, name->data.identifier.name);
                else
                    ir_build_proto(context, proto, name);

                switch (node->data.assignment.type) {
                    case ASSIGN: {
                        proto->target_register = target;

                        ir_build_proto(context, proto, expr);

                        proto->target_register = -1;
                        break;
                    }
                    case ASSIGN_DIV:
                    case ASSIGN_MOD:
                    case ASSIGN_POW:
                    case ASSIGN_SUB:
                    case ASSIGN_MUL:
                    case ASSIGN_ADD: {
                        const uint8_t top = proto->top_register;
                        enum opcode code = get_arith_opcode(node->data.assignment.type - 1, false);

                        ir_build_proto(context, proto, expr);

                        ir_append(proto->code, ir_instruction_ABC(code, target, target, top));
                        break;
                    }
                    case ASSIGN_CON: {
                        const uint8_t top = ir_allocate_register(context, proto, 1);
                        ir_append(proto->code, ir_instruction_ABC(OP_MOVE, top, target, 0));

                        ir_build_proto(context, proto, expr);

                        const uint8_t bottom = proto->top_register - 1;

                        ir_append(proto->code, ir_instruction_ABC(OP_CONCAT, target, top, bottom));
                        break;
                    }
                }

                if (name->type != NODE_IDENTIFIER)
                    ir_build_assignment(context, proto, name, target);

                if (namelist->type != NODE_NAME_LIST)
                    break;
            }

            break;
        }
        case NODE_WHILELOOP: {
            const uint8_t top = proto->top_register;

            ir_build_proto(context, proto, node->data.while_loop.condition);

            struct ir_instruction *jump = ir_instruction_AD(OP_JMPIF, top, 0);
            ir_append(proto->code, jump);

            /* cache old program counter for jump calculation */
            const uint32_t old_pc = proto->code->size;

            ir_build_proto(context, proto, node->data.while_loop.body);

            /* calculate jump size */
            const uint32_t jmp = proto->code->size - old_pc;

            ir_append(proto->code, ir_instruction_E(OP_JMPBACK, -jmp));

            jump = ir_instruction_AD(OP_JMPIF, top, jmp);
            break;
        }
        case NODE_REPEATLOOP: {
            /* cache instruction position for jump */
            const int32_t jump_back_pc = proto->code->size;

            ir_build_proto(context, proto, node->data.repeat_loop.body);

            const uint8_t top = proto->top_register;

            ir_build_proto(context, proto, node->data.repeat_loop.condition);

            const int32_t jump = -(proto->code->size - jump_back_pc) - 2;
            ir_append(proto->code, ir_instruction_AD(OP_JMPIF, top, 1));
            ir_append(proto->code, ir_instruction_E(OP_JMPBACK, jump));
            break;
        }
        case NODE_BINARY_OPERATION: {
            /* ir build proto will alloc */
            const uint8_t target = ir_target_register(proto);

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

                    /* top_register contains the next availible register so -1 to get
                     * previous */
                    const uint8_t end = proto->top_register - 1;

                    struct ir_instruction *instruction =
                        ir_instruction_ABC(OP_CONCAT, target, target, end);

                    /* Pop all experssions from the stack */
                    ir_free_register(context, proto, end - target);

                    ir_append(proto->code, instruction);
                    break;
                }
                case BINOP_GE:
                case BINOP_LE:
                case BINOP_GT:
                case BINOP_LT:
                case BINOP_NE:
                case BINOP_EQ: {
                    enum opcode op = get_compare_opcode(node->data.binary_operation.operation);

                    ir_build_proto(context, proto, node->data.binary_operation.left);
                    ir_build_proto(context, proto, node->data.binary_operation.right);

                    const uint8_t end = proto->top_register - 1;

                    if (node->data.binary_operation.operation == BINOP_GE ||
                        node->data.binary_operation.operation == BINOP_GT)
                        ir_append(proto->code, ir_instruction_ABC(op, target, end, target));
                    else
                        ir_append(proto->code, ir_instruction_ABC(op, target, target, end));

                    ir_append(proto->code, ir_instruction_sub(0)); /* skip none */

                    /* Pop all experssions from the stack */
                    ir_free_register(context, proto, end - target);
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case NODE_UNARY_OPERATION: {
            enum opcode op;

            const uint8_t top = ir_allocate_register(context, proto, 1);
            const uint8_t reg =
                ir_get_name_register(context, proto, node->data.unary_operation.expression);

            /* Easy unary operator? */
            if ((op = get_unary_opcode(node->data.unary_operation.operation)) != OP_NOP) {
                ir_append(proto->code, ir_instruction_ABC(op, top, reg, 0));
                break;
            }

            /* Used for all increment/decrement */
            int32_t rc = ir_constant_number(proto, 1);
            ir_free_register(context, proto, 1);

            switch (node->data.unary_operation.operation) {
                case UNOP_INCRRET:
                    ir_append(proto->code, ir_instruction_ABC(OP_ADDK, reg, reg, rc));
                    break;
                case UNOP_DECRRET:
                    ir_append(proto->code, ir_instruction_ABC(OP_SUBK, reg, reg, rc));
                    break;
            }

            ir_build_proto(context, proto, node->data.unary_operation.expression);

            switch (node->data.unary_operation.operation) {
                case UNOP_INCR:
                    ir_append(proto->code, ir_instruction_ABC(OP_ADDK, reg, reg, rc));
                    break;
                case UNOP_DECR:
                    ir_append(proto->code, ir_instruction_ABC(OP_SUBK, reg, reg, rc));
                    break;
            }
            break;
        }
        case NODE_STRING: {
            const uint32_t index = ir_constant_string(proto, node->data.string.s);
            const uint8_t target = ir_allocate_register(context, proto, 1);

            ir_append(proto->code, ir_instruction_AD(OP_LOADK, target, index));
            break;
        }
        case NODE_NAME_REFERENCE: {
            ir_build_proto(context, proto, node->data.name_reference.identifier);
            break;
        }
        case NODE_EXPRESSION_GROUP: {
            ir_build_proto(context, proto, node->data.expression_group.expression);
            break;
        }
        case NODE_NUMBER: {
            struct ir_instruction *instruction, *sub;
            const uint8_t target = ir_allocate_register(context, proto, 1);

            if (node->data.number.value <= USHRT_MAX && node->data.number.value >= -USHRT_MAX &&
                floor(node->data.number.value) == node->data.number.value) {
                /* Determine whether we have a negative or positive value */
                const bool is_positive = node->data.number.value >= 0;

                /* We have a whole number that is large enough to fit in the Du operand
                 */
                instruction = ir_instruction_ADu(is_positive ? OP_LOADPN : OP_LOADNN, target,
                                                 fabs(node->data.number.value));
                ir_append(proto->code, instruction);
                break;
            }

            uint32_t index = ir_constant_number(proto, node->data.number.value);
            /* Each Lua++ instruction (like Lua) must strictly be 32-bits in size, so we
             * need to
             * account for extremely large programs with massive constant pools */
            if (index <= UINT16_MAX) {
                instruction = ir_instruction_AD(OP_LOADK, target, index);

                ir_append(proto->code, instruction);
                break;
            } else {
                /* Here we use a sub instruction. An operation less instruction that
                 * simply stores a singular value */
                instruction = ir_instruction_AD(OP_LOADKX, target, 0);
                sub = ir_instruction_sub(index);

                ir_append(proto->code, instruction);
                ir_append(proto->code, sub);
                break;
            }
        }
        case NODE_BOOLEAN: {
            const uint8_t target = ir_allocate_register(context, proto, 1);

            struct ir_instruction *instruction =
                ir_instruction_ABC(OP_LOADBOOL, target, node->data.boolean.value, 0);

            ir_append(proto->code, instruction);
            break;
        }
        case NODE_IDENTIFIER: {
            const uint8_t target = ir_allocate_register(context, proto, 1);
            const int32_t reg = ir_get_local_register(context, node->data.identifier.name);
            /* If reference to local variable, move it into the stack frame */
            if (reg >= 0)
                ir_append(proto->code, ir_instruction_ABC(OP_MOVE, target, reg, 0));
            /* Identifier must be reference to global variable */
            else {
                const uint32_t index = ir_constant_env(proto, node->data.identifier.s);

                ir_append(proto->code, ir_instruction_AD(OP_GETENV, target, index));
            }
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
            const struct node *params = node->data.function_body.exprlist;
            struct node *namelist = params ? params->data.parameter_list.namelist : NULL;
       
            /* Create new function prototype */
            struct ir_proto *p = ir_proto();
            p->is_vararg = params ? params->data.parameter_list.vararg != NULL : false;
            p->parameters_size = namelist ? namelist->data.name_list.size : 0;
 
            /* First couple registers will point to function parameters (load them) */
            if (p->parameters_size)
                ir_load_function_args(context, p, namelist);

            /* Prepare function params if vararg is present */
            if (p->is_vararg)
                ir_append(p->code, ir_instruction_ABC(OP_VARARGPREP, p->parameters_size, 0, 0));

            ir_build_proto(context, p, node->data.function_body.body);
            
            /* Keep constant return result for now */
            ir_append(p->code, ir_instruction_ABC(OP_RETURN, 0, 1, 0));
            ir_proto_append(context->protos, p);

            proto->protos[proto->proto_size++] = context->protos->size - 1;

            /* Add closure instruction in main proto */
            ir_append(proto->code,
                      ir_instruction_AD(OP_CLOSURE, ir_allocate_register(context, proto, 1),
                                        proto->proto_size - 1));
            break;
        }
        case NODE_EXPRESSION_LIST: {
            struct node *init = node->data.expression_list.init;
            struct node *expression = node->data.expression_list.expression;

            if (expression == NULL)
                ir_build_proto(context, proto, init);
            else {
                ir_build_proto(context, proto, expression);
                ir_build_proto(context, proto, init);
            }
            break;
        }
        case NODE_LOCAL: {
            uint8_t first = proto->top_register;

            ir_build_proto(context, proto, node->data.local.exprlist);

            struct node *namelist = node->data.local.namelist;

            while (true) {
                struct node *n = NULL;

                if (namelist->type == NODE_NAME_LIST)
                    n = namelist->data.name_list.name;
                else
                    n = namelist;

                if (n->type == NODE_TYPE_ANNOTATION) {
                    ir_set_local_register(
                        context, n->data.type_annotation.identifier->data.identifier.name, first++);
                } else if (n->type == NODE_IDENTIFIER)
                    ir_set_local_register(context, n->data.identifier.name, first++);

                if (namelist->type != NODE_NAME_LIST)
                    break;
            }
            break;
        }
        case NODE_RETURN: {
            const uint8_t top = proto->top_register;
            const size_t size =
                node->data.return_statement.exprlist->type == NODE_EXPRESSION_LIST
                    ? node->data.return_statement.exprlist->data.expression_list.size
                    : 1;

            ir_build_proto(context, proto, node->data.return_statement.exprlist);

            ir_append(proto->code, ir_instruction_ABC(OP_RETURN, top, size + 1, 0));
            break;
        }
    }
}

/* ir_build() -- will build a new IR proto based on an AST
 *      args: context, AST node
 *      rets: proto list
 */
struct ir_proto_list *ir_build(struct ir_context *context, struct node *node)
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

    return ir_proto_append(context->protos, proto);
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
    fprintf(output, "proto->sizecode        %7d\n", proto->code->size);

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

    fputc('\n', output);

    /* Dump all closures */
    fprintf(output, "closures:\n");

    for (int32_t i = 0; i < proto->proto_size; i++)
        fprintf(output, "%d    %d\n", i, proto->protos[i]);

    fprintf(output, "----------------------------------------------------------------\n");
}

/* ir_print_context() -- will print all of the contents of the IR context
 *      args: output, context
 *      rets: none
 */
void ir_print_context(FILE *output, struct ir_context *context)
{
    /* Dump the symbol table */
    symbol_print_table(output, context->table);

    /* Dump each function prototype */
    for (struct ir_proto *iter = context->protos->first; iter != NULL; iter = iter->next)
        ir_print_proto(output, iter);
}