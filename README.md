# NF16_MiniProject
## Introduction:

* Le but de ce TP est de se familiariser avec les listes chaînées et d’utiliser nos compétences acquises dans le langage C. En suivant l’énoncé, nous avons “créé” une monnaie appelé Eatcoin qui est basée sur le modèle du Bitcoin. À l’aide de notre programme, nous avons simulé les différentes transactions des étudiants de l’UTC et stocké ces informations dans une blockchain.

## Technologies

Projet est crée with:

* C

* Data Structure : linked Lists

* IDE : Code Block


### 1.Raisons et choix des fonctions supplémentaires


#### Remarque :
* Dans la structure définissant un bloc nommé T_Block, nous avons ajouté le type time_t pour la date. Time_t est un type qui permet de représenter un temps écoulé depuis le 1er janvier 1970 à 00:00:00 (on parle également de timestamp) en secondes.


#### Fonctions supplémentaires :

* void afficherDate(T_Block block):
Cette fonction permet d’afficher la date sous le format demandé. En effet, comme le timestamp nous donne le nombre de secondes qui s’est écoulé depuis le 01/01/1970, on a dû le convertir d’abord en jour, mois et année (struct tm) puis l’afficher au bon format(1900+(time->tm_year), 1+(time->tm_mon), time->tm_mday).

Tout d’abord pour obtenir la date du jour, on utilise la fonction time () (lors de la création d’un nouveau bloc) qui permet d’obtenir le temps qui s’est écoulé depuis 1970. Ensuite, on utilise localtime() qui est une fonction transformant un timestamp (donc de type time_t) en un struct tm. Il est important de préciser le fait que cette fonction n'alloue pas de nouveau bloc mémoire pour la structure retournée. C’est pour cela que l’on a décidé d’utiliser cette fonction seulement dans la fonction afficher_date(). De cette manière, on stock la valeur en secondes sous forme d’un timestamp dans T_block->date. On peut alors simuler une nouvelle journée (+86400) et, seulement au moment de l'affichage, utiliser localtime() pour ne pas allouer un nouveau bloc mémoire.

* void affichageListeBlocks (Blockchain blockchain)

Cette fonction permet d’afficher la totalité des blocs dans la blockchain. Nous avons décidé d’ajouter cette fonction afin de rappeler à l’utilisateur les blocs déjà créés pour faciliter l’utilisation du programme.

* void affichageListeTransaction(Blockchain blockchain,int idBlock)
Cette fonction nous permet d’afficher la totalité des transactions dans un bloc de la blockchain au choix. Nous l’avons créé dans le même but que la fonction précédente.

* int demandeIdBlock(Blockchain blockchain)
* int demandeIdEtu()
* float demandeMontant()
* char* demandeDescr()

Ces fonctions utilitaires permettent de demander des informations à l’utilisateur à diverses endroits dans le programme.

* void affichageListeTransactionEtuBlock(Blockchain blockchain,int idEtu)

Cette fonction permet d’afficher toute les transactions du jour d’un étudiant en particulier.

### 2.Complexité des fonctions implémentées

## Remarques :

* Dans la suite, nous considérerons que la complexité des fonctions time(), localtime(), getchar() et gets() est de O(1).

* On utilisera n pour désigner le nombre de transaction par bloc et p le nombre de blocs à parcourir dans la liste chaînée.

* float totalTransactionEtudiantBlock(int idEtu, T_Block b)
* void affichageListeTransactionEtuBlock(Blockchain blockchain,int idEtu)

A l'aide de la boucle while, on parcourt “n” transactions d'un bloc. Pour chaque itération, on réalise des opérations élémentaires en O(1). La complexité de ces deux fonctions est donc en O(n).

* float soldeEtudiant(int idEtu, Blockchain bc)

La boucle while permet de parcourir l'ensemble des blocs et on réutilise dans cette boucle la fonction totalTransactionEtudiantBlock() de complexité O(n). On obtient alors une complexité de O(n*p).

* int payer(int idEtu, float montant, char *descr, Blockchain bc)

On utilise d’abord la fonction soldeEtudiant() de complexité O(n*p). Ensuite, on effectue des opérations élémentaires en O(1) donc la complexité finale est de O(n*p)

* int transfert(int idSource, int idDestination, float montant, char *descr, Blockchain bc)

Dans le pire des cas, on réalise un paiement et un créditement. La complexité de cette fonction est donc O((n*p)+1)=O(max((n*p),1))=O(n*p)

* void consulter(int idEtu, Blockchain bc)

Tout d'abord, on utilise la fonction soldeEtudiant qui a pour complexité O(n*p).

Ensuite, on utilise deux boucles while imbriquées. On remarque que dans le pire des cas, on doit parcourir tous les blocs et toutes les transactions. La première parcourt les p blocs. L’autre est de complexité O (n) puisqu’elle parcourt n transactions correspondant à un étudiant. Pour ces deux boucles, on obtient donc une complexité de O(n*p)

Enfin pour conclure, on a O(n*p + n*p)=O(max((n*p),(n*p))=O(n*p)

* void affichageListeBlocks (Blockchain blockchain);

La boucle while permet de parcourir l'ensemble de la blockchain, on est donc en O(p).
* int demandeIdEtu()
* float demandeMontant();

Ce sont des fonctions en O(m) avec m étant le nombre de fois où l'utilisateur entre une valeur qui ne vérifie pas la condition d'arrêt.

###Conclusion :

Pour conclure, grâce à ce TP nous avons eu l’occasion d’appliquer les notions du langage C acquises au cours du semestre, ainsi que de revoir le concept des listes chaînées.
En essayant de résoudre les problèmes rencontrés au cours de ce projet, nous avons appris à mieux manipuler les listes chaînées et à affiner notre compréhension sur la notion de complexité.
