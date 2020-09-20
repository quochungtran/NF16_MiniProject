#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tp3.h"
#define DAY_IN_SECOND 86400

T_Transaction* ajouterTransaction(int idEtu, float montant, char* descr, T_Transaction* listeTransaction){
    T_Transaction* newTransaction = malloc(sizeof(T_Transaction));
    newTransaction->idEtu = idEtu;
    newTransaction->montant = montant;
    newTransaction->descr = descr;
    newTransaction->nextTransaction=listeTransaction;
    return newTransaction;

}

Blockchain ajouterBlock (Blockchain bc){
    T_Block* newBlock = malloc(sizeof(T_Block));
    newBlock->firstTransaction = NULL;
    if(bc == NULL){;
        newBlock->idBlock = 0;
        newBlock->nextBlock = NULL;
        newBlock->date = time(NULL);
        afficherDate(*newBlock);
    } else{
        newBlock->idBlock = (bc->idBlock)+1;
        newBlock->nextBlock = bc;
        newBlock->date = bc->date + DAY_IN_SECOND;
        afficherDate(*newBlock);
    }
    return newBlock;

}


void afficherDate(T_Block block){
    struct tm* time = localtime(&block.date);
    printf("date=%4d-%02d-%02d\n",1900+(time->tm_year), 1+(time->tm_mon), time->tm_mday);

}




float totalTransactionEtudiantBlock(int idEtu, T_Block b){
    T_Transaction* currentTransaction = b.firstTransaction;
    float totalMontantJour = 0;
    while (currentTransaction != NULL){
        if(currentTransaction->idEtu == idEtu){
            totalMontantJour = totalMontantJour + currentTransaction->montant;
        }
        currentTransaction = currentTransaction->nextTransaction;
    }
    return totalMontantJour;
}

float soldeEtudiant(int idEtu, Blockchain bc){
    float solde = 0;
    T_Block* currentBlock = bc;
    while(currentBlock != NULL){
        solde = solde + totalTransactionEtudiantBlock(idEtu, *currentBlock);
        currentBlock = currentBlock -> nextBlock;
    }
    return solde;
}

void crediter(int idEtu, float montant, char *descr, Blockchain bc){
    bc->firstTransaction = ajouterTransaction(idEtu, montant, descr, bc->firstTransaction);
}

int payer(int idEtu, float montant, char *descr, Blockchain bc){
    float solde = soldeEtudiant(idEtu, bc);
    if (solde >= montant){
        bc->firstTransaction = ajouterTransaction(idEtu, - montant, descr, bc->firstTransaction);
        return 1;
    }
    return 0;
}



void consulter(int idEtu, Blockchain bc){
    float solde = soldeEtudiant(idEtu, bc);
    printf("Le solde de l'etudiant %d est %f\n", idEtu, solde);
    T_Block* currentBlock = bc;
    T_Transaction* currentTransaction = NULL;
    int i=5;
    while(currentBlock != NULL && i > 0){
        currentTransaction = currentBlock->firstTransaction;
        while (currentTransaction != NULL && i > 0){
            if (currentTransaction->idEtu == idEtu){
                printf("montant=%f et description=%s \n",currentTransaction->montant, currentTransaction->descr);
                afficherDate(*currentBlock);
                i--;
            }
            currentTransaction = currentTransaction->nextTransaction;
        }
        currentBlock = currentBlock->nextBlock;
    }

}


//on considère que le montant de transfert est positif
int transfert(int idSource, int idDestination, float montant, char *descr, Blockchain bc){
    int result = 0;
    if (montant > 0){
        result = payer(idSource, montant ,descr, bc);
        if (result != 0){
            crediter(idDestination, montant, descr, bc);
        }
    }
    return result;
}

void affichageListeBlocks (Blockchain blockchain) {
    printf("Affichage de la liste des blocs de la BlockChain\n");
    T_Block* currentBlock = blockchain;
    while (currentBlock != NULL){
        printf("idBlock=%d\n", currentBlock->idBlock);
        afficherDate(*currentBlock);
        currentBlock = currentBlock->nextBlock;
    }
}


void affichageListeTransaction(Blockchain blockchain,int idBlock){
    printf("Affichage de toutes les transactions du bloc %d\n",idBlock);
    T_Block* currentBlock = blockchain;
    while(currentBlock->idBlock != idBlock){
        currentBlock = currentBlock->nextBlock;
    }
    if (currentBlock->firstTransaction == NULL){
        printf("le block est vide\n");
    }else{
        T_Transaction* currentTransaction = currentBlock->firstTransaction;
        while (currentTransaction != NULL){
            printf("*****Transaction*****\n");
            afficherDate(*currentBlock);
            printf("idEtu=%d\n", currentTransaction->idEtu);
            printf("montant=%f\n", currentTransaction->montant);
            printf("description=%s\n", currentTransaction->descr);
            currentTransaction = currentTransaction->nextTransaction;
            printf("*****Transaction Fin*****\n\n");
        }
    }

}


int demandeIdBlock(Blockchain blockchain){
    int choixBlock = 0;
    do{
        printf("Choisissez idBlock valide\n");
        scanf("%ld",&choixBlock);
    }while(choixBlock > blockchain->idBlock || choixBlock < 0);
    return choixBlock;
}
int demandeIdEtu(){
    int choixEtu = 0;
    do{
        printf("Choisissez idEtu valide\n");
        scanf("%ld",&choixEtu);
    }while(choixEtu < 0);
    return choixEtu;
}
float demandeMontant(){
    float choixMontant = 0;
    do{
        printf("Choisissez montant valide (superieur a 0)\n");
        scanf("%f",&choixMontant);
    }while(choixMontant <= 0);
    return choixMontant;
}
char* demandeDescr(){
    char* choixDescr = malloc(256*sizeof(char));
    printf("Indiquer une description\n");
    getchar();
    gets(choixDescr);
    return choixDescr;
}


void affichageListeTransactionEtuBlock(Blockchain blockchain,int idEtu){
    printf("Affichage de toutes les transactions du jour pour un etudiant%d : \n",idEtu);
    T_Transaction* currentTransaction = blockchain->firstTransaction;
    while (currentTransaction != NULL){
        if (currentTransaction->idEtu == idEtu){
            printf("*****Transaction*****\n");
            printf("idEtu=%d\n", currentTransaction->idEtu);
            printf("montant=%f\n", currentTransaction->montant);
            printf("description=%s\n", currentTransaction->descr);
            printf("*****Transaction Fin*****\n\n");
        }
        currentTransaction = currentTransaction->nextTransaction;
    }
}
