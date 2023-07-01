enum TokenType
{
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, LEFT_BRACK, RIGHT_BRACK,
    COMMA, DOT, SEMICOLON, COLON, QUOTE, TYPE,

    OPERATOR, EQUAL,

    IDENTIFIER, STR, NUMBER, NULLT, DOUBLE,

    NEWLINE, IF, ELSE, AND, OR, NOT, PRINT, TRUE, FALSE, LABEL, GOTO, RET, CALL, WAIT,

    END_OF_FILE,
    UNDEF // ??
};

struct Token
{
    TokenType type;
    const char* lexeme;

    Token(TokenType t, const char* l)
    {
        type = t;
        lexeme = l;
    }
    Token()
    {
        lexeme = "";
        type = UNDEF;
    }
};

enum LexMode
{
    DEFAULT,
    STRING,
    COMMENT
};
qq::vector<Token, 1024> lex(const char* source)
{
    LexMode mode = DEFAULT;

    // split string by space and new line
    const size_t maxLength = 1024; // Maximum length of the word

qq::vector<const char*, 1024> unprocessed;
char words[1024][24]; // Array to store words, assuming maximum word length of 23 characters (plus null-terminator)

size_t wordIndex = 0;
size_t wordCount = 0;

for (size_t i = 0; source[i] != '\0'; i++)
{
    if (source[i] == ' ' || source[i] == '\n' || source[i] == '\0' || source[i] == '\t')
    {
        if (wordIndex > 0)
        {
            words[wordCount][wordIndex] = '\0'; // Null-terminate the word
            unprocessed.push_back(words[wordCount]); // Add the word to the vector
            wordCount++;
            wordIndex = 0; // Reset word index for the next word
        }
    }
    else
    {
        words[wordCount][wordIndex] = source[i]; // Copy the character to the current word
        wordIndex++;

        if (wordIndex >= 23) // Check if the word exceeds the maximum length
        {
            // Handle word length error
            // You can define custom behavior here
            // For example, skip the remaining characters or truncate the word
            // Avoiding std::length_error as requested
        }
    }
}

if (wordIndex > 0)
{
    words[wordCount][wordIndex] = '\0'; // Null-terminate the last word
    unprocessed.push_back(words[wordCount]); // Add the last word to the vector
}













    qq::vector<Token, 1024> tokens;

for (const char* token : unprocessed) {
    if (mode == DEFAULT) {
        TokenType type = UNDEF;

        // if single-character token
        if (strlen(token) == 1) {
            if (token[0] == '(')
                type = LEFT_PAREN;
            else if (token[0] == ')')
                type = RIGHT_PAREN;
            else if (token[0] == '{')
                type = LEFT_BRACE;
            else if (token[0] == '}')
                type = RIGHT_BRACE;
            else if (token[0] == '[')
                type = LEFT_BRACK;
            else if (token[0] == ']')
                type = RIGHT_BRACK;
            else if (token[0] == ',')
                type = COMMA;
            else if (token[0] == '.')
                type = DOT;
            else if (token[0] == ';')
                type = SEMICOLON;
            else if (token[0] == ':')
                type = COLON;
            else if (token[0] == '+' || token[0] == '-' || token[0] == '*' ||
                     token[0] == '/' || token[0] == '>' || token[0] == '&' ||
                     token[0] == '|' || token[0] == '<')
                type = OPERATOR;
            else if (token[0] == '=') 
                type = EQUAL;
            else if (token[0] == '"') {
                type = QUOTE;
                mode = STRING;
                words[wordCount][0] = '\0';
                continue;
            }
            else if (token[0] == '~') {
                mode = COMMENT;
                continue;
            }
            else {
                if (isNumber(token))
                    type = NUMBER;
                else if (isDecimal(token))
                    type = DOUBLE;
                else if (isValidId(token))
                    type = IDENTIFIER;
                else
                    type = END_OF_FILE;
            }
        }
        // if multiple-symbol operator
        else if (strcmp(token, "==") == 0 || strcmp(token, ">=") == 0 ||
                 strcmp(token, "<=") == 0 || strcmp(token, "!=") == 0 ||
                 strcmp(token, "and") == 0 || strcmp(token, "or") == 0 ||
                 strcmp(token, "not") == 0) {
            type = OPERATOR;
        }
        // if keyword
        else if (strcmp(token, "newline") == 0)
            type = NEWLINE;
        else if (strcmp(token, "label") == 0)
            type = LABEL;
        else if (strcmp(token, "goto") == 0)
            type = GOTO;
        else if (strcmp(token, "random") == 0)
            type = OPERATOR;
        else if (strcmp(token, "call") == 0)
            type = CALL;
        else if (strcmp(token, "ret") == 0)
            type = RET;
        else if (strcmp(token, "wait") == 0)
            type = WAIT;
        else if (strcmp(token, "int") == 0)
            type = TYPE;
        else if (strcmp(token, "double") == 0)
            type = TYPE;
        else if (strcmp(token, "string") == 0)
            type = TYPE;
        else if (strcmp(token, "bool") == 0)
            type = TYPE;
        else if (strcmp(token, "null") == 0)
            type = NULLT;
        else if (strcmp(token, "if") == 0)
            type = IF;
        else if (strcmp(token, "else") == 0)
            type = ELSE;
        else if (strcmp(token, "print") == 0)
            type = PRINT;
        else if (strcmp(token, "true") == 0)
            type = TRUE;
        else if (strcmp(token, "false") == 0)
            type = FALSE;
        else if (isNumber(token))
            type = NUMBER;
        else if (isDecimal(token))
            type = DOUBLE;
        else if (token[0] == '"') {
            mode = STRING;
            char ntoken[24] = "\0";
            erase(token, 0, 1, ntoken);
            strncpy(words[wordCount], ntoken, 24); // start after the opening quote
            continue;
        }
        else if (isValidId(token))
            type = IDENTIFIER;

        tokens.push_back(Token(type, token));
    }
    else if (mode == COMMENT) {
        if (token[0] != '~') {
            continue;
        }
        else {
            mode = DEFAULT;
            continue;
        }
    }
    else if (mode == STRING) {
        const char *s = " ";
        strcat(words[wordCount], s);

        if (token[strlen(token) - 1] == '"') {
            char ntoken[24] = "\0";
            erase(token, strlen(token) - 1, 1, ntoken);
            char nntoken[24];
            strcpy(nntoken, ntoken);
            strcat(words[wordCount], nntoken);
            const char *word2 = strdup(words[wordCount]);
            tokens.push_back(Token(STR, word2));
            wordCount++;
            mode = DEFAULT;
        }
        else {
            strcat(words[wordCount], token);
        }
    }
}

return tokens;

}