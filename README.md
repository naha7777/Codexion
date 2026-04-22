Quand le main demarre on est dans le thread (fil d'execution) principal.


Quand je cree une thread, je lui envoie une fonction, quand il l'a finit cela signifie qu'il a finit toutes ses taches.

Quand on arrive sur pthread_create (sur la creation d'un thread), le systeme d'exploitation cree une nouvelle unite d'execution (nouveau fil d'execution) independante>
=> Mon programme a alors 2 bras.
Le thread principale continue sa roue vers la fin de la fonction alors que le thread va executer la fonction qu'on lui a donne.
SI le main va trop vite et se finit, il tue tous les autres threads.
Donc on utilise pthread_join = blooque le thread principal (main) tant que le thread secondaire n'est pas termine.

D'abord on cree les variables :
```c
pthread_t tid, tid2
```
Puis:
pthread_create => creer le thread avec en parametre l'adresse de notre variable, NULL, une fonction a effectuer, et l'argument de la fonction
pthread_join => demander au thread principale d'attendre que les autres threads aient fini leur execution avant de continuer, on met en parametre le nom de la variable et NULL

Avec plusieurs threads :
- creer d'abord tous les threads
- puis join tous les threads

Le mutex lui sert a attendre qu'une ressource se libere.
C'est un verrou.
On cree d'abord la variable avec pthread_mutex_t et le nom.
Puis on l'initialise avec pthread_mutex_init avec en parametre l'adresse de la variable et NULL
Dans la fonction on va pouvoir lock et unlock le mutex/verrou avec pthread_mutex_lock avec en parametre l'adresse de la variable.
Puis de retour dans notre main on va destroy le mutex avec pthread_mutex_destroy.
Je pense que c'est le monitor qui va le destroy.

Variables de condition :
pthread_cond_wait = n'entre pas avant que j'ai fini telle chose.
Parfois un thread n'a pas juste besoin d'exclusivite avec le mutex, il a aussi besoin d'attendre qu'un evenement particulier se produise.
Cela evite de laisser le thread tourner et utiliser a 100% ses performances.
Avec pthread_cond_wait, le thread s'endort en attendant le signal il dverouille le mutex et endort le thread quand il se reveille puis verouille le mutex

pthread_cond_broadcast : reveille tous les threads qui attendent

Il faut mettre un while, pas un if.

Avant d'utiliser une variable de condition, il faut l'initialiser :
- pthread_cond_t cond = nom
- pthread_cod_init

pthread_cont_timedwait evite l'endormissement a l'infini du thread

pthread_cond_destroy
Libere quand on utilise plus.
Ne pas liberer une variable de condition sur laquelle des threads sont encore entrain de dormir sinon CRASH

Chaque dongle doit etre un mutex.
Un coder doit lock celui de gauche puis celui de droite (sauf le dernier qui fait l'inverse -> evite deadlock)

Il faut enregistrer le moment de la derniere compile car temps_actuel - temps_de_la_derniere_compile > burn-out = signal du burn-out

Quand un codeur veut un dongle, il depose une requete dans la file d'attente (heap) qu'on doit implemter.
Liste chainee simple pour fifo et HEAP pour EDF
Le codeur arive et demande le dongle. Si il est pris ou si il y a d'autres gens dans la file d'attente il s'endort avec pthread_cond_wait.

Quand un dongle est repose, on regarde la file d'attente et on envoie pthread_cond_broadcast pour tous les reveiller. Le 1er peut prendre le dongle et les autres se rendormir.

Mais il y a un dongle cooldown a gerer : reveiller le codeur quand le cooldown est finit en utilisant pthread_cond_timedwait

Mutex : proteger l'acces aux dongles, a la file d'attente et a l'affichage
Variables de condition : pour mettre les codeurs en attente selon la queu

HEAP/Prioriy queue : pour gerer mathematiquement qui est le 1er (fifo) ou qui est le + proche du burnout (edf)

Creer une structure generale a passer aux threads: toutes les datas des arguments

Heap = arbre binaire qui s'auto-organise pour que l'element le plus important soit toujours a la racine (index 0 du tableau)
- FIFO : timestamp d'arrivee
- EDF : selon l'echeance de burnout

HEAP + efficace qu'une liste pour un ordonnanceur
-> a coder dans un tableau
Avec l'element a indice i :
- son fils gauche : 2*i+1
- son fils droit : 2*i+2
- son parent : (i-1)/2

Chaque codeur est un thread qui effectue une boucle.
- prend 2 dnogles (a sa gauche et sa droite)
- compile -> usleep
- relache -> activation du cooldown
- debug -> usleep
- refactor -> usleep

Monitor = thread a part qui tourne en boucle super vite, il parcourt les codeurs et check le burnout (arrete et affiche)

IL y a un dongle entre chaque codeur.
entre N et N+1
entre N et N-1
meme entre le 1er codeur et le dernier codeur car ils sont en cercle

Un codeur peut toucher qu'a ceux a cote de lui.
SI le codeur 2 finit, seuls les codeurs 1 et 3 peuvent prendre les dongles (1 chacun)

Chaque dongle a son propre mutex, sa propre variable de condition, sa propre heap


<!-- MONITOR -->
GRANDES QUESTIONS :
- Comment avoir le monitor qui tema H24 les codeurs?????? -> est-ce qu'on lui envoie les infos H24?
- le monitor est une thread a part entiere lance au debut de la simulation.
- il ne compile pas, il ne debug pas, et il ne touche jamais aux dongles.
- il doit juste boucler a l'infini sur une liste de donnees
- chaque codeur possede une structure de donnees ou il ecrit j'ai commence a compiler a telle heure precise
- le codeur ecrit l'heure des qu'il attrape ses deu dongles
- le monitor lis les heures de debut pour chaque codeur
- a chaque tour de boucle, le monitor fait un calcul : heure actuelle - heure du dernier debut de compile = temps ecoule
Si le temps ecoule est plus grand que le temps de burnout autorise par le sujet alors il arrete tout

en gros le monitor :
- check tous les codeurs
- micro sieste avec usleep de 1/2 ms
- recommence
Comme il verifie toutes les 1 ou 2ms, il est physiquement impossible qu'un codeur soit mort depuis plus de 10ms sans que le monitor ne s'en apercoive.

Pour eviter que le monitor ne lise une heure pendan que le codeur est en train de l'ecrire (=data race), ils utilisent un mutex
- le codeur verouille, ecrit l'heure, deverouille
- le monitor verouille, lit l'heure, deverouille

Des que le monitor detecte un burnout ou que le nombre de compilation requis est atteint, il change un flag. TOus les autres threads regardent regulierement ce flag et s'arretent des qu'il passe a VRAI
Ce flag se trouve dans la structure de donnees donnee a tous les threads :
On y met un int stop_simulation qui a 0 tourne et a 1 se stop
Et le monitor est le seul habilite a eteindre l'usine
- il verouille le stocp lock (pthread_mutex_t stop_lock)
- passe stop_simulation a 1

Les codeurs doivent etre programmes pour verifier l'etat de l'interrupteur regulierement
Dans leur boucle (compile, debug, refactor) ils font une verif a chaque etape : est-ce que stop_simulation est a 1? si oui j'arrete ma boucle et je termine mon thread proprement.
<!-- MONITOR -->

<!-- BESOIN DE RETURN ? -->
Avec les threads, on n'a pas besoin de return pour mettre a jour les donnees.
Dans un programme multi-threads tous les threads partagent le meme espace memoire (le tas ou heap)
- quand je cree mes threads je donne directement l'adresse en memoire de ma structure de donnees, pas une copie -> permet que les threads voient tous la meme chose en temps reel, c'est pour ca qu'il faut verouiller avant de modifier et deverouiller ensuite comme ca ya pas de data race
- le return d'un thread sert juste a envoyer une valeur une fois qu'il est mort.

Imaginer la structure comme un tableau blanc au milieu de la piece :
- le codeur ecrit au feutre rouge l'heure de sa derniere compilation sur le tableau
- le moniteur a les yeux fixes sur le tableau et des qu'il voit l'heure changer, il l'utilise pour ses calculs
- l'arret sir le monitor ecrit STOP en gros sur le tableau tous les codeurs qui regardent le tableau vont le voir simultanement et s'arreter.

C'est precisement parce que tout le monde touche a la meme structure en direct qu'on a besoin des mutex. SI le codeur ecrit sur le tableau blanc pendant que le moniteur essaie de lire, le moniteur va voir un gribouillis illisible (data race)
Le mutex force l'un a attendre que l'autre ait fini de toucher au tableau blanc
<!-- BESOIN DE RETURN ? -->

<!-- NESTING (EMBOITEMENT) DE STRUCTURES -->
- une structure coder avec l'id, le nombre de compilations realisees, le temps de debut de la derniere compilation, le thread lui meme, et un pointeur vers la structure config pour acceder aux regles
- une structure dongle avec le mutex du dongle, la variable de condition, et la gestion du cooldown
- enfin la structure mere, la structure principale avec toutes les regles, le drapeau de stop, une proteciton pour les logs, et un pointeur vers les structures codeurs et dongles (plutot un tableau avec toutes les structures pour chaque codeur/chaque dongle)

-> apres le parsing : malloc un tableau de codeurs et malloc un tableau de dongles
-> le monitor parcourt le tableau dans la structure principale pour check les temps
-> le codeurN accede a son dongle gauche via le tableau dongles dans la structure principale [N-1] et droite avec N

data->coders[i]
data->dongles[N-1]
data->dongles[N]

Comme chaque codeur a un pointeur vers la structure principale, il peut lire data->stop_simulation ou data->t_compile a n'importe quel moment
<!-- NESTING DE STRUCTURES -->

faire une boucle pour creer les threads

<!-- ORGA -->
- creer un tableau de structures : tableau des structures coder, et tableau des structures dongle, ils doivent avoir exactement la meme taille que le nombre de coders passe en argument -> malloc
POURQUOI ?
-> chaque odeur est un individu autonome (un thread). Chaque individu doit avoir son propre espace memoire pour stocker son id, son horloge perso, son compteur de compilations, son idententifiant de thread.
-> 5 codeurs = 5 structures...

Donc apres le parsing :
a partir de la structure principale data (pour enregistrer tout dedans et y avoir acces a tout moment) : data.nb_coders...
- recuperer le nombre de codeurs avec argv et atoi
- allouer le tableau de structures pour les codeurs : malloc de la taille de la structure * le nombre de coders
- pareil pour les dongles
- puis securiser les malloc
- quand le tableau est malloc, il faut faire une boucle pour creer les threads. A chaque creationm l faut donner a chaque thread l'adresse de sa propre structure dans le tableau

- on cree le thread du monitor
- on cree les codeurs / threads
- on leur envoie la structure config
- du coup les threads vont dans une fonction et la fonction directe regarde si c'est FIFO ou EDF qu'il faut utiliser
- si c'est fifo on va dans une fonction
- sinon dans une autre
<!-- ORGA -->























Qu'en faire quand c'est check ?
Les stocker mais ou ?


Faire des structures.
parser et envoyer dans les structures


Thread (fil d'execution) = tache que le programme fait en parallele. ex : dans un restau, le programme c'est le restau, les threads sont les serveurs qui travaillent tous dans le meme espace memoire sans se connaitre forcement.

POSIX thread (pthread) = bibliotheque standard en C qui permet de creer et gerer des threads

Mutex (MUTual EXclusion) c'est un verrou : ex d'une salle de bain avec une serrure, une personne peut l'utiliser a la fois. Quand un thread prend le mutex, les autres attendent. Donc ici chaque dongle est protege par un mutex. Sans ca plusieurs codeurs pourraient prendre le meme dongle en meme temps.

USB dongle : dans la realite c'est un petit boitier physique qui sert de preuve de licence, pour activer un logiciel par exemple. C'est un systeme anti piratage materiel. Ici c'est la ressource partagee et limitee. C'est une analogie : les dongles sont rares et partages, comme dans un vrai atelier ou uneequipe de 10 developpers n'auraient que 4 ou 5 licences materielles pour un outil couteux et devrait se les partager a tour de role.

Smart Scheduling (FIFO/EDF) = le scheduler decide qui obtient un dongle quand plusieurs codeurs en demande en meme temps.
FIFO : 1er arrive = 1er servi
EDF : priorite a celui qui va burnout le plus tot => systeme + intelligent et efficace

Quantum Compiler et Quantum Coder : c'est juste du lore = quantique

Refactor = reecrire du code pour l'ameliorer

CPU usage time : le temps CPU mesure combien de temps le processeur a activement travaille pour un processus. Le sujet recommande le temps reel avec l'utilisation de gettimeofday()

FONCTIONS:
- pthread_create = cre un nouveau thread = point d'entree du codeur. Chaque appel lance un codeur independant.
- pthread_join = attend qu'un thread se termine avant de continuer : ex attend que les serveurs finissent de servir avant de fermer le restaurant
- pthread_mutex_init / pthread_mutex_destroy = cree/detruit une variable de condition. Mecanisme qui permet a un thread d'attendre qu'une condition soit vraie. ex : attendre que le dongle soit dispo
- pthread_cond_wait = met le thread en attente et relache le mutex automatiquement. Pas d risque de rater la notif. Le thread se rendort jusqu'a ce qu'on le reveille.
- pthread_cond_timedwait = comme pthread_cond_wait mais avec un timeout : si personne ne reveille le thread avant la fin du timeout alors il se reveille tout seul. C'est utile pour detecter le burnout
- pthread_cond_broadcast = reveille tous les threads qui attendent sur une condition. Utile quand un dongle est libere : tous les codeurs qui l'attendaient se reveillent pour voir si c'est leur tour
- usleep = met le thread en pause pendant un certain nombre de microsecondes (1ms = 1000us) = temps d'une action
- gettimeofday() = donne l'heure actuelle a la microseconde pres -> calcul des timestamps (logs), depassement delai burnout, cooldowns dongles.

Monitor thread = thread dedie a la surveillance, ne fait rien lui meme, observe les codeurs H24. Detecte si burn-out et arrete vite la simu. Verifie aussi que les codeurs ont atteint le nombre de compilation.

C89 (ANSI C) = 1ere version du langage C de 1989 : pas de tableaux, commentaires, bool... Pas de heap dans sa bibli stanard. Je dois implementer moi meme une priority queu pour gerer l'ordonnancement FIFO et EDF.

=> Maitriser la concurrence en C : creer des threads, les proteger avec des mutexs, les faire communiquer avec des variables de condition, gerer le temps avec precision, implemtenter un scheduler intelligent. Utile dans OS, ases de donneees, serveurs web... partout ou plusieurs choses se passent en meme temps.

On a plusieurs codeurs, il y a autant de dongles que de codeurs
Au debut tous les dongles sont dispos
Alors les codeurs chacun leur tour prennent deux dongles et compile, jusqu'a ce qu'il n'y ait plus de dongles de dispo
Quand ils ont fini ils remettent a dispo les dongles
des que yen a deux de dispo le prochain codeur peut les prendre et compiler
des la fin de la compil le codeur debug
des la fin du debug le codeur refactor
des la fin du refactor il se place dans la queue et attend son tour
on compte le temps d'attente
si il est trop important burnout
le monitoring recoit un burnout et stop le programme
si il n'y a pas de burnout le programme se stop lorsque tous les codeurs ont fini de tout compiler

- un endroit ou on met le nombre de codeurs qui ont atteint le nombre de compilation
- un endroit ou on a une queue des codeurs qui ont fini de refactoring et attende d'avoir un dongle
-


# Codexion

## Resources
### Documentation
https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/
https://dev.to/yel-bakk/codexion-4fk8
