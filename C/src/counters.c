#include "../includes/counters.h"

// Initialize all counters to 1
int entreprise_id_counter = 1;
int role_id_counter = 1;
int salle_id_counter = 1;
int employe_id_counter = 1;

int reunion_id_counter = 1;
int ordre_du_jour_id_counter = 1;
int document_id_counter = 1;
int reunion_document_id_counter = 1;

int notification_id_counter = 1;
int notification_reunion_id_counter = 1;
int notification_invitation_id_counter = 1;

int invitation_id_counter = 1;

void init_counters() {
    
    entreprise_id_counter = 1;
    role_id_counter = 1;
    salle_id_counter = 1;
    employe_id_counter = 1;
    
    reunion_id_counter = 1;
    ordre_du_jour_id_counter = 1;
    document_id_counter = 1;
    reunion_document_id_counter = 1;
    
    notification_id_counter = 1;
    notification_reunion_id_counter = 1;
    notification_invitation_id_counter = 1;
    
    invitation_id_counter = 1;
}
