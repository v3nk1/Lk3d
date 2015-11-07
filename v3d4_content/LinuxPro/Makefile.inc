
bold=`tput bold`

MAKEFLAGS += -rR --no-print-directory
RM=@rm -rf a.out *~ *.o *.swp *.sow *.swp* .*swp* .*sw*
SRM=@sudo rm -rf a.out *~ *.o *.swp *.sow *.swp* .*swp* .*sw*
GCC=@gcc -w -g  
SGCC=@sudo gcc -w -g  
ECHO=&& echo -n "  CC  " && echo "$P"

CPATH=echo "\033[3;33m\033[4m${bold}$${dir}\033[0m:"
