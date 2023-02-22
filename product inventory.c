/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct products{
    int id;
    char * name;
    int quantity;
    struct products * next;
}product;

product * add_newproduct(int * id, char * name, int quantity, product * root){
    product * new_product = (product *)malloc(sizeof(product));
    *id = *id + 1;
    new_product->id = *id;
    new_product->name = (char *)malloc(sizeof(char));
    strcpy(new_product->name,name);
    new_product->quantity = quantity;
    new_product->next = NULL;

    if(root == NULL){
        root = new_product;
    }else{
        product * pointing;
        pointing = root;
        while(pointing->next != NULL){
            pointing = pointing->next;
        }
        pointing->next = new_product;
    }

    return root;
}
void search(int id, product * root){
    product * pointing = root;
    bool not_exist = false;
    while(pointing != NULL){
        if(pointing->id == id){
            printf("Successfully searched---\n");
            printf("%d\t%s\t%d", pointing->id, pointing->name, pointing->quantity);
            not_exist = false;
            break;
        }else{
            not_exist = true;
        }
        pointing = pointing->next;
    }
    if(not_exist){
        printf("id not found!\n");
        not_exist = true;
    }
}

void update(int id, product * root){
    product * pointing = root;
    char choose;
    bool not_exist = false;
    while(pointing != NULL){
        if(pointing->id == id){
            printf("update product---\n");
            printf("product name: %s\n", pointing->name);
            char * name = (char *)malloc(sizeof(char));
            printf("update product name? (Y/N) :");
            scanf(" %c", &choose);
            if(choose == 'Y'){
                printf("update product name: ");
                scanf(" %[^\n]", name);
                strcpy(pointing->name, name);
            }
            printf("product quantity: %d\n", pointing->quantity);
            printf("update product quantity? (Y/N) :");
            scanf(" %c", &choose);
            if(choose == 'Y'){
                printf("update product quantity: ");
                scanf(" %d", &pointing->quantity);
            }
            not_exist = false;
            break;
            printf("Successfully updated!\n");
        }else{
            not_exist = true;
        }
        pointing = pointing->next;
    }
    if(not_exist){
        printf("id not found!\n");
        not_exist = true;
    }
}

int count(product * root, int id){
    int c = 0;
    bool exist = false;
    product * pointing = root;
    while(pointing != NULL){
        if(pointing->id == id){
            exist = true;
            break;
        }
        c++;
        pointing = pointing->next;
    }
    if(exist){
        return c;
    }else{
        return 0;
    }

}

product * delete(product * root, int count){
    product * pointing = root;
    for(int i = 1; i < count; i++){
        pointing = pointing->next;
    }
    product * delete = pointing->next;
    pointing->next = delete->next;
    free(delete);
    printf("successfully deleted!\n");
    return root;
}

void display(product * root){
    product * pointing = root;
    printf("ID\tNAME\tQUANTITY\n");
    while(pointing != NULL){
        printf("%d\t%s\t%d\n", pointing->id, pointing->name, pointing->quantity);
        pointing = pointing->next;
    }
}

int main()
{
    product * product1 = NULL;
    int select, id = 0, quantity, search_id, count_index;
    char * product_name;
    while(1){
        printf("1. Add a product\n");
        printf("2. Show products\n");
        printf("3. Search product\n");
        printf("4. Update product\n");
        printf("5. Delete product\n");
        printf("select: ");
        scanf("%d", &select);

        switch(select){
            case 1:
                printf("---APPEND PRODUCT---\n");
                printf("Enter name of product: \n");
                product_name = (char *)malloc(sizeof(char));
                scanf(" %[^\n]", product_name);
                printf("Enter quantity: \n");
                scanf("%d", &quantity);
                product1 = add_newproduct(&id,product_name,quantity,product1);
                break;
            case 2:
                printf("---SHOWED PRODUCTS---\n");
                display(product1);
                break;
            case 3:
                printf("---SEARCH---\n");
                printf("Enter an id:");
                scanf("%d", &search_id);
                search(search_id, product1);
                break;
            case 4:
                printf("---UPDATE---\n");
                printf("Enter an id:");
                scanf("%d", &search_id);
                update(search_id, product1);
                break;
            case 5:
                printf("---DELETE---\n");
                printf("Enter an id:");
                scanf("%d", &search_id);
                count_index = count(product1, search_id);
                if(count_index == 0){
                    printf("Id not found\n");
                }else{
                    product1 = delete(product1, count_index);
                }

                break;
        }

    }
    return 0;
}
