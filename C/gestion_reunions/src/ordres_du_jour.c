#include "../includes/ordres_du_jour.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../includes/counters.h"

OrdreDuJour* ordres_du_jour = NULL;
int nb_ordres_du_jour = 0;
int cap_ordres_du_jour = 0;

#define CAPACITE_INITIALE 10

void initialiser_ordres_du_jour() {
    ordres_du_jour = malloc(CAPACITE_INITIALE * sizeof(OrdreDuJour));
    cap_ordres_du_jour = CAPACITE_INITIALE;
    nb_ordres_du_jour = 0;
}

OrdreDuJour* ajouter_ordre_du_jour(const char* sujet, Employe* presentateur, Reunion* reunion) {
   
    if (nb_ordres_du_jour >= cap_ordres_du_jour) {
        cap_ordres_du_jour++;
        OrdreDuJour* new_tab = realloc(ordres_du_jour, cap_ordres_du_jour * sizeof(OrdreDuJour));
        
        ordres_du_jour = new_tab;
    }

    // Set fields
    ordres_du_jour[nb_ordres_du_jour].id = ordre_du_jour_id_counter++;
    ordres_du_jour[nb_ordres_du_jour].sujet = strdup(sujet);
    ordres_du_jour[nb_ordres_du_jour].presentateur = presentateur;
    ordres_du_jour[nb_ordres_du_jour].reunion = reunion;

    return &ordres_du_jour[nb_ordres_du_jour++];
}

OrdreDuJour* trouver_ordre_par_id(int id) {
    for (int i = 0; i < nb_ordres_du_jour; i++) {
        if (ordres_du_jour[i].id == id) {
            return &ordres_du_jour[i];
        }
    }
    return NULL;
}

OrdreDuJour* trouver_ordres_par_reunion(Reunion* reunion) {
    for (int i = 0; i < nb_ordres_du_jour; i++) {
        if (ordres_du_jour[i].reunion == reunion) {
            return &ordres_du_jour[i]; 
        }
    }
    return NULL;
}

OrdreDuJour* trouver_ordres_par_presentateur(Employe* presentateur) {
    for (int i = 0; i < nb_ordres_du_jour; i++) {
        if (ordres_du_jour[i].presentateur == presentateur) {
            return &ordres_du_jour[i]; 
        }
    }
    return NULL;
}

void supprimer_ordre_du_jour_de_table(int id) {
    for (int i = 0; i < nb_ordres_du_jour; i++) {
        if (ordres_du_jour[i].id == id) {
            free(ordres_du_jour[i].sujet);
 
            for (int j = i; j < nb_ordres_du_jour - 1; j++) {
                ordres_du_jour[j] = ordres_du_jour[j + 1];
            }
            nb_ordres_du_jour--;
            return;
        }
    }
}

void liberer_ordres_du_jour() {
    for (int i = 0; i < nb_ordres_du_jour; i++) {
        free(ordres_du_jour[i].sujet);
    }
    free(ordres_du_jour);
    ordres_du_jour = NULL;
    nb_ordres_du_jour = cap_ordres_du_jour = 0;
}





OrdreDuJour* creer_ordre_du_jour(int id, const char* sujet,  Employe* presentateur, Reunion* reunion) {
    OrdreDuJour* ordre = malloc(sizeof(OrdreDuJour));
    if (ordre) {
        ordre->id = id;
        ordre->sujet = strdup(sujet);
        ordre->presentateur = presentateur;
        ordre->reunion = reunion;
    }
    return ordre;
}

void modifier_ordre_du_jour(OrdreDuJour* ordre, const char* nouveau_sujet, Employe* nouveau_presentateur, Reunion* nouvelle_reunion) {
    if (!ordre) return;

    // Modifier le sujet si fourni
    if (nouveau_sujet) {
    free(ordre->sujet);  // LibÃ©rer l'ancien sujet
    ordre->sujet = strdup(nouveau_sujet);  // Allouer et copier le nouveau
    }

    if (nouveau_presentateur) {
    ordre->presentateur = nouveau_presentateur;
    }

    if (nouvelle_reunion) {
    ordre->reunion = nouvelle_reunion;
    }
}

void afficher_ordre_du_jour(const OrdreDuJour* ordre) {
    if (ordre) {
        printf("Ordre du jour [ID: %d]\nSujet: %s\n", ordre->id, ordre->sujet);
        if (ordre->presentateur) printf("Presentateur: %s %s\n", 
               ordre->presentateur->prenom, ordre->presentateur->nom);
    }
}



void supprimer_ordre_du_jour(OrdreDuJour* ordre) {
    if (ordre) {
        free(ordre->sujet);
        free(ordre);
    }
}
void enregistrer_ordres_du_jour_dans_fichier(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "w");
    if (!fichier) {
        perror("Erreur d'ouverture du fichier pour écriture");
        return;
    }

    for (int i = 0; i < nb_ordres_du_jour; i++) {
        fprintf(fichier, "%d;%s;%d;%d\n",
                ordres_du_jour[i].id,
                ordres_du_jour[i].sujet,
                ordres_du_jour[i].presentateur ? ordres_du_jour[i].presentateur->id : -1,
                ordres_du_jour[i].reunion ? ordres_du_jour[i].reunion->id : -1);
    }

    fclose(fichier);
}


void charger_ordres_du_jour_depuis_fichier(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        perror("Erreur d'ouverture du fichier pour lecture");
        return;
    }

    initialiser_ordres_du_jour();

    int id, id_presentateur, id_reunion;
    char sujet[256];

    while (fscanf(fichier, "%d;%255[^;];%d;%d\n", &id, sujet, &id_presentateur, &id_reunion) == 4) {
        Employe* presentateur = trouver_employe_par_id(id_presentateur);
        Reunion* reunion = trouver_reunion_par_id(id_reunion);

        OrdreDuJour* o = ajouter_ordre_du_jour(sujet, presentateur, reunion);
        o->id = id;

        if (id >= ordre_du_jour_id_counter) {
            ordre_du_jour_id_counter = id + 1;
        }
    }

    fclose(fichier);
}

