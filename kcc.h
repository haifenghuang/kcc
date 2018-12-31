// ================================
// util.c
// ================================

typedef struct {
    void **data;
    int capacity;
    int len;
} Vector;

Vector *new_vector();
void vec_push(Vector *vec, void *elem);

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
    TK_NUM = 256,
    TK_IDENT,
    TK_EQ,
    TK_NE,
    TK_EOF,
};

typedef struct {
    int ty;      // token type
    int val;     // number value for TK_NUM
    char *input; // original token (for error message)
} Token;

extern Token tokens[100];

void tokenize(char *p);

// ================================
// parse.c
// ================================

enum {
    ND_NUM = 256,
    ND_IDENT,
    ND_EQ,
    ND_NE,
};

typedef struct Node {
    int ty;
    struct Node *lhs;
    struct Node *rhs;
    int val;          // ty == ND_NUM
    char name;        // ty == ND_IDENT
} Node;

extern Node *code[100];

void parse();

// ================================
// gen.c
// ================================

void gen();
