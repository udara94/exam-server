
 /******************************************************************************************************/
 /*		              Acknowledgement						               */  													              
 /*           	SLIIT 3rd year DCCN-III Lab 1,2							   1,2                                                                                                  */                                         
/*          	SLIIT 3rd year DCCN-III Lecture 2                                                              */                                                  
/*           	Referance book:2003-unix-network-programming-vol-1-3rd-ed                             */                        
/* 		getsockname():                                                                        */
/*		ref:https://support.sas.com/documentation/onlinedoc/sasc/doc700/html/lr2/zockname.htm */
/******************************************************************************************************/
 


#include	"cc352.h"

int
main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	servaddr;
	int len=sizeof(servaddr);
	//char hash[100]="----------------------------------------";

	if (argc != 2)	/* process the request */
			
		err_quit("usage: tcpcli <IPaddress>");

	sockfd = Socket(AF_INET, SOCK_STREAM, 0); /*creating a socket*/

	bzero(&servaddr, sizeof(servaddr)); /*initialize a socket address structure to 0*/
	servaddr.sin_family = AF_INET;		/*set the address family to IPv4*/
	servaddr.sin_port = htons(SERV_TCP_PORT);	/*assign the port 52001*/
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));/*Connect with the server*/
	
	if(getsockname(sockfd,(SA *)&servaddr,&len)== -1){  /*Get the local ip address and port number*/
		perror("getsockname faild");
		return -1;
	}
	else{
		printf("\nLocal IP address is:%s and port number is:%d\n\n",inet_ntoa(servaddr.sin_addr),ntohs(servaddr.sin_port)); /*print the local ip addres*/
	}

	str_cli(stdin, sockfd);		/* do it all */

	exit(0);
}
