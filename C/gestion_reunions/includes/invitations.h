#ifndef INVITATIONS_H
#define INVITATIONS_H

#include "employes.h"
#include "reunions.h"

typedef struct {
    char *disponibilite;
    char *presence;
    bool type;  // 0=Présentiel, 1=En ligne
    Employe *invite;
    Reunion *reunion;
} Invitation;


extern Invitation* invitations;
extern int nb_invitations;
extern int cap_invitations;


void initialiser_invitations();
void ajouter_invitation(const char* disponibilite, const char* presence, bool type, Employe* invite, Reunion* reunion);
Invitation* trouver_invitation_par_employe_et_reunion(Employe* emp, Reunion* reun);
void mettre_a_jour_statut_invitation(Invitation* inv, const char* new_dispo, const char* new_presence);
void supprimer_invitation_de_table(Invitation* inv);
void liberer_invitations();



Invitation* creer_invitation(const char* disponibilite, const char* presence, bool type, Employe* invite, Reunion* reunion);
void afficher_invitation(const Invitation* inv);
void modifier_invitation(Invitation* inv, const char* nouvelle_disponibilite, const char* nouvelle_presence, bool nouveau_type, Employe* nouvel_invite, Reunion* nouvelle_reunion);
void supprimer_invitation(Invitation* inv);
void enregistrer_invitations_dans_fichier(const char* nom_fichier);
void charger_invitations_depuis_fichier(const char* nom_fichier);

#endif
