# minishell

# 주의 사항.
 > 해당 코드는 기능구현만 완료된 상태입니다. 
 변수명 수정 및 코드정리는 팀원끼리 각자 진행하였습니다. 

### 완료본 링크
>hoylee : https://github.com/hey-chocopie/42_seoul/tree/main/minishell
sejpark :
seuyu : 
seojeong : 
jiylee : 
djeon : https://github.com/Daewoong-Jeon/minishell

# 프로젝트 소개
 쉘은 사용자로부터 명령을 받아, 그것을 해석하고 프로그램을 실해하는 역활을 합니다. 리눅스에서 표준으로 사용되는 쉘은 bash입니다.
이 프로젝트에서 저만의 작은(mini) bash를 제작해보았습니다. 그래서 프로젝트 이름은  minishell 입니다.


Summary: The objective of this project is for you to create a simple shell. Yes, your
little bash or zsh. You will learn a lot about processes and file descriptors.

* 이번 과제에서는 베쉬처럼 동작하는 shell을 만들어보자. 




# 구현목표
### 구현할 빌트인 함수들
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options

> 나머지 명령들은 /bin/에 있는 명령들로 동작되게 만들었다.

### 따옴표 처리
’ inhibit all interpretation of a sequence of characters.
• " inhibit all interpretation of a sequence of characters except for $.
* \'또는 \"에로 둘러쌓인 값들은 문자로 인식되게 했다. (|, >, < , $ 와 화이트 스페이스)

### 리다이렉트 파이프 처리
* 리다이렉트로 표준출력을 다른파일로 표준입력으로 넣어주는 기능 (>, >>, <)
* 리다이렉트로 표준입력을 받고 구분자가 들어오면 끝나는 기능 (<<)
* 파이프가 있으면 파이프 기준 왼쪽 출력값을 오른쪽으로 표준입력으로 넘겨주는 기능(|)
* 에러처리구현

### exit status
* 쉘 명령 실행후 $? 으로 출력했을 때, 명령 실행에 대한 상태를 나타내는기능
* exit로 프로세스 종료시 종료상태를 나타내는 기능

### signal
* 인터럽트 발생시 기능 구현
* ctrl-c, ctrl-d, ctrl-\기능



# 사용전 라이브러리. 

mac기준 대부분 xcode commandline tools을 설치하면 내장되어있는 라이브러리를 사용했다. 
commandline tools 없던 라이브러리.
```
brew install readline
brew info realine
```
info 커맨드를 입력하면 -L과 -I옵션에 대한 경로가 나온다. 
해당 경로를 minishell 폴더 속 MAKEFILE을 열어

```
 21 READLINE_LIB    = -lreadline -L/usr/local/opt/readline/lib
 22 READLINE_INC    = -I/usr/local/opt/readline/include
```
 를 본인 info 경로로 바꾸어주면 정상적으로 실행된다.

# 기타
```
CC 				= gcc
#CC 				= gcc -g -fsanitize=address
# 컴파일 옵션 바꾸면 릭 테스트 해볼수 있습니다.
```
```
#CC 				= gcc
CC 				= gcc -g -fsanitize=address
# 컴파일 옵션 바꾸면 릭 테스트 해볼수 있습니다.
```
아래 cc 옵션을 릭 검사를 진행하며 제작하였습니다.


# 테스트 케이스 
### Example for minishell
![미니쉘사진1](https://user-images.githubusercontent.com/52343427/143850527-3c7f508c-2967-46b9-960f-7cc7026ae037.gif)

### Example for bash
![미니쉘사진3](https://user-images.githubusercontent.com/52343427/143851541-2407809a-1029-47a7-a03d-84bb10484b6e.gif)

### simple Command & global
```
/bin/ls
/bin/ps
/bin/pwd
```
>bin 폴더의 실행파일들이 실행된다, 코멘드라인에 스페이스바나 텝 또는 공백을 넣고 enter를 입력해도 bash와같이 실행된다. 

### arguments & history
```
echo hi > test
/bin/cat test
/bin/rm test
/bin/ls iwejfoij
```

### echo
```
echo hellow word
echo -n hellow word
echo -nnnnn hellow word
echo -n -n hellow word
echo sliefjilaejfilajeilfjl
ech"o hio"
echo "hio"
ecoh "h"i"o"
```


### exit
```
./minishell
exit
$?
./minishell
eixt 5
$?
./minishell
exit 500
$?
./minishell
exit aioejf
$?
./minishell
exit 500 200 300
$?
exit
$?
```

### return value of a process
```
/bin/ls
$?
/bin/pwd
$?
/bin/ls isjefio
$?
/bin/pwd iflwej 
$?
cat < qeew
$?
export 123eifj
$?
$?
expr $? + $?
```

### signals
* 아무 입력없이 ctrl + c : 새줄
* 아무 입력없이 ctrl + d : 아무변화 없음
* 아무 입력없이 ctrl + \ : 미니쉘 종료
* 글자 입력한상태로 ctrl + c : 새줄
* 글자 입력한상태로 ctrl + d : 아무변화 없음
* 글자 입력한상태로 ctrl + \ : 아무변화 없음
* cat, 이나 grep 표준 입력인상태 ctrl + c : 배쉬와 같음
* cat, 이나 grep 표준 입력인상태 ctrl + d : 배쉬와 같음
* cat, 이나 grep 표준 입력인상태 ctrl + \ : 배쉬와 같음

### double Quotes
```
echo "cat lol.c | cat > lol.c"
echo "h"e"l"l""o"w wo"r"d"
echo "h"e"l"l""o"w wo"r"<d"
echo "h"e"l"l""o"w wo"r"|d"
echo "hellow          w       ord"
echo hellow         w           ord
echo "hellow<< ,< ,> ,>> word"
```

### Single Qoutes
```
echo 'hellow word'
echo '<< >> < > |'
echo '$USER'
echo $USER
```

### env
```
env
```

### export
'''
export
export aa
export test=123
export test=321
'''

### unset
```
unset aa
unset test
```

### cd
```
cd
cd /
cd ~
cd ~/
cd ~/sldkfjj
cd .
cd ..
```

### pwd
```
pwd
```

### Relativ Path
```
../../../../../../../../bin/ls
```
> 경로 다르면 실행 안되수도 있음.

### Redirection
```
echo 1 > file1
echo 2 > file2
cat < file1 > out1
cat < file1 >> out1
cat < file1 > out1 > out2
cat < file1 > out1 > out2 < file2 > out3 
cat < file1 > out1 > out2 < file2 > out3 << test
rm file1 file2 out1 out2 out3
```

### pipes
```
cat file | grep | bla | more
```
>bla 들어간 file만들고 해보아야합니다.

### enviroment variables
```
echo $USER
echo '$USER'
echo "$USER"
```
