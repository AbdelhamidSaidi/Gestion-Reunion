#ifndef ORDRES_DU_JOUR_H
#define ORDRES_DU_JOUR_H

#include "employes.h"
#include "reunions.h"

typedef struct {
    int id;
    char *sujet;
    Employe *presentateur;
    Reunion *reunion;
} OrdreDuJour;


extern OrdreDuJour* ordres_du_jour;
extern int nb_ordres_du_jour;
extern int cap_ordres_du_jour;

void initialiser_ordres_du_jour();
OrdreDuJour* ajouter_ordre_du_jour(const char* sujet, Employe* presentateur, Reunion* reunion);
void supprimer_ordre_du_jour_de_table(int id);
OrdreDuJour* trouver_ordre_par_id(int id);
OrdreDuJour* trouver_ordres_par_reunion(Reunion* reunion);
OrdreDuJour* trouver_ordres_par_presentateur(Employe* presentateur);
void liberer_ordres_du_jour();

OrdreDuJour* creer_ordre_du_jour(int id, const char* sujet, Employe* presentateur, Reunion* reunion);
void afficher_ordre_du_jour(const OrdreDuJour* ordre);
void modifier_ordre_du_jour(OrdreDuJour* ordre, const char* nouveau_sujet, Employe* nouveau_presentateur, Reunion* nouvelle_reunion);
void supprimer_ordre_du_jour(OrdreDuJour* ordre);
void enregistrer_ordres_du_jour_dans_fichier(const char* nom_fichier);
void charger_ordres_du_jour_depuis_fichier(const char* nom_fichier);


#endif
