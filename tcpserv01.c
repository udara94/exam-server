 /***********************************************************************************************/
 /*		              Acknowledgement						        */ 														              
/*              SLIIT 3rd year DCCN-III Lab 2                                                          */                                                          
/*            	SLIIT 3rd year DCCN-III Lecture 3                                                        */                                                   
/*            	Referance book:2003-unix-network-programming-vol-1-3rd-ed                       */      
/* 												*/
/************************************************************************************************/


#include"cc352.h"
#include<signal.h>
#include<fcntl.h>
#include<sys/wait.h>

int
main(int argc, char **argv)
{

	void sig_chld(int);
	int			listenfd, connfd;
	pid_t			childpid;
	socklen_t		clilen;
	struct sockaddr_in	cliaddr, servaddr;
	const char	*ptr;
	char buff[MAXLINE];

	listenfd = Socket(AF_INET, SOCK_STREAM, 0); /*create a socket and assign the return value to listenfd*/

	bzero(&servaddr, sizeof(servaddr)); /*initialize a socket address structure to 0*/
	servaddr.sin_family      = AF_INET;	/*set the address family to IPv4*/
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port        = htons(SERV_TCP_PORT); /*assign the port 52001*/

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr)); /*bind the port number and IP addres*/

	if(Listen(listenfd, LISTENQ)<0){
		perror("listen faild");
		exit(1);
	}
	//read_file();
	Signal(SIGCHLD, sig_chld); /*handling zombie processes*/

	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		if((connfd = Accept(listenfd, (SA *) &cliaddr, &clilen))<0){ /*accept the client connection and return the connection file descriptor*/
		if(errno==EINTR)
			continue;
		else
			err_sys("accept error");
		}

		if(getpeername(listenfd,(SA *)&cliaddr,&clilen)==0) /*get the client port number and IP address*/
			exit(0);
			
		if((ptr= inet_ntop(PF_INET,&cliaddr.sin_addr,buff,sizeof(buff)))==NULL){ /*convert the network address to presentaion format*/
			fprintf(stderr,"inet_ntop error \n");
			exit(0);
		
		}
		printf("connection from %s,port %d\n",ptr,ntohs(cliaddr.sin_port)); /*display the IP address and port number*/

		if ( (childpid = Fork()) == 0) {	/* child process */
			Close(listenfd);	/* close listening socket */
			str_echo(connfd);	/* process the request */
			
			exit(0);
		}
		Close(connfd);			/* parent closes connected socket */
	}
}
