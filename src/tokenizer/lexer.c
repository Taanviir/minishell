#include "../include/token.h"
#include "../include/utils.h"
#include "../include/token/type.h"

/* grammar is written in a format called "Backus-Naur Form" 
cmd [arg]* [|cmd [arg]* ]* [ [> filename] [< filename] [ >& filename] [>> filename] [>>& filename] ]* [&] 
This is shell grammar in Backus-Naur form
*/

/* based on matching a pattern set the type field in t_simple_command 
pattern is simple either an operator from a list, or no its a word */
