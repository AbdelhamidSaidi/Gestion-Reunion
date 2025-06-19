#ifndef COUNTERS_H
#define COUNTERS_H

extern int entreprise_id_counter;
extern int role_id_counter;
extern int salle_id_counter;
extern int employe_id_counter;

extern int reunion_id_counter;
extern int ordre_du_jour_id_counter;
extern int document_id_counter;
extern int reunion_document_id_counter;

extern int notification_id_counter;
extern int notification_reunion_id_counter;
extern int notification_invitation_id_counter;



void init_counters(void);


#endif 