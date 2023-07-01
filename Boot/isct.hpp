typedef void* object;
typedef enum ISCTChar{
    ISCT_NULL,
    ISCT_APP,
    ISCT_LBR,
    ISCT_RBR,
    ISCT_LA,
    ISCT_CLA,
    ISCT_LB,
    ISCT_CLB,
    ISCT_LC,
    ISCT_CLC,
    ISCT_LD,
    ISCT_CLD,
    ISCT_LE,
    ISCT_CLE,
    ISCT_LF,
    ISCT_CLF,
    ISCT_LG,
    ISCT_CLG,
    ISCT_LH,
    ISCT_CLH,
    ISCT_LI,
    ISCT_CLI,
    ISCT_LJ,
    ISCT_CLJ,
    ISCT_LK,
    ISCT_CLK,
    ISCT_LL,
    ISCT_CLL,
    ISCT_LM,
    ISCT_CLM,
    ISCT_LN,
    ISCT_CLN,
    ISCT_LO,
    ISCT_CLO,
    ISCT_LP,
    ISCT_CLP,
    ISCT_LQ,
    ISCT_CLQ,
    ISCT_LR,
    ISCT_CLR,
    ISCT_LS,
    ISCT_CLS,
    ISCT_LT,
    ISCT_CLT,
    ISCT_LU,
    ISCT_CLU,
    ISCT_LV,
    ISCT_CLV,
    ISCT_LW,
    ISCT_CLW,
    ISCT_LX,
    ISCT_CLX,
    ISCT_LY,
    ISCT_CLY,
    ISCT_LZ,
    ISCT_CLZ,
    ISCT_NEWL,
    ISCT_PERC,
    ISCT_AND,
    ISCT_SPEECH,
    ISCT_ADD,
    ISCT_DIV,
    ISCT_OR,
    ISCT_COMMA,
    ISCT_STOP,
    ISCT_SEMI,
    ISCT_COLON,
    ISCT_GRT,
    ISCT_LST,
    ISCT_EQQ,
    ISCT_N0,
    ISCT_N1,
    ISCT_N2,
    ISCT_N3,
    ISCT_N4,
    ISCT_N5,
    ISCT_N6,
    ISCT_N7,
    ISCT_N8,
    ISCT_N9,
    ISCT_SPACE,
    ISCT_EXCL,
    ISCT_AST,
    ISCT_QUE,
    ISCT_CUA,
    ISCT_SRB,
    ISCT_SLB,
    ISCT_BDIV,
    ISCT_POW,
    ISCT_LONA,
    ISCT_CRB,
    ISCT_CLTB,
    ISCT_CURL,
    ISCT_HASH,
    ISCT_DOLL,
    ISCT_TAB,
    ISCT_CRET,
    ISCT_DASH,
    ISCT_UND,
} Char;
Char lookup[128] = {
        ISCT_NULL,
        ISCT_NULL,
        ISCT_NULL,
        ISCT_NULL,
        ISCT_NULL,
        ISCT_NULL,
        ISCT_NULL,
        ISCT_NULL,
        ISCT_NULL,
        ISCT_TAB,
        ISCT_NEWL,
        ISCT_NULL,
        ISCT_NULL,
        ISCT_CRET,
        ISCT_NULL,
        ISCT_NULL,
        ISCT_NULL,
        ISCT_NULL,
        ISCT_NULL,
        ISCT_NULL,
        ISCT_NULL,
        ISCT_NULL,
        ISCT_NULL,
        ISCT_NULL,
        ISCT_NULL,
        ISCT_NULL,
        ISCT_NULL,
        ISCT_NULL,
        ISCT_NULL,
        ISCT_NULL,
        ISCT_NULL,
        ISCT_NULL,
        ISCT_SPACE,
        ISCT_EXCL,
        ISCT_SPEECH,
        ISCT_HASH,
        ISCT_DOLL,
        ISCT_PERC,
        ISCT_AND,
        ISCT_APP,
        ISCT_LBR,
        ISCT_RBR,
        ISCT_AST,
        ISCT_ADD,
        ISCT_COMMA,
        ISCT_DASH,
        ISCT_STOP,
        ISCT_DIV,
        ISCT_N0,
        ISCT_N1,
        ISCT_N2,
        ISCT_N3,
        ISCT_N4,
        ISCT_N5,
        ISCT_N6,
        ISCT_N7,
        ISCT_N8,
        ISCT_N9,
        ISCT_COLON,
        ISCT_SEMI,
        ISCT_LST,
        ISCT_EQQ,
        ISCT_GRT,
        ISCT_QUE,
        ISCT_CUA,
        ISCT_CLA,
        ISCT_CLB,
        ISCT_CLC,
        ISCT_CLD,
        ISCT_CLE,
        ISCT_CLF,
        ISCT_CLG,
        ISCT_CLH,
        ISCT_CLI,
        ISCT_CLJ,
        ISCT_CLK,
        ISCT_CLL,
        ISCT_CLM,
        ISCT_CLN,
        ISCT_CLO,
        ISCT_CLP,
        ISCT_CLQ,
        ISCT_CLR,
        ISCT_CLS,
        ISCT_CLT,
        ISCT_CLU,
        ISCT_CLV,
        ISCT_CLW,
        ISCT_CLX,
        ISCT_CLY,
        ISCT_CLZ,
        ISCT_SLB,
        ISCT_BDIV,
        ISCT_SRB,
        ISCT_POW,
        ISCT_UND,
        ISCT_LONA,
        ISCT_LA,
        ISCT_LB,
        ISCT_LC,
        ISCT_LD,
        ISCT_LE,
        ISCT_LF,
        ISCT_LG,
        ISCT_LH,
        ISCT_LI,
        ISCT_LJ,
        ISCT_LK,
        ISCT_LL,
        ISCT_LM,
        ISCT_LN,
        ISCT_LO,
        ISCT_LP,
        ISCT_LQ,
        ISCT_LR,
        ISCT_LS,
        ISCT_LT,
        ISCT_LU,
        ISCT_LV,
        ISCT_LW,
        ISCT_LX,
        ISCT_LY,
        ISCT_LZ,
        ISCT_CLTB,
        ISCT_OR,
        ISCT_CRB,
        ISCT_CURL,
        ISCT_NULL
    };
typedef struct ISCTString {
    int len;
    Char value[1024];
} String;

Char asciitoisct(int isct) {
    return lookup[isct];
}
int findex(Char num, Char arr[]) {
    for (int i = 0; i < 128; i++) {
        if (arr[i] == num) {
            return i;
        }
    }
    return -1;
}
String init(char asciis[1024])
{
    int l = strlen(asciis);
    String str;
    str.len = l;
    for(int i = 0; i <l; i++)
    {
        str.value[i] = asciitoisct(asciis[i]);
    }
    return str;
}
Char init(char asciic)
{
    return asciitoisct(asciic);
}
void setv(String *str, char ascii[1024]) {
    int l = strlen(ascii);
    str->len = l;
    for(int i = 0; i<l; i++)
        str->value[i] = asciitoisct(ascii[i]);
}
void setv(Char *c, char cc) {
    *c = asciitoisct(cc);
}
char* getv(String str) {
    char strr[1024];
    char* stra = strr;
    int pos = 0;
    for(int i = 0;i<str.len;i++)
    {
        stra[i] = (char)findex(str.value[i], lookup);
        pos++;
    }
    stra[pos+1] = '\0';
    return stra;
}
char getv(Char c) {
    return (char)findex(c, lookup);
}