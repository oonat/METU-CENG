module HW2 (
    parse, -- reexport for easy terminal use
    foldAndPropagateConstants,
    assignCommonSubexprs,
    reducePoly
) where

import Expression
import Parser

-- Do not change the module definition and imports above! Feel free
-- to modify the parser, but please remember that it is just a helper
-- module and is not related to your grade. You should only submit
-- this file. Feel free to import other modules, especially Data.List!

import Data.List

is_num::ExprV->Bool
is_num (Leaf(Constant _)) = True
is_num _ = False

get_val::ExprV->Int
get_val (Leaf(Constant val)) = val

search_check::[(String, ExprV)]->String->Bool
search_check [] _ = False
search_check [(str1, Leaf (Constant _))] source = if source == str1 then True else False
search_check ((str1, Leaf (Constant _)):xs) source = if source == str1 then True else search_check xs source
search_check (_:xs) source = search_check xs source
                                        

search_helper::[(String, ExprV)]->String->Int
search_helper [(_, Leaf (Constant val))] _ = val
search_helper ((str1, Leaf (Constant val)):xs) source = if source == str1 then val else search_helper xs source
search_helper (_:xs) source = search_helper xs source

eval_helper::[(String, ExprV)]->ExprV->ExprV
eval_helper _ (Leaf (Constant val)) = Leaf (Constant val)

eval_helper database (Leaf (Variable val)) = if search_check database val then Leaf (Constant (search_helper database val)) else Leaf (Variable val)

eval_helper database (BinaryOperation binop (x)(y)) = case binop of Plus -> if is_num (eval_helper database x) && is_num (eval_helper database y) then Leaf (Constant (get_val(eval_helper database x)+get_val(eval_helper database y))) else BinaryOperation Plus (eval_helper database x) (eval_helper database y)
                                                                    Times -> if is_num (eval_helper database x) && is_num (eval_helper database y) then Leaf (Constant (get_val(eval_helper database x)*get_val(eval_helper database y))) else BinaryOperation Times (eval_helper database x) (eval_helper database y)

eval_helper database (UnaryOperation Minus x) = if is_num (eval_helper database x) then Leaf (Constant ((-1)*get_val(eval_helper database x))) else UnaryOperation Minus (eval_helper database x)



foldAndPropagateConstants :: [(String, ExprV)] -> [(String, ExprV)]
foldAndPropagateConstants list = foldl (\x y-> x++[(fst y, eval_helper x (snd y))]) [] list


common_subst:: ExprV->ExprV->String-> ExprV
common_subst expr pattern symbol
   | expr == pattern = Leaf (Variable symbol)
   | otherwise = case expr of BinaryOperation op (t1) (t2) -> BinaryOperation op (common_subst t1 pattern symbol) (common_subst t2 pattern symbol)
                              UnaryOperation op (t1) -> UnaryOperation op (common_subst t1 pattern symbol)
                              otherwise -> expr
                                                

common_count:: ExprV->ExprV->Int
common_count expr pattern
   | expr == pattern = 1
   | otherwise = case expr of BinaryOperation _ (t1) (t2) -> (common_count t1 pattern) + (common_count t2 pattern)
                              UnaryOperation _ (t1) -> (common_count t1 pattern)
                              otherwise -> 0
                                         
leaf_finder::ExprV->[ExprV]
leaf_finder expr = case expr of BinaryOperation _ (Leaf (_)) (Leaf (_)) -> [expr]
                                UnaryOperation _ (Leaf (_)) -> [expr]
                                BinaryOperation _ (t1) (t2) -> leaf_finder t1 ++ leaf_finder t2
                                UnaryOperation _ (t1) -> leaf_finder t1
                                otherwise -> []

rmduplicate::[ExprV]->[ExprV]
rmduplicate [] = []
rmduplicate (x:xs) 
    | x `elem` xs = rmduplicate xs
    | otherwise = x:rmduplicate xs


assigncommon_helper::([(String, ExprV)], ExprV)->Int->([(String, ExprV)], ExprV)
assigncommon_helper dict counter
    | filtered_leaves == [] = dict
    | otherwise =  assigncommon_helper (fst(subst_leaves (dict,counter) filtered_leaves)) (snd (subst_leaves (dict,counter) filtered_leaves))
    where filtered_leaves = rmduplicate [x | x<-(leaf_finder (snd dict)), 2<=common_count (snd dict) x]
          subst_leaves = foldl (\x y-> (((fst(fst x))++[("$"++show (snd x),y)], common_subst (snd(fst x)) y ("$"++show (snd x))),(snd x)+1))




assignCommonSubexprs :: ExprV -> ([(String, ExprV)], ExprV)
assignCommonSubexprs expr = assigncommon_helper ([],expr) 0



add_helper::[Int]->[Int]->[Int]
add_helper t1 t2
   | length t1 >= length t2 = (zipWith (+) (take (length t2) t1) (t2)) ++ (drop (length t2) t1)
   | otherwise = add_helper t2 t1

product_helper::[Int]->[Int]->[Int]
product_helper t1 t2 = if t1 == [] then [] else add_helper (map (*(head t1)) t2) (0 : (product_helper (tail t1) t2))
                    

poly_to_array::ExprV -> [Int]
poly_to_array (Leaf(Constant val)) = [val]
poly_to_array (Leaf(Variable _)) = [0,1]
poly_to_array (BinaryOperation Plus (t1) (t2)) = add_helper (poly_to_array t1) (poly_to_array t2)
poly_to_array (BinaryOperation Times (t1) (t2)) = product_helper (poly_to_array t1) (poly_to_array t2)
poly_to_array (UnaryOperation Minus (t1)) = map (*(-1)) (poly_to_array t1)



var_finder:: ExprV -> String
var_finder (Leaf(Constant _)) = ""
var_finder (Leaf(Variable val)) = val
var_finder (BinaryOperation Plus (t1) (t2)) = if (var_finder t1) /= "" then var_finder t1 else var_finder t2
var_finder (BinaryOperation Times (t1) (t2)) = if (var_finder t1) /= "" then var_finder t1 else var_finder t2
var_finder (UnaryOperation Minus (t1)) = var_finder t1


power_func::(Int,Int)->String->ExprV
power_func term var_name
   | degree == 0 = Leaf(Constant (coef))
   | coef == 1 = foldl(\x y-> multiply x y) (Leaf(Variable var_name)) (take (degree-1) (repeat (Leaf(Variable var_name))))
   | coef == -1 = foldl(\x y-> multiply x y) (UnaryOperation Minus(Leaf(Variable var_name))) (take (degree-1) (repeat (Leaf(Variable var_name))))
   | otherwise = foldl(\x y-> multiply x y) (Leaf(Constant (coef))) (take (degree) (repeat (Leaf(Variable var_name))))
   where multiply (x) (y) = BinaryOperation Times (x) (y)
         coef = fst term
         degree = snd term
         



generate::[(Int,Int)]->String->ExprV
generate term_list var_name = foldl(\x y-> adder x (power_func y var_name)) (power_func first_term var_name) (tail term_list)
                              where adder (x) (y) = BinaryOperation Plus (x) (y)
                                    first_term = head term_list



reducePoly :: ExprV -> ExprV
reducePoly expr
   | var_finder expr == "" = Leaf (Constant (head (poly_to_array expr)))
   | all (==0) (poly_to_array expr) = Leaf (Constant 0)
   | length filtered_list == 1 = power_func (head filtered_list) (var_finder expr)
   | otherwise = generate (filtered_list)  (var_finder expr)
   where filtered_list = [x | x<-(zip (poly_to_array expr) (take (length (poly_to_array expr)) [0..])), fst x /= 0]






-- an extra dummy variable, so as to not crash the GUI
notImpl :: ExprV
notImpl = Leaf $ Variable "Not Implemented"

