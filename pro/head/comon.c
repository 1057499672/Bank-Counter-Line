#include"bank_head.h"

/********************
*����һ�����нڵ�ṹ��
*����ͻ�����Ϣ
*********************/
typedef struct QNode{
	QElemType data;
	struct QNode *next;
} QNode,*QueuePtr;

/*******************
*���нṹ��
*
*********************/
struct Link
{
	QueuePtr front;
	QueuePtr rear;
}Queue,*Q;



/************
*���ֺ����Ķ���
*
**************/

//�ṹ���ʼ��
void InitRDRSt()
{
   rep_req_st.sign_type = 0;
}


//��ʾ��ǰʱ��
void CurentTime()
{
	time_t timep;
	time(&timep);
	printf("                   NOW TIME: %s",ctime(&timep));
}

void DeleteFirstEle(char *g)
{
  int i;
  for(i = 0;i < strlen(g)-1;i++)
  {
    g[i] = g[i+1];
	
  }
  g[strlen(g)-1] = 0;

}

/*
//��������
void CreateQueue(struct Link* Q)
{   
    int a;
	a = 0;
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
    Q = (struct Link*)malloc(sizeof(struct Link));
	if(!p)
	{
	   printf("create fail��");
    }
	else 
	{
	   p->next = NULL;
	   Q->front = p;
	     //printf("333333333444444443333\n");
	   Q->rear = p;
	   
	   p = (QueuePtr)malloc(sizeof(QNode));
	   p->next = NULL;
	   
	   if(!p) 
	   {
	      printf("create fail��") ;
	   }
	   else
	   {  
		  p->data = a;
          Q->rear->next = p;	
          Q->rear = p;		    
	   }
     }
}

//��ӡ����Ԫ��
void PrintfQueue(struct Link* Q)
{
    QueuePtr p;
	Q = (struct Link*)malloc(sizeof(struct Link));
	printf("���ڰ���ҵ��Ŀͻ�������:\n");
	for(p = Q->front->next; p != NULL; p = p->next)
    {
	   printf("customer:%d\n",p->data);
    }	
}
//����к���
void EnQueue(struct Link *Q,QElemType x)
{
     QueuePtr p;
	 p = (QueuePtr)malloc(sizeof(QNode));
	 Q = (struct Link*)malloc(sizeof(struct Link));
	 if(!p)
	 {
	    printf("create fail") ;
	 }
	 else
	 {
	    p->data=x;
		p->next=NULL;
		p = (QueuePtr)malloc(sizeof(QNode));
		Q->rear->next = p;
		Q->rear=p;
	 }
}

//�����к���
void DeQueue(struct Link *Q,QElemType *f)
{  
    QueuePtr p;
	if(Q->front == Q->rear)  
		printf("\nError");
	else 
	{    
	    p = Q->front->next;
		*f = p->data;
		Q->front->next = p->next;
		
		if(Q->rear == p)
			Q->rear = Q->front;
		
		free(p);
	}
}

//�ж϶����Ƿ�Ϊ��
int QueueEmpty(struct Link Q)  

 {  

    if(Q.front != NULL && Q.rear != NULL)  
    {
        if(Q.front == Q.rear)  
        return 0;  

        else 
        return 1; 
    }

 }  

*/

/*****************************
*ȡ�Ż��û����溯����
*����:1. ȡ�ú���
*             2. ��ѯ��ǰ�Ŷ����
******************************/








