#ifndef DATE_HEURE_H
#define DATE_HEURE_H

#include <stdbool.h>

typedef struct {
    int annee, mois, jour, hr, min;
} Date_Heure;

Date_Heure* creer_date_heure(int annee, int mois, int jour, int hr, int min);
void afficher_date_heure(const Date_Heure* dh);
void modifier_date_heure(Date_Heure* dh, int annee, int mois, int jour, int hr, int min);
void supprimer_date_heure(Date_Heure* dh);
int comparer_date_heure(const Date_Heure* dh1, const Date_Heure* dh2);
Date_Heure ajouter_date_duree(Date_Heure date, int minutes);
bool est_annee_bissextile(int annee);

int jours_dans_mois(int mois, int annee);
#endif


