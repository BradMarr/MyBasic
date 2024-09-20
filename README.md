# My Basic
## basic but MINE

Meant for Linux x64, not going to bother curating to anything else. I'm Learning assembly as we go so don't expect quality. 

using [this](https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/) table as reference and it is very useful.

The language is very simple, look in ex/ex.mybasic for reference. The only required code is the exit at the end, without that it will not properly run.

| Command  | Arg 1       | Arg 2     | Arg 3    | Description                                      |
|----------|-------------|-----------|----------|--------------------------------------------------|
| exit     | exit code: int  |           |          | Exits program with <arg 1>'s exit code          |
| print    | value: any      | ...       | ...      | Prints value, concatenates all args provided     |
| _        | assembly   | ...       | ...      | Inlines assembly, takes every token after        |
| import   | item        | library    |          | Imports an item from a library                   |
| var      | name       | size (bytes): int     | value    | Defines a var with a set value                   |
| add      | variable    | value: int     |          | Adds value to variable                            |
| sub      | variable     | value: int     |          | Subtracts value from variable                     |
| inc      | variable    |           |          | Increments variable by 1                          |
| dec      | variable    |           |          | Decrements value by 1                            |
