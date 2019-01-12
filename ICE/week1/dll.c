#include <stdio.h>
#include <stdlib.h>
typedef struct ELE
{
	int data, id;
	struct ELE *prev;
	struct ELE *next;
} list_ele, *list_ptr;


list_ele nodes[10];
list_ptr head;


list_ptr new(){
	int i = 0;
	while(i<10){
		if(nodes[i].next == NULL && nodes[i].prev == NULL && &nodes[i] != head){
			return &nodes[i];
		}
		i++;
	}
	return NULL;

}

void delete(int value){
	list_ptr t = head;
	while(t){
		if(t->data == value){
			if(t == head){
				head = t->next;
			}else{
				(t->prev)->next = t->next;
				if(t->next){
					(t->next)->prev=t->prev;
				}
				t->prev = NULL;
				t->next = NULL;
			}
		}
		t = t->next;
	}
}

void insert(int value){
	list_ptr temp = new();
	if(!temp){
		printf("No more nodes\n");
		return;
	}else if(!head){
		temp->data = value;
		head = temp;
		head->next = NULL;
		head ->prev = NULL;
	}else{
		temp->data = value;
		list_ptr trav = head;
		list_ptr prev = NULL;
		while(trav && trav->data < value){
			prev = trav;
			trav = trav->next;
		}
		if(!trav){
			prev->next = temp;
			temp->prev = prev;
			temp->next = NULL;
		}else if(!prev){
			temp->next = head;
			head->prev = temp;
			head = temp;
		}else{
			temp->next = trav;
			temp->prev = prev;
			prev->next = temp;
			trav->prev = temp;
		}
	}
}

void show(){
	list_ptr trav = head;
	printf("Showing list\n");
	while(trav){
		printf("ID: %d \t Data: %d\n", trav->id, trav->data);
		trav = trav->next;
	}
}

void parseInput(char *buffer, char *op, int *value){
	char** temp;
	*op= *buffer;
	
	*value = strtol(&buffer[2], temp, 10);

}

int main(void){
	for(int i = 0; i < 10; i++){
		nodes[i].id = i;
	}
	char buffer[100];
	char op;
	int value;

	printf("Command Value\n");
	fgets(buffer, sizeof(buffer), stdin);
	parseInput(buffer, &op, &value);
	while(op != 'Q'){
		//printf("OP: %c \tValue: %d\n",op, value);
		if(op == 'I' || op == 'i'){
			insert(value);
		}else if(op == 'D' || op =='d'){
			delete(value);
		}else if(op == 'P' || op == 'p'){
			show();
		}else{
			printf("Invalid command. Use format: \n<command> <value>\nCommands:\nI - inserts value into list\nD - deletes value from list\nP - print list with id's\nQ - quits program\n");
		}
		fgets(buffer, sizeof(buffer), stdin);
		parseInput(buffer, &op, &value);
	}
	return 0;

}
