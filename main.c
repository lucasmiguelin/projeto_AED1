#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct filme { 
    char nome[50];
    int duration;
    int id;
    struct filme *next;
    struct filme *prev;
} film;

film *lista = NULL;

film *criar_list(int id, char *nome, int duration) {
    film *new_node = (film*) malloc(sizeof(film));
    
    new_node->id = id;
    strcpy(new_node->nome, nome);
    new_node->duration = duration;
    new_node->next = NULL;
    new_node->prev = NULL;
    
    return new_node;
}

void insertion(int id, char *nome, int duration) { 
    film *new_node = criar_list(id, nome, duration);
    
    if (lista == NULL) { 
        lista = new_node;
    } else { 
        film *atual = lista;
        while (atual->next != NULL) { 
            atual = atual->next;
        }
        
        atual->next = new_node;
        new_node->prev = atual;
    }
}

void removing(int id) { 
    film *ptr = lista;
    while (ptr != NULL) { 
        if (ptr->id == id) { 
            if (ptr->prev == NULL) { 
                lista = ptr->next;
                if (lista != NULL) { 
                    lista->prev = NULL;
                }
            } else if (ptr->next == NULL) { 
                ptr->prev->next = NULL;
            } else { 
                ptr->prev->next = ptr->next;       
                ptr->next->prev = ptr->prev;
            }
            
            free(ptr);
            printf("Removido\n");
            return;
        }
        ptr = ptr->next;
    }
    printf("Filme nao encontrado\n");
}

void ver_list(film *lista) {
    film *ptr = lista;
    while (ptr != NULL) { 
        printf("\n\nNome do filme: %s\n", ptr->nome);
        printf("Duracao: %d min\n", ptr->duration);
        printf("Posicao na lista: %d\n", ptr->id);
        printf("_______________________________________________\n");
        ptr = ptr->next;
    }
}

int main() {
    int option;
    int dura, chave;
    char name[50];
    
    while (option != 4) {
        printf("1 - Adicionar filme\n");
        printf("2 - Remover filme\n");
        printf("3 - Ver lista\n");
        printf("4 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &option);
        
        switch (option) { 
            case 1:
                printf("Numero da chave: ");
                scanf("%d", &chave);
                printf("Nome do filme: ");
                scanf("%s[^\n]", name);
                printf("Duracao do filme (em minutos): ");
                scanf("%d", &dura);
                insertion(chave, name, dura);
                break;
            
            case 2:
                printf("Insira a chave do filme: ");
                scanf("%d", &chave);
                removing(chave);
                break;
            
            case 3:
                ver_list(lista);
                break;
            
            case 4: 
                printf("Saindo do programa.\n");
                break;
            
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }

   
    film *current = lista;
    while (current != NULL) {
        film *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}