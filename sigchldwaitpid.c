
 
 /**********************************************************************************************************/
 /*                     		Acknowledgement					                   */
 /*                  SLIIT 3rd year DCCN-III Lab 4						           */
 /*                  SLIIT 3rd year DCCN-III Lecture 4                                                     */
 /*                  Referance book:2003-unix-network-programming-vol-1-3rd-ed                             */
 /**********************************************************************************************************/
#include	"cc352.h"
#include	<sys/wait.h>

void
sig_chld(int signo)
{
	pid_t	pid;
	int		stat;

	while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
		printf("child %d terminated\n", pid);
	return;
}
