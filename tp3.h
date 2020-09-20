#ifndef TP3_H_INCLUDED
#define TP3_H_INCLUDED
#include <time.h>
typedef struct Transaction T_Transaction;
struct Transaction {
    int idEtu;
    float montant;
    char* descr;
    T_Transaction* nextTransaction;
};


typedef struct Block T_Block;
struct Block {
    int idBlock;
    time_t date;
    T_Transaction* firstTransaction;
    T_Block* nextBlock;
};

typedef T_Block* Blockchain;


T_Transaction* ajouterTransaction(int idEtu, float montant, char *descr, T_Transaction* listeTransaction);
Blockchain ajouterBlock (Blockchain bc);
float totalTransactionEtudiantBlock(int idEtu, T_Block b);
float soldeEtudiant(int idEtu, Blockchain bc);
void crediter(int idEtu, float montant, char *descr, Blockchain bc);
int payer(int idEtu, float montant, char *descr, Blockchain bc);
void consulter(int idEtu, Blockchain bc);
int transfert(int idSource, int idDestination, float montant, char *descr, Blockchain bc);
void affichageListeBlocks (Blockchain blockchain);
int saisieIdBlock(Blockchain blockchain);
int demandeIdEtu();
float demandeMontant();
char* demandeDescr();
void affichageListeTransactionEtuBlock(Blockchain blockchain,int idEtu);
void afficherDate(T_Block block);

#endif // TP3_H_INCLUDED
