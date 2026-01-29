#include "huffman.h"
#include <stdlib.h>
#include <stdio.h>
int main(){
    char choice;
    
        printf("\n===== Huffman Codec System =====\n");
        printf("1. Initialization (I)\n");
        printf("2. Encoding (E)\n");
        printf("3. Decoding (D)\n");
        printf("4. Print Code File (P)\n");
        printf("5. Print Huffman Tree (T)\n");
        printf("6. Quit (Q)\n");
        printf("===============================\n");
        printf("Please enter your choice: \n");
        while(1){
        choice=getchar();
        while(getchar()!='\n');
        switch(choice){
            case'I':
                Initialization();
                break;
            case'E':
                encoding();
                break;
            case'D':
                decoding();
                break;
            case'P':
                print();
                break;
            case'T':
                TreePrinting();
                break;
            case 'Q':
                if (HTree.Htree != NULL) {
                    free(HTree.Htree);
                    HTree.Htree = NULL;
                }
                for (int i = 0; i < n; i++) {
                    if (HC[i] != NULL) {
                        free(HC[i]);
                        HC[i] = NULL;
                    }
                }
                printf("Quit program successfully!\n");
                return 0;
            default:
                printf("Please try again!\n");
                break;
                   
        }

    }

}