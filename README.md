# Lua++ programming language
This is the Lua++ C lang build, currently private but will soon be public. This codebase is not specifically tweaked to a certain compiler, so any C/C++ compiler should be able to build this project easily. Personally, I recommend building it with ```gcc``` although ```clang``` or ```MSVSC``` would also work fine.

### How to compile and run
1. Make sure that you have ```make``` installed.
```
make
./bin/luapp ...
```

### Lua++ syntax in extented BNF
Most of this is from [lua.org](https://www.lua.org/manual/5.1/manual.html#8), but I have added some modifications. Those are marked in the codebase.
```
chunk ::= {stat [`;´]} [laststat [`;´]]

block ::= chunk

stat ::=  varlist assigntype explist | 
	 functioncall | 
	 do block end | 
	 while exp do block end | 
	 repeat block until exp | 
	 if exp then block {elseif exp then block} [else block] end | 
	 for var `=´ exp `,´ exp [`,´ exp] do block end | 
	 for namelist in explist do block end | 
	 function funcname funcbody | 
	 local function Name funcbody | 
	 local namelist [`=´ explist] 

laststat ::= return [explist] | break

funcname ::= Name {`.´ Name} [`:´ Name]

varlist ::= var {`,´ var}

var ::=  Name | prefixexp `[´ exp `]´ | prefixexp `.´ Name 

namelist ::= nametype {`,´ nametype}

nametype ::= Name `:´ type

type ::= number | string | boolean

explist ::= {exp `,´} exp

exp ::=  nil | false | true | Number | String | `...´ | function | 
	 prefixexp | tableconstructor | exp binop exp | unop exp 

prefixexp ::= var | functioncall | `(´ exp `)´

functioncall ::=  prefixexp args | prefixexp `:´ Name args 

args ::=  `(´ [explist] `)´ | tableconstructor | String 

function ::= function funcbody

funcbody ::= `(´ [parlist] `)´ `:´ type block end

parlist ::= namelist [`,´ `...´] | `...´

tableconstructor ::= `{´ [fieldlist] `}´

fieldlist ::= field {fieldsep field} [fieldsep]

field ::= `[´ exp `]´ `=´ exp | Name `=´ exp | exp

fieldsep ::= `,´ | `;´

binop ::= `+´ | `-´ | `*´ | `/´ | `^´ | `%´ | `..´ | 
	 `<´ | `<=´ | `>´ | `>=´ | `==´ | `~=´ | 
	 and | or

unop ::= `-´ | not | `#´

assigntype ::= `=´ | `+=´ | `-=´ | `*=´ | `/=´ | `^=´ | `%=´ | `..=´
  ```
