#ifndef EMPLOYES_H
#define EMPLOYES_H

#include "entreprises.h"
#include "roles.h"

typedef struct {
    int id;
    char *cin;
    char *nom;
    char *prenom;
    char *email;
    char *telephone;
    Entreprise *entreprise;
    Role *role;
} Employe;


extern Employe* employes;
extern int nb_employes;
extern int cap_employes;


void initialiser_employes();
void ajouter_employe(const char* cin, const char* nom, const char* prenom, const char* email, const char* telephone, Entreprise* entreprise, Role* role);
Employe* trouver_employe_par_id(int id);
void supprimer_employe_de_table(int id);
void liberer_employes();


Employe* creer_employe(int id, const char* cin, const char* nom, const char* prenom, const char* email, const char* telephone, Entreprise* entreprise, Role* role);
void afficher_employe(const Employe* emp);
void modifier_employe(Employe* emp, const char* nouveau_cin, const char* nouveau_nom,const char* nouveau_prenom, const char* nouveau_email,const char* nouveau_telephone, Entreprise* nouvelle_entreprise,Role* nouveau_role);
void supprimer_employe(Employe* emp);
void enregistrer_employes_dans_fichier(const char* nom_fichier);
void charger_employes_depuis_fichier(const char* nom_fichier);

#endif
