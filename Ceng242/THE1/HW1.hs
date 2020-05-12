module HW1 (
    form,
    constGrid,
    flatten,
    access,
    slice,
    vcat,
    hcat,
    without,
    matches2d
) where

-- do not modify the module declaration above!
-- this will ensure that you cannot load (compile)
-- the module without implementing all of the functions.

-- If you have functions you do not want to implement,
-- leave them as undefined or make them have another
-- default value. If you fully remove any of their definitions,
-- that will be a compilation error during evaluation,
-- and you will be eligible for (yay!) a 5 point deduction
-- (that's bad for your grade). Runtime errors in your code 
-- (rather than compilation errors) are acceptable and will simply
-- result in you getting zero from the specific test case causing
-- an error.

-------------------------
-- Fellowship of the Grid (25, 5, 5, 5 points)


form :: [a] -> (Int, Int) -> [[a]] 
form list (x,y) = case list of [] -> []
                               [t] -> [[t]]
                               otherwise -> [take y list] ++ (form (drop y list) (x, y))

constGrid :: a -> (Int, Int) -> [[a]]
constGrid m (x,y) = let atom = [ m | k<-[1..y]] in [ atom | w<-[1..x]]

flatten :: [[a]] -> [a]
flatten x = [ k | w<-x, k<-w ]

access :: [[a]] -> (Int, Int) -> a
access list (x,y) = (list !! x) !! y


----------------------------
-- The Two Signatures (10, 5, 5, 10 points)


slice :: [[a]] -> (Int, Int) -> (Int, Int) -> [[a]]
slice list (x,y) (z,t) = let newlist = f1 list in map (f2) newlist
                         where f1 l = take (y-x).drop x $ l
                               f2 l = take (t-z).drop z $ l

vcat :: [[a]] -> [[a]] -> [[a]]
vcat list1 list2 = list1 ++ list2

hcat :: [[a]] -> [[a]] -> [[a]]
hcat list1 list2 = zipWith (++) list1 list2

without :: [[a]] -> (Int, Int) -> (Int, Int) -> [[a]]
without list (x,y) (z,t) = let newlist = f1 list in map (f2) newlist
                           where f1 l = (take x l) ++ (drop y l)
                                 f2 l = (take z l) ++ (drop t l)
----------------------------
-- Return of the Non-trivial (30 points, 15 subject to runtime constraints)


matches2d :: Eq a => [[a]] -> [[a]] -> [(Int, Int)]
matches2d list grid
    | (source_row <  grid_row) || (source_col < grid_col) = []
    | otherwise =  row_helper list grid 0 grid_col grid_row source_col source_row
    where source_row = length list
          source_col = length (list !! 0)
          grid_row = length grid
          grid_col = length (grid !! 0)

row_helper list grid rowcount grid_col grid_row source_col source_row
    | (rowcount + grid_row) > source_row = []
    | otherwise = (col_helper (take grid_row list) grid rowcount 0 grid_col source_col) ++ (row_helper (tail list) grid (rowcount+1) grid_col grid_row source_col source_row)

col_helper liste grid rowcount colcount grid_col source_col
    | (colcount + grid_col) > source_col = []
    | otherwise = (if (grid == (map (take grid_col) liste)) then [(rowcount,colcount)] else []) ++ (col_helper (map (tail) liste) grid rowcount (colcount+1) grid_col source_col)

----------------------------
-- What is undefined? Just a value that will cause an error
-- when evaluated, from the GHC implementation:
-- undefined = error "Prelude.undefined"
-- But it allows your module to be compiled
-- since the function definitions will exist.
