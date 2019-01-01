// ================================
// util.c
// ================================

typedef struct {
    void **data;
    int capacity;
    int len;
} Vector;

typedef struct {
    Vector *keys;
    Vector *vals;
} Map;

Vector *new_vector();
void vec_push(Vector *vec, void *elem);

Map *new_map();
void map_put(Map *map, char *key, void *val);
void map_puti(Map *map, char *key, int val);
int map_exists(Map *map, char *key);
void *map_get(Map *map, char *key);
int map_geti(Map *map, char *key);

void error(char *fmt, ...);

// ================================
// util_test.c
// ================================

void run_test();

// ================================
// token.c
// ================================

// token type
enum {
    TK_NUM = 256, // Number literal
    TK_IDENT,     // Identifier
    TK_EQ,        // "=="
    TK_NE,        // "!="
    TK_INT,       // "int"
    TK_IF,        // "if"
    TK_ELSE,      // "else"
    TK_RETURN,    // "return"
    TK_EOF,       // end of file
};

typedef struct {
    int ty;      // token type
    int val;     // number value for TK_NUM
    char *name;  // name for TK_IDENT
    char *input; // original token (for error message)
} Token;

Vector *tokenize(char *p);

// ================================
// parse.c
// ================================

enum {
    ND_NUM = 256, // Number literal
    ND_VARDEF,    // Define variable
    ND_IDENT,     // Identifier
    ND_EQ,        // equal
    ND_NE,        // not equal
    ND_IF,        // "if"
    ND_CALL,      // Function call
    ND_FUNC,      // Function definition
    ND_RETURN,    // "return"
};

typedef struct Node {
    int ty;           // token type
    struct Node *lhs;
    struct Node *rhs;

    // ty == ND_NUM
    int val;

    // Function name or Identifier
    char *name;

    // "if" ( cond ) then "else" els
    struct Node *cond;
    struct Node *then;
    struct Node *els;

    // Function call arguments
    Vector *args;

    // Function body
    Vector *body;

    // "return"
    struct Node *expr;
} Node;

Vector *parse(Vector *tokens);

// ================================
// ir.c
// ================================

enum {
    IR_PUSH_IMM = 256,
    IR_PUSH_VAR_PTR,
    IR_POP,
    IR_LOAD_VAL,
    IR_ASSIGN,
    IR_EQ,
    IR_NE,
    IR_LABEL,
    IR_UNLESS,
    IR_JMP,
    IR_CALL,
    IR_RETURN,
};

typedef struct {
    int ty;
    int val;
    char *name;
} IR;

typedef struct {
    char *name;
    Vector *codes;
    int args;
    int varsiz;
} Function;

typedef struct {
    Vector *funcs;
} Program;

Program *gen_ir(Vector *nodes);

// ================================
// gen.c
// ================================

void gen(Program *program);
