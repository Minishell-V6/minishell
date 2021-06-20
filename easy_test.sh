GREEN='\033[0;32m'
RED='\033[0;31m'
BLANK='\033[0m'

#echo "$0\n"
if [ $# -eq 1 ]; then
	ARG="$1";
else
	echo "매개변수는 1개만 입력하세요"
	echo 'ex) bash easy_test.sh "cd .."'
	exit
fi

bash_result=$(echo $ARG | bash)
bash_exit=$?
minishell_result=$(echo $ARG | ./minishell)
minishell_exit=$?
if [ "$bash_result" == "$minishell_result" ]
then
        printf "$GREEN OK$BLANK\n"
else
        printf "$RED Kill$BLANK\n"
fi
printf "=========bash_result=========\n$bash_result\n"
printf "=========minishell_result=========\n$minishell_result\n"
