/*Faça um programa que armazene a informação de várias pessoas numa pilha

- O programa deve possuir um menu:
    0: Insere a pessoa
    1: Deleta pessoa do topo
    2: Delete pessoa por nome(Delete do topo até achar)
    3: Limpa a pilha
    4: Lista na tela as pessoas
    5: Sair do programa

    POP PUSH RESET CLEAR EMPTY LIST
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
     char nome[30];
     int idade;
} Pessoa;

typedef struct{
    Pessoa *pessoas;
    Pessoa *topo;
    Pessoa *base;
    int limite;
} Pilha;

void Push(Pilha *pilha, Pessoa *pes);
int Empty(Pilha *pilha);
Pessoa *criarPessoa();
void Reset(Pilha *pilha);
void Pop(Pilha *pilha, Pessoa *pes);
void Clear(Pilha *pilha);
void listStack(Pilha *pilha);
void popByName(Pilha *pilha, char *nome, Pessoa *pes);

int main(){

    Pessoa lixo;
    Pilha stack;
    int esc;
    char nome[20];

    Reset(&stack);


    while (1){
        printf("\n");
        printf("0- Insere Pessoa\n");
        printf("1- Deleta Pessoa do topo\n");
        printf("2- Delete Pessoa por nome\n");
        printf("3- Limpa a pilha\n");
        printf("4- Lista a pilha\n");
        printf("5- Sair\n");
        printf("Digite sua escolha: ");
        scanf("%d", &esc);
        switch (esc){
        case 0:
            Push(&stack, criarPessoa());
            break;
        case 1:
            Pop(&stack, &lixo);
            break;
        case 2:
            printf("Nome a ser deletado: ");
            scanf("%s", nome);
            popByName(&stack, nome, &lixo);
            break;
        case 3:
            Clear(&stack);
            break;
        case 4:
            listStack(&stack);
            break;
        case 5:
            return 0;
            break;
        }
    }
}


Pessoa *criarPessoa(){

    Pessoa *pessoa;
    pessoa = (Pessoa*)malloc(sizeof(Pessoa));
    printf("Nome: ");
    scanf("%s", &pessoa->nome);
    printf("Idade: ");
    scanf("%d", &pessoa->idade);

    return pessoa;
}

void Reset(Pilha *pilha){

    pilha->base = NULL;
    pilha->limite = 0;
    pilha->pessoas = NULL;
    pilha->topo = NULL;
}

int Empty(Pilha *pilha){
    
    if (pilha->topo == NULL){
        return 1;
    }
    return 0;
}

void Push(Pilha *pilha, Pessoa *pes){

    if (pes == NULL){
        return;
    }

    if(Empty(pilha)){
        pilha->limite++;
        pilha->pessoas = (Pessoa *)malloc(sizeof(Pessoa) * pilha->limite);
        pilha->pessoas[pilha->limite - 1] = *pes;
        pilha->topo = &pilha->pessoas[pilha->limite - 1];
        pilha->base = &pilha->pessoas[pilha->limite - 1];
        return;
    }
    
    pilha->limite++;
    pilha->pessoas = realloc(pilha->pessoas, sizeof(Pessoa) * pilha->limite);
    pilha->pessoas[pilha->limite - 1] = *pes;
    pilha->topo = &pilha->pessoas[pilha->limite - 1];
    return;

}

void Pop(Pilha *pilha, Pessoa *pes){

    if (pes == NULL){
        return;
    }

    if (Empty(pilha)){
        return;
    }

    if (pilha->limite == 0){
        Reset(pilha);
        return;
    }

    *pes = pilha->pessoas[pilha->limite - 1];
    pilha->limite--;
    pilha->topo = &pilha->pessoas[pilha->limite - 1];
    pilha->pessoas = realloc(pilha->pessoas, sizeof(Pessoa) * pilha->limite);

}


void Clear(Pilha *pilha){

    Reset(pilha);
    free(pilha->pessoas);
}

void listStack(Pilha *pilha){

    printf("\n");
    Pessoa tmp;
    Pilha tmpStack;
    Reset(&tmpStack);
    int counter = pilha->limite;

    for (int i = 0; i < counter; i++){
        Pop(pilha, &tmp);
        Push(&tmpStack, &tmp);
        printf("Nome: %s\n", tmp.nome);
        printf("Idade: %d\n", tmp.idade);
        printf("\n");
    }

    for (int i = 0; i < counter; i++){
        Pop(&tmpStack, &tmp);
        Push(pilha, &tmp);
    }

    printf("\n");
}

void popByName(Pilha *pilha, char *nome, Pessoa *pes){

    if (Empty(pilha)){
        return;
    }

    int count = pilha->limite;

    for (int i = 0; i < count; i++){
        if (strcmp(pilha->pessoas[pilha->limite - 1].nome, nome) == 0){
            Pop(pilha, pes);
            return;
        }
        Pop(pilha, pes);
    }
}