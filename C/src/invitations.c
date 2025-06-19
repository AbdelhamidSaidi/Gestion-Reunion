#include "../includes/invitations.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


Invitation* invitations = NULL;
int nb_invitations = 0;
int cap_invitations = 0;

#define CAPACITE_INITIALE 10

void initialiser_invitations() {
    invitations = malloc(CAPACITE_INITIALE * sizeof(Invitation));
    cap_invitations = CAPACITE_INITIALE;
    nb_invitations = 0;
}

void ajouter_invitation(const char* disponibilite, const char* presence, bool type, Employe* invite, Reunion* reunion) {

    if (nb_invitations >= cap_invitations) {
        cap_invitations++;
        Invitation* new_tab = realloc(invitations, cap_invitations * sizeof(Invitation));
        invitations = new_tab;
    }

    // Set fields
    invitations[nb_invitations].disponibilite = strdup(disponibilite);
    invitations[nb_invitations].presence = strdup(presence);
    invitations[nb_invitations].type = type;
    invitations[nb_invitations].invite = invite;  // Reference only
    invitations[nb_invitations].reunion = reunion; // Reference only

    nb_invitations++;
}

Invitation* trouver_invitation_par_employe_et_reunion(Employe* emp, Reunion* reun) {
    for (int i = 0; i < nb_invitations; i++) {
        if (invitations[i].invite == emp && invitations[i].reunion == reun) {
            return &invitations[i];
        }
    }
    return NULL;
}

void mettre_a_jour_statut_invitation(Invitation* inv, const char* new_dispo, const char* new_presence) {
    if (!inv) return;
    

    free(inv->disponibilite);
    free(inv->presence);
    
    inv->disponibilite = strdup(new_dispo);
    inv->presence = strdup(new_presence);

}

void supprimer_invitation_de_table(Invitation* inv) {
    if (!inv) return;
    
    for (int i = 0; i < nb_invitations; i++) {
        if (&invitations[i] == inv) {

            free(invitations[i].disponibilite);
            free(invitations[i].presence);
            

            for (int j = i; j < nb_invitations - 1; j++) {
                invitations[j] = invitations[j + 1];
            }
            nb_invitations--;
            return;
        }
    }
}

void liberer_invitations() {
    for (int i = 0; i < nb_invitations; i++) {
        free(invitations[i].disponibilite);
        free(invitations[i].presence);
    }
    free(invitations);
    invitations = NULL;
    nb_invitations = cap_invitations = 0;
}




Invitation* creer_invitation(const char* disponibilite, const char* presence, bool type, Employe* invite, Reunion* reunion) {
    Invitation* inv = malloc(sizeof(Invitation));
    if (inv) {
        inv->disponibilite = strdup(disponibilite);
        inv->presence = strdup(presence);
        inv->type = type;
        inv->invite = invite;
        inv->reunion = reunion;
    }
    return inv;
}


void modifier_invitation(Invitation* inv, const char* nouvelle_disponibilite, const char* nouvelle_presence, bool nouveau_type, Employe* nouvel_invite, Reunion* nouvelle_reunion) {
    if (!inv) return;

    if (nouvelle_disponibilite) {
    free(inv->disponibilite);
    inv->disponibilite = strdup(nouvelle_disponibilite);
    }

    if (nouvelle_presence) {
    free(inv->presence);
    inv->presence = strdup(nouvelle_presence);
    }

    inv->type = nouveau_type;

    if (nouvel_invite) {
    inv->invite = nouvel_invite;
    }

    if (nouvelle_reunion) {
    inv->reunion = nouvelle_reunion;
    }
}

void afficher_invitation(const Invitation* inv) {
    if (inv) {
        printf("Invitation\nDisponibilite: %s\nPresence: %s\nType: %s\n",
               inv->disponibilite, inv->presence, 
               inv->type ? "En ligne" : "Presentiel");
        if (inv->invite) printf("Invite: %s %s\n", 
               inv->invite->prenom, inv->invite->nom);
        if (inv->reunion) printf("Reunion [ID]: %d\n", inv->reunion->id);
    }
}

void supprimer_invitation(Invitation* inv) {
    if (inv) {
        free(inv->disponibilite);
        free(inv->presence);
        free(inv);
    }
}
void enregistrer_invitations_dans_fichier(const char* nom_fichier) {
    FILE* f = fopen(nom_fichier, "w");
    if (!f) {
        perror("Erreur ouverture fichier export");
        return;
    }

    for (int i = 0; i < nb_invitations; i++) {
        fprintf(f, "%s\n", invitations[i].disponibilite);
        fprintf(f, "%s\n", invitations[i].presence);
        fprintf(f, "%d\n", invitations[i].type);
        fprintf(f, "%d\n", invitations[i].invite->id);   // ID de l'employ�
        fprintf(f, "%d\n\n", invitations[i].reunion->id); // ID de la r�union
    }

    fclose(f);
}
void charger_invitations_depuis_fichier(const char* nom_fichier) {
    FILE* f = fopen(nom_fichier, "r");
    if (!f) {
        perror("Erreur ouverture fichier import");
        return;
    }

    liberer_invitations();
    initialiser_invitations();

    char dispo[256], presence[256];
    int type, id_emp, id_reun;

    while (fgets(dispo, sizeof(dispo), f)) {
        dispo[strcspn(dispo, "\n")] = 0;

        if (!fgets(presence, sizeof(presence), f)) break;
        presence[strcspn(presence, "\n")] = 0;

        if (fscanf(f, "%d\n%d\n%d\n", &type, &id_emp, &id_reun) != 3) break;

        // Lire ligne vide
        char buffer[256];
        fgets(buffer, sizeof(buffer), f);

        Employe* emp = trouver_employe_par_id(id_emp);
        Reunion* reun = trouver_reunion_par_id(id_reun);

        if (emp && reun) {
            ajouter_invitation(dispo, presence, type, emp, reun);
        }
    }

    fclose(f);
}

