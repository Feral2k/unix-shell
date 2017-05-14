## Team Members

- Jason Martin
- Robert Carleton
- Christopher Cervantez-Hernandez
- Logan Garcia

## Description

This is a C program designed to serve as a shell interface that accepts user commands and then executes each command in a separate process.

## Compilation

After downloading the code:

```$ gcc shell.c -o shell```

```$ ./shell```

After which, the user can enter terminal commands from osh>.

## Commands

Apart from terminal commands, this program supports retrieving and executing past commands. To see all past commands, type:

```$ osh>history```

To execute the last command entered, type:

```$ osh>!!```

To execute a specific command, type:

```$ osh>!n```

where n is a specific command number listed in history. To exit the program, type:

```$ osh>exit```

In order for the child process to continue running, append ```&``` to whatever command you are executing.

## Errors

Currently, the history displays the command but not the arguments of the command. This is because it is difficult to know how many arguments have been passed through.
