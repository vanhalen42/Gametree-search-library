# DSA-Mini-Project-Team-52-Tree-search-library
1.  The idea behind Tree Search Library is that, once given the 'comparator' function between nodes by 
    the user, the library can use this to perform any kind of search by the change of just one function.
2. The comparator function takes as input the pointers of two nodes and outputs whether the first is 
    lesser than the other. You can use this comparator for deciding the order of 2 nodes in the priority 
    queue.
## The following files can be modified by the user: 
1. ## node.h
    - This file contains the structure of a tree node and all the parameters that it has. User is free to modify the user modfiyable paramteres in the file.
    -This file also contains the different functions in the library, some of which are in-buit which the user can use.
    -More information is diplayed in the file itself.
2. ## comparator.c
    - This file contains all user modifiable functions and list of all the comparators for the library, like the ones needed for input of node and print functions.
    - User can add any number of comparators to the comparator functions, and give a name to them.
    - User is free to add any function in this file, to print the traversal order or for any other task.
    - There are some inbuilt functions in the file which the user can use. 
    - More instructions are present in the file itself.

## Instructions to Use the library
1. A sample main.c file is provided which shows how the file can be used. 
2. The library expects a main.c to be included in the root directory as the Makefile requires it to compile the code.
3. Run make to compile the code to genereate the "tree_lib" file which can be used using the commad :
    ```
    ./tree_lib 
    ``` 
4. For normal/user-defined tree sturcture, you can input in the format specified in the comparator.c `(check ./testcases/ts_data_1.txt)`.
5. For the in-built game tree, sample code has been provided to use. This code has been written as a user.