#ifndef SALLES_H
#define SALLES_H

#include <stdbool.h>

typedef struct {
    int id;
    char *nom;
    int capacite;
    bool disponible;
} Salle;


extern Salle* salles;
extern int nb_salles;
extern int cap_salles;

void initialiser_salles();
void ajouter_salle(const char* nom, int capacite, bool disponible);
Salle* trouver_salle_par_id(int id);
void supprimer_salle_de_table(int id);
void liberer_salles();


Salle* reserver_salle(int id_reunion);

Salle* creer_salle(int id, const char* nom, int capacite, bool disponible);
void afficher_salle(const Salle* salle);
void modifier_salle(Salle* salle, const char* nouveau_nom, int nouvelle_capacite, bool nouvelle_disponibilite);

void supprimer_salle(Salle* salle);
void enregistrer_salles_dans_fichier(const char* nom_fichier);
void charger_salles_depuis_fichier(const char* nom_fichier);

#endif
