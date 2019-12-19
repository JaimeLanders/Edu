> module ParseInfix where

> import Pic
> import Prop
> import Lex

> ppic = picTree . prop           
> prop = checkTrailing . parseP . lexProp

> checkTrailing (p, []) = p 
> checkTrailing (p, ts) = error ("trailing tokens: " ++ show ts)

Grammar:

   P -> C OR P     propositions
   P -> C

> parseP              :: [Token] -> (Prop, [Token])
> parseP ts            = case parseC ts of
>                          (p, TOR : ts1) -> case parseP ts1 of
>                                              (q, ts2) -> (OR p q, ts2)
>                          (p, ts1) -> (p, ts1)
>

   C -> N AND C    conjunctions
   C -> N

> parseC              :: [Token] -> (Prop, [Token])
> parseC ts            = case parseN ts of
>                          (p, TAND : ts1) -> case parseC ts1 of
>                                               (q, ts2) -> (AND p q, ts2)
>                          (p, ts1) -> (p, ts1)

   N -> NOT N      negations
   N -> A

> parseN               :: [Token] -> (Prop, [Token])
> parseN (TNOT : ts)    = case parseN ts of
>                           (p, ts1) -> (NOT p, ts1)
> parseN ts             = parseA ts

   A -> VAR        atoms
   A -> TRUE
   A -> FALSE
   A -> ( P )

> parseA              :: [Token] -> (Prop, [Token])
> parseA (TVAR v : ts)  = (VAR v, ts)
> parseA (TTRUE : ts)   = (TRUE, ts)
> parseA (TFALSE : ts)  = (FALSE, ts)
> parseA (TOPEN : ts)
>   = case parseP ts of
>       (p, TCLOSE : ts1) -> (p, ts1)
>       (p, ts1) -> error "missing close parentheses"
> parseA (TCLOSE : ts)
>   = case parseP ts of
>       (p, TOPEN : ts1) -> (p, ts1)
>       (p, ts1) -> error "missing open parentheses"
> parseA ts             = error "syntax error: missing atom"
