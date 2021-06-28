#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../includes/minishell.h"
#include "../get_next_line/get_next_line.h"

//int		left_redirect(t_cmd *cmd_list), char *argv[], char **envp[])

//int		main(void)
//{
//	int		fd;
//	int fds[2];                      // an array that will hold two file descriptors
//	pipe(fds);                       // populates fds with two file descriptors
//
//	pid_t pid = fork();
//	char *buf;
//	int value;
//	if (pid == 0)
//	{
//		fd = open("test", O_RDONLY, 0644);
////		fd = open (cmd_list->redirect_filename[1] , O_RDONLY, 0644);
//		//: 파일을 읽기 전용으로 open합니다.
//		if (fd < 0)
//		{
//			printf("no surch file");
//			return (-1);
//		}
//
//		close(fds[0]);
//		//while((value = get_next_line(fd, &buf)  > 0))
//		//	ft_putendl_fd(buf, fds[1]);
//		//fds[1]);
//
//		dup2(fd, fds[1]);
//		dup2(fd, STDIN);
//
//		//while((value = get_next_line(STDIN, &buf)  > 0))
//		//	printf("%s\n", buf);
//		close(fds[1]);
//		close(fd);
//		exit(0);
//	}
//	int status;
//	pid_t wpid = waitpid(pid, &status, 0);
//	close(fds[1]);
//
//	//while((value = get_next_line(fds[0], &buf)  > 0))
//	//	printf("%s\n", buf);
//	while((value = get_next_line(STDIN, &buf)  > 0))
//		printf("%s\n", buf);
//	//while((value = get_next_line(fds[0], &buf)  > 0))
//	//	printf("%s\n", buf);
//	//dup2(fds[0], STDIN); 
//	printf("==%d==", STDIN);
//	close(fds[0]);
//	return wpid == pid && WIFEXITED(status) ? WEXITSTATUS(status) : -1;
//
//
////	int fd = open("test", O_RDONLY);
//  //int fd = open("test", O_WRONLY | O_CREAT | O_APPEND, 0744); 
////	while((value = get_next_line(0, &buf)  > 0))
////	{
////	  printf("%s\n", buf);
////	  printf("sdfsdf");
////	}// 이거 있으면 sort출력이 안나오는데,  이거 없으면 소트 출력이 나옴.. 개신깋마.
//}

//int		right_redirect(t_cmd *cmd_list, char *argv[], char **envp[])


int		left_redirect(void)
{
	int		fd;
//
//	pid_t pid = fork();
// ================
	fd = open("test", O_RDONLY, 0644);
	//cmd_list->redirect_filename[3]
	dup2(fd, STDIN);
	close(fd);


	return 0;
}


int		right_redirect(void)
{
//	int		fd;

//	fd = open("test1234", O_WRONLY | O_CREAT | O_TRUNC, 0744);
	//cmd_list->redirect_filename[3]
//	dup2(fd, STDOUT);

//	char *buf;
//	int value;
//	while((value = get_next_line(STDIN, &buf)  > 0))
//	{
//	  printf("%s\n", buf);
//	}
//	close(fd);
//	close(STDOUT);
	return 0;
}

int		right_redirect_double(void)
{
	int		fd;

	fd = open("test1234", O_WRONLY | O_CREAT |  O_APPEND, 0744);
	write(fd, "***\n", 4);
	close (fd);
	return 0;	
}
//	//0744
//	//cmd_list->redirect_filename[3]
//	dup2(fd, STDOUT);
////	char *buf;
////	int value;
////	while((value = get_next_line(STDIN, &buf)  > 0))
////	{
////	  printf("%s\n", buf);
////	}
//
//	write(STDOUT, "wersaaawjekfjf\n", 4);
//	write(STDOUT, "b", 1);
//	write(STDOUT, "b", 1);
//	write(STDOUT, "b", 1);
//	write(STDOUT, "b", 1);
//	write(STDOUT, "asdfqw", 6);
//	
//	close(fd);
//	close(STDOUT);
//	//printf("giigigigi");
//	return 0;
//}

int		main(void)
{
	int fd;
	
	left_redirect();
//	fd = open("test1234", O_WRONLY | O_CREAT | O_TRUNC, 0744);
//	close(fd);
	fd = open("test1234", O_WRONLY | O_CREAT |  O_APPEND, 0744);
	write(fd, "***\n", 4);
	close (fd);	
	return 0;
}


	//right_redirect_double();

//	char *buf;
//	int value;
//	while((value = get_next_line(STDIN, &buf)  > 0))
//	{
//	  printf("%s\n", buf);
//	}

//	right_redirect();

//	return (0);
	//write(STDOUT, 
//}
// ================
//	if (pid == 0)
//	{
//		fd = open(cmd_list->redirect_filename[3], O_WRONLY | O_CREAT | O_TRUNC, 0744);
//		//파일을 쓰기 전용으로 open합니다.
//		if (fd < 0)
//		{
//			printf("no surch file");
//			return (-1);
//		}
//		// 지금 문제가, fd의 출력 장소에, 삽입해야할 
//		// 근데, 삽입을 할려는데, 그럴려면,
//		// 이런식으로 먼저 연결하고, exec_funtion을 돌려야함.
//		dup2(fd, STDOUT);
//		close(fd);
//		exit(0);
//	}
//	int status;
//	pid_t wpid = waitpid(pid, &status, 0);
//	return wpid == pid && WIFEXITED(status) ? WEXITSTATUS(status) : -1;
//	return 0;
//}

//
//
//int		right_redirect_double(t_cmd *cmd_list, char *argv[], char **envp[])
//{
//	int		fd;
//
//	pid_t pid = fork();
//	if (pid == 0)
//	{
//		fd = open(cmd_list->redirect_filename[3], O_WRONLY | O_CREAT |  O_APPEND, 0744);
//		if (fd < 0)
//		{
//			printf("no surch file");
//			return (-1);
//		}
//		dup2(fd, STDOUT);
//		close(fd);
//		exit(0);
//	}
//	int status;
//	pid_t wpid = waitpid(pid, &status, 0);
//	return wpid == pid && WIFEXITED(status) ? WEXITSTATUS(status) : -1;
//}
//
//void	redirec(t_cmd *cmd_list, char *argv[], char **envp[])
//{
//	// 지금 걸리는 부분, 파일이름, 확인
//	int i = 0;
//	int j = 1;
//	if (ft_strncmp("<", cmd_list->redirect_filename[1], 2) == 0)
//		left_redirect(fds);
//	else if (ft_strncmp("<<", cmd_list->redirect_filename[1], 3) == 0)
//		left_redirect_double();
//	if (ft_strncmp(">", cmd_list->redirect_filename[2], 3) == 0)
//		right_redirect();
//	else if (ft_strncmp(">>", cmd_list->redirect_filename[2], 3) == 0)
//		right_redirect_double();
//	exec(cmd_line, argv, envp);
//	//exec_function
//}
//
//
//
//int main(int argc, char *argv[]) {
//  int fds[2];                      // an array that will hold two file descriptors
//  pipe(fds);                       // populates fds with two file descriptors
//  pid_t pid = fork();              // create child process that is a clone of the parent
//
//  if (pid == 0) {                  // if pid == 0, then this is the child process
//
//
//    dup2(fds[0], STDIN);    // fds[0] (the read end of pipe) donates its data to file descriptor 0
//    close(fds[0]);                 // file descriptor no longer needed in child since stdin is a copy
//    close(fds[1]);                 // file descriptor unused in child
//    char *argv[] = {(char *)"sort", NULL};   // create argument vector
//    if (execvp(argv[0], argv) < 0) exit(0);  // run sort command (exit if something went wrong)
//  }
//
//  // if we reach here, we are in parent process
//  const char *words[] = {"pear", "peach", "apple"};
//  // write input to the writable file descriptor so it can be read in from child:
//  size_t numwords = sizeof(words)/sizeof(words[0]);
//  for (size_t i = 0; i < numwords; i++) {
//	write(fds[1], words[i], (int)(ft_strlen(words[i])));
//	write(fds[1], "\n", 1);
//  }
//
//  //close(fds[0]);                 // file descriptor unused in parent
//  // send EOF so child can continue (child blocks until all input has been processed):
//
//  close(fds[1]);
//  char *buf;
//  int value;
//
////  int fd = open("test", O_RDONLY);
////  //int fd = open("test", O_WRONLY | O_CREAT | O_APPEND, 0744); 
//  while((value = get_next_line(fds[0], &buf)  > 0))
//  {
//	  printf("%s\n", buf);
//  }// 이거 있으면 sort출력이 안나오는데,  이거 없으면 소트 출력이 나옴.. 개신깋마..
//  int status;
//  pid_t wpid = waitpid(pid, &status, 0); // wait for child to finish before exiting
//
//
//	  //======
//
//  return wpid == pid && WIFEXITED(status) ? WEXITSTATUS(status) : -1;
//}
