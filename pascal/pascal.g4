grammar pascal;

start     : 'program' ID ';' 'var' decl_list main_code EOF ;

decl_list : decl | decl decl_list ;
decl      : ID ',' decl | ID ':' 'integer' ';' ;

main_code : 'begin' st_list 'end' '.' ;
code_block: statement | 'begin' st_list 'end' ;
st_list   : statement ';' | statement ';' st_list ;
          
statement : assign | repeat | out | branch | in;

assign    : ID ':=' expr ;
out       : 'writeln' '(' expr ')' | 'writeln' '(' string ')';
in        : 'readln' '(' expr ')' ;
branch    : 'if' relation 'then' code_block | 'if' relation 'then' code_block 'else' code_block ;
repeat    : 'repeat' st_list 'until' relation;
expr      : NUMBER | ID | expr SUM expr | expr SUB expr
          | expr PROD expr | expr DIV expr | expr MOD expr | PAR_O expr PAR_C;
string    : STRG;
relation  : expr LT expr | expr LEQ expr | expr EQ expr
          | expr NEQ expr | expr GEQ expr | expr GT expr
          | relation AND relation | relation OR relation | relation NOT relation | PAR_O relation PAR_C ;


EQ        : '=' ;
LT        : '<' ;
LEQ       : '<=' ;
GT        : '>' ;
GEQ       : '>=' ;
NEQ       : '<>' ;
SUM       : '+' ;
SUB       : '-' ;
PROD      : '*' ;
DIV       : '/' ; 
MOD       : '%' ;
PAR_O     : '(' ;
PAR_C     : ')' ;
AND       : 'and' ;
OR        : 'or' ;
NOT       : 'not' ;
ID        : [a-z]+ ;
NUMBER    : [0-9]+ ;
STRG    : '\'' .*? '\'' ;
R_COMMENT : '(*' .*? '*)' -> skip ;     // .*? matches anything until the first */
C_COMMENT : '{' .*? '}' -> skip ;       // .*? matches anything until the first }
LINE_COMMENT : '//' ~[\r\n]* -> skip ;  // ~[\r\n]* matches anything but \r and \n
WS        : [ \n\t\r]+ -> skip;
ErrorChar : . ;

/*
liste di variabili nelle dichiarazioni
    var
        x, y, z: integer;
        a : integer ;
cicli repeat-until
    repeat   
        istruzione1;
        istruzione2;
        ...
    until guardia;
    dove le istruzioni sono racchiuse tra repeat e until, senza la necessità di un blocco begin ... end

estendere costrutto if-then con il ramo else:
    if guardia then
    blocco_di_codice
    else
    blocco_di_codice ;

    il ramo else è opzionale e può essere omesso. blocco_di_codice è una singola istruzione oppure un blocco begin ... end.

espressioni aritmetiche che usano gli operatori +, -, *, / e % (modulo), e le parentesi

espressioni booleane complesse che utilizzano gli operatori logici and, or, not, e le parentesi

la procedura readln(variabile) che legge un valore intero dallo standard input e lo memorizza in variabile

permettere alla procedura writeln di scrivere stringhe sullo schermo
    writeln ( stringa ) 
    dove stringa è una qualsiasi sequenza di caratteri compresi tra apici '    '

*/