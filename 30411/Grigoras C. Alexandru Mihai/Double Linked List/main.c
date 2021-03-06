#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node
{
    int code;
    struct node *next,*prev;
} NodeT;
struct node *head,*tail;
void addFirst(int code)
{
    if (head==NULL)
    {
        head=(struct node*)malloc(sizeof(struct node));
        head->code=code;
        head->next=NULL;
        head->prev=NULL;
        tail=head;
    }
    else
    {
        struct node *p=(struct node*)malloc(sizeof(struct node));
        p->code=code;
        p->next=head;
        p->prev=NULL;
        head->prev=p;
        head=p;
    }
}
void printelist(FILE *af)
{
    struct node *p=head;
    while (p!=NULL)
    {
        fprintf(af,"%d ",p->code);
        p=p->next;
    }
    fprintf(af,"\n");
}
void addLast(int code)
{
    if (head==NULL)
    {
        head=(struct node*)malloc(sizeof(struct node));
        head->code=code;
        head->next=NULL;
        head->prev=NULL;
        tail=head;
    }
    else
    {
        struct node *p=(struct node*)malloc(sizeof(struct node));
        p->code=code;
        p->next=NULL;
        p->prev=tail;
        tail->next=p;
        tail=p;
    }
}
void deletefirst()
{
    if (head!=NULL)
    {
        struct node *p=head;
        head=head->next;
        head->prev=NULL;
        free(p);
    }
}
void deletelast()
{
    if (head!=NULL)
    {
        struct node *p=tail->prev;
        p->next=NULL;
        free(tail);
        tail=p;
    }
}
void DOOM_THE_LIST()
{
    struct node *p=head,*q;

    while (p!=NULL)
    {
        q=p->next;
        free(p);
        p=q;
    }
    head=NULL;
    tail=NULL;
}
void delete_x(int x)
{
    NodeT *p,*q,*z;
    p=head;
    while(p!=NULL && p->code!=x)
    {
        p=p->next;
    }
    if (p!=NULL)
    {
        if (head!=p && tail!=p)
        {
            p->prev->next=p->next;
            p->next->prev=p->prev;
            free(p);
        }
        else
            if (head==p)
                deletefirst();
            else
                deletelast();
    }
}
int count_el()
{
    struct node *p=head;
    int ct=0;
    while (p!=NULL)
    {
        ct++;
        p=p->next;
    }
    return ct;
}
void print_f(int x,FILE *af)
{
    struct node *p=head;
    int i;
    for (i=1; i<=x&&p!=NULL; i++,p=p->next)
    {
        fprintf(af,"%d ",p->code);
    }
    fprintf(af,"\n");
}
void print_l(int x,FILE *af)
{
    struct node *p=head;
    int ct=count_el();
    if (ct<x)
        printelist(af);
    else
    {
        while (ct-x!=0)
        {
            p=p->next;
            x++;
        }
        while (p!=NULL)
        {
            fprintf(af,"%d ",p->code);
            p=p->next;
        }
        fprintf(af,"\n");
    }
}
void citire()
{
    char a[100];
    int x;
    FILE *pf=fopen("input.dat","r");
    FILE *af=fopen("output.dat","w");
    while (fscanf(pf,"%s",a)==1)
    {
        if(strcmp(a,"AF")==0)
        {
            fscanf(pf," %d",&x);
            addFirst(x);
        }
        if(strcmp(a,"AL")==0)
        {
            fscanf(pf," %d",&x);
            addLast(x);
        }
        if(strcmp(a,"DF")==0)
        {
            deletefirst();
        }
        if(strcmp(a,"DL")==0)
        {
            deletelast();
        }
        if(strcmp(a,"DOOM_THE_LIST")==0)
        {
            DOOM_THE_LIST();
        }
        if(strcmp(a,"DE")==0)
        {
            fscanf(pf," %d",&x);
            delete_x(x);
        }
        if(strcmp(a,"PRINT_ALL")==0)
        {
            printelist(af);
        }
        if(strcmp(a,"PRINT_F")==0)
        {
            fscanf(pf," %d",&x);
            print_f(x,af);
        }
        if(strcmp(a,"PRINT_L")==0)
        {
            fscanf(pf," %d",&x);
            print_l(x,af);
        }
    }
}

int main()
{
    citire();
    return 0;
}
