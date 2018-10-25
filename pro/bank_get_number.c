#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include"head/bank_head.h"
#include<sys/stat.h>
#include<fcntl.h> 

#define savefile "./savefile.txt"

REP_REQ_ST rep_req_st;
int g_curent_num,g_i;


/**********************
 *������:ȡ�Ż��û����溯��
 *����:��������˿͵Ľ���
 *��ӡ��ǰ�˿ͺ���Ͳ�ѯ
 *��ǰҵ������������ȴ�
 *����
 *����ֵ:��ǰȡ�Ź˿͵ĺ���
 ***********************/
int GetNumberUserMenu(int arg)
{
  int n;
 
  if(g_i == 5)
  {
    g_curent_num = 1;
	g_i++;
  } 
loop1:  printf("\n******************************welcom to ICBC**********************\n");
  printf("                              1    customer get number and see the queue\n");                          
  printf("                              2    exit\n");
  CurentTime();
  printf("*******************************************************************\n");
  printf("please input : ");
  scanf("%d",&n);
  
  switch(n)
  	{
     case 1:
		 printf("\n*****************customer get number interface***********************\n\n"); 
		 printf("your server number is %d.\n",++g_curent_num);		
		 printf("there are %d people in front of you!\n",arg);
		 sleep(1);
         system("clear");
		 return(g_curent_num);
		 break;
	 case 2:
	 	 return 0;

	 default :

	 	 break;	 	 
     
    }
  return(0);
}



int main(int argc,char **argv)
{
	int fd,first_customer;
	int len,ret,recvnum,GNUM_ARG = 0;
	struct sockaddr_in remoteaddr;
	char data[1024];
	int send_number;

	
	
    //
    // �����׽ӿ�
    // 
    fd = socket(AF_INET, SOCK_STREAM, 0);
 
    //
    // ����
    //
    remoteaddr.sin_family = AF_INET;
    remoteaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    remoteaddr.sin_port = htons(5000);
    len = sizeof(remoteaddr);


    ret = connect(fd, (struct sockaddr *)&remoteaddr, len);
	    if(ret == -1) 
	    {
	       printf("connect() error\n");
	       return -1;
	    } 
	g_i = 5;
	
    //����ȡ�Ż��ź�
	rep_req_st.sign_type = IS_GET_NUMBER;
    ret = send(fd, &rep_req_st, sizeof(REP_REQ_ST),0);
	
	while(1)
	{
	    if(g_i == 5)
	    {
		  printf("\n******************************welcom to ICBC**********************\n");
		  printf("                              1    customer get number and see the queue\n");                          
		  CurentTime();
		  printf("*******************************************************************\n");
		  printf("please input : ");
		  scanf("%d",&first_customer);
		  send_number = 1;
		  system("clear");
		}
	    
		printf("currentt number:%d\n",send_number);
		//���͹˿ͺ����������
		ret = send(fd, &send_number, sizeof(int),0);
		if(ret <= 0)
		{
		   printf("send() error\n");
		}
		ret = recv(fd,&recvnum, sizeof(REP_REQ_ST), 0);
		GNUM_ARG = recvnum;
		
		//�˿��û�����
        send_number = GetNumberUserMenu(GNUM_ARG);
		
	}
	close(fd);
	return 0;
}

