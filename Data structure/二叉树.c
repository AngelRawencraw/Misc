#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct bitnode
{
char data;
struct bitnode *lchild, *rchild;
}bitnode, *bitree;

void createbitree(t,n)
bitnode ** t;
int *n;
{
char x;
bitnode *q;

*n=*n+1;
printf("\n       Input  %d  DATA:",*n);
x=getchar();
if(x!='\n') getchar();

if (x=='\n')
return;

q=(bitnode*)malloc(sizeof(bitnode));
q->data=x;
q->lchild=NULL;
q->rchild=NULL;
*t=q;

printf("      This Address is:   %o,    Data is:  %c,\n      Left Pointer is:   %o,       Right Pointer is:  %o",q,q->data,q->lchild,q->rchild);

createbitree(&q->lchild,n);
createbitree(&q->rchild,n);
return;
}

void visit(e)
bitnode *e;
{
printf("  Address:  %o,  Data:  %c,  Left Pointer:  %o,  Right Pointer:  %o\n",e,e->data,e->lchild,e->rchild);
}

void preordertraverse(t)
bitnode *t;
{
if(t)
{
visit(t);
preordertraverse(t->lchild);
preordertraverse(t->rchild);
return ;
}else return ;
}

void countleaf(t,c)
bitnode *t;
int *c;
{
	if(t!=NULL)
  {
	  if (t->lchild==NULL && t->rchild==NULL)
	  {*c=*c+1;
	  }
   countleaf(t->lchild,c);
   countleaf(t->rchild,c);
  }
 return;
}

int treehigh(t)
bitnode *t;
{int lh,rh,h;
 if(t==NULL)
 h=0;
 else{
 lh=treehigh(t->lchild);
 rh=treehigh(t->rchild);
 h=(lh>rh ? lh:rh)+1;
      }
 return h;
}
main()
{
bitnode *t; int count=0;
int n=0;

printf("\n                  Please input TREE Data:\n");
createbitree(&t,&n);

printf("\n                  This is TREE Struct: \n");
preordertraverse(t);

countleaf(t,&count);
printf("\n       This TREE has %d leaves    ",count);

printf("    ,       High of The TREE is: %d\n",treehigh(t));
}

