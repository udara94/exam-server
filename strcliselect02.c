 
 /**********************************************************************************************************/
 /*                     		Acknowledgement					                   */
 /*                  SLIIT 3rd year Lab 4						                   */
 /*                  SLIIT 3rd year Lab 5                                                                  */
 /*                  SLIIT 3rd year DCCN-III Lecture 5                                                     */
 /*                  Referance book:2003-unix-network-programming-vol-1-3rd-ed                             */
 /**********************************************************************************************************/

#include	"cc352.h"

void
str_cli(FILE *fp, int sockfd)
{
	int			maxfdp1, stdineof;
	fd_set		rset;
	char		sendline[MAXLINE], recvline[MAXLINE];

	stdineof = 0;	/**/
	FD_ZERO(&rset);	/*clear all bits in fdset*/
	for ( ; ; ) {
		if (stdineof == 0)
			FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);		/* turn on the bit for fd in fdset */
		maxfdp1 = max(fileno(fp), sockfd) + 1;  /*get the max from the max function and assign to maxfdp1*/
		Select(maxfdp1, &rset, NULL, NULL, NULL); 
			/*if(errno==EINTR)
				continue;
			else
				err_sys("select error");*/
		

		if (FD_ISSET(sockfd, &rset)) {	/* is the bit for fd on in fdset ? */
			if (Read(sockfd, recvline, MAXLINE) == 0) {	/*read the content recive from the server until end of file*/
				if (stdineof == 1)	/*if the stdineof value is 1 then return */
					return;		/* normal termination */
				else
					err_quit("str_cli: server terminated prematurely"); /*if the stdineof is not 1 give an error*/
			}

			Fputs(recvline, stdout);	/*display the content in the recvline to standed output */
			memset(&recvline,0, sizeof(recvline));/* set the recvline buffer to zero*/
		}

		if (FD_ISSET(fileno(fp), &rset)) {  /* is the bit for fd on in fdset ? */
			if (Fgets(sendline, MAXLINE, fp) == NULL) {	/*get the input to a sendline buffer*/
				stdineof = 1;
				Shutdown(sockfd, SHUT_WR);	/* send FIN */
				FD_CLR(fileno(fp), &rset);	/* turn off the bit for fd in fdset */
				continue;
			}

			Writen(sockfd, sendline, strlen(sendline)); /*write the content to the sendline buffer*/
		}
	}
}
