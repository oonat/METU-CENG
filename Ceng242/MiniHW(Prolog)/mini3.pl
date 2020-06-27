:- module(hw, [cost/2, sort_units/2, buyable/4]).
:- [kb].

% DO NOT CHANGE THE UPPER CONTENT, WRITE YOUR CODE AFTER THIS LINE

cost([], Cost):- Cost is 0.
cost([active_unit(Name, Star) | Rest], Cost):- cost(Rest, Crest), unit(Name, Price, _), Cost is Crest + (3**(Star-1) * Price).


sort_units(Arr, Sorted):- sort_helper(Arr, [], Sorted).

sort_helper([], Stack, Stack).
sort_helper([Name | Rest], Stack, Sorted):- insert_helper(Name, Stack, New_stack), sort_helper(Rest, New_stack, Sorted).

insert_helper(Item, [], [Item]).
insert_helper(Item, [H | R], [Item, H | R]):- unit(Item, Price_Item, _), unit(H, Price_H, _), Price_Item > Price_H.
insert_helper(Item, [H | R], [H | Res]):- unit(Item, Price_Item, _), unit(H, Price_H, _), Price_Item =< Price_H, insert_helper(Item, R, Res).


buyable(List, Money, Purchase, Left):- buyable_helper(List, Money, Purchase, Left).

sum_of_list([], Sum):- Sum is 0.
sum_of_list([H | R], Sum):- sum_of_list(R,S), unit(H, Price, _), Sum is S + Price.

subset_gen([H|_], [H]).
subset_gen([H|Rest1], [H|Rest2]):- subset_gen(Rest1,Rest2).
subset_gen([_|R1],R2):- subset_gen(R1, R2).

buyable_helper(Arr, Limit, Pur, Rem):- subset_gen(Arr,Pur), sum_of_list(Pur,Sum), Sum =< Limit, Rem is (Limit - Sum).