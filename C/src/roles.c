#include "../includes/roles.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include "../includes/counters.h"


Role* roles = NULL;
int nb_roles = 0;
int cap_roles = 0;

#define CAPACITE_INITIALE 10

void initialiser_roles() {
    roles = malloc(CAPACITE_INITIALE * sizeof(Role));
    cap_roles = CAPACITE_INITIALE;
    nb_roles = 0;
}

void ajouter_role(const char* nom) {

    if (nb_roles >= cap_roles) {
        cap_roles++;  
        Role* new_tab = realloc(roles, cap_roles * sizeof(Role));
        roles = new_tab;
    }
    
    
    roles[nb_roles].id = role_id_counter++; 
    roles[nb_roles].nom = strdup(nom);
    nb_roles++;

}

Role* trouver_role_par_id(int id) {
    for (int i = 0; i < nb_roles; i++) {
        if (roles[i].id == id) {
            return &roles[i];
        }
    }
    return NULL;
}

void supprimer_role_de_table(int id) {
    for (int i = 0; i < nb_roles; i++) {
        if (roles[i].id == id) {
            free(roles[i].nom);

            for (int j = i; j < nb_roles - 1; j++) {//decalage
                roles[j] = roles[j + 1];
            }
            nb_roles--;
            break;
        }
    }
}

void liberer_roles() {
    for (int i = 0; i < nb_roles; i++) {
        free(roles[i].nom);
    }
    free(roles);
    roles = NULL;
    nb_roles = cap_roles = 0;
}



Role* creer_role(int id, const char* nom) {
    Role* role = malloc(sizeof(Role));
    if (role) {
        role->id = id;
        role->nom = malloc(strlen(nom) + 1);
        if (role->nom) strcpy(role->nom, nom);
    }
    return role;
}

void afficher_role(const Role* role) {
    if (role) printf("Role [ID: %d] Nom: %s\n", role->id, role->nom);
}

void modifier_role(Role* role, const char* nouveau_nom) {
    if (role) {
        free(role->nom);
        role->nom = malloc(strlen(nouveau_nom) + 1);
        if (role->nom) strcpy(role->nom, nouveau_nom);
    }
}

void supprimer_role(Role* role) {
    if (role) {
        free(role->nom);
        free(role);
    }
}
    void enregistrer_roles_dans_fichier(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "w");
    if (!fichier) {
        perror("Erreur d'ouverture du fichier pour écriture");
        return;
    }

    for (int i = 0; i < nb_roles; i++) {
        fprintf(fichier, "%d;%s\n", roles[i].id, roles[i].nom);
    }

    fclose(fichier);
}

void charger_roles_depuis_fichier(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        perror("Erreur d'ouverture du fichier pour lecture");
        return;
    }

    initialiser_roles();  // vide l'ancienne liste

    int id;
    char nom[256];

    while (fscanf(fichier, "%d;%255[^\n]\n", &id, nom) == 2) {
        ajouter_role(nom); // ajoute en mémoire
        roles[nb_roles - 1].id = id; // impose l'ID original

        if (id >= role_id_counter) {
            role_id_counter = id + 1;
        }
    }

    fclose(fichier);
}


