#ifndef REUNIONS_H
#define REUNIONS_H

#include "date_heure.h"
#include "employes.h"
#include "salles.h"

typedef struct Reunion {
    int id;
    Date_Heure date_debut;
    int duree;
    char *lien;
    char *type;
    Employe *organisateur;
    Salle *salle;
    struct Reunion *suivante;
} Reunion;

// Global declarations (extern)
extern Reunion* reunions;
extern int nb_reunions;
extern int cap_reunions;


void initialiser_reunions();
Reunion* ajouter_reunion(Date_Heure date_debut, int duree, const char* lien,
                        const char* type, Employe* organisateur, Salle* salle);
void ajouter_session_reunion(Reunion* reunion_principale, Date_Heure nouvelle_date);
Reunion* trouver_reunion_par_id(int id);
void supprimer_reunion_et_sessions(int id);
void liberer_reunions();

int compter_invites_par_reunion_id(int reunion_id);
int compter_invites_presentiel_par_reunion_id(int reunion_id);




Reunion* creer_reunion(int id, Date_Heure date_debut, int duree, const char* lien, const char* type, Employe* organisateur, Salle* salle);
void afficher_reunion(const Reunion* reunion);
void modifier_reunion(Reunion* reunion, const Date_Heure* nouvelle_date, int nouvelle_duree, const char* nouveau_lien, const char* nouveau_type, Employe* nouvel_organisateur, Salle* nouvelle_salle);
void supprimer_reunion(Reunion* reunion);

void supprimer_liste_reunions(Reunion** tete);
void enregistrer_reunions_dans_fichier(const char* nom_fichier);
void charger_reunions_depuis_fichier(const char* nom_fichier);

#endif
