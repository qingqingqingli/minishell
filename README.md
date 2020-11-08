[![Logo](https://github.com/qingqingqingli/readme_images/blob/master/codam_logo_1.png)](https://github.com/qingqingqingli/minishell)

# minishell
***This project is to create a simple shell. Concepts about processes and file descriptors are introduced.***

Working on this project allows you to travel through time and come back to problems people faced when Windows didn't exist. 

This is a group project completed by [Q. Li](https://github.com/qingqingqingli") & [R. Bakker](https://github.com/rbakker96)

## Technical considerations
> The following elements need to work like in bash

- Show a ```prompt``` when waiting for a new command

- Search and launch the right ```executable``` (based on the ```$PATH``` variable or by using relative or absolute path)

- Implement the below builtins:
  - ```echo``` with option ’-n’
  - ```cd``` with only a relative or absolute path
  - ```pwd``` without any options
  - ```export``` without any options
  - ```unset``` without any options
  - ```env``` without any options and any arguments
  - ```exit``` without any options

- ```;``` to separate commands

- Pipes ```|```

- ```'``` and ```"``` except for multiline commands

- Redirections ```<``` ```>``` ```>>``` except for file descriptor aggregation

- ```Environment variables``` ($ followed by characters)

- ```$?``` to store exit status of the previous command

- ```ctrl-C```, ```ctrl-D``` and ```ctrl-\```

## How to test
> Run the following commands

```shell
$ git clone https://github.com/qingqingqingli/minishell
$ cd minishell
$ make
$ ./minishell
```

## Examples

- Create minishell executable

[![minishell_0](https://github.com/qingqingqingli/readme_images/blob/master/minishell_0.png)](https://github.com/qingqingqingli/minishell)

[![minishell_1](https://github.com/qingqingqingli/readme_images/blob/master/minishell_1.png)](https://github.com/qingqingqingli/minishell)

- Start testing

[![minishell_2](https://github.com/qingqingqingli/readme_images/blob/master/minishell_2.png)](https://github.com/qingqingqingli/minishell)