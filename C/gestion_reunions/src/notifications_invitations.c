#include "../includes/notifications_invitations.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


NotificationInvitation* notifications_invitations = NULL;
int nb_notifications_invitations = 0;
int cap_notifications_invitations = 0;

#define CAPACITE_INITIALE 10

void initialiser_notifications_invitations() {
    notifications_invitations = malloc(CAPACITE_INITIALE * sizeof(NotificationInvitation));
    cap_notifications_invitations = CAPACITE_INITIALE;
    nb_notifications_invitations = 0;
}

NotificationInvitation* ajouter_notification_invitation(Date_Heure date_envoi, const char* statut, Employe* employe, Reunion* reunion, Notification* notification) {
    
    if (nb_notifications_invitations >= cap_notifications_invitations) {
        cap_notifications_invitations++;
        NotificationInvitation* new_notif = realloc(notifications_invitations, cap_notifications_invitations * sizeof(NotificationInvitation));
        
        notifications_invitations = new_notif;
    }

    
    NotificationInvitation* new_notif = &notifications_invitations[nb_notifications_invitations];
    new_notif->date_envoi = date_envoi;
    new_notif->statut = strdup(statut);
    new_notif->employe = employe;          
    new_notif->reunion = reunion;          
    new_notif->notification = notification; 


    nb_notifications_invitations++;
    return new_notif;
}

void mettre_a_jour_statut_notification(NotificationInvitation* notif, const char* new_statut) {
    if (!notif || (strcmp(new_statut, "Lu") && strcmp(new_statut, "Envoyee") && strcmp(new_statut, "Echouee"))) return;
    
    free(notif->statut);
    notif->statut = strdup(new_statut);

}

NotificationInvitation* trouver_notification_par_employe_reunion_et_notification(Employe* emp, Reunion* reun, Notification* notif) 
{
    if (!emp || !reun || !notif) return NULL;
    
    for (int i = 0; i < nb_notifications_invitations; i++) {
        NotificationInvitation* current = &notifications_invitations[i];
        if (current->employe == emp && 
            current->reunion == reun &&
            current->notification == notif) {
            return current;
        }
    }
    return NULL;
}

void supprimer_notification_invitation_de_table(NotificationInvitation* notif) {
    if (!notif) return;
    
    for (int i = 0; i < nb_notifications_invitations; i++) {
        if (&notifications_invitations[i] == notif) {
            free(notifications_invitations[i].statut);
            
            for (int j = i; j < nb_notifications_invitations - 1; j++) {
                notifications_invitations[j] = notifications_invitations[j + 1];
            }
            nb_notifications_invitations--;
            return;
        }
    }
}

void liberer_notifications_invitations() {
    for (int i = 0; i < nb_notifications_invitations; i++) {
        free(notifications_invitations[i].statut);
    }
    free(notifications_invitations);
    notifications_invitations = NULL;
    nb_notifications_invitations = cap_notifications_invitations = 0;
}



NotificationInvitation* creer_notification_invitation(Date_Heure date_envoi, const char* statut, Employe* employe, Reunion* reunion, Notification* notification) {
    NotificationInvitation* notif_inv = malloc(sizeof(NotificationInvitation));
    if (notif_inv) {
        notif_inv->date_envoi = date_envoi;
        notif_inv->statut = strdup(statut);
        notif_inv->employe = employe;
        notif_inv->reunion = reunion;
        notif_inv->notification = notification;
    }
    return notif_inv;
}

void modifier_notification_invitation(NotificationInvitation* notif_inv, const Date_Heure* nouvelle_date, const char* nouveau_statut, Employe* nouvel_employe, Reunion* nouvelle_reunion, Notification* nouvelle_notification) {
    if (!notif_inv) return;

    if (nouvelle_date) {
    notif_inv->date_envoi = *nouvelle_date;
    }

    if (nouveau_statut) {
    free(notif_inv->statut);
    notif_inv->statut = strdup(nouveau_statut);
    }

    if (nouvel_employe) {
    notif_inv->employe = nouvel_employe;
    }

    if (nouvelle_reunion) {
    notif_inv->reunion = nouvelle_reunion;
    }

    if (nouvelle_notification) {
    notif_inv->notification = nouvelle_notification;
    }
}


void afficher_notification_invitation(const NotificationInvitation* notif_inv) {
    if (notif_inv) {
        printf("Notification d'invitation\nStatut: %s\n", notif_inv->statut);
        printf("Date envoi: ");
        afficher_date_heure(&notif_inv->date_envoi);
        printf("\n");
        if (notif_inv->employe) printf("Employe: %s %s\n", 
               notif_inv->employe->prenom, notif_inv->employe->nom);
    }
}

void supprimer_notification_invitation(NotificationInvitation* notif_inv) {
    if (notif_inv) {
        free(notif_inv->statut);
        free(notif_inv);
    }
}
void enregistrer_notifications_invitations_dans_fichier(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "w");
    if (!fichier) {
        perror("Erreur d'ouverture du fichier pour écriture");
        return;
    }

    for (int i = 0; i < nb_notifications_invitations; i++) {
        NotificationInvitation* n = &notifications_invitations[i];

        fprintf(fichier, "%04d-%02d-%02d;%02d:%02d;%s;%d;%d;%d\n",
                n->date_envoi.annee,
                n->date_envoi.mois,
                n->date_envoi.jour,
                n->date_envoi.hr,
                n->date_envoi.min,
                n->statut,
                n->employe ? n->employe->id : -1,
                n->reunion ? n->reunion->id : -1,
                n->notification ? n->notification->id : -1);
    }

    fclose(fichier);
}
void charger_notifications_invitations_depuis_fichier(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        perror("Erreur d'ouverture du fichier pour lecture");
        return;
    }

    initialiser_notifications_invitations();

    int a, m, j, h, min;
    char statut[100];
    int id_employe, id_reunion, id_notification;

    while (fscanf(fichier, "%d-%d-%d;%d:%d;%99[^;];%d;%d;%d\n",
                  &a, &m, &j, &h, &min,
                  statut, &id_employe, &id_reunion, &id_notification) == 9) {
        Date_Heure date = {a, m, j, h, min};

        Employe* e = trouver_employe_par_id(id_employe);
        Reunion* r = trouver_reunion_par_id(id_reunion);
        Notification* n = trouver_notification_par_id(id_notification); // ?? à implémenter si nécessaire

        ajouter_notification_invitation(date, statut, e, r, n);
    }

    fclose(fichier);
}

