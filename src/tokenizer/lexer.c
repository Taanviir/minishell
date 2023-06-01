#include "../include/token.h"
#include "../include/utils.h"
#include "../include/token/type.h"

/* grammar is written in a format called "Backus-Naur Form" 
cmd [arg]* [|cmd [arg]* ]* [ [> filename] [< filename] [ >& filename] [>> filename] [>>& filename] ]* [&] 
This is shell grammar in Backus-Naur form
*/
