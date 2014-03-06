/* -*- C -*- */
#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List *newList() {
  List *p = (List *)malloc(sizeof(List));
  p->m_head = p->m_tail = NULL;
  return p;
}
void initList(List *p) {
  p->m_head = p->m_tail = NULL;
}

unsigned int ListLength(List *p) {
  unsigned int n=0;
  ListElem *cur = p->m_head;
  while(cur!=0) {
    n++;
    cur=cur->m_next;
  }
  return n;
}

void ListPrepend(List *p, void *data) {
  ListElem *elem = (ListElem *)malloc(sizeof(ListElem));  
  elem->m_data=data;
  elem->m_next=p->m_head;
  if(p->m_head==NULL)
    p->m_tail = elem;
  p->m_head=elem;
  
}

void ListAppend(List *p, void *data) {
  
  ListElem *elem = (ListElem *)malloc(sizeof(ListElem));  
  elem->m_data=data;
  elem->m_next=NULL;

  if(p->m_head==NULL) {
    p->m_head = p->m_tail = elem;
  } else {
    p->m_tail->m_next = elem;
    p->m_tail = elem;
  }
}

void ListInsertAfter(ListElem *p, void *data) {
  ListElem *elem = (ListElem *)malloc(sizeof(ListElem));  
  elem->m_data=data;
  elem->m_next=p->m_next;
  p->m_next = elem;
}

void destroyList(List *p, void *userData, void (*destroyData)(void *userData, void *data))
{
  ListElem *cur = p->m_head;
  while(cur!=NULL) {
    ListElem *next = cur->m_next;
    cur->m_next=NULL;
    if(destroyData!=NULL)
      (*destroyData)(userData,cur->m_data);
    cur->m_data=NULL;
    free(cur);
    cur=next;
  }
}

void forEach(List *p, void *userData, ForEachItemFunction applyFunc)
{
  ListElem *cur = p->m_head;
  while(cur!=NULL) {
    (*applyFunc)(userData,cur->m_data);
    cur=cur->m_next;
  }
}

void ListUnlinkElem(List *p, ListElem *elem) {
  if(p->m_head==elem) {
    p->m_head = p->m_tail = NULL;
    memset(elem,0,sizeof(ListElem));
    free(elem);
    return;
  }
  ListElem *prev = p->m_head;
  ListElem *cur = prev->m_next;
  while( cur != NULL ) {
    if(cur==elem) {
      prev->m_next = cur->m_next;
      //cur->m_next->m_prev=prev;
      free(elem);
      return;
    }
    prev=cur;
    cur=cur->m_next;
  }
}

void ListUnlinkItem(List *p, void *data) {
  ListElem *cur = p->m_head;
  ListElem *prev = cur;
  
  if(cur->m_data==data) {
    (void)ListRemoveHead(p);
    return;
  }
  cur=cur->m_next;
  while(1) {
    if(cur->m_data==data)
      break;
    if(cur->m_next==NULL)
      return;
    
    prev=cur;
    cur=cur->m_next;
  }
  prev->m_next = cur->m_next;
  free(cur);
}

void *ListRemoveHead(List *p) {
  if(p->m_head==NULL) return NULL;
  ListElem *head = p->m_head;
  p->m_head = head->m_next;
  if(head==p->m_tail)
    p->m_tail = p->m_head;
  void *data = head->m_data;
  free(head);
  return data;
}

/*
FIXME need to turn list into a doubly-linked list to implement this properly.
void *ListRemoveTail(List *p)
{
  if(p->m_tail==NULL) return NULL;
  ListElem *tail = p->m_head;
  p->m_head = head->m_next;
  if(head==p->m_tail)
    p->m_tail = p->m_head;
  void *data = head->m_data;
  free(head);
  return data;
}

*/
