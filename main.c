
#include <stdio.h>
#include <string.h>

//#include "header.h"


#define MAX_SIZE 255


// Konto erstellen: 1. neue Anmeldung

void neue_Anmeldung() {

    char Benutzer_Name[MAX_SIZE] ;
    char Benutzer_Password[MAX_SIZE] ;
    char file_name[MAX_SIZE];

    FILE * benutzer;


//#########################################  BENUTZER-ERSTELLEN   ######################################
    printf("Bitte gebe deinen Benutzer_Namen ein. \n");                         // Benutzer_Name erstellen
    scanf("%s", Benutzer_Name);

    printf("Bitte gebe deinen Benutzer_Password ein. \n");                      // Benutzer_PW erstellen
    scanf("%s", Benutzer_Password);                         // BEACHTE

//Benutzer_Datei wird erstellt
    strcpy(file_name,Benutzer_Name);                                        // wird kopiert, damit der 'file_name' geaendert werden kann, ohne den Benutzernamen zu aendern
//    benutzer = fopen(strcat(strcat("01_benutzer\\",file_name) ,".txt"), "w");           // mit der 'strcat'-funktion wird das '.txt' an den eingegeben string angehangen


//    strcat(file_name, ".txt");
//    benutzer= fopen(strcat("./01_benutzer/", file_name), "w");


    char str[]="01_benutzer/";                                                          // um die datei in einen unterorder zu speichern
    strcat(str, file_name);
    benutzer= fopen(strcat(str, ".txt"), "w");


// fehlerabfrage
    if(benutzer == NULL){
        printf("FEHLER");
        //check, ob schon so eine Datei besteht         TO-DO       -> siehe 'LogIn'-funktion
    }

// Benutzer_Name in datei speichern
    fprintf(benutzer, "Name : ");
    fprintf(benutzer, Benutzer_Name );              // wird in die Datei gespeichert
    fprintf(benutzer, "\n");

// Benutzer_PW wird in die Datei gespeichert
    fprintf(benutzer, "Password: PW");
    fprintf(benutzer, Benutzer_Password );              // wird in die Datei gespeichert
    fprintf(benutzer, "\n");

//###################################################   ENDE   ####################################################


    fclose(benutzer);                                       // Datei wird geschlossen
}

void LogIn() {
    char buchstabe = 'w';

    char Benutzer_Name[MAX_SIZE];
    char Benutzer_Password[MAX_SIZE];
    char Benutzer_Password_Check[MAX_SIZE];
    char file_name[MAX_SIZE];

    char file_content_01[MAX_SIZE];                // hier wird der Inhalt der Datei gespeichert
    char file_content_02[MAX_SIZE];                // hier wird der Inhalt der Datei gespeichert

    int file_content_int01 = 0;                      // fuer die 'fgetc'-funktion
    int file_content_int02 = 0 ;
    int a, b, c, d ;
    int counter = 0 ;
    int counter_01 = 0 ;
    int counter_02= 0 ;

    double file_address_01 = 0;

    FILE * benutzer ;

//#########################################   LOGIN_ABFRAGE   ###########################################
//Benutzer-Abfrage
    printf("LogIn Abfrage \n");
    printf("Benutzer_Name eingeben: \n");

    scanf("%s", Benutzer_Name);
    strcpy(file_name, Benutzer_Name);               // siehe 'neue_Anmeldung' fuer Beschreibung
    strcat(file_name, ".txt");

    benutzer= fopen(file_name, "r");            // FILE ist zum LESEN geoeffnet
// fehlerabfrage
    if(benutzer == NULL){
        printf("FEHLER\nKeine Datei vorhanden");
    }

// Password-Abfrage

    printf("Bitte gebe deinen Benutzer_Password ein. \n");                      // Benutzer_PW abfragen
    getchar();
    counter = 0 ;
    a = 0 ;                                      // 'a' hat sonst noch das 'enter' von oben
    while ( a != 10)                            // solange kein 'Enter' eingegeben wird
    {
        a = getchar();
        Benutzer_Password[counter] =a;          // richtigen Werte an die ersten stellen speichern

        counter++;                              // counter fuer die Gr. des neues ARRAY (Benutzer_Password_Resized)
    }


//PW wird aus der Datei geholen und gespeichert in Benutzer_Password_Check(das Gr. Array)
    a = 0 ;
    while(counter_02 < MAX_SIZE && (a != 10) ){
        file_content_int01 = fgetc(benutzer);
        //  printf("file_content_01 : %i\n", file_content_01);

        if(file_content_int01 == 'P') {                      // pruefen ob pointer in der Datei bei 'P' ist
            //    printf("in der ersten Schleife ");
            file_content_int02 = fgetc(benutzer);       // und pruefen ob Zweite stelle in 'W'
            if (file_content_int02 == 'W') {
                //       printf("in der Zweiten Schleife ");
                for (int i = 0; a != 10 ; ++i) {           // die darauf folgenden buchstaben bis zum '\0' speichern
                    a = fgetc(benutzer);                // '10' steht fuer den INTEGER-Wert des 'ENTER'
                    Benutzer_Password_Check[i] = a;
                    printf("%c", Benutzer_Password_Check[i]);
                    counter_01++;                         // counter fuer die Gr. des neues ARRAY (Benutzer_Password__Check_Resized)
                }
            }
        }
        counter_02++;       // um die Schleife zu verlassen (sicherung)
    }




// hier passiert die Umwandlung beim EINGEGEBEN PASSWORT des alten Gr. Arrays in die angepasste ideale Gr.
    char Benutzer_Password_Resized[counter] ;                                // fuer die Spaetere abfrage muss auch die Gr. gleich sein
    strcpy(Benutzer_Password_Resized, Benutzer_Password );       // siehe: PW vergleich
    printf("Echtes_Benutzer_Password : %s\n", Benutzer_Password_Resized);

// hier passiert die Umwandlung beim HINTERLEGEN PASSWORT des alten Gr. Arrays in die angepasste ideale Gr.
    char Benutzer_Password_Ceck_Resized[counter_01] ;                                // fuer die Spaetere abfrage muss auch die Gr. gleich sein
    strcpy(Benutzer_Password_Ceck_Resized, Benutzer_Password_Check );       // siehe: PW vergleich
    printf("Echtes_Benutzer_Password_Check : %s\n", Benutzer_Password_Ceck_Resized);

// Abfrage, ob PW korrekt
    if(strcmp(Benutzer_Password_Resized, Benutzer_Password_Ceck_Resized) == 0 ){                           // PW vergleichen
        printf("Sie haben Zugang \n");
        // zugang zum Benutzer_Konto herstellen                 TO-DO
    }

//////BEACHTE: IWIE funktionert die PW abfrage mit 'strcmp' noch nicht





//#########################################   ENDE   #####################################################

    fclose(benutzer);

}


void Zugang_Transaktionen(){
    char buchstabe = 'w';

    char Benutzer_Name[] = "MAX";
//    char Benutzer_Password[MAX_SIZE];
//    char Benutzer_Password_Check[MAX_SIZE];
    char file_name[MAX_SIZE];

    char file_content_01[MAX_SIZE];                // hier wird der Inhalt der Datei gespeichert
    char file_content_02[MAX_SIZE];                // hier wird der Inhalt der Datei gespeichert

    char ueberweisung_01[255];
    char ueberweisung_02[255];
    char ueberweisung_03[255];

    float Ueberweisungs_Betrag_01 = 0;
    float Ueberweisungs_Betrag_02 = 0;
    float Ueberweisungs_Betrag_03 = 0;

    int file_content_int01 = 0;                      // fuer die 'fgetc'-funktion
    int file_content_int02 = 0;
    int file_content_int03 = 0;
    int a, b, c, d ;
    int counter = 0 ;

    double file_address_01 = 0;

    FILE * benutzer ;
    benutzer= fopen("mar.txt", "a");
// fehlerabfrage
    if(benutzer == NULL){
        printf("FEHLER\nKeine Datei vorhanden");
    }

//######################################## ZUGANG TRANSAKTIONEN   ##############################

// Betrag eintragen und in Datei Speichern
    printf("Zu Ueberweisenden Betrag eingeben: ");
    scanf("%i", &file_content_int01);

// Betrag hinzufuegen
    printf("Wie viel soll dem Konto hinzugefuegt werden : ");
    scanf("%s", file_content_01);

    fprintf(benutzer, "Transaktion von : %s", Benutzer_Name);
    fprintf(benutzer, "\n");
    fprintf(benutzer, "Transaktionssummer : TRK%s", file_content_01);
//    fprintf(benutzer, "Transaktionspartner", );




//    printf("Folgender Betrag wird hinzugefuegt : %s ", file_content_01);

    fclose(benutzer);



// Abfrage an Datei, welcher Betrag vorhanden ist
    benutzer= fopen("mar.txt", "r");
    while (file_content_int01 != EOF ){
        file_content_int01 = fgetc(benutzer);
        //  printf("file_content_01 : %i\n", file_content_01);
        if(file_content_int01 == 'T') {                      // pruefen ob pointer in der Datei bei 'P' ist
            //    printf("in der ersten Schleife ");
            file_content_int02 = fgetc(benutzer);       // und pruefen ob Zweite stelle in 'W'
            if (file_content_int02 == 'R') {
                //       printf("in der Zweiten Schleife ");
                file_content_int03 = fgetc(benutzer);
                if (file_content_int03 == 'K') {


                    printf("TRK: ");
                    while (file_content_int01 != 10) {
                        //speicher die folgenden Zeichen in var, bis das erste Leerzeichen kommt
                        file_content_int01 = fgetc(benutzer);
                        printf("%c", file_content_int01);

                        file_content_01[counter] = file_content_int01;
                        counter++;
                    }
                }
            }
        }
    }
    fclose(benutzer);

    benutzer= fopen("mar.txt", "r+");

    strcpy(file_content_02,ueberweisung_01);
// dateipointer ermitteln, um die belegten stellen nach BETRAG und TRK zu aendern
    printf("Die aktuelle Position des Dateipointers ist: %i \n", pos);


    fseek(benutzer, pos, SEEK_SET);
    fprintf(benutzer, file_content_02);
}

void test(){

    long int pos ;
    long int *ptr_pos;
    ptr_pos = &pos ;

    char buchstabe = 'w';

    char Benutzer_Name[] = "MAX";
//    char Benutzer_Password[MAX_SIZE];
//    char Benutzer_Password_Check[MAX_SIZE];
    char file_name[MAX_SIZE];

    char file_content_01[MAX_SIZE];                // hier wird der Inhalt der Datei gespeichert
    char file_content_02[MAX_SIZE];                // hier wird der Inhalt der Datei gespeichert

    char ueberweisung_01[]= "300";
    char ueberweisung_02[255];
    char ueberweisung_03[255];

    float Ueberweisungs_Betrag_01 = 0;
    float Ueberweisungs_Betrag_02 = 0;
    float Ueberweisungs_Betrag_03 = 0;

    int file_content_int01 = 0;                      // fuer die 'fgetc'-funktion
    int file_content_int02 = 0;
    int file_content_int03 = 0;
    int a, b, c, d ;
    int counter = 0 ;

    double file_address_01 = 0;

    FILE * benutzer ;
    benutzer= fopen("mar.txt", "r");
// fehlerabfrage
    if(benutzer == NULL){
        printf("FEHLER\nKeine Datei vorhanden");
    }

//#########################################   TEST   ###########################################


//######################################## ZUGANG TRANSAKTIONEN   ##############################

// Abfrage an Datei, welcher Betrag vorhanden ist

    while (file_content_int01 != EOF ){
        file_content_int01 = fgetc(benutzer);
        //  printf("file_content_01 : %i\n", file_content_01);
        if(file_content_int01 == 'T') {                      // pruefen ob pointer in der Datei bei 'P' ist
            //    printf("in der ersten Schleife ");
            file_content_int02 = fgetc(benutzer);       // und pruefen ob Zweite stelle in 'W'
            if (file_content_int02 == 'R') {
                //       printf("in der Zweiten Schleife ");
                file_content_int03 = fgetc(benutzer);
                if(file_content_int03 == 'K'){
                    printf("TRK: ");

                    pos = ftell(benutzer);

                    counter = 0 ;
                    while (file_content_int01 != 10 && file_content_int01 != (-1)){
                        //speicher die folgenden Zeichen in var, bis das erste Leerzeichen kommt
                        file_content_int01 = fgetc(benutzer);
                        printf("%c", file_content_int01);

                        file_content_01[counter] = file_content_int01;
                        counter++;
                    }
                    printf("\n");
                    // resizend
//                    benutzer= fopen("mar.txt", "a");
//                    char file_content_01_resized[counter] ;
//                    strcpy(file_content_01_resized, file_content_01);
//                    printf("%s", file_content_01_resized);
//                    fprintf(benutzer,"%s",file_content_01_resized);
                    //fputs(file_content_01_resized, benutzer);           // TO-DO: hier werden noch 'NULL' mit uebergeben
                }
            }
        }

    }

    fclose(benutzer);

    benutzer= fopen("mar.txt", "r+");

    strcpy(file_content_02,ueberweisung_01);
// dateipointer ermitteln, um die belegten stellen nach BETRAG und TRK zu aendern
    printf("Die aktuelle Position des Dateipointers ist: %i \n", pos);


    fseek(benutzer, pos, SEEK_SET);
    fprintf(benutzer, file_content_02);




//#######################################   ENDE   ############################################

//#####################################   ENDE   ###############################################

    fclose(benutzer);

}





/////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
    neue_Anmeldung();
    LogIn();
//    test();

        return 0 ;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
