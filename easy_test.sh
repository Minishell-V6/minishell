GREEN='\033[0;32m'
RED='\033[0;31m'
BLANK='\033[0m'

echo "$0\n"
if [ $# -eq 1 ]; then
	ARG="$1";
else
	echo "매개변수는 1개만 입력하세요"
	echo 'ex) bash easy_test.sh "cd .."'
	exit
fi

value1=$(echo $ARG | bash)
value2=$(echo $ARG | ./minishell)
if [ $value1=$value2 ]
then
        echo -e "$GREEN OK$BLANK"
else
        echo -e "$RED Kill$BLANK"
fi
echo -e "=========value1=========\n$value1"
echo -e "=========value2=========\n$value2"
