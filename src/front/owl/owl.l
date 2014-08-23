%option noyywrap
%option nodefault
%x comment uri langtag
%{

%}

%%
 /* Whitespace without newline. */
 /* Newline is treated elsewhere to count lines. */
[ \t\r]+			;

 /* nonNegativeInteger */
[0-9]+				{
						yylval = yytext;
						return TOKEN_nonNegativeInteger;
					}

 /* quotedString */
\"(\\.|[^\\"])*\"	{
						yylval = yytext;
						return TOKEN_quotedString;
					}

 /* Comment */
"#"					{ BEGIN(comment); }
<comment>[\r\n]		{ BEGIN(INITIAL); }
<comment>.*			;

/* languageTag (ignored) */
"@"					{ BEGIN(langtag); }
<langtag>[A-Za-z0-9-]+	;
<langtag>.*			{ BEGIN(INITIAL); }

 /* Delimiters */
"="					{ return '='; }
"("					{ return '('; }
")"					{ return ')'; }
"<"					{ return '<'; }
">"					{ return '>'; }
"@"					{ return '@'; }
"^"					{ return '^'; }
"\n"				{ yylineno++; }
<<EOF>>		{
				DL::eof = true;
				return 0;
			}
[A-Za-z][0-9A-Za-z]*	{ 
				yylval = DL::identifier(yytext); 
				return TOKEN_IDENT;
			}
%%