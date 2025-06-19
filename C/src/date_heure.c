#include "../includes/date_heure.h"
#include <stdlib.h>
#include <stdio.h>


Date_Heure* creer_date_heure(int annee, int mois, int jour, int hr, int min) {
    Date_Heure* dh = malloc(sizeof(Date_Heure));
    if (dh) {
        dh->annee = annee;
        dh->mois = mois;
        dh->jour = jour;
        dh->hr = hr;
        dh->min = min;
    }
    return dh;
}

static const int jours_par_mois[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool est_annee_bissextile(int annee) {
    return (annee % 400 == 0) || ((annee % 100 != 0) && (annee % 4 == 0));
}

int jours_dans_mois(int mois, int annee) {
    return (mois == 2 && est_annee_bissextile(annee)) ? 29 : jours_par_mois[mois-1];
}


Date_Heure ajouter_date_duree(Date_Heure date, int minutes) {
    
    date.min += minutes;
    

    while (date.min >= 60) {
        date.min -= 60;
        date.hr++;
    }
    while (date.hr >= 24) {
        date.hr -= 24;
        date.jour++;
    }
    while (date.jour > jours_dans_mois(date.mois, date.annee)) {
        date.jour -= jours_dans_mois(date.mois, date.annee);
        date.mois++;
        if (date.mois > 12) {
            date.mois -= 12;
            date.annee++;
        }
    }
    
    return date;
}

void afficher_date_heure(const Date_Heure* dh) {
    if (dh) printf("%02d/%02d/%04d %02d:%02d", dh->jour, dh->mois, dh->annee, dh->hr, dh->min);
}

void modifier_date_heure(Date_Heure* dh, int annee, int mois, int jour, int hr, int min) {
    if (dh) {
        dh->annee = annee;
        dh->mois = mois;
        dh->jour = jour;
        dh->hr = hr;
        dh->min = min;
    }
}

void supprimer_date_heure(Date_Heure* dh) {
    free(dh);
}

int comparer_date_heure(const Date_Heure* dh1, const Date_Heure* dh2) {


    if (dh1->annee > dh2->annee) return 1;
    if (dh1->annee < dh2->annee) return -1;
    

    if (dh1->mois > dh2->mois) return 1;
    if (dh1->mois < dh2->mois) return -1;
    

    if (dh1->jour > dh2->jour) return 1;
    if (dh1->jour < dh2->jour) return -1;
    

    if (dh1->hr > dh2->hr) return 1;
    if (dh1->hr < dh2->hr) return -1;
    
   
    if (dh1->min > dh2->min) return 1;
    if (dh1->min < dh2->min) return -1;
    
    return 0; 
}