LOL            (ALPHA)|((DIGITS)|(SYMBOLS))
%%
"hello world"    {printf("GOODBYE!\n");}
"hello world"    printf("%%");
[0-9,a-z]        printf("%%");
l                printf(".");
\"               write(1, "A\n", 2);
%%
