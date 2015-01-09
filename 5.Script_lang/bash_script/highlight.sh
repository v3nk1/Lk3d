# For any references see man tput or terminfo

select=`tput smso`		#Dont use single quotes(') here, use (`) by pressing " ~ "
desel=`tput rmso`
bold=`tput bold`
unbold=`tput sgr0`
reset=`tput reset`

line="\033[4m"			# but here ` its not at all do our requirement, so use double quotes
unline="\033[0m"

RED="\033[1;31m"		#1;47 then text will be selected
YELLOW="\033[1;33m"		
WHITE="\033[1;37m"
ITALIC="\033[3;33m"

echo -e ${line}${RED}"Name"${unline}:${WHITE}
echo -e ${line}${ITALIC}"Name"${unline}:${WHITE}${unbold}

#or use bellow one
#echo -e "\033[4mName\033[0m:"
echo -e ${line}${bold}${ITALIC}"Name"${unline}:${WHITE}${unbold} 

#In make script you want coloring then use bellow, In make file dont specify -e option but must in bash script
#YELLOW ITALLIC UNDERLINE BOLD
echo "\033[3;33m\033[4m${bold}THISISIT\033[0m:"

echo VENKATESH
#echo ${bold}B.Venkatesh ${unbold}
echo ${select}Bolla Venkatesh ${desel}
