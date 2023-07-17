# PROGRAM PROGRESS

## Mandatory

- [x] Your shell must implement the following builtins:
	- [x] `echo` with option `-n`
	- [x] `cd` with only a relative or absolute path
	- [x] `pwd` with no options
	- [x] `export` with no options
	- [x] `unset` with no options
	- [x] **[Needs bugfix]** `env` with no options or arguments
	- [x] **[Needs bugfix]** `exit` with no options
- [x] Display a **prompt** when waiting for a new command.
- [x] Have a working **history**.
- [x] Search and launch the right executable (based on the **PATH** variable or using a relative or an absolute path).
- [x] Not interpret unclosed quotes or special characters which are not required by the subject such as `\` (backslash) or `;` (semicolon).
- [x] Handle `'` (single quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence.
- [x] Handle `"` (double quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence except for `$` (dollar sign)
- [x] **[Needs bugfix]** Handle environment variables ($ followed by a sequence of characters) which should expand to their values.
- [x] In interactive mode:
	- [x] <kbd>Ctrl</kbd>+<kbd>C</kbd> displays a new prompt on a new line.
	- [x] <kbd>Ctrl</kbd>+<kbd>D</kbd> exits the shell.
	- [x] <kbd>Ctrl</kbd>+<kbd>\\</kbd> does nothing.
- [x] Handle <kbd>Ctrl</kbd>+<kbd>C</kbd>, <kbd>Ctrl</kbd>+<kbd>D</kbd> and <kbd>Ctrl</kbd>+<kbd>\\</kbd> which should behave like in bash.
- [ ] Implement redirections:
	- [ ] `>` should redirect output.
	- [ ] `<` should redirect input.
	- [ ] `>>` should redirect output in append mode.
	- [ ] `<<` should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
- [ ] Implement pipes (`|` character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
- [ ] Handle `$?` which should expand to the exit status of the most recently executed foreground pipeline.
	- [ ] Exit/Error status management.

## Bonus

- [ ] `&&` and `||` with parenthesis for priorities.
- [ ] Wildcards `*` should work for the current working directory.
