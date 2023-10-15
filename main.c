// ######################################################################################################
// ############################  Kompensationsarbeit SWE 2 - Bankanwendung   ############################
// ######################################################################################################
// AUTHOR:    MARKUS BAMMER
// DATE:      2023-10
// FILE:      main.c
// DESCRIPTON:    Bankanwendung mit Anmeldung, Transaktionen und Speicherung der Daten in einer Datei
// ######################################################################################################


// #########################################   INCLUDES   ################################################

#include <stdio.h>
#include <string.h>                      // Für strcmp(), strstr(), getchar()
#include <stdlib.h>                      // Für exit()
#include <conio.h>                       // Für getch() -> Passwortverschleiern
#include <time.h>                        // Für srand() und time()
#include "header.h"


// #############################################   MAIN   ##################################################

int main()
{
    while (1)       // Endlosschleife
    {
        begruessung();
    }

    return 0;
}

// #############################################  FUNKTIONEN   ##############################################

void begruessung()
{
    int auswahl;
    Bankkonto konto;                        // Bankkonto "konto": Struct

    printf("Herzlich willkommen bei SPAR-RAIK-VOLK - Der Bank deines Vertrauens\n"
           "Was moechtest du tun? \n"
           "1. Neues Konto erstellen \n"
           "2. Auf bestehendes Konto zugreifen \n"
           "3. Programm beenden \n\n");

    scanf("%i", &auswahl);

    switch (auswahl)
    {
    case 1: // Neues Konto erstellen
        printf("Deine Auswahl: Neues Konto erstellen \n");
        neue_Anmeldung(&konto);
        break;
    case 2: // Auf ein bestehendes Konto zugreifen
        printf("Deine Auswahl: Auf bestehendes Konto zugreifen \n");
        if (LogIn(&konto)) // Wenn LogIn erfolgreich war, dann Zugang zu den Transaktionen
        {
            zugang_Transaktionen(&konto);
        }
        break;
    case 3: // Programm beenden
        printf("Deine Auswahl: Programm beenden \n");
        exit(0); // Programm beenden
    default:     // Ungültige Auswahl
        printf("Ungueltige Auswahl \n");
        break;
    }
}

void neue_Anmeldung(Bankkonto *konto)                   // Bankkonto *konto: Pointer auf ein Bankkonto
{
    char Benutzer_Password_CHECK[MAX_PASSWORD_SIZE];    // Wird für die Passwort-Überprüfung benötigt

    printf("\nBitte gib deinen Benutzer_Namen ein. \n");
    scanf("%s", konto->Benutzer_Name);

    printf("Bitte gib dein gewuenschtes Benutzer_Password ein. \n");
    hidePasswordInput(konto->Benutzer_Password);        // Funktion zum Passwort-Eingeben mit Verschleierung

    printf("\nBitte gib dein Benutzer_Password erneut ein. \n");
    hidePasswordInput(Benutzer_Password_CHECK);

    if (strcmp(konto->Benutzer_Password, Benutzer_Password_CHECK) != 0) // Wenn die Passwörter nicht übereinstimmen
    {
        printf("Die Passwoerter stimmen nicht ueberein und wird abgebrochen. \n\n");
        return;
    }

    //Erstellung der IBAN-Nummer -> ersten zwei Buchstaben des Benutzernamens + 4 Zahlen
    srand(time(NULL)); // srand: Initialisiert den Zufallsgenerator
    int zufallsZahl = rand() % 10000; // rand: Erzeugt eine Zufallszahl
    sprintf(konto->IBAN_Nummer, "%s%04d", "AT", zufallsZahl); // sprintf: Schreibt in einen String

    printf("\nDeine IBAN-Nummer lautet: %s \n", konto->IBAN_Nummer); // Ausgabe der IBAN-Nummer (wird später in die Datei geschrieben

    printf("\n\nBitte gib nun deinen Geldbetrag ein: \n"); // Erste Einzahlung
    scanf("%lf", &konto->Geldbetrag_am_Konto);

    printf("\nDein Konto wurde erstellt. \n"
           "Vielen Dank für dein Vertrauen. \n\n");

    FILE *benutzer;

    char file_path_copy[MAX_NAME_SIZE + 5];       // +5 wegen dem ".txt"
    strcpy(file_path_copy, "./");                 // "./" ist der Pfad zum aktuellen Ordner
    strcat(file_path_copy, konto->Benutzer_Name); // strcat: String concatenation: hängt den Benutzer_Name an den Pfad an
    strcat(file_path_copy, ".txt");

    benutzer = fopen(file_path_copy, "w"); // "w" = write: Datei wird zum Schreiben geöffnet
    if (benutzer == NULL)
    {
        printf("FEHLER: Datei konnte nicht geoeffnet werden. \n");
        return;
    }

    fprintf(benutzer, "Name : %s\n", konto->Benutzer_Name); // fprintf: Schreibt in die Datei
    fprintf(benutzer, "Password: %s\n", konto->Benutzer_Password);
    fprintf(benutzer, "Geldbetrag am Konto: %.2lf\n", konto->Geldbetrag_am_Konto);
    fprintf(benutzer, "Iban-Nummer: %s\n", konto->IBAN_Nummer);

    fclose(benutzer);
}

// Funktion zur Passwort-Eingabe mit Verschleierung -> Funktion wurde durch Unterstützung von Albin Ehrengruber erstellt
void hidePasswordInput(char *password)
{
    int index = 0;
    char ch;

    while (1)               // Endlosschleife, bis die Eingabetaste gedrückt wurde, um die Eingabe zu beenden
    {
        ch = getch();       // Ein Zeichen einlesen, ohne es anzuzeigen
        if (ch == '\r') // Wenn die Eingabetaste gedrückt wurde, beende die Eingabe, \r: Carriage Return, bewirkt, dass der Cursor an den Anfang der Zeile springt
        {
            password[index] = '\0'; // Nullterminierung des Passworts
            break;
        }
        else if (ch == 8) // Wenn Backspace gedrückt wurde
        {
            if (index > 0)
            {
                index--;
                printf("\b \b"); // Lösche das zuletzt eingegebene Zeichen, \b = Backspace = Bewegt den Cursor um ein Zeichen nach links
            }
        }
        else
        {
            if (index < MAX_PASSWORD_SIZE - 1) // -1: Platz für die Nullterminierung
            {
                password[index] = ch;
                index++;
                printf("*"); // Zeige ein '*' anstatt des eingegebenen Zeichens
            }
        }
    }
}

int LogIn(Bankkonto *konto)
{
    char line[256];                                  // Verwendung: Zeile für Zeile aus der Datei lesen
    char Benutzer_Password_Check[MAX_PASSWORD_SIZE]; // Wird für die Passwort-Überprüfung benötigt

    FILE *benutzer;                            // Pointer auf eine Datei
    char file_path[MAX_NAME_SIZE + 5]; // +5 für ".txt"
    strcpy(file_path, "./");           // "./" ist der Pfad zum aktuellen Ordner

    printf("\nLogIn Abfrage \n");
    printf("Benutzer_Name eingeben: \n");
    scanf("%s", konto->Benutzer_Name);
    strcat(file_path, konto->Benutzer_Name);
    strcat(file_path, ".txt");

    benutzer = fopen(file_path, "r"); // "r" = read: Datei wird zum Lesen geöffnet
    if (benutzer == NULL)
    {
        printf("FEHLER\nKeine Datei vorhanden");
        return 0;
    }

    printf("Bitte gebe dein Benutzer_Password ein. \n");
    hidePasswordInput(Benutzer_Password_Check); // Passwort mit Verschleierung eingeben

    int loginErfolgreich = 0;                // Hinzugefügt, um den Login-Status zu überprüfen

    // Jetzt das Passwort einlesen:
    while (fgets(line, sizeof(line), benutzer) != NULL) // fgets: Liest eine Zeile aus der Datei
    {
        if (strstr(line, "Password:") != NULL) // Wenn "Password:" in der Zeile enthalten ist; strstr: Sucht nach einem String in einem String
        {
            char gespeichertesPassword[MAX_PASSWORD_SIZE];       // Wird für die Passwort-Überprüfung benötigt
            sscanf(line, "Password: %s", gespeichertesPassword); // sscanf: Liest einen formatierten String | Unterschied printf: Schreibt in die Konsole

            if (strcmp(gespeichertesPassword, Benutzer_Password_Check) == 0) // Wenn die Passwörter übereinstimmen
            {
                printf("\n\nDu hast Zugang \n");
                printf("Benutzer_Name: %s \n", konto->Benutzer_Name);

                // Jetzt das Guthaben einlesen
                while (fgets(line, sizeof(line), benutzer) != NULL) // Solange die Datei nicht zu Ende ist
                {
                    if (strstr(line, "Geldbetrag am Konto:") != NULL) // Wenn "Geldbetrag am Konto:" in der Zeile enthalten ist
                    {
                        sscanf(line, "Geldbetrag am Konto: %lf", &(konto->Geldbetrag_am_Konto));
                        break;
                    }
                }

                printf("Aktuelles Guthaben: %.2lf \n", konto->Geldbetrag_am_Konto);
                loginErfolgreich = 1; // Login erfolgreich
                break;
            }
        }
    }

    fclose(benutzer);

    if (!loginErfolgreich) // Wenn der Login nicht erfolgreich war
    {
        printf("\nFalsches Passwort \n");
    }

    return loginErfolgreich; // Überprüft, ob der Login erfolgreich war
}

void zugang_Transaktionen(Bankkonto *konto) // Bankkonto *konto: Pointer auf ein Bankkonto
{
    FILE *benutzer;
    char file_path[MAX_NAME_SIZE + 5]; // +5 für ".txt"
    strcpy(file_path, "./");
    strcat(file_path, konto->Benutzer_Name);
    strcat(file_path, ".txt");

    benutzer = fopen(file_path, "r"); // "r" = read: Datei wird zum Lesen geöffnet
    if (benutzer == NULL)
    {
        printf("FEHLER\nKeine Datei vorhanden");
        return;
    }

    double aktuellerBetrag = 0.0;

    char line[256];
    while (fgets(line, sizeof(line), benutzer) != NULL) // fgets: Liest eine Zeile aus der Datei
    {
        if (strstr(line, "Geldbetrag am Konto:") != NULL) // strstr: Sucht nach einem String in einem String
        {
            sscanf(line, "Geldbetrag am Konto: %lf", &aktuellerBetrag); // sscanf: Liest einen formatierten String
            break;
        }
    }

    fclose(benutzer);

    int transaktionsOption; // 1 = Einzahlung, 2 = Auszahlung, 3 = Überweisung, 4 = Abbrechen
    printf("\nWillkommen zu Deinen Transaktionen\n");
    printf("1. Geld zum Konto hinzufuegen\n");
    printf("2. Geld vom Konto abheben\n");
    printf("3. Geld auf ein anderes Konto ueberweisen\n");
    printf("4. Abbrechen\n\n");
    printf("Bitte waehle eine Option: ");

    scanf("%d", &transaktionsOption);

    switch (transaktionsOption)
    {
    case 1: // Einzahlung
        printf("\nAktuelles Guthaben: %.2lf\n", aktuellerBetrag);
        printf("\nWie viel soll dem Konto hinzugefuegt werden: ");
        double einzahlungsBetrag;
        scanf("%lf", &einzahlungsBetrag);

        aktuellerBetrag += einzahlungsBetrag;

        break;

    case 2: // Auszahlung
        printf("Aktuelles Guthaben: %.2lf\n", aktuellerBetrag);
        printf("\nWie viel soll vom Konto abgehoben werden: ");
        double abhebungsBetrag;
        scanf("%lf", &abhebungsBetrag);

        if (abhebungsBetrag > aktuellerBetrag)
        {
            printf("Nicht ausreichendes Guthaben auf dem Konto.\n");
            return;
        }

        aktuellerBetrag -= abhebungsBetrag;
        break;

    case 3: // Überweisung
        printf("Aktuelles Guthaben: %.2lf\n", aktuellerBetrag);

        char empfaengerName[MAX_NAME_SIZE];
        printf("\nBitte gib den Namen des Empfaengers ein: ");
        scanf("%s", empfaengerName);

        // Empfänger-Datei öffnen
        FILE *empfaenger;
        char empfaenger_file_path[MAX_NAME_SIZE + 5]; // +5 für ".txt"
        strcpy(empfaenger_file_path, "./");
        strcat(empfaenger_file_path, empfaengerName);
        strcat(empfaenger_file_path, ".txt");

        empfaenger = fopen(empfaenger_file_path, "r+"); // "r+" = read and write: Datei wird zum Lesen und Schreiben geöffnet
        if (empfaenger == NULL)
        {
            printf("FEHLER\nKeine Datei vorhanden\n\n");
            return;
        }

        printf("\nGib den IBAN des Empfaengers ein: ");
        char empfaenger_IBAN_Nummer_Eingabe[100];
        scanf("%s", empfaenger_IBAN_Nummer_Eingabe);

        char empfaenger_IBAN_Nummer_Ausgabe[100];
        char empfaenger_password[100];
        double empfaenger_aktuellerBetrag = 0.0;

        while (fgets(line, sizeof(line), empfaenger) != NULL) // fgets: Liest eine Zeile aus der Datei
        {
            if (strstr(line, "Password:") != NULL) // strstr: Sucht nach einem String in einem String
            {
                sscanf(line, "Password: %s", empfaenger_password); // sscanf: Liest einen formatierten String
            }

            else if (strstr(line, "Geldbetrag am Konto:") != NULL) // strstr: Sucht nach einem String in einem String
            {
                sscanf(line, "Geldbetrag am Konto: %lf", &empfaenger_aktuellerBetrag); // sscanf: Liest einen formatierten String
            }

            else if (strstr(line, "Iban-Nummer:") != NULL) // strstr: Sucht nach einem String in einem String
            {
                sscanf(line, "Iban-Nummer: %s", empfaenger_IBAN_Nummer_Ausgabe); // sscanf: Liest einen formatierten String
            }
        }

        if (strcmp(empfaenger_IBAN_Nummer_Eingabe, empfaenger_IBAN_Nummer_Ausgabe) != 0) // Wenn die IBAN-Nummern nicht übereinstimmen
        {
            printf("Ungueltiger IBAN! \n\n");
            return;
        }

        printf("\nWie viel soll ueberwiesen werden: ");
        double ueberweisungsBetrag;
        scanf("%lf", &ueberweisungsBetrag);

        if (ueberweisungsBetrag > aktuellerBetrag)
        {
            printf("\nNicht ausreichendes Guthaben auf dem Konto.\n\n");
            return;
        }

        aktuellerBetrag -= ueberweisungsBetrag;

        empfaenger_aktuellerBetrag += ueberweisungsBetrag;

        // Empfänger-Datei aktualisieren
        fseek(empfaenger, 0, SEEK_SET); // fseek: Setzt den Dateizeiger auf eine bestimmte Position, in dem Fall auf den Anfang der Datei
        fprintf(empfaenger, "Name : %s\n", empfaengerName);
        fprintf(empfaenger, "Password: %s\n", empfaenger_password);
        fprintf(empfaenger, "Geldbetrag am Konto: %.2lf\n", empfaenger_aktuellerBetrag);
        fprintf(empfaenger, "Iban-Nummer: %s\n", empfaenger_IBAN_Nummer_Ausgabe);

        fclose(empfaenger);

        break;

    case 4: // Abbrechen
        printf("Abbrechen\n");
        return;

    default: // Ungültige Option
        printf("Ungueltige Option\n");
        return;
    }


    // Aktualisierung der Datei
    benutzer = fopen(file_path, "r+"); // "r+" = read and write: Datei wird zum Lesen und Schreiben geöffnet
    if (benutzer == NULL)
    {
        printf("FEHLER\nKeine Datei vorhanden");
        return;
    }

    while (fgets(line, sizeof(line), benutzer) != NULL) // fgets: Liest eine Zeile aus der Datei
    {
        if (strstr(line, "Password:") != NULL) // strstr: Sucht nach einem String in einem String
        {
                sscanf(line, "Password: %s", konto->Benutzer_Password); // sscanf: Liest einen formatierten String
        }

        else if (strstr(line, "Iban-Nummer:") != NULL) // strstr: Sucht nach einem String in einem String
            {
                sscanf(line, "Iban-Nummer: %s", konto->IBAN_Nummer); // sscanf: Liest einen formatierten String
            }
    }

    fseek(benutzer, 0, SEEK_SET); // fseek: Setzt den Dateizeiger auf eine bestimmte Position, in dem Fall auf den Anfang der Datei
    fprintf(benutzer, "Name : %s\n", konto->Benutzer_Name);
    fprintf(benutzer, "Password: %s\n", konto->Benutzer_Password);
    fprintf(benutzer, "Geldbetrag am Konto: %.2lf\n", aktuellerBetrag);
    fprintf(benutzer, "Iban-Nummer: %s\n", konto->IBAN_Nummer);

    fclose(benutzer);

    printf("\nTransaktion erfolgreich durchgefuehrt.\n");
    printf("Name: %s\n", konto->Benutzer_Name);
    printf("IBAN-Nummer: %s\n", konto->IBAN_Nummer);
    printf("Aktuelles Guthaben: %.2lf\n", aktuellerBetrag);
    printf("\n\n");
}

// ############################################   FUNKTIONEN ENDE  ####################################################
