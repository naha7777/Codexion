- une heap de 2 codeurs par dongles
- on regarde de quels dongles a besoin le codeur
- on regarde si il est devant dans la liste des 2 dongles (+ autres conditions de fifo)
- si non il attend
- si oui bah let's go
OU une seule grosse HEAP mais du coup ca sera moins efficace que mon fifo

inscription dans les heap en debut de simu
check pour verif l'ordre dans les heap et le changer si besoin
gerer burnout et fin


tous les codeurs se lancent -> ils vont dans i_want_dongle
dans i_wont_dongle ils vont dans edf
dans edf on check les dongles qui les interesse ---
grace a ca on les met dans cette heap
si il n'est pas deja dans la heap :
- si ya prsn dans la heap, genial tu vas en premier
- sinon tu regardes ton temps de burnout
si tu vas burnout plus vite tu vas en 1 er sinon deuxieme
et ca pour chaque heap

mtn que pour chaque dongle on a nos codeurs dans leurs heaps
on va check les memes trucs que fifo + la position dans la heap (check ca en 1er)
si il prend le dongle on le passe en deuxieme dans la heap
ensuite c'est comme d'hab
si ya burnout ou fin : on doit les sortir de la heap


edf check flag
edf check l'id
il trouve les deux dongles
il trouve les heaps respectives de ces dongles
il regarde dans la heap pour y mettre notre codeur id et notre deadline
ensuite il trouve le dongle le moins grand
puis regarde si ils sont available
regarde en premier si notre codeur est 1er de sa liste
si tout reussi il prend les dongles
compile etc

en fait je devrais refaire le meme systeme que mon fifo mais a chaque fois verifier si le codeur est premier dans la queu de ceux qui vont burn out en premier
et si un autre codeur est devant lui et a des dongles de dispo il y va avant
-> je le rends juste plus efficace en mode il finit grave avant fifo ou burn out plus loin si fifo burnout (car mon fifo est deja tres efficace)
en fait je dois faire comme fifo sauf qu'au lieu que ce soit un coder au hasard qui se lance, on regarde parmi les codeurs qui veulent se lancer lequel a la deadline la plus short (on prend celui qui arrive le plus tot dans notre liste)
donc liste de tous les codeurs en meme temps qui s'actualise a chaque fois
peut-etre les lancer en 1 sur 2


_This project has been created as part of the 42 curriculum by anacharp._

# Codexion
## Description
Presents the project, including goals and brief overview

## Instructions
Informations about compilation, installation and/or execution

## Blocking cases handled
Section describing all the concurrency issues adressed in your solution (deadlock prevention and Coffman's conditions, starvation prevention, cooldown handling, precise burnout detection, log serialization)

## Thread synchronization mechanisms
Section explaining the specific threading primitives used in your implementation  (pthread_mutex_t, pthread_cond_t, custom event implementation) and how they coordinate access to shared resources (dongles, logging, monitor state). Include examples of how race conditions are prevented and how thread-safe communication is achieved between coders and the monitor.

## Resources
### Documentation
- https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/
- https://dev.to/yel-bakk/codexion-4fk8
- https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2
- https://www.geeksforgeeks.org/c/heap-in-c/
- https://nkugwamarkwilliam.medium.com/heap-in-c-programming-made-easy-e84a8b423660
- https://codexion-visualizer.sacha-dev.me/

### AI Usage
AI was used for the following tasks :
- better understanding of threads
-
