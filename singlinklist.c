/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */
#include<stdio.h>
#include<stdlib.h>

 /* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode = NULL;
	headnode = initialize(headnode);;
	printf("[----- [한민우] [2018038047] -----]\n");
	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
			/* 리스트 초기화 */
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
			/* 리스트 출력 */
		case 'p': case 'P':
			printList(headnode);
			break;
			/* 노드 중간에 삽입 */
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
			/* 원하는 노드 삭제 */
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
			/* 리스트 끝에 노드 삽입 */
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
			/* 리스트 끝에 노드 삭제 */
		case 'e': case 'E':
			deleteLast(headnode);
			break;
			/* 리스트 맨 앞에 노드 삽입 */
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
			/* 리스트 맨 앞에 노드 삭제 */
		case 't': case 'T':
			deleteFirst(headnode);
			break;
			/* 리스트 역순으로 만들기 */
		case 'r': case 'R':
			invertList(headnode);
			break;
			/* 프로그램 종료 */
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while (p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* curr, * prev; // 현재 노드, 이전 노드 가리킬 포인터
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;
	curr = h->first;
	prev = NULL;
	if (h->first == NULL) { // 리스트가 공백상태면 맨 앞에 node 삽입
		h->first = node;
	}
	else {
		if (curr->key >= node->key) { // 첫 노드의 key가 입력받은 key보다 크거나 같으면
			node->link = curr;     // 삽입
			h->first = node;       // head 변경
		}
		else {
			while (curr != NULL && curr->key < node->key) { // 입력받은 key가 더 크면 다음 노드로 이동
				prev = curr;
				curr = curr->link;
			}
			if (curr != NULL) { // 입력받은 key보다 더 큰 값 찾으면
				node->link = curr;
				prev->link = node;
			}
			else { // 입력받은 key보다 큰 값이 없을 때 맨 뒤에 삽입
				prev->link = node;
			}
		}
	}
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* Toend; // 리스트 맨 끝까지 갈 포인터
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;
	Toend = h->first;

	if (h->first == NULL) { // 리스트가 공백상태면 맨 앞에 node 삽입
		h->first = node;
	}
	else {
		while (Toend->link != NULL) { // 리스트 맨 끝가지 이동
			Toend = Toend->link;
		}
		Toend->link = node; // 맨 끝에 삽입
	}
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	if (h->first == NULL) { // 리스트가 공백상태면 오류
		printf("Linked List is empty!\n");
		return 0;
	}
	listNode* delist;
	delist = h->first;
	h->first = delist->link; // head 다음으로 이동
	free(delist);        // 메모리 해제
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	if (h->first == NULL) { // 리스트가 공백상태면 오류
		printf("Linked List is empty!\n");
		return 0;
	}
	if (h->first->key == key) { // 삭제 대상인 node가 맨 앞에 있으면 deleteFirst호출해서 삭제
		deleteFirst(h);
	}
	else {
		listNode* curr, * prev;
		curr = h->first;
		prev = NULL;
		while (curr != NULL && curr->key != key) { // 입력받은 key 탐색
			prev = curr;
			curr = curr->link;
		}
		if (curr == NULL) { // ket를 찾지 못하면 오류
			printf("Fail to find the key\n");
		}
		else {
			prev->link = curr->link; // 노드 삭제
			free(curr);
		}
	}
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	if (h->first == NULL) { // 리스트가 공백상태면 오류
		printf("Linked List is empty!\n");
		return 0;
	}
	if (h->first->link == NULL) { // 리스트에 node가 하나만 존재하면
		deleteFirst(h);           // 맨 앞에 있는 node == 맨 뒤에 있는 노드이므로 deleteFirst로 삭제
	}
	else {
		listNode* curr, * prev;
		curr = h->first;
		prev = NULL;
		while (curr->link != NULL) { // 리스트 맨 끝까지 이동
			prev = curr;
			curr = curr->link;
		}
		prev->link = NULL; // 맨 마지막 노드와 link 해제
		free(curr);
	}

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	if (h->first == NULL) { // 리스트가 공백상태면 오류
		printf("Linked List is empty!");
		return 0;
	}
	listNode* prev, * curr, * head;
	head = h->first;
	prev = NULL;
	curr = NULL;
	while (head) { // 리스트 끝까지
		prev = curr;
		curr = head;
		head = head->link;
		curr->link = prev; // 이전 노드를 link해서 역순으로 만듦
	}
	h->first = curr; // 역순으로 된 list의 head로 변경
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

