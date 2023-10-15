// ######################################################################################################
// ############################  Kompensationsarbeit SWE 2 - Bankanwendung   ############################
// ######################################################################################################

// AUTHOR:    MARKUS BAMMER
// DATE:      2023-10
// FILE:      header.h
// DESCRIPTON:    Bankanwendung mit Anmeldung, Transaktionen und Speicherung der Daten in einer Datei


// ######################################################################################################
// ###########################################  HEADER-DATEI  ###########################################
// ######################################################################################################

// #############################################   INCLUDES   ###########################################

#ifndef INC_01_BANKANWENDUNG_AUFGERAEUMT_HEADER_H
#define INC_01_BANKANWENDUNG_AUFGERAEUMT_HEADER_H

#define MAX_SIZE 100
#define MAX_NAME_SIZE 100
#define MAX_PASSWORD_SIZE 100

// ##############################################  STRUCTS   #############################################

typedef struct
{
    char Benutzer_Name[MAX_NAME_SIZE];
    char Benutzer_Password[MAX_PASSWORD_SIZE];
    double Geldbetrag_am_Konto;
    char IBAN_Nummer[MAX_SIZE];
} Bankkonto;

// ##########################################  FUNKTIONSPROTOTYPEN   #######################################

void begruessung();
void neue_Anmeldung();
int LogIn(Bankkonto *konto);
void zugang_Transaktionen(Bankkonto *konto);
void hidePasswordInput(char *password); // Funktion zur Passwort-Eingabe mit Verschleierung


#endif // INC_01_BANKANWENDUNG_AUFGERAEUMT_HEADER_H
