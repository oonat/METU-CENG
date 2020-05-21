module Mini1 (
    gridMap,
    gridMapIf,
    evalExpr,
    getVars,
    evalDeriv,
    parse -- reexported to allow use
    ) where

import Expression
import Parser

-- Do not modify the module declaration and imports above!
-- Also do not change the function signatures and do not
-- remove the dummy implementations of the functions if
-- you want your code to compile.

-- Feel free to import anything else here
import Data.List
import Data.Maybe

-- gridMap (20 points), map function over grid elements
gridMap :: (a -> b) -> [[a]] -> [[b]]
gridMap func xs = [ map func x | x<-xs]

-- gridMapIf (20 points), map functions over grid elements 
-- that satisfy the predicate provided as the first arg.
gridMapIf :: (a -> Bool) -> (a -> a) -> [[a]] -> [[a]]
gridMapIf pre func xs = [ map (\x-> if pre x then func x else x) k | k<-xs]

-- evalExpr (20 points), evaluate the expression by
-- substituting (var, value) pairs given in the first arg.
evalExpr :: [(String, Int)] -> ExprV -> Int
evalExpr _ (Leaf (Constant val)) = val
evalExpr database (Leaf (Variable var)) = fromJust $ lookup var database
evalExpr database (BinaryOperation binop (x)(y)) = case binop of Plus -> (evalExpr database x)+(evalExpr database y)
                                                                 Times -> (evalExpr database x)*(evalExpr database y)
evalExpr database (UnaryOperation Minus x) = (-1)*(evalExpr database x)


getvar_helper::ExprV ->[String]
getvar_helper (Leaf(Constant _)) = []
getvar_helper (Leaf(Variable val)) = [val]
getvar_helper (BinaryOperation _ (t1) (t2)) = (getvar_helper t1)++(getvar_helper t2)
getvar_helper (UnaryOperation Minus (t1)) = getvar_helper t1

rmduplicate::[String]->[String]
rmduplicate [] = []
rmduplicate (x:xs) 
    | x `elem` xs = rmduplicate xs
    | otherwise = x:(rmduplicate xs)

-- getVars (20 points), return the variables contained
-- in the expression in a list (ordered, no duplicates)
getVars :: ExprV -> [String]
getVars expr = sort $ rmduplicate $ getvar_helper expr


deriv_helper::ExprV->String->ExprV
deriv_helper (Leaf (Constant val)) _ = Leaf(Constant 0)
deriv_helper (Leaf (Variable var)) var_name = if var == var_name then Leaf (Constant 1) else Leaf(Constant 0)
deriv_helper (BinaryOperation binop (x)(y)) var_name = case binop of Plus -> BinaryOperation Plus (deriv_helper x var_name)(deriv_helper y var_name)
                                                                     Times -> BinaryOperation Plus (BinaryOperation Times (x) (deriv_helper y var_name)) (BinaryOperation Times (deriv_helper x var_name) (y))
deriv_helper (UnaryOperation Minus x) var_name = UnaryOperation Minus (deriv_helper x var_name)

-- evalDeriv (20 points), evaluate the first derivative
-- with respect to the variable given in the second
-- arg. using (var, value) pairs given in the first arg.
evalDeriv :: [(String, Int)] -> String -> ExprV -> Int
evalDeriv database var_name expr  = evalExpr database (deriv_helper expr var_name)

-- Looks like that's all! 
