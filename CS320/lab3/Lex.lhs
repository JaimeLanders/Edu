> module Lex where

> import Data.Char

> data Token  = TAND 
>             | TOR 
>             | TNOT
>             | TOPEN
>             | TCLOSE
>             | TTRUE
>             | TFALSE
>             | TASSIGN
>             | TSEMI
>             | TVAR String
>               deriving Show

AND (OR B C) (NO TRUE)

> lexProp             :: [Char] -> [Token]
> lexProp []           = []
> lexProp ('(':cs)     = TOPEN   : lexProp cs 
> lexProp (')':cs)     = TCLOSE  : lexProp cs 
> lexProp ('&':cs)     = TAND    : lexProp cs 
> lexProp ('|':cs)     = TOR     : lexProp cs 
> lexProp ('!':cs)     = TNOT    : lexProp cs 
> lexProp ('=':cs)     = TASSIGN : lexProp cs 
> lexProp (';':cs)     = TSEMI   : lexProp cs 
> lexProp (c:cs)    
>     | isSpace c      = lexProp cs
>     | isAlpha c      = lexWord (c:cs)
>     | otherwise      = error ("unexpected character " ++ [c]) 

> lexWord             :: [Char] -> [Token]
> lexWord cs          = case span isAlpha cs of 
>                         ("AND", rest)     -> TAND       : lexProp rest
>                         ("OR", rest)      -> TOR        : lexProp rest
>                         ("NOT", rest)     -> TNOT       : lexProp rest
>                         ("TRUE", rest)    -> TTRUE      : lexProp rest
>                         ("FALSE", rest)   -> TFALSE     : lexProp rest
>                         (word, rest)      -> TVAR word  : lexProp rest

