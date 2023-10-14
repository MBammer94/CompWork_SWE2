// #pragma once                    //sorgt dafür, dass die Header-Datei nur einmal eingebunden wird
#ifndef INC_01_BANKANWENDUNG_AUFGERAEUMT_HEADER_H
#define INC_01_BANKANWENDUNG_AUFGERAEUMT_HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define MAX_NAME_SIZE 100
#define MAX_PASSWORD_SIZE 100

typedef struct
{
    char Benutzer_Name[MAX_NAME_SIZE];
    char Benutzer_Password[MAX_PASSWORD_SIZE];
    double Geldbetrag_am_Konto;
    unsigned int Kontonummer[2]; // Kontonummer[0] = 1. Teil der Kontonummer, Kontonummer[1] = 2. Teil der Kontonummer
} Bankkonto;

// ###################################################   FUNKTIONSPROTOTYPEN   ######################################

void begruessung();
void neue_Anmeldung();
int LogIn(Bankkonto *konto);
void zugang_Transaktionen(Bankkonto *konto);
void hidePasswordInput(char *password); // Funktion zur Passwort-Eingabe mit Verschleierung


#endif // INC_01_BANKANWENDUNG_AUFGERAEUMT_HEADER_H
