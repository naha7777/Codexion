etape 1 - parsing :
- ne pas accepter si ya pas 9 arguments
- si ya 9 arguments :
+ check si deux de 1 a 8 sont des int positifs et 9 string fifo ou edf
si non -> return None et dans le main si on recup None on return (0)

Qu'en faire quand c'est check ?
Les stocker mais ou ?
- nombre de coders
- temps de burnout
- temps pour compiler
- temps pour debug
- temps pour refactorer
- nombre de compilations requises
- cooldown des dongles
- type de scheduler

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
- pthread_create = cre un nouveau thread = point d'entree du codeur. Chaque appel lanceun codeur independant.
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


# Codexion
