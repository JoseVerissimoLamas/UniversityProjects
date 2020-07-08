%{
    //Beatriz Isabel Santos 2017263066
    //José Veríssimo Lamas  2017259895

    #include "semantic.h"
%}


lower                           [a-z]
upper                           [A-Z]
digit                           [0-9]

ID                              ({lower}|{upper}|"$"|"_")({lower}|{upper}|"$"|"_"|[0-9])*
INTLIT                          ("0")|([1-9]([0-9]|"_"*[0-9])*)
RealAux                         [0-9]([0-9]|"_"*[0-9])*
RL1                             ({RealAux}("."{RealAux}*)(("e"|"E")("+"|"-")?{RealAux})?)
RL2                             ("."({RealAux}+)(("e"|"E")("+"|"-")?{RealAux})?)
RL3                             {RealAux}(("e"|"E")("+"|"-")?{RealAux})
REALLIT                         {RL1}|{RL2}|{RL3}
BOOLLIT                         ("true"|"false")

AND                             "&&"
ASSIGN                          "="
STAR                            \*
COMMA                           ","
EQ                              "=="
GE                              ">="
GT                              ">"
LE                              "<="
LT                              "<"
LBRACE                          "{"
LPAR                            "("
LSQ                             "["
RBRACE                          "}"
RPAR                            ")"
RSQ                             "]"
PLUS                            \+
MINUS                           "-"
DIV                             "/"
MOD                             "%"
NE                              "!="
NOT                             "!"
OR                              "||"
SEMICOLON                       ";"
ARROW                           "->"
LSHIFT                          "<<"
RSHIFT                          ">>"
XOR                             \^
CLASS                           "class"
BOOL                            "boolean"
DOTLENGTH                       ".length"
DOUBLE                          "double"
ELSE                            "else"
IF                              "if"
INT                             "int"
PRINT                           "System.out.print"
PARSEINT                        "Integer.parseInt"
PUBLIC                          "public"
RETURN                          "return"
STATIC                          "static"
STRING                          "String"
VOID                            "void"
WHILE                           "while"
RESERVED                        ("++"|"--"|null|System|Integer|abstract|continue|for|new|switch|assert|default|do|goto|private|this|break|implements|protected|throw(s)?|byte|import|case|enum|instanceof|transient|catch|extends|short|try|char|final|interface|finally|long|strictfp|volatile|const|float|native|super|package|synchronized)

INVALID_ESC_SEQ                 \\[^(t|n|r|f|\\|\")]
ESC_SEQ                         (t|n|r|f|\\|\")

%X COMMENT_MultiLine
%X COMMENT_SingleLine
%X STRLIT_
%X ESCAPE
   

%{
    #include "y.tab.h"
    int line = 1;   
    int collumn = 0;
    int cantPrintFlag = 0;
    char toPrint[1024]; 
    void countLine();
    int auxLine = 0;
    int auxCollumn = 0;
    int flag=0;
    int flag_erros = 0;
    int token=0;
    int flag_t = 0;
    bool yacc = false;
    bool syntaxError = false;
    extern asTree* tree;
    void yylvalInitialize(int line, int col, char* val);

    int flagSymbT = 0;

%}

%%
\/\/                            {countLine();BEGIN (COMMENT_SingleLine);}
<COMMENT_SingleLine>\n|\r       {countLine();BEGIN (0);}
<COMMENT_SingleLine>\r\n        {countLine();BEGIN (0);}
<COMMENT_SingleLine><<EOF>>     {BEGIN (0);}
<COMMENT_SingleLine>.           {countLine();}

\/\*                            {auxLine=line; auxCollumn=collumn+1;BEGIN (COMMENT_MultiLine);countLine();}       
<COMMENT_MultiLine>\n|\r        {countLine();} 
<COMMENT_MultiLine>\r\n         {countLine();}
<COMMENT_MultiLine>\*\/         {countLine();BEGIN (0);}
<COMMENT_MultiLine><<EOF>>      {if(flag_erros == 0){printf("Line %d, col %d: unterminated comment\n", auxLine, auxCollumn);} BEGIN (0);}
<COMMENT_MultiLine>.            {countLine();}

\"                               {auxLine= line;auxCollumn = collumn+1;toPrint[0]='\0';cantPrintFlag=0;countLine();BEGIN (STRLIT_);}
<STRLIT_>\\                      {strcat(toPrint, yytext);countLine();BEGIN (ESCAPE);}
<STRLIT_>(\n|\r|\r\n)            {if(flag_erros == 0){printf("Line %d, col %d: unterminated string literal\n", auxLine, auxCollumn);} countLine();BEGIN (0);}            
<STRLIT_>\"                      {countLine();strcat(toPrint, yytext); if(cantPrintFlag == 0 && flag==1){printf("STRLIT(\"%s)\n", toPrint);};BEGIN (0); yylvalInitialize(line,collumn,toPrint); if(yacc == true && cantPrintFlag == 0){ return STRLIT;}}
<STRLIT_><<EOF>>                 {if(flag_erros == 0){printf("Line %d, col %d: unterminated string literal\n", auxLine, auxCollumn);} BEGIN (0); }
<STRLIT_>.                       {countLine();strcat(toPrint, yytext);}

<ESCAPE>{ESC_SEQ}               {strcat(toPrint, yytext);BEGIN (STRLIT_);countLine();}
<ESCAPE>" "                     {cantPrintFlag = 1;if(flag_erros == 0){printf("Line %d, col %d: invalid escape sequence (\\ )\n", line, collumn);}countLine();BEGIN (STRLIT_);}
<ESCAPE>(\n|\r|\r\n)            {   if(flag_erros == 0){printf("Line %d, col %d: invalid escape sequence (\\)\n", line, collumn);}
                                    if(flag_erros == 0){printf("Line %d, col %d: unterminated string literal\n", auxLine, auxCollumn);}
                                    countLine(); BEGIN (0);}
<ESCAPE><<EOF>>                 {cantPrintFlag = 1;if(flag_erros == 0){printf("Line %d, col %d: unterminated string literal\n", auxLine, auxCollumn);}; BEGIN (0);}
<ESCAPE>.                       {cantPrintFlag = 1;if(flag_erros == 0){printf("Line %d, col %d: invalid escape sequence (\\%c)\n", line, collumn, yytext[0]);};  BEGIN (STRLIT_);countLine();}


{AND}                           {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("AND\n");};if(yacc) return AND;}
{ASSIGN}                        {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("ASSIGN\n");};if(yacc) return ASSIGN;}
{STAR}                          {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("STAR\n");}; if(yacc) return STAR;}
{COMMA}                         {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("COMMA\n");}; if(yacc) return COMMA;}
{EQ}                            {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("EQ\n");};if(yacc)if(yacc) return EQ;}
{GE}                            {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("GE\n");};if(yacc) return GE;}
{GT}                            {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("GT\n");};if(yacc) return GT;}
{LE}                            {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("LE\n");};if(yacc) return LE;}
{LT}                            {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("LT\n");};if(yacc) return LT;}
{LBRACE}                        {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("LBRACE\n");};if(yacc) return LBRACE;}
{LPAR}                          {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("LPAR\n");};if(yacc) return LPAR;}
{LSQ}                           {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("LSQ\n");};if(yacc) return LSQ;}
{RBRACE}                        {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("RBRACE\n");};if(yacc) return RBRACE;}
{RPAR}                          {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("RPAR\n");};if(yacc) return RPAR;}
{RSQ}                           {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("RSQ\n");};if(yacc) return RSQ;}
{PLUS}                          {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("PLUS\n");};if(yacc) return PLUS;}
{MINUS}                         {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("MINUS\n");};if(yacc) return MINUS;}
{DIV}                           {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("DIV\n");};if(yacc) return DIV;}
{MOD}                           {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("MOD\n");};if(yacc) return MOD;}
{NE}                            {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("NE\n");};if(yacc) return NE;}
{NOT}                           {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("NOT\n");};if(yacc) return NOT;}
{OR}                            {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("OR\n");};if(yacc) return OR;}
{SEMICOLON}                     {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("SEMICOLON\n");};if(yacc) return SEMICOLON;}
{ARROW}                         {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("ARROW\n");};if(yacc) return ARROW;}
{LSHIFT}                        {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("LSHIFT\n");};if(yacc) return LSHIFT;}
{RSHIFT}                        {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("RSHIFT\n");};if(yacc) return RSHIFT;}
{XOR}                           {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("XOR\n");};if(yacc) return XOR;}
{CLASS}                         {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("CLASS\n");};if(yacc) return CLASS;}
{BOOL}                          {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("BOOL\n");};if(yacc) return BOOL;}
{DOTLENGTH}                     {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("DOTLENGTH\n");};if(yacc) return DOTLENGTH;}
{DOUBLE}                        {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("DOUBLE\n");};if(yacc) return DOUBLE;}
{ELSE}                          {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("ELSE\n");};if(yacc) return ELSE;}
{IF}                            {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("IF\n");};if(yacc) return IF;}
{INT}                           {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("INT\n");};if(yacc) return INT;}
{PRINT}                         {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("PRINT\n");};if(yacc) return PRINT;}
{PARSEINT}                      {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("PARSEINT\n");};if(yacc) return PARSEINT;}
{PUBLIC}                        {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("PUBLIC\n");};if(yacc) return PUBLIC;}
{RETURN}                        {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("RETURN\n");};if(yacc) return RETURN;}
{STATIC}                        {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("STATIC\n");};if(yacc) return STATIC;}
{STRING}                        {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("STRING\n");};if(yacc) return STRING;}
{VOID}                          {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("VOID\n");};if(yacc) return VOID;}
{WHILE}                         {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("WHILE\n");};if(yacc) return WHILE;}
{RESERVED}                      {countLine();yylvalInitialize(line,collumn,NULL);if(flag==1){printf("RESERVED(%s)\n", yytext);}; if(yacc) return RESERVED;}
{BOOLLIT}                       {countLine();yylvalInitialize(line,collumn,yytext);if(flag==1){printf("BOOLLIT(%s)\n", yytext);};if(yacc) return BOOLLIT;}
{INTLIT}                        {countLine();yylvalInitialize(line,collumn,yytext);if(flag==1){printf("INTLIT(%s)\n", yytext);};if(yacc) return INTLIT;}
{REALLIT}                       {countLine();yylvalInitialize(line,collumn,yytext);if(flag==1){printf("REALLIT(%s)\n", yytext);};if(yacc) return REALLIT;}
{ID}                            {countLine();yylvalInitialize(line,collumn,yytext);if(flag==1){printf("ID(%s)\n", yytext);};if(yacc) return ID;}
\n                              {countLine();}
\r\n                            {countLine();}
\r                              {countLine();}
\t                              {countLine();}
\f                              {countLine();}
" "                             {countLine();}
.                               {countLine();if(flag_erros == 0){printf("Line %d, col %d: illegal character (%c)\n", line, collumn, yytext[0]);}}

%%

int main(int argc, char *argv[]){
    bool isE3 = false;

    char flag1[5] = "-l";   //análise lexical
    char flag2[5] = "-e1";  //erros de análise lexical
    char flag3[5] = "-e2";  //erros de análise lexical e sintática
    char flag4[5] = "-t";   //arvore AST
    char flag5[5] = "-s";   // tabela de simbolos
    char flag6[5] = "-e3";   // erros 

    if(argc == 2 && strcmp(flag1,argv[1])==0){
        flag = 1;  //Para imprimir apenas os tokens
        flag_erros = 0; //Para imprimir apenas os erros lexicais
    }else if(argc == 2 && strcmp(flag2,argv[1])==0){
        flag_erros = 0; //para imprimir apenas os erros lexicais

    }else if(argc == 2 && strcmp(flag3,argv[1])==0){
        yacc = true;
        flag_erros = 0; //imprimir erros lexicais
    }
    else if(argc == 2 && strcmp(flag4,argv[1])==0){
        yacc = true;
        flag_t = 1;
    }else if(argc == 2 && strcmp(flag5,argv[1])==0){
        // imprimir tabela de simbolos !!
        yacc = true;
        flagSymbT = 1;
    }else if(argc == 2 && strcmp(flag6,argv[1])==0){
        // erros semanticos
        yacc = true;
        flagSymbT = 1; 
        isE3 = true;
    }
    else{
        yacc = true;
        flag_erros = 0;    // caso nao for apresentada flag fazer -e2
    }
    if(!yacc){
        yylex();
    }else{
        if(flag_t == 1){
            yyparse();
            if(!syntaxError){ 
                displayAST(0, tree, false);               
            }
        }else{
            yyparse();
            if(flagSymbT == 1 && !syntaxError){
                symbTable* root = makeTable_Program(tree);
                //enterAST(tree);
                if(!isE3){
                    displayTables(root);
                    displayAST(0, tree, true);
                }         
            } 
        }
    }
    

   return 0;
}

int yywrap(){
    return 1;
}

void countLine(){
    for(int i=0; i < yyleng; i++){
        if(yytext[i]=='\n' || yytext[i]=='\r'){
            line++;
            collumn = 0;
            break;
        }
        else{
            collumn++;
        }
    }
}

void yylvalInitialize(int line, int col, char* val){
    yylval.s = (struct args *) malloc(sizeof(struct args));
    yylval.s->line = line;
    yylval.s->col = col;
    if (val != NULL){
        yylval.s->val = strdup(val);
    } else {
        yylval.s->val = NULL;
    }
}
