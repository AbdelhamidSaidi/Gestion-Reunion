#include "../includes/entreprises.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../includes/counters.h"

Entreprise* entreprises = NULL;
int nb_entreprises = 0;
int cap_entreprises = 0;


#define CAPACITE_INITIALE 10

void initialiser_entreprises() {
    entreprises = malloc(CAPACITE_INITIALE * sizeof(Entreprise));
    cap_entreprises = CAPACITE_INITIALE;
    nb_entreprises = 0;
}

void ajouter_entreprise(const char* nom) {
    if (nb_entreprises >= cap_entreprises) {
        cap_entreprises++;
        Entreprise* new_tab = realloc(entreprises, cap_entreprises * sizeof(Entreprise));
        entreprises = new_tab;
    }

    entreprises[nb_entreprises].id = entreprise_id_counter++;
    entreprises[nb_entreprises].nom = strdup(nom);
    nb_entreprises++;
}

Entreprise* trouver_entreprise_par_id(int id) {
    for (int i = 0; i < nb_entreprises; i++) {
        if (entreprises[i].id == id) return &entreprises[i];
    }
    return NULL;
}

void supprimer_entreprise_de_table(int id) {
    for (int i = 0; i < nb_entreprises; i++) {
        if (entreprises[i].id == id) {
            free(entreprises[i].nom);
            for (int j = i; j < nb_entreprises - 1; j++) {
                entreprises[j] = entreprises[j + 1];
            }
            nb_entreprises--;
        }
    }
}

void liberer_entreprises() {
    for (int i = 0; i < nb_entreprises; i++) {
        free(entreprises[i].nom);
    }
    free(entreprises);
    entreprises = NULL;
    nb_entreprises = cap_entreprises = 0;
}


Entreprise* creer_entreprise(int id, const char* nom) {
    Entreprise* ent = malloc(sizeof(Entreprise));
    if (ent) {
        ent->id = id;
        ent->nom = strdup(nom);
    }
    return ent;
}

void afficher_entreprise(const Entreprise* ent) {
    if (ent) {
        printf("ID Entreprise: %d\n", ent->id);
        printf("Nom: %s\n", ent->nom);
    }
}

void modifier_entreprise(Entreprise* ent, const char* nouveau_nom) {
    if (ent) {
        free(ent->nom);
        ent->nom = strdup(nouveau_nom);
    }
}

void supprimer_entreprise(Entreprise* ent) {
    if (ent) {
        free(ent->nom);
        free(ent);
    }
}

// === FONCTIONS DE FICHIER ===

void enregistrer_entreprises_dans_fichier(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "w");
    if (!fichier) {
        perror("Erreur d'ouverture du fichier pour écriture");
        return;
    }

    for (int i = 0; i < nb_entreprises; i++) {
        fprintf(fichier, "%d;%s\n", entreprises[i].id, entreprises[i].nom);
    }

    fclose(fichier);
}

void charger_entreprises_depuis_fichier(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        perror("Erreur d'ouverture du fichier pour lecture");
        return;
    }

    initialiser_entreprises(); // Réinitialise la table

    int id;
    char nom[256];

    while (fscanf(fichier, "%d;%255[^\n]\n", &id, nom) == 2) {
        ajouter_entreprise(nom);
        entreprises[nb_entreprises - 1].id = id;

        if (id >= entreprise_id_counter) {
            entreprise_id_counter = id + 1;
        }
    }

    fclose(fichier);
}



