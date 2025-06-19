#include "gestion_reunions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "../includes/counters.h"

#define TAILLE_BUFFER 256
#define MIN_ANNEE 2025
#define MAX_ANNEE 2125


void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

bool est_date_valide(int jour, int mois, int annee) {
    if (annee < MIN_ANNEE || annee > MAX_ANNEE) return false;
    if (mois < 1 || mois > 12) return false;
    
    int jours_par_mois[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    
    if (mois == 2 && (annee % 400 == 0 || (annee % 100 != 0 && annee % 4 == 0))) {
        jours_par_mois[1] = 29;
    }
    
    return jour >= 1 && jour <= jours_par_mois[mois-1];
}

bool est_heure_valide(int heure, int minutes) {
    return heure >= 0 && heure < 24 && minutes >= 0 && minutes < 60;
}

int saisir_entier(const char* prompt) {
    int valeur;
    while (1) {
        printf("%s: ", prompt);
        if (scanf("%d", &valeur) != 1) {//valeur numeric
            printf("Saisie invalide. Veuillez entrer un nombre.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        return valeur;
    }
}

char *saisir_chaine(const char* prompt, bool obligatoire) {
    char c;
    int n = 0;
    char *str = malloc(sizeof(char));
    if (!str) return NULL; 

    while (1) { 
        printf("%s: ", prompt);
        

        n = 0;
        if (str) free(str);
        str = malloc(sizeof(char));
        if (!str) return NULL;

        while ((c = getchar()) != '\n') {
            str = realloc(str, (n + 2)*sizeof(char));
            if (!str) return NULL;
            str[n++] = c;
        }
        str[n] = '\0';

        
        if (!obligatoire || (n > 0)) {
            break; 
        }
        printf("ce champ ne peut pas etre vide, ressayez!\n");
    }

    return str;
}

bool est_email_valide(const char* email) {
    return strchr(email, '@') != NULL && strchr(email, '.') != NULL;
}


Date_Heure saisir_date_heure() {
    Date_Heure dh;
    printf("\n=== Saisie Date/Heure ===\n");
    

    do {
        dh.annee = saisir_entier("Annee");
        if (dh.annee < MIN_ANNEE || dh.annee > MAX_ANNEE) {
            printf("L'annee doit etre entre %d et %d\n", MIN_ANNEE, MAX_ANNEE);
            continue;
        }

        dh.mois = saisir_entier("Mois");
        if (dh.mois < 1 || dh.mois > 12) {
            printf("Le mois doit etre entre 1 et 12\n");
            continue;
        }

        dh.jour = saisir_entier("Jour");
        if (!est_date_valide(dh.jour, dh.mois, dh.annee)) {
            printf("Jour invalide pour mois %d\n", dh.mois);
            continue;
        }
        
        break;
    } while (1);
    

    do {
        dh.hr = saisir_entier("Heure");
        if (dh.hr < 0 || dh.hr > 23) {
            printf("L'heure doit etre entre 0 et 23\n");
            continue;
        }
        
        dh.min = saisir_entier("Minutes");
        if (dh.min < 0 || dh.min > 59) {
            printf("Les minutes doivent etre entre 0 et 59\n");
            continue;
        }
        
        break;
    } while (1);
    
    return dh;
}

Entreprise* saisir_entreprise() {
    Entreprise* ent = malloc(sizeof(Entreprise));
    printf("\n=== Saisie Entreprise ===\n");
    
    // ent->id = entreprise_id_counter++;
    ent->nom = saisir_chaine("Nom Entreprise", true);
    
    return ent;
}

Role* saisir_role() {
    Role* role = malloc(sizeof(Role));
    printf("\n=== Saisie Role ===\n");
    
    // role->id = role_id_counter++;
    role->nom = saisir_chaine("Nom Role", true);
    
    return role;
}

Salle* saisir_salle() {
    Salle* salle = malloc(sizeof(Salle));
    printf("\n=== Saisie Salle ===\n");
    
    // salle->id = salle_id_counter++;
    salle->nom = saisir_chaine("Nom Salle", true);
    
    salle->capacite = saisir_entier("Capacite");
    while (salle->capacite <= 0) {
        printf("La capacite doit etre positive\n");
        salle->capacite = saisir_entier("Capacite");
    }
    
    char* disp = saisir_chaine("Disponible (O/N)", true);
    while (strlen(disp) != 1 || (tolower(disp[0]) != 'o' && tolower(disp[0] != 'n'))) {
        printf("Option invalid!\n");
        disp = saisir_chaine("Disponible (O/N)", true);
    }

    salle->disponible = (tolower(disp[0]) == 'o');//retourne true pour o et false pour N
    free(disp);
    
    return salle;
}

Employe* saisir_employe() {
    Employe* emp = malloc(sizeof(Employe));
    printf("\n=== Saisie Employe ===\n");
    
    // emp->id = employe_id_counter++;
    emp->cin = saisir_chaine("CIN", true);
    emp->nom = saisir_chaine("Nom", true);
    emp->prenom = saisir_chaine("Prenom", true);
    
    while (1) {
        emp->email = saisir_chaine("Email", true);
        if (est_email_valide(emp->email)) break;
        printf("Email invalide (doit contenir @ et .)\n");
        free(emp->email);
    }
    
    while (1) {
        emp->telephone = saisir_chaine("Telephone", true);
        bool valide = strlen(emp->telephone) >= 8;
        for (int i = 0; valide && i < strlen(emp->telephone); i++) {
            if (!isdigit(emp->telephone[i])) valide = false;
        }
        if (valide) break;
        printf("Telephone invalide (8+ chiffres)\n");
        free(emp->telephone);
    }
    
    printf("\nEntreprise:\n");
    emp->entreprise = saisir_entreprise();
    
    printf("\nRole:\n");
    emp->role = saisir_role();
    
    return emp;
}

Document* saisir_document() {
    Document* doc = malloc(sizeof(Document));
    printf("\n=== Saisie Document ===\n");
    
    // doc->id = document_id_counter++;
    doc->nom = saisir_chaine("Nom Document", true);
//Compte Rendu, Ordre du jour, Annexe, Convocation, suivi
    doc->type = saisir_chaine("Type Document (Compte rendu / Ordre du jour / Annexe/ Convocation / Suivi)", true);
    while(strcmp(doc->type, "Compte rendu") && strcmp(doc->type, "Ordre du jour") && strcmp(doc->type, "Annexe") && strcmp(doc->type, "Convocation") && strcmp(doc->type, "Suivi")) {
        
        free(doc->type);
        printf("Veuillez saisir les types affiches!\n");
        doc->type = saisir_chaine("Type Document (Compte rendu / Ordre du jour / Annexe/ Convocation / Suivi)", true);

    }
    
    
    while (1) {
        doc->extension_fichier = saisir_chaine("Extension (.pdf,.docx)", true);
        if (doc->extension_fichier[0] == '.' && (!strcmp(doc->extension_fichier, ".pdf") || !strcmp(doc->extension_fichier, ".docx"))) break;
        printf("Extension saisie invalid!\n");
        free(doc->extension_fichier);
    }
    
    doc->lien = saisir_chaine("Lien/Chemin", true);
    
    printf("\nDate Creation:\n");
    doc->date_creation = saisir_date_heure();
    
    return doc;
}

Reunion* saisir_reunion() {
    Reunion* reunion = malloc(sizeof(Reunion));
    int id_saisie;
    printf("\n=== Saisie Reunion ===\n");
    
    // reunion->id = reunion_id_counter++;
    
    printf("\nDate/Heure Debut:\n");
    reunion->date_debut = saisir_date_heure();
    
    reunion->duree = saisir_entier("Duree (minutes)");
    while (reunion->duree <= 0) {
        printf("La duree doit etre positive\n");
        reunion->duree = saisir_entier("Duree (minutes)");
    }

    
    while(1) {
        reunion->type = saisir_chaine("Type Reunion (Presentiel/En ligne/Mixte)", true);
        if(!strcmp(reunion->type, "Presentiel") || !strcmp(reunion->type, "En ligne") || !strcmp(reunion->type, "Mixte")) break;
        printf("Veuillez saisir un des type affiches!\n");
        free(reunion->type);
    } 
    
    printf("\nOrganisateur (ID):\n");
    while (1) {
        id_saisie = saisir_entier("ID Employe");
        reunion->organisateur = trouver_employe_par_id(id_saisie);
        if (reunion->organisateur != NULL) break;
        printf("Employe avec ID %d non trouve\n", id_saisie);
    }
    //MARK:Was HEREAAAAAAAAAAA
        reunion->lien = NULL;
        reunion->salle = NULL;   
        reunion->suivante = NULL;
    
    return reunion;
}

Notification* saisir_notification() {
    Notification* notif = malloc(sizeof(Notification));
    printf("\n=== Saisie Notification ===\n");
    
    // notif->id = notification_id_counter++;
    
    while (1) {
        notif->type = saisir_chaine("Type (Rappel/Alerte/Annulation/Invitation)", true);
        if (strcmp(notif->type, "Rappel") == 0 || 
            strcmp(notif->type, "Alerte") == 0 ||
            strcmp(notif->type, "Annulation") == 0 ||
            strcmp(notif->type, "Invitation") == 0) break;
        printf("Type doit etre: Rappel, Alerte, Annulation ou Invitation\n");
        free(notif->type);
    }
    
    notif->sujet = saisir_chaine("Sujet", true);
    notif->message = saisir_chaine("Message", true);
    
    return notif;
}

Invitation* saisir_invitation() {
    Invitation* inv = malloc(sizeof(Invitation));
    int invite_id;
    int reuninon_id;
    printf("\n=== Saisie Invitation ===\n");
    
    while (1) {
        inv->disponibilite = saisir_chaine("Disponibilite (Disponible/Indisponible)", true);
        if (strcmp(inv->disponibilite, "Disponible") == 0 || 
            strcmp(inv->disponibilite, "Indisponible") == 0) break;
        printf("Doit etre 'Disponible' ou 'Indisponible'\n");
        free(inv->disponibilite);
    }
    
    while (1) {
        inv->presence = saisir_chaine("Presence (Present/Absent/En attente)", true);
        if (strcmp(inv->presence, "Present") == 0 || 
            strcmp(inv->presence, "Absent") == 0 ||
            strcmp(inv->presence, "En attente") == 0) break;
        printf("Doit etre 'Present', 'Absent' ou 'En attente'\n");
        free(inv->presence);
    }
    
    char* type = saisir_chaine("Type (P=Presentiel, L=En ligne)", true);

    while(1) {
        if(strlen(type) == 1 && (tolower(type[0]) == 'p' || tolower(type[0] == 'l'))) break;
        printf("Veuillez saisir type affiche!\n");
        free(type);
        type = saisir_chaine("Type (P=Presentiel, L=En ligne)", true);
    }
    
    inv->type = (tolower(type[0]) == 'l');
    free(type);

    printf("\nInvite:\n");

    invite_id = saisir_entier("Saisir ID d invite");
    inv->invite = trouver_employe_par_id(invite_id);

    while(1) {
        
        if(inv->invite) {
            printf("Employee trouve!\n");
            break;
        }
        printf("Employe avec ID %d non trouve\n", invite_id);
        invite_id = saisir_entier("Saisir ID d invite");
        inv->invite = trouver_employe_par_id(invite_id);
    }


    printf("\nReunion:\n");
    reuninon_id = saisir_entier("Saisir ID de reunion");
    inv->reunion = trouver_reunion_par_id(reuninon_id);

    while(1) {
        if(inv->reunion) {
            printf("Reunion trouve!\n");
            break;
        }
        printf("Reunion avec ID %d non trouve\n", reuninon_id);
        reuninon_id = saisir_entier("Saisir ID de reunion");
        inv->reunion = trouver_reunion_par_id(reuninon_id);
    }


    return inv;
}

NotificationInvitation* saisir_notification_invitation() {
    NotificationInvitation* ni = malloc(sizeof(NotificationInvitation));
    int id_saisie;
    printf("\n=== Saisie Notification Invitation ===\n");
    
    printf("\nDate Envoi:\n");
    ni->date_envoi = saisir_date_heure();
    
    while (1) {
        ni->statut = saisir_chaine("Statut (Envoyee/Lue/Echouee)", true);
        if (strcmp(ni->statut, "Envoyee") == 0 || 
            strcmp(ni->statut, "Lue") == 0 ||
            strcmp(ni->statut, "Echouee") == 0) break;
        printf("Statut invalide\n");
        free(ni->statut);
    }
    
    printf("\nEmploye (ID):\n");
    while (1) {
        id_saisie = saisir_entier("ID Employe");
        if ((ni->employe = trouver_employe_par_id(id_saisie)) != NULL) break;
        printf("Employe avec ID %d non trouve\n", id_saisie);
    }
    
    
    printf("\nReunion (ID):\n");
    while (1) {
        id_saisie = saisir_entier("ID Reunion");
        if ((ni->reunion = trouver_reunion_par_id(id_saisie)) != NULL) break;
        printf("Reunion avec ID %d non trouvee\n", id_saisie);
    }
    
    
    printf("\nNotification (ID):\n");
    while (1) {
        id_saisie = saisir_entier("ID Notification");
        if ((ni->notification = trouver_notification_par_id(id_saisie)) != NULL) break;
        printf("Notification avec ID %d non trouvee\n", id_saisie);
    }
    
    return ni;
}

OrdreDuJour* saisir_ordre_du_jour() {
    OrdreDuJour* ordre = malloc(sizeof(OrdreDuJour));
    printf("\n=== Saisie Ordre du Jour ===\n");
    
    // ordre->id = ordre_du_jour_id_counter++;
    ordre->sujet = saisir_chaine("Sujet", true);
    
    printf("\nPresentateur:\n");
    ordre->presentateur = saisir_employe();
    
    printf("\nReunion:\n");
    ordre->reunion = saisir_reunion();
    
    return ordre;
}

ReunionDocument* saisir_reunion_document() {
    ReunionDocument* rd = malloc(sizeof(ReunionDocument));
    printf("\n=== Saisie Lien Reunion-Document ===\n");
    
    printf("\nReunion:\n");
    rd->reunion = saisir_reunion();
    
    printf("\nDocument:\n");
    rd->document = saisir_document();
    
    return rd;
}