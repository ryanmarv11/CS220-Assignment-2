#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>

struct node{
  int val;
  struct node *next;
}; 
typedef struct node Node;


Node **split_list(Node *head);
Node * node_swap(Node * head, unsigned int index1, unsigned int index2);
Node *interleave_list(Node * head1, Node * head2);
void print_list(Node *head);
Node* copy_node(Node* old_node);
Node *list_gen(unsigned int num_nodes);
int get_float_exponent(float f);

int main(void) {
   return 0;
  }

Node **split_list(Node *head){
  Node **ret;
  ret = (Node**) malloc(2 * sizeof(Node*));

  if(head == NULL) //base cases of 0 or 1 nodes
    return NULL;
  if(head->next == NULL){
    ret[0] = head;
    ret[1] = NULL;
    return ret;
  }

  Node *head_current, *tail1, *tail2;
  head_current = head->next->next;
  ret[0] = head;
  ret[1] = head->next;
  tail1  = head;
  tail2  = head->next;
  while(head_current){
    tail1->next = head_current;
    head_current = head_current->next;
    tail1 = tail1->next;
    tail1->next = NULL;
    if(!head_current)
      return ret;
    tail2->next = head_current;
    head_current = head_current->next;
    tail2 = tail2->next;
    tail2->next = NULL;
  }
  return ret;

}

Node * node_swap(Node * head, unsigned int index1, unsigned int index2){
  if(head == NULL|| index1 == index2 || index1 < 0 || index2 < 0)
    return head;

  Node *previousX = NULL, *currentX = head;
  int counterX = 0;
  while(currentX && counterX != index1){ //finds node @index1
    previousX = currentX;
    currentX = currentX->next;
    counterX++;
  }  

  Node *previousY = NULL, *currentY = head; 
  int counterY = 0;
  while(currentY && counterY != index2){ //finds node @index2
    previousY = currentY;
    currentY = currentY->next;
    counterY++;
  }
  if(currentX  == NULL || currentY == NULL) //hecks to see if either are not present for some reason
    return head;

  if(previousX != NULL) //handles if X is the head of the list
    previousX->next = currentY;
  else
    head = currentY;

  if(previousY != NULL) //handles if Y is the head of the list
    previousY->next = currentX;
  else
    head = currentX;

  Node* temp = currentY ->next; //does the actual swapping
  currentY->next = currentX->next;
  currentX ->next = temp;
  return head;
}

Node *interleave_list(Node * head1, Node * head2){
  if(head1 == NULL && head2 == NULL) //base cases where lists are empty, head1 is empty, or head2 is empty
    return NULL;
  if(head1 == NULL)
    return head2;
  if(head2 == NULL)
    return head1;
  
  Node *new_head, *new_root;
  new_head = (Node*) malloc(sizeof(Node));
  new_root = new_head;

  while(head1 || head2){
    if(head1){
      new_head->next = copy_node(head1);
      new_head = new_head->next;
      head1 = head1->next;
    }
    if(head2){
      new_head->next = copy_node(head2);
      new_head = new_head->next;
      head2 = head2->next;
    }
  }
return new_root->next;

}
Node* copy_node(Node* old_node){
  Node *temp;
  temp = (Node*) malloc(sizeof(Node));
  temp->val = old_node->val;
  return temp;
}

void print_list(Node *head)
{
  while(head != NULL) {
    printf("%d -> ", head->val); 
    head = head->next; 
  }
  printf("NULL\n"); 
}

Node *list_gen(unsigned int num_nodes)
{
  unsigned int i; 
  Node *head, *n;
        head = n = NULL;  
  unsigned int seed = (unsigned int) time (NULL); 
  srand(seed); 
  for(i = 0; i < num_nodes; i++) {
    n = (Node *) malloc (sizeof(Node)); 
    n->val = rand()%20; 
    n->next = head; 
    head = n; 
  }
  return head;
}

int get_float_exponent(float f){
if(f == 0)
  return 0; //have to handle this tomorrow
uint32_t binary_representation = *(uint32_t *)&f;
binary_representation = binary_representation << 1;
binary_representation = binary_representation >> 24;
binary_representation -= 127;
return (int) binary_representation;
}
