> module Parse where

> import Pic 
> import Prop 
> import Lex

> picProp                     = picTree . fst. parseProp . lexProp

--parseProp is of type list of tokens which is assigned values of type tuple/pair of a Prop and List of Tokens

> parseProp                  :: [Token]               -> (Prop, [Token])

--parseProp matches TVAR word token and remaining tokens ts resulting in a pair of (VAR word, [ts])

> parseProp (TVAR word : ts)  = (VAR word, ts) 

--parseProp matches TAND token and remaining tokens ts resulting in (p, ts1) or (AND p q, ts2)   

> parseProp (TAND : ts)       = case parseProp ts of
>                                 (p, ts1)            -> case parseProp ts1 of 
>                                                           (q, ts2) -> (AND p q, ts2)

> parseProp (TOR : ts)        = case parseProp ts of
>                                 (p, ts1)            -> case parseProp ts1 of 
>                                                           (q, ts2) -> (OR p q, ts2)

> parseProp (TNOT : ts)       = case parseProp ts of
>                                 (p, ts1)            -> (NOT p, ts1)

> parseProp (TOPEN : ts)      = case parseProp ts of
>                                 (p, TCLOSE : ts1)   -> (p, ts1)
>                                 (p, ts2)            -> error "missing close parentheses" 

-----------
Homework 3:
-----------

> parseDefn                           :: [Token]      -> ([(String, Prop)], [Token])

> parseDefn (TVAR s : TASSIGN : ts)    = ([(s, VAR s)], ts) -- Works but VAR instead of String 

> parseDefn (TAND : ts)  = parseProp (ts)  
