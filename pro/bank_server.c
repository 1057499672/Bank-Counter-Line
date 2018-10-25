#include"head/bank_head.h"
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h> 
 
 
#define savefile "./savefile.txt"
 int client_sockfd;
 REP_REQ_ST buf_st;
 
 int g_add = 0;
 
 /*************
 *�̼߳乲���ȫ�ֱ���
 **************/
 int g_i = 0,g_wait_customer = 0;
 char r_buf[2048];
 
 
 
 /**********************
 *������:ȡ�Ż��̺߳���
 *����: ��ȡ�Ż������շ�����
 * ��ù˿ͺ��룬����ǰ�ȴ�����
 *����ȡ�Ż�
 *����ֵ:��
 ***********************/
 void *ThreadGetNumber(void *arg)
 { 
   int ret = 0,client_sockfd = *((int *)arg);
   int recvnum;
   while(1)
	   {      
		
		   recv(client_sockfd,&recvnum, sizeof(REP_REQ_ST), 0); 
		   r_buf[g_add]= recvnum;
		   g_add++;
		   g_wait_customer += 1;//�ȴ�����+1
              
		   send(client_sockfd,&g_wait_customer,sizeof(int),0);		 
	   }   
 } 
 
 
 
 /**********************
 *������:���й�̨�̺߳���
 *����: �����й�̨�����շ�����
 * ���͹˿ͺ��룬��ȡ�˿ʹ�������ź�
 *����ֵ:��
 ***********************/
 void *ThreadCount(void *arg)
 {
   int ret = 0,client_sockfd = *((int *)arg);
   int	customer_num;
   
   while(1)  
   { 
		 if(r_buf[g_i] != '\0')
		 {
			 InitRDRSt(); 
			 customer_num = r_buf[g_i];
			 
			 //���͹˿ͺ���
			 send(client_sockfd,&customer_num,sizeof(int),0);
		 
			 //���ܹ˿ʹ�������ź�
			 recv(client_sockfd, (REP_REQ_ST *)&buf_st, sizeof(REP_REQ_ST), 0);
			 if(buf_st.sign_type == IS_CLIENT_END)
			 {
			   g_wait_customer -= 1;//�ȴ�������1
			   
			   printf("please call the next client\n");  
			 } 
			 g_i++;
		 }
		 else
		 {
			 sleep(1);
			  
		 }
	 }
		   
 }	 

 
 //������
 int main(int argc,char **argv)
 {
	 int fd;
	 int len,ret;
	 pthread_t c_ptid,g_ptid;
	 
	 struct sockaddr_in remoteaddr;
	 struct sockaddr_in localaddr;

  
	 //
	 // �����׽ӿ�
	 //  
	 
	 fd = socket(AF_INET, SOCK_STREAM, 0);
	 if(fd == -1)
		{
		  printf("socket2() error %d\n",errno);
		  return -1;
		}
	 
	 //
	 // �󶨵�ַ�Ͷ˿�
	 //
	 localaddr.sin_family = AF_INET;
	 localaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	 localaddr.sin_port = htons(5000); 
	 len = sizeof(localaddr); 
	 
	 if(bind(fd, (struct sockaddr *)&localaddr, len) == -1)
		{
		  printf("bind() error\n");
		  return -1;
		}
	 
	 //
	 // �����׽ӿڶ���
	 //
	 if(listen(fd, 5) == -1)
		{
		  printf("listen() error\n");
		  return -1;
		}
	 // 
	 // �ȴ� 
	 //
	 
	 len = sizeof(remoteaddr);
	 
	 while(1)
	 {
		client_sockfd = accept(fd,(struct sockaddr *)&remoteaddr, &len);
		printf("server recieve connect!--\n");
 
 
		ret = recv(client_sockfd,&buf_st, sizeof(REP_REQ_ST), 0);
		
		if(buf_st.sign_type == IS_BANK_COUNT )
		{
		   printf("From counter!\n");
		   pthread_create(&c_ptid,NULL,ThreadCount,&client_sockfd); 
		   
		}
		if(buf_st.sign_type == IS_GET_NUMBER)
		{ 
		   printf("From getnumber!\n");
		   pthread_create(&g_ptid,NULL,ThreadGetNumber,&client_sockfd); 
		}			
		 
	 }
	 
	 close(client_sockfd);
	 printf("exit bank system\n");	 
	 return 0;
 }
 
 
 
 
