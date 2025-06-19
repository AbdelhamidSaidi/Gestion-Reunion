#ifndef NOTIFICATIONS_INVITATIONS_H
#define NOTIFICATIONS_INVITATIONS_H

#include "date_heure.h"
#include "employes.h"
#include "reunions.h"
#include "notifications.h"

typedef struct {
    Date_Heure date_envoi;
    char *statut;  // Envoyée, Lue, Échouée
    Employe *employe;
    Reunion *reunion;
    Notification *notification;
} NotificationInvitation;



extern NotificationInvitation* notifications_invitations;
extern int nb_notifications_invitations;
extern int cap_notifications_invitations;


void initialiser_notifications_invitations();
NotificationInvitation* ajouter_notification_invitation(Date_Heure date_envoi, const char* statut, Employe* employe, Reunion* reunion, Notification* notification);
void mettre_a_jour_statut_notification(NotificationInvitation* notif, const char* new_statut);
NotificationInvitation* trouver_notification_invitation_par_employe_et_reunion_et_notification(Employe* emp, Reunion* reun, Notification* notif);
void supprimer_notification_invitation_de_table(NotificationInvitation* notif);
void liberer_notifications_invitations();


NotificationInvitation* creer_notification_invitation(Date_Heure date_envoi, const char* statut, Employe* employe, Reunion* reunion, Notification* notification);
void afficher_notification_invitation(const NotificationInvitation* notif_inv);
void modifier_notification_invitation(NotificationInvitation* notif_inv, const Date_Heure* nouvelle_date, const char* nouveau_statut, Employe* nouvel_employe, Reunion* nouvelle_reunion, Notification* nouvelle_notification);
void supprimer_notification_invitation(NotificationInvitation* notif_inv);
void enregistrer_notifications_invitations_dans_fichier(const char* nom_fichier);
void charger_notifications_invitations_depuis_fichier(const char* nom_fichier);
#endif
