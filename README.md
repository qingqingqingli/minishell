<p align="center">
  <img src="https://github.com/qingqingqingli/readme_images/blob/master/codam_logo.png" height='200'>
</p>

# minishell
***The objective of this project is for you to create a shell. New concepts about processes and file descriptors are introduced.***

---

### Project summary
> 3th ring Codam project

This project’s objectives are similar to all this first year’s objectives: Rigor, use of C, use of basic algorithms, information research etc. With Minishell, you’ll be able to travel through time and come back to problems people faced when Windows didn’t exist.

This is an group project created by R. Bakker & <a href="https://github.com/qingqingqingli" target="_blank">Q. Li</a>



---

### Technical considerations
> The project needs to comply with the following rules/functionalities.

- Show a prompt when waiting for a new command
- Search and launch the right executable (based on the PATH variable or by using relative or absolute path) like in bash
- It must implement the builtins like in bash:
  - echo with option ’-n’
  - cd with only a relative or absolute path
  - pwd without any options
  - export without any options
  - unset without any options
  - env without any options and any arguments
  - exit without any options
- ; in the command should separate commands like in bash
- ’ and " should work like in bash except for multiline commands
- Redirections < > “>>” should work like in bash except for file descriptor aggregation
- Pipes | should work like in bash
- Environment variables ($ followed by characters) should work like in bash
- $? should work like in bash
- ctrl-C, ctrl-D and ctrl-\ should have the same result as in bash

---

### Usage
> Run the following commands in the terminal

```shell
$ git clone https://github.com/rbakker96/minishell.git minishell
$ cd minishell
$ make
$ ./minishell
```

---

### Used resources
> Most noteworthy resources used during this project

- <a href="https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html" target="_blank">Bash Reference Manual</a>
- <a href="https://www.geeksforgeeks.org/pipe-system-call/?ref=rp" target="_blank">pipe() System call</a>
- <a href="https://www.geeksforgeeks.org/wait-system-call-c/?ref=rp" target="_blank">Wait System Call in C</a>
- <a href="https://www.geeksforgeeks.org/fork-system-call/?ref=rp" target="_blank">fork() in C</a>

