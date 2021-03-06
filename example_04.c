// gcc ./example_04.c -o example_04 -no-pie
// 동적 할당을 통한 펫 영입
// free를 통한 펫 방출
// Heap Overflow

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// C++의 Class 모방
struct Animal {
    char name[100]; // 이름
    char type;      // Type (0=Dog, 1=Cat)
    void (*bark)(); // Function
};

struct Animal* createAnimal();// Animal 진짜 생성자 
void releaseAnimal(); // Animal 소멸자
void setAnimal();   // Animal 생성자
void animalInfo();  // Animal 정보
void dog();         // 멍멍이 소리
void cat();         // 고양이 소리

int main() {
    struct Animal *pets[MAX];
    char name[1000];
    char byeAnimal[100]={0,};
    int count = 0;
    int menu;
    int type;

    while(1) {
        system("clear");
        printf("------------------------------------------------\n");
        printf("              < Minivet Pet Shop >\n");
        printf("               Animals %d pets.\n", count);
        printf("------------------------------------------------\n");
        printf("    1. Get Animal \n");
        printf("    2. Release Animal \n");
        printf("    3. List of Animal \n");
        printf("    4. Animal Information \n");
        printf("    5. Exit \n");
        printf("------------------------------------------------\n");
        printf(">> ");
        scanf("%d", &menu);

        switch(menu) {
            case 1: // Get a Pet
                if(count >= MAX-1) {
                    printf("Pets can not over %d\n", MAX);
                    break;
                }
                printf("\nWhich do you want to get a pet? ( 0 = dog, 1 = cat ) : ");
                scanf("%d", &type);
                __fpurge(stdin);
                printf("\nWhat is the pet's name? : ");
                gets(name);
                pets[count++] = createAnimal(name, type);
                break;
            case 2: // Release a Pet
                printf("\n What is pet's number? : ");
                scanf("%d", &type);
                __fpurge(stdin);
                releaseAnimal(pets[type]);
                byeAnimal[type] = 1;
                // count --;
                // for(int i=type;i<count;i++) {
                //     pets[i] = pets[i+1];
                // }
                break;
            case 3: // List of Pets
                for(int i=0;i<count;i++) {
                    if(byeAnimal[i] == 1) continue;
                    printf("------------------------\n");
                    printf("ID : %d\n", i);
                    animalInfo(pets[i]);
                    printf("------------------------\n");
                }
                printf("Enter to exit this list.");
                __fpurge(stdin);
                getchar();
                break;
            case 4:
                printf("\n What is pet's number? : ");
                scanf("%d", &type);
                printf("------------------------\n");
                animalInfo(pets[type]);
                printf("------------------------\n");
                printf("Enter to exit this list.");
                __fpurge(stdin);
                getchar();
                break;
            case 5:
                printf("Bye.");
                return 0;
                break;
            default:
                puts("Wrong!");
                break;
        }
    }

    return 0;
}

struct Animal* createAnimal(char *name, int type) {
    struct Animal* animal;
    animal = malloc(sizeof(struct Animal));
    setAnimal(animal, name, type);
    return animal;
}

void releaseAnimal(struct Animal* animal) {
    free(animal);
}

void setAnimal(struct Animal* animal, char *name, int type) {
    strcpy(animal -> name, name);
    animal -> type = type;
    if(type == 0) {
        animal -> bark = dog;
    } else {
        animal -> bark = cat;
    }
}

void animalInfo(struct Animal* animal) {
    printf("Address : %p\n", animal);
    printf("PetName : %s\n", animal -> name);
    printf("Type : %d\n", animal -> type);
    printf("She/He Bark : ");
    animal -> bark();
}

void dog() {
    puts("Bark! Bark!");
}

void cat() {
    puts("Mew~ Mew~");
}
