#include "../includes/salles.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../includes/counters.h"
#include "../includes/gestion_reunions.h"



Salle* salles = NULL;
int nb_salles = 0;
int cap_salles = 0;

#define CAPACITE_INITIALE 10

void initialiser_salles() {
    salles = malloc(CAPACITE_INITIALE * sizeof(Salle));
    cap_salles = CAPACITE_INITIALE;
    nb_salles = 0;
}

void ajouter_salle(const char* nom, int capacite, bool disponible) {
    if (nb_salles >= cap_salles) {
        cap_salles++;
        Salle* new_tab = realloc(salles, cap_salles * sizeof(Salle));
        salles = new_tab;
    }

    salles[nb_salles].id = salle_id_counter++;
    salles[nb_salles].nom = strdup(nom);
    salles[nb_salles].capacite = capacite;
    salles[nb_salles].disponible = disponible;
    nb_salles++;
}

Salle* trouver_salle_par_id(int id) {
    for (int i = 0; i < nb_salles; i++) {
        if (salles[i].id == id) 
            return &salles[i];
    }
    return NULL;
}

void supprimer_salle_de_table(int id) {
    for (int i = 0; i < nb_salles; i++) {
        if (salles[i].id == id) {
            free(salles[i].nom); 
            for (int j = i; j < nb_salles - 1; j++) {
                salles[j] = salles[j + 1];
            }
            nb_salles--;
            break; 
        }
    }
}

void liberer_salles() {
    for (int i = 0; i < nb_salles; i++) {
        free(salles[i].nom);
    }
    free(salles); 
    salles = NULL;
    nb_salles = cap_salles = 0;
}


static bool salle_disponible(const Salle *salle, const Reunion* reu) {
    if (!salle || !reu) return false;


    int nbr_presentiel = compter_invites_presentiel_par_reunion_id(reu->id);
    if (salle->capacite < nbr_presentiel) return false;
    

    Date_Heure fin_existante, fin_nouvelle;
    
    for (int i = 0; i < nb_reunions; i++) {
        if (reunions[i].salle && reunions[i].salle->id == salle->id && reunions[i].id != reu->id) {
            fin_existante = ajouter_date_duree(reunions[i].date_debut, reunions[i].duree);
            fin_nouvelle = ajouter_date_duree(reu->date_debut, reu->duree);
            
            
            bool debuts_avant_fin = comparer_date_heure(&reu->date_debut, &fin_existante) < 0;
            bool fin_apres_debut = comparer_date_heure(&fin_nouvelle, &reunions[i].date_debut) > 0;
            
            if (debuts_avant_fin && fin_apres_debut) {
                return false;
            }
        }
    }
    return true;
}


Salle* reserver_salle(int id_reunion) {
    Reunion* reu = trouver_reunion_par_id(id_reunion);
    if (!reu) {
        printf("Reunion introuvable avec l'ID %d\n", id_reunion);
        return NULL;
    }
    

    for (int i = 0; i < nb_salles; i++) {
        if (salles[i].disponible && salle_disponible(&salles[i], reu)) {
    
            reu->salle = &salles[i];
            printf("Salle %s reservee pour la reunion %d\n", salles[i].nom, id_reunion);
            
            return reu->salle;
        }
    }
    
    printf("Aucune salle disponible pour la reunion %d\n", id_reunion);
    return NULL;
}




Salle* creer_salle(int id, const char* nom, int capacite, bool disponible) {
    Salle* salle = malloc(sizeof(Salle));
    if (salle) {
        salle->id = id;
        salle->nom = strdup(nom);
        salle->capacite = capacite;
        salle->disponible = disponible;
    }
    return salle;
}

void modifier_salle(Salle* salle, const char* nouveau_nom, int nouvelle_capacite, bool nouvelle_disponibilite) {
    if (!salle) return;

    if (nouveau_nom) {
        free(salle->nom);
        salle->nom = strdup(nouveau_nom);
    }

    salle->capacite = nouvelle_capacite;
    salle->disponible = nouvelle_disponibilite;
}

void afficher_salle(const Salle* salle) {
    if (salle) {
        printf("Salle [ID: %d] Nom: %s\nCapacite: %d\nDisponible: %s\n",
               salle->id, salle->nom, salle->capacite, 
               (salle->disponible) ? "Oui" : "Non");
    }
}

void supprimer_salle(Salle* salle) {
    if (salle) {
        free(salle->nom);
        free(salle);
    }
}
void enregistrer_salles_dans_fichier(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "w");
    if (!fichier) {
        perror("Erreur d'ouverture du fichier pour �criture");
        return;
    }

    for (int i = 0; i < nb_salles; i++) {
        fprintf(fichier, "%d;%s;%d;%d\n",
                salles[i].id,
                salles[i].nom,
                salles[i].capacite,
                salles[i].disponible ? 1 : 0);
    }

    fclose(fichier);
}

void charger_salles_depuis_fichier(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        perror("Erreur d'ouverture du fichier pour lecture");
        return;
    }

    initialiser_salles(); // vide et pr�pare la m�moire

    int id, capacite, disponible_int;
    char nom[256];

    while (fscanf(fichier, "%d;%255[^;];%d;%d\n", &id, nom, &capacite, &disponible_int) == 4) {
        ajouter_salle(nom, capacite, disponible_int);
        salles[nb_salles - 1].id = id;

        if (id >= salle_id_counter) {
            salle_id_counter = id + 1;
        }
    }

    fclose(fichier);
}



