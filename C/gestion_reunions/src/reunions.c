#include "../includes/reunions.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../includes/counters.h"
#include "../includes/gestion_reunions.h"

Reunion* reunions = NULL;
int nb_reunions = 0;
int cap_reunions = 0;



#define CAPACITE_INITIALE 10

void initialiser_reunions() {
    reunions = malloc(CAPACITE_INITIALE * sizeof(Reunion));
    cap_reunions = CAPACITE_INITIALE;
    nb_reunions = 0;
}

int compter_invites_par_reunion_id(int reunion_id) {
    int count = 0;
    
    if (trouver_reunion_par_id(reunion_id) == NULL) {
        printf("Erreur : Réunion ID %d introuvable\n", reunion_id);
        return 0;
    }

    for (int i = 0; i < nb_invitations; i++) {
        if (invitations[i].reunion->id == reunion_id) { 
            count++;
        }
    }
    
    return count;
}

int compter_invites_presentiel_par_reunion_id(int reunion_id) {
    int count = 0;
    
    if (trouver_reunion_par_id(reunion_id) == NULL) {
        printf("Erreur : Réunion ID %d introuvable\n", reunion_id);
        return 0;
    }

    for (int i = 0; i < nb_invitations; i++) {
        if (invitations[i].reunion->id == reunion_id && invitations[i].type == 0/*0 pour presentiel et 1 pour en ligne*/) { 
            count++;
        }
    }
    
    return count;
}

Reunion* ajouter_reunion(Date_Heure date_debut, int duree, const char* lien,
                        const char* type, Employe* organisateur, Salle* salle) {

    if (nb_reunions >= cap_reunions) {
        cap_reunions++;
        Reunion* new_tab = realloc(reunions, cap_reunions * sizeof(Reunion));
        reunions = new_tab;
    }


    Reunion* nouvelle = &reunions[nb_reunions];
    nouvelle->id = reunion_id_counter++;
    nouvelle->date_debut = date_debut;
    nouvelle->duree = duree;
    if(lien) nouvelle->lien = strdup(lien);  
    else nouvelle->lien = NULL;
    nouvelle->type = strdup(type);
    nouvelle->organisateur = organisateur;
    nouvelle->salle = salle;
    nouvelle->suivante = NULL;  // No sessions initially


    nb_reunions++;
    return nouvelle;
}

void ajouter_session_reunion(Reunion* reunion_principale, Date_Heure nouvelle_date) {
    if (!reunion_principale) return;


    Reunion* current = reunion_principale;
    while (current->suivante != NULL) {
        current = current->suivante;
    }

    current->suivante = malloc(sizeof(Reunion));


    current->suivante->id = reunion_principale->id;  //meme id 
    current->suivante->date_debut = nouvelle_date;
    current->suivante->duree = reunion_principale->duree;
    current->suivante->lien = (reunion_principale->lien)? strdup(reunion_principale->lien): NULL;
    current->suivante->type = strdup(reunion_principale->type);
    current->suivante->organisateur = reunion_principale->organisateur;
    current->suivante->salle = reunion_principale->salle;
    current->suivante->suivante = NULL;

}

Reunion* trouver_reunion_par_id(int id) {
    for (int i = 0; i < nb_reunions; i++) {
        Reunion* current = &reunions[i];
        while (current != NULL) {
            if (current->id == id) {
                return current;
            }
            current = current->suivante;
        }
    }
    return NULL;
}

void supprimer_reunion_et_sessions(int id) {
    for (int i = 0; i < nb_reunions; i++) {
        if (reunions[i].id == id) {
            Reunion* current = reunions[i].suivante;
            while (current != NULL) {
                Reunion* next = current->suivante;
                free(current->lien);
                free(current->type);
                free(current);
                current = next;
            }

            free(reunions[i].lien);
            free(reunions[i].type);

            for (int j = i; j < nb_reunions - 1; j++) {
                reunions[j] = reunions[j + 1];
            }
            nb_reunions--;
            break;
        }
    }
}

void liberer_reunions() {
    for (int i = 0; i < nb_reunions; i++) {

        Reunion* current = reunions[i].suivante;
        while (current != NULL) {
            Reunion* next = current->suivante;
            free(current->lien);
            free(current->type);
            free(current);
            current = next;
        }

        free(reunions[i].lien);
        free(reunions[i].type);
    }
    free(reunions);
    reunions = NULL;
    nb_reunions = cap_reunions = 0;
}




Reunion* creer_reunion(int id, Date_Heure date_debut, int duree, const char* lien, const char* type,Employe* organisateur, Salle* salle) {Reunion* reunion = malloc(sizeof(Reunion));
    if (reunion) {
        reunion->id = id;
        reunion->date_debut = date_debut;
        reunion->duree = duree;
        reunion->lien = strdup(lien);
        reunion->type = strdup(type);
        reunion->organisateur = organisateur;
        reunion->salle = salle;
        reunion->suivante = NULL;
    }
    return reunion;
}

void modifier_reunion(Reunion* reunion, const Date_Heure* nouvelle_date, int nouvelle_duree, const char* nouveau_lien, const char* nouveau_type, Employe* nouvel_organisateur, Salle* nouvelle_salle) {
    if (!reunion) return;

    if (nouvelle_date) {
    reunion->date_debut = *nouvelle_date;
    }

    reunion->duree = nouvelle_duree;

    if (nouveau_lien) {
    free(reunion->lien);
    reunion->lien = strdup(nouveau_lien);
    }

    if (nouveau_type) {
    free(reunion->type);
    reunion->type = strdup(nouveau_type);
    }

    if (nouvel_organisateur) {
    reunion->organisateur = nouvel_organisateur;
    }

    if (nouvelle_salle) {
    reunion->salle = nouvelle_salle;
    }
}
void enregistrer_reunions_dans_fichier(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "w");
    if (!fichier) {
        perror("Erreur d'ouverture du fichier pour �criture");
        return;
    }

    for (int i = 0; i < nb_reunions; i++) {
        Reunion* current = &reunions[i];
        while (current != NULL) {
            fprintf(fichier, "%d;%d-%d-%d;%d:%d;%d;%s;%s;%d;%d\n",
                    current->id,
                    current->date_debut.annee, current->date_debut.mois, current->date_debut.jour,
                    current->date_debut.hr, current->date_debut.min,
                    current->duree,
                    current->type,
                    current->lien,
                    current->organisateur ? current->organisateur->id : -1,
                    current->salle ? current->salle->id : -1);
            current = current->suivante;
        }
    }

    fclose(fichier);
}
void charger_reunions_depuis_fichier(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        perror("Erreur d'ouverture du fichier pour lecture");
        return;
    }

    initialiser_reunions(); // r�initialise

    int id, annee, mois, jour, heure, minute, duree;
    char type[100], lien[256];
    int id_org, id_salle;

    while (fscanf(fichier, "%d;%d-%d-%d;%d:%d;%d;%99[^;];%255[^;];%d;%d\n",
                  &id, &annee, &mois, &jour, &heure, &minute, &duree,
                  type, lien, &id_org, &id_salle) == 11) {

        Date_Heure date;
        date.annee = annee;
        date.mois = mois;
        date.jour = jour;
        date.hr = heure;
        date.min = minute;

        Employe* org = trouver_employe_par_id(id_org);
        Salle* salle = trouver_salle_par_id(id_salle);

        Reunion* r = ajouter_reunion(date, duree, lien, type, org, salle);
        r->id = id;

        if (id >= reunion_id_counter) {
            reunion_id_counter = id + 1;
        }
    }

    fclose(fichier);
}



void afficher_reunion(const Reunion* reunion) {
    if (reunion) {
        printf("Reunion [ID: %d]\nType: %s\nDuree: %d min\n", 
               reunion->id, reunion->type, reunion->duree);
        printf("Date: ");
        afficher_date_heure(&reunion->date_debut);
        printf("\nLien: %s\n", reunion->lien);
        if (reunion->organisateur) printf("Organisateur: %s %s\n", 
               reunion->organisateur->prenom, reunion->organisateur->nom);
        if (reunion->salle) printf("Salle: %s\n", reunion->salle->nom);
    }
}

void supprimer_reunion(Reunion* reunion) {
    if (reunion) {
        free(reunion->lien);
        free(reunion->type);
        free(reunion);
    }
}

void supprimer_liste_reunions(Reunion** tete) {//reunion qui sont chaine sont des seances
    Reunion* courant = *tete;
    while (courant) {
        Reunion* temp = courant;
        courant = courant->suivante;
        supprimer_reunion(temp);
    }
    *tete = NULL;
}
