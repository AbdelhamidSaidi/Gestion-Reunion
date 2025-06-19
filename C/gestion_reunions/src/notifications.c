#include "../includes/notifications.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../includes/counters.h"


Notification* notifications = NULL;
int nb_notifications = 0;
int cap_notifications = 0;

#define CAPACITE_INITIALE 10

void initialiser_notifications() {
    notifications = malloc(CAPACITE_INITIALE * sizeof(Notification));
    cap_notifications = CAPACITE_INITIALE;
    nb_notifications = 0;
}

void ajouter_notification(const char* type, const char* sujet, const char* message) {
    if (nb_notifications >= cap_notifications) {
        cap_notifications++; 
        Notification* new_tab = realloc(notifications, cap_notifications * sizeof(Notification));
        notifications = new_tab;
    }

    notifications[nb_notifications].id = notification_id_counter++;
    notifications[nb_notifications].type = strdup(type);
    notifications[nb_notifications].sujet = strdup(sujet);
    notifications[nb_notifications].message = strdup(message);
    
    nb_notifications++;
}

Notification* trouver_notification_par_id(int id) {
    for (int i = 0; i < nb_notifications; i++) {
        if (notifications[i].id == id) {
            return &notifications[i];
        }
    }
    return NULL;
}

void supprimer_notification_de_table(int id) {
    for (int i = 0; i < nb_notifications; i++) {
        if (notifications[i].id == id) {
            free(notifications[i].type);
            free(notifications[i].sujet);
            free(notifications[i].message);
            
            for (int j = i; j < nb_notifications - 1; j++) {
                notifications[j] = notifications[j + 1];
            }
            nb_notifications--;
            break;
        }
    }
}

void liberer_notifications() {
    for (int i = 0; i < nb_notifications; i++) {
        free(notifications[i].type);
        free(notifications[i].sujet);
        free(notifications[i].message);
    }
    free(notifications);
    notifications = NULL;
    nb_notifications = cap_notifications = 0;
}


Notification* creer_notification(int id, const char* type, const char* sujet, const char* message) {
    Notification* notif = malloc(sizeof(Notification));
    if (notif) {
        notif->id = id;
        notif->type = strdup(type);
        notif->sujet = strdup(sujet);
        notif->message = strdup(message);
    }
    return notif;
}

void modifier_notification(Notification* notif, const char* nouveau_type, const char* nouveau_sujet, const char* nouveau_message) {
    if (!notif) return;

    if (nouveau_type) {
    free(notif->type);
    notif->type = strdup(nouveau_type);
    }

    if (nouveau_sujet) {
    free(notif->sujet);
    notif->sujet = strdup(nouveau_sujet);
    }

    if (nouveau_message) {
    free(notif->message);
    notif->message = strdup(nouveau_message);
    }
}


void afficher_notification(const Notification* notif) {
    if (notif) {
        printf("Notification [ID: %d]\nType: %s\nSujet: %s\nMessage: %s\n", 
               notif->id, notif->type, notif->sujet, notif->message);
    }
}

void supprimer_notification(Notification* notif) {
    if (notif) {
        free(notif->type);
        free(notif->sujet);
        free(notif->message);
        free(notif);
    }
}
void  enregistrer_notifications_dans_fichier(const char* nom_fichier) {
    FILE* f = fopen(nom_fichier, "w");
    if (!f) {
        perror("Erreur ouverture fichier export");
        return;
    }

    for (int i = 0; i < nb_notifications; i++) {
        fprintf(f, "%d\n", notifications[i].id);
        fprintf(f, "%s\n", notifications[i].type);
        fprintf(f, "%s\n", notifications[i].sujet);
        fprintf(f, "%s\n\n", notifications[i].message);  // ligne vide comme séparateur
    }

    fclose(f);
}
void charger_notifications_depuis_fichier(const char* nom_fichier) {
    FILE* f = fopen(nom_fichier, "r");
    if (!f) {
        perror("Erreur ouverture fichier import");
        return;
    }

    // Libérer les notifications actuelles avant import
    liberer_notifications();
    initialiser_notifications();

    char buffer[1024];

    while (1) {
        int id;
        char type[256], sujet[256], message[1024];

        if (fscanf(f, "%d\n", &id) != 1) break;
        if (!fgets(type, sizeof(type), f)) break;
        if (!fgets(sujet, sizeof(sujet), f)) break;
        if (!fgets(message, sizeof(message), f)) break;

        // Supprimer le \n final de chaque chaîne
        type[strcspn(type, "\n")] = 0;
        sujet[strcspn(sujet, "\n")] = 0;
        message[strcspn(message, "\n")] = 0;

        // Ajouter la notification à la liste
        if (nb_notifications >= cap_notifications) {
            cap_notifications++;
            notifications = realloc(notifications, cap_notifications * sizeof(Notification));
        }
        notifications[nb_notifications].id = id;
        notifications[nb_notifications].type = strdup(type);
        notifications[nb_notifications].sujet = strdup(sujet);
        notifications[nb_notifications].message = strdup(message);

        if (id >= notification_id_counter)
            notification_id_counter = id + 1;

        nb_notifications++;

        // Lire la ligne vide séparatrice
        fgets(buffer, sizeof(buffer), f);
    }

    fclose(f);
}

