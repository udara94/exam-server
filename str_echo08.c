/******************************************************************************************************/
/*                                       Acknowledgement			                      */
/*                  SLIIT 3rd year DCCN-III Lab 4					              */
/*                  SLIIT 3rd year DCCN-III Lab 5                                                     */
/*                  SLIIT 3rd year DCCN-III Lecture 4,5                                               */
/*                  Referance book:2003-unix-network-programming-vol-1-3rd-ed                         */  
/*     Stackoverflow:https://stackoverflow.com/questions/822323/how-to-generate-a-random-number-in-c  */   
/*                                                                                                    */                                          
/******************************************************************************************************/

#include	"cc352.h"
#define SIZE 10
#include<sys/time.h>
#include <unistd.h>

void
str_echo(int sockfd)
{
	
	ssize_t		n;
	char		line[MAXLINE],tmp[MAXLINE];
	char 		arg3,arg;
	int count=0,correct=0,incorrect=0,correct_ans=0,wrong_ans=0;

	for ( ; ; ) {
//
	int n,r,qno,ca,a_qno,a_ca;
	FILE *fp;
	char q[100],an1[100],an2[100],an3[100],an4[100],correct_buff[30]="correct !!!",incorrect_buff[30]="incorrect !!!";
	char end[100]="-----------------------------------------",star[100]="*************************************";
	
	fd_set rfds;
	struct timeval tv;
	int retval;
	
	
	
	

	FD_ZERO(&rfds);
	FD_SET(sockfd,&rfds);
		
	tv.tv_sec=30;
	tv.tv_usec=0;
		
	retval=select(sockfd+1,&rfds,NULL,NULL,&tv);
	
	if(retval==-1){
		perror("error select");
	}
	else if(retval){
		

		if ( (n = Readline(sockfd, line, MAXLINE)) == 0){  /*read line buffer and see whether it got anything to read,if nothing to read return*/
			//printf("returning");		
			return;		/* connection closed by other end */
		} 
		else if (sscanf(line, "%s",&arg3) == 1){	/*scan the key bord input to line buffer by giving a place holder*/
		
	
			if(arg3=='q'){				/*if the scan value is equal to 'q' then*/
				fp=fopen("quiz.txt","r");	/*open the question file*/
						
						

				count=1;
				srand(time(NULL));
				r = rand() % 10;		/*generate random number between 0 and 9*/
				while ((void *) Fgets(line, MAXLINE, fp) != NULL) {	/*get file data to line buffer until it's end of file*/
							
					sscanf(line,"%d \t %[^\t]\t %[^\t]\t  %[^\t]\t  %[^\t]\t  %[^\t]\t %d",&qno,q,an1,an2,an3,an4,&ca); /*scan the data in line buffer and seperate them to given variables*/
					if(r==qno){			/*if the random number equal to question number*/
						
						
						snprintf(line, sizeof(line), "%d %s\n %s\n %s\n %s\n %s\n",qno,q,an1,an2,an3,an4); 		/*print the question relavent to the random number */
						Writen(sockfd,line,strlen(line));  
						
						again:	
						if ( (n = Read(sockfd, tmp, MAXLINE)) == 0){  /*read the input give from key bord to tmp buffer*/ 					
						return;		/* connection closed by other end */
						} 
						
						else if(sscanf(tmp, "%s %d %d",&arg,&a_qno,&a_ca) == 3){/*scan the tmp buffer and get the a# q# and answer# */
						
							if(arg!='a'){
								//correct=correct+1;
								snprintf(tmp,sizeof(tmp),"invalid answer structure  ('a' q# a#)\n" ); /*if the answered format is incorrect*/
								Writen(sockfd,tmp,strlen(tmp));
								goto again;
								
								//Fgets(sendline, MAXLINE, fp);
								
							}
							if(a_qno!=qno){
								//correct=correct+1;
								snprintf(tmp,sizeof(tmp),"invalid question number  ('a' q# a#)\n" ); /*if the answered format is incorrect*/
								Writen(sockfd,tmp,strlen(tmp));
								goto again;
								
								//Fgets(sendline, MAXLINE, fp);
								
							}
						
						
							
							else if(arg=='a' && a_qno==qno && a_ca==ca){
								//correct=correct+1;
								snprintf(tmp,sizeof(tmp),"%s\n%s",correct_buff,end); /*if the scaned answer equal to the correct answer print correct*/
								Writen(sockfd,tmp,strlen(tmp));
								correct_ans++;
								break;
							}
							else if(arg=='a' && a_qno==qno && a_ca!=ca){	/*if the answer is incorrect*/
								//incorrect=incorrect+1;
								snprintf(tmp,sizeof(tmp),"%s\ncorrect answer is:%d\n%s",incorrect_buff,ca,end);
								Writen(sockfd,tmp,strlen(tmp));
								wrong_ans++;
								break;
							}
						}
					
							//break;
						
														
						//break;		
									
					}//(r==qno)
															
										
				
				}//(while)
					
			
				fclose(fp);	/*close the file*/
				
					
				
			}//if(arg3=='q')
			
		else if(arg3=='e'){ // when user press e server must 
		
		int got=correct_ans+wrong_ans;
   		snprintf(tmp,sizeof(tmp),"\n\n%s\nYou got %d out of %d , Have a nice day ! \n%s\n\n",star,correct_ans,got,star);
  		Writen(sockfd,tmp,strlen(tmp));	
		exit(1);	
		
		}//if(arg3=='e')
		
		
		else if(arg3=='s'){ // when user press e server must 
		continue;
		exit(1);	
		}
		
			
		}//(sscanf(line, "%s",&arg3) == 1)
		
		
		snprintf(tmp,sizeof(tmp),"\npress (q) to go to next question | press (e) to exit\n");
		Writen(sockfd,tmp,strlen(tmp));
		
		//n = strlen(line);
		//Writen(sockfd, line, n);

	
	}
	else{
		printf("No input within 30 seconds\n");
		return;
	}	
	}//for()
	
	int got=correct_ans+wrong_ans;
	snprintf(tmp,sizeof(tmp),"\nSry Your questions is over!\nYou got %d out of %d , Have a nice day ! \n",correct_ans,got);
	Writen(sockfd,tmp,strlen(tmp));
	
	
}//str_echo




