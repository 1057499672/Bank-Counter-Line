#ifndef _BANK_HEAD_H
#define _BANK_HEAD_H

#include <time.h>
#include<stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include<pthread.h>
#include<string.h>
#include<time.h>



#define IS_GET_NUMBER 1
#define IS_BANK_COUNT 2
#define IS_CLIENT_END 3
#define QElemType int




/*����һ���ṹ��
����server��Ӧ��ͬ
�ͻ��˵�����*/
typedef struct ReplayDifferentRequest
{
  long sign_type;
}REP_REQ_ST;

//ȫ�ֱ���
REP_REQ_ST rep_req_st;




/*******************
*����������
*
********************/
void DeleteFirstEle(char *a);
void InitRDRSt(void);
void CurentTime(void);


#endif


