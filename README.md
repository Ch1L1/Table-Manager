# Table processor
The aim of project is create application, that will implement basic operations of table processors.
Input for application will be text data (to stdin). Commands will be set by arguments in command line.
For output use standard output (stdout).  

# Compile
Use makefile. That is easiest way:

    make
Alternatively you can compile it on your own:
 
    gcc -std=c99 -Wall -Wextra -Werror -pedantic -c -o sheet.o sheet.c

# Usage

    ./sheet [-d delimiter] [table editing commands]
or:

    ./sheet [-d delimiter] [selection commands] [data processing commands]

Argument `-d` defines what characters could be interpreted as columns delimiters.
In case delimtier is not set, delimiter is space ` `.  
First delimiter from delimiters will be used as delimiter for output data.


## Available commands
### Table editing commands
Commands that changes table dimension.
- `irow R` - adds new row with empty cells before row `R` (`R` > 0) 
- `arow` - adds new row with empty cells at the end of table
- `drow R` - deletes row `R` (`R` > 0)
- `icol C` - adds empty column before the column `C`
- `acol` - adds empty column behind last column
- `dcol C` - deletes column `C`
- `dcols N M` - deletes columns `N` to `M`, including `M` and `N`.

### Data processing commands
Commands that process data in table.
##### Required commands:
- `cset C STR` - to cell `C` sets string `STR` 
- `tolower C` - string in column `C` converts to lowercase
- `toupper C` - string in column `C` converts to uppercase
- `round C` - rounds number in column `C`
- `int C` - removes decimal part of number in column `C`  
- `copy N M` - replaces value in column `M` with value from column `N`   
- `swap N M` - swaps value of column `N` with value of column `M`  

### Row selection commands 
Commands that selects range of rows to be processed.
- `rows N M` - selects rows `N` to `M` including. 
    - Rows from row `N` to end of table could be represented as `rows N -`
    - Last row only could be represented as `rows - -`
- `beginswith C STR` - selects rows, where column `C` starts with string `STR`
- `contains C STR` - selects rows, where column `C` contains string `STR`
 
