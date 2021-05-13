# gpass
Make random passwords on the command line

### Command line options
| Option | Description |
| ------ | ------ |
| `-a`  | Only characters |
| `-m`  | Characters and numbers |
| `-s`  | Characters, numbers and symbols |
| `-n`  | Only numbers |
| `-u`  | Username and password mode |
| `-l <length>`  | Make password with specified length |


It gets the entropy directly from the Linux kernel using glibc. Only one such call is made per running the program so the max length is capped at 64 characters. Default length is 40 alphanumeric characters.
