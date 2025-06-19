#ifndef SAISIE_H
#define SAISIE_H

#include "gestion_reunions.h"

// Prototypes
Date_Heure saisir_date_heure();
Entreprise* saisir_entreprise();
Role* saisir_role();
Salle* saisir_salle();
Employe* saisir_employe();
Reunion* saisir_reunion();
Document* saisir_document();
Notification* saisir_notification();
Invitation* saisir_invitation();
NotificationInvitation* saisir_notification_invitation();
OrdreDuJour* saisir_ordre_du_jour();
ReunionDocument* saisir_reunion_document();


void clear_input_buffer();
bool est_date_valide(int jour, int mois, int annee);
bool est_heure_valide(int heure, int minutes);
int saisir_entier(const char* prompt);
char *saisir_chaine(const char* prompt, bool obligatoire);
bool est_email_valide(const char* email);

#endif