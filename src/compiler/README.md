## Lua++ Compiler
The current folder contains all of the contents of the compiler (``luappc``). If you are interested in the codebase, take a look in ``src/``.

> The current compiler will soon be replaced by lorraine. You can learn more about it [here](https://github.com/luapp-org/lorraine).

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

type ::= number | string | boolean | Array `<´ type `>´ | Table `<´ type `,´ type `>´

explist ::= {exp `,´} exp

exp ::=  nil | false | true | Number | String | `...´ | function | 
	 prefixexp | tableconstructor | exp binop exp | unop exp 

prefixexp ::= var | functioncall | `(´ exp `)´

functioncall ::=  prefixexp args | prefixexp `:´ Name args 

args ::=  `(´ [explist] `)´ | tableconstructor | String 

function ::= function funcbody

typelist ::= type {`,´ type}

funcbody ::= `(´ [parlist] `)´ `:´ typelist block end

parlist ::= namelist [`,´ `...´] | `...´

arrayconstructor = `{´ [exprlist] `}´

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
