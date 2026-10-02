#include <stdio.h>
#include <stdlib.h>

typedef struct Item {
    struct Item *next;
    struct Item *prev;
} Item;
typedef struct List {
    Item *head;
    Item *tail;
} List;

void Add(List *list, Item *item);
void Delete(List *list, int index);
Item* GetItem(const List *list, int index);
Item* Remove(List *list, int index);
void Insert(List *list, Item *item, int index);
int Сount(const List *list);
void Сlear(List *list);
int GetIndex(const List *list, Item *item);
void PrintList(const List *list);

void Add(List *list,Item *item) {
    if (list == NULL || item == NULL) return;
    item->next = NULL;
    item->prev = list->tail;
    if (list->tail != NULL) {
        list->tail->next = item;
    }
    else {
        list->head = item;
    }
    list->tail = item;
}
int Count(const List *list) {
    int n = 0;
    Item *p;
    if (list == NULL) return 0;
    p = list->head;
    while (p != NULL) {
        n++;
        p = p->next;
    }
    return n;
}
Item* GetItem(const List *list,int index) {
    Item *p;
    int i = 0;
    if (list == NULL || index < 0) return NULL;
    p = list->head;
    while (p != NULL && i < index) {
        p = p->next;
        i++;
    }
    return p;
}
Item* Remove(List *list, int index) {
    Item *p = GetItem(list,index);
    if (p == NULL) return NULL;
    if (p->prev != NULL) {
        p->prev->next = p->next;
    } else {
        list->head = p->next;
    }
    if (p->next != NULL) {
        p->next->prev = p->prev;
    } else {
        list->tail = p->prev;
    }
    p->next = NULL;
    p->prev = NULL;
    return p;
}
void Delete(List *list, int index) {
    Item *p = Remove(list,index);
    if (p != NULL) {
        free(p);
    }
}
void Insert(List *list, Item *item, int index) {
    Item *pn = GetItem(list,index);
    if (pn == NULL) {
        Add(list,item);
        return;
    }
    if (pn == list->head) {
        item->prev = NULL;
        item->next = list->head;
        list->head->prev = item;
        list->head = item;
        return;
    }
    Item *pp = pn->prev;
    item->prev = pp;
    item->next = pn;
    pn->prev = item;
    pp->next = item;
}
void Clear(List *list) {
    if (list == NULL) return;
    while (list->head) {
        Delete(list, 0);
    }
    list->head = NULL;
    list->tail = NULL;
}
int GetIndex(const List *list, Item *item) {
    if (list == NULL || item == NULL) {
        return -1;
    }
    Item *p = list->head;
    int i = 0;
    while (p!=NULL) {
        if (p == item) {
            return i;
        }
        p = p->next;
        i++;
    }
    return -1;
}
void PrintList(const List *list){
    if (list == NULL){
        printf("List: NULL\n");
        return;
    }
    printf("List: %p  Head: %p  Tail: %p\n",
           (void*)list, (void*)list->head, (void*)list->tail);
    printf("#\tp\tprev\tnext\n");
    Item *p = list->head;
    int i = 0;
    while (p != NULL){
        printf("%d\t%p\t%p\t%p\n", i++, (void*)p,
               (void*)p->prev, (void*)p->next);
        p = p->next;
    }
}

int main(void){
    List list;
    list.head = NULL;
    list.tail = NULL;

    int choice = -1;
    while (choice != 0){
        printf("\n=== MENU ===\n");
        printf("1. Add\n");
        printf("2. Count\n");
        printf("3. PrintList\n");
        printf("4. GetItem\n");
        printf("5. Delete\n");
        printf("6. Insert\n");
        printf("7. Clear\n");
        printf("8. GetIndex\n");
        printf("0. Exit\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1){
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Invalid input. Enter a number.\n");
            continue;
        }

        if (choice == 1){
            Item *it = (Item*)malloc(sizeof(Item));
            if (it == NULL){ printf("malloc failed\n"); continue; }
            it->prev = NULL;
            it->next = NULL;
            Add(&list, it);
            printf("Added. Count = %d\n", Count(&list));
        }
        else if (choice == 2){
            printf("Count = %d\n", Count(&list));
        }
        else if (choice == 3){
            PrintList(&list);
        }
        else if (choice == 4){
            int idx;
            printf("index: ");
            if (scanf("%d", &idx) != 1){
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Invalid input.\n");
                continue;
            }
            if (idx < 0){
                printf("Index cannot be negative.\n");
                continue;
            }
            Item *p = GetItem(&list, idx);
            printf("GetItem(%d) = %p\n", idx, (void*)p);
        }
        else if (choice == 5){
            int idx;
            printf("index: ");
            if (scanf("%d", &idx) != 1){
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Invalid input.\n");
                continue;
            }
            if (idx < 0){
                printf("Index cannot be negative.\n");
                continue;
            }
            Delete(&list, idx);
            printf("Deleted. Count = %d\n", Count(&list));
        }
        else if (choice == 6){
            int idx;
            printf("index: ");
            if (scanf("%d", &idx) != 1){
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Invalid input.\n");
                continue;
            }
            if (idx < 0){
                printf("Index cannot be negative.\n");
                continue;
            }
            Item *it = (Item*)malloc(sizeof(Item));
            if (it == NULL){ printf("malloc failed\n"); continue; }
            it->prev = NULL;
            it->next = NULL;
            Insert(&list, it, idx);
            printf("Inserted. Count = %d\n", Count(&list));
        }
        else if (choice == 7){
            Clear(&list);
            printf("Cleared. Count = %d\n", Count(&list));
        }
        else if (choice == 8){
            Item *p;
            printf("pointer (hex, like 0x...): ");
            if (scanf("%p", (void**)&p) != 1){
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Invalid pointer.\n");
                continue;
            }
            printf("GetIndex = %d\n", GetIndex(&list, p));
        }
    }

    Clear(&list);
    return 0;
}