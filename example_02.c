// gcc ./example_02.c -o example_02 -no-pie
// 동적 할당을 통한 펫 영입
// free를 통한 펫 방출

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
    struct Animal* pet1;
    struct Animal* pet2;

    pet1 = createAnimal("Tae-Ji", 0);
    pet2 = createAnimal("Shee", 1);

    animalInfo(pet1);
    animalInfo(pet2);

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
    printf("------------------------\n");
    printf("Address : %p\n", animal);
    printf("PetName : %s\n", animal -> name);
    printf("Type : %d\n", animal -> type);
    printf("She/He Bark : ");
    animal -> bark();
    printf("------------------------\n");    
}

void dog() {
    puts("Bark! Bark!");
}

void cat() {
    puts("Mew~ Mew~");
}

