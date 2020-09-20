#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"

int main(int argc, char *argv[]){
    int choix = 0;
    int choixBlock = 0;
    int choixEtu = 0;
    int idSource = 0;
    int idDestination = 0;
    float choixMontant = 0;
    char* choixDescr;
    int payement=0;
    int varTransfert=0;
    Blockchain blockchain = NULL;
    blockchain = ajouterBlock(blockchain);
    do{
        printf("MENU  Taper:\n");
        printf("\n");
        printf("1 pour afficher la liste des blocs de la BlockChain\n");
        printf("2 pour afficher toutes les transactions d un bloc\n");
        printf("3 pour afficher toutes les transactions du jour pour un etudiant\n");
        printf("4 pour afficher l historique pour un etudiant\n");
        printf("5 pour crediter un compte\n");
        printf("6 pour payer un repas\n");
        printf("7 pour transferer des EATCoins entre deux etudiants\n");
        printf("8 pour quitter\n");
        printf("9 pour simuler nouvelle journee creation block\n");
        scanf("%ld",&choix);
        printf("\n");

        switch(choix){
            case 1:
                affichageListeBlocks(blockchain);
                break;

            case 2:
                affichageListeBlocks(blockchain);
                choixBlock = demandeIdBlock(blockchain);
                affichageListeTransaction(blockchain, choixBlock);
                break;

            case 3:
                printf("Affichage de toutes les transactions du jour pour un etudiant\n");
                choixEtu = demandeIdEtu();
                affichageListeTransactionEtuBlock(blockchain,choixEtu);
                break;
            case 4:
                printf("Affichage de l historique pour un etudiant\n");
                choixEtu = demandeIdEtu();
                consulter(choixEtu, blockchain);
                break;
            case 5:
                printf("Crediter un compte\n");
                choixEtu = demandeIdEtu();
                choixMontant = demandeMontant();
                choixDescr = demandeDescr();
                crediter(choixEtu, choixMontant, choixDescr,blockchain);
                break;
            case 6:
                printf("Payer un repas\n");
                choixEtu = demandeIdEtu();
                choixMontant = demandeMontant();
                choixDescr = demandeDescr();
                payement = payer(choixEtu, choixMontant, choixDescr,blockchain);
                if (payement == 1){
                    printf("payement realise\n");
                } else{
                    printf("pas assez de Eatcoin\n");
                }
                break;
            case 7:
                printf("Transferer des EATCoins entre deux etudiants\n");
                printf("idSource?\n");
                idSource = demandeIdEtu();
                printf("idDestination?\n");
                idDestination = demandeIdEtu();
                choixMontant = demandeMontant();
                choixDescr = demandeDescr();
                varTransfert = transfert(idSource, idDestination, choixMontant, choixDescr, blockchain);
                if (varTransfert == 1){
                    printf("transfert realise\n");
                } else{
                    printf("transfert pas realise\n");
                }
                break;
            case 8:
                printf("Quitter\n");
                break;
            case 9:
                printf("simulation nouvelle journee creation block\n");
                blockchain = ajouterBlock(blockchain);
                break;
            default:
                printf("taper un nombre compris entre 1 et 8\n");
        }
        printf("\n");
    }while(choix != 8);
    //TODO liberer l'espace memoire de la blockchain et des strings



    while (blockchain!=NULL){
        while (blockchain->firstTransaction != NULL){
            T_Transaction* suivTransaction = blockchain->firstTransaction->nextTransaction;
            free (blockchain->firstTransaction->descr);
            free (blockchain->firstTransaction);
            blockchain->firstTransaction = suivTransaction;
        }
        T_Block* suivBlock = blockchain->nextBlock;
        free (blockchain);
        blockchain = suivBlock;

    }













   return 0;
}
