#ifndef RECHERCHE_H
#define RECHERCHE_H

#include "gestion_reunions.h"

Entreprise* trouver_entreprise_par_id(int id);
Role* trouver_role_par_id(int id);
Salle* trouver_salle_par_id(int id);
Employe* trouver_employe_par_id(int id);


Reunion* trouver_reunion_par_id(int id);
OrdreDuJour* trouver_ordre_par_id(int id);
Document* trouver_document_par_id(int id);
ReunionDocument* trouver_reunion_document_par_id(int id);


Notification* trouver_notification_par_id(int id);
NotificationInvitation* trouver_notification_invitation_par_id(int id);

Invitation* trouver_invitation_par_id(int id);

#endif