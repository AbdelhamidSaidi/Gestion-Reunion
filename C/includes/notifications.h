#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

typedef struct {
    int id;
    char *type;  // Rappel, Alerte, Annulation, Invitation
    char *sujet;
    char *message;
} Notification;


extern Notification* notifications;
extern int nb_notifications;
extern int cap_notifications;


void initialiser_notifications();
void ajouter_notification(const char* type, const char* sujet, const char* message);
Notification* trouver_notification_par_id(int id);
void supprimer_notification_de_table(int id);
void liberer_notifications();

Notification* creer_notification(int id, const char* type, const char* sujet, const char* message);
void afficher_notification(const Notification* notif);
void modifier_notification(Notification* notif, const char* nouveau_type, const char* nouveau_sujet, const char* nouveau_message);
void supprimer_notification(Notification* notif);
void  enregistrer_notifications_dans_fichier(const char* nom_fichier);
void charger_notifications_depuis_fichier(const char* nom_fichier);

#endif
