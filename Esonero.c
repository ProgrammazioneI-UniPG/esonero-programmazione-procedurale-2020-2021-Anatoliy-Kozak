#include<stdio.h>
#include<time.h> //per TIME che serve per RANDOM
#include<stdlib.h> //per RANDOM
#include<string.h> //per STRLEN

//variabili
char sms[129];
char chiave[129];
char criptato[129];

int size = 129;

//dimensioni sms e chiave
int dim_sms;
int dim_chiave;

//---------------------------------------------------------------------------|
//NB - La chiave avrà sempre dimensioni uguali o maggiori al messaggio, mai meno
void cifratura(){
  //CIFRATURA
  for(int i=0; i<dim_chiave; i++){
    criptato[i] = sms[i]^chiave[i];
  }
  //output CIFRATURA
  puts("\n|-SMS cifrato");
  for(int i=0; i<dim_chiave; i++){
    printf("%x", criptato[i]);
  }

  //Decifratura
  for(int i=0; i<dim_chiave; i++){
    sms[i] = criptato[i]^chiave[i];
  }
  //output DECIFRATURA
  puts("\n|-SMS decifrato");
  for(int i=0; i<dim_chiave; i++){
    printf("%c", sms[i]);
  }
  puts("");
}
//---------------------------------------------------------------------------|
void manuale(){
  int r=0;

  //***GENERATA RANDOMICAMENTE*******************************
  puts("\n/-------CHIAVE MANUALE-------/");
  printf("\n-/Inserisci la chiave di almeno %d caratteri/-\n", dim_sms);

  do {
    printf("-|");
    fgets(chiave, size, stdin);
    dim_chiave = strlen(chiave)-1;
    //controllo dimensione chiave
    if(dim_chiave < dim_sms){
      puts("<!--ERRORE! chiave troppo piccola-->\n");
      printf("<--/Macano %i caratteri, riprova/-->\n", (dim_sms-dim_chiave));
    } else {
      r=1;
    }
  }while(r==0);

  cifratura();
}
//---------------------------------------------------------------------------|
void automatica(){
  //***GENERATA RANDOMICAMENTE*******************************
  puts("\n/******CHIAVE GENERATA********/");
  for(int i=0; i<=dim_sms; i++){
    chiave[i] = (rand() %128);
    if(chiave[i]<33){
      i--;
    }
  }

  dim_chiave = strlen(chiave)-1;

  //output CHIAVE
  puts("\n|--La chiave generata:");
  for(int i=0; i<dim_sms; i++){
    printf("%x", chiave[i]);
  }
  puts("");

  cifratura();
}
//---------------------------------------------------------------------------|
int main(){
  time_t t;
  srand((unsigned) time(&t));//fa il random diverso a ogni esecuzione

  char risposta;

  puts("|--Benvenuto/a:--|");
  puts("!-ATTENZIONE\n-Il massimo numero di caratteri che è possibile decifrare è 128,\nnon verranno presi in considerazione i caratteri successivi al 128esimo!!");
  puts("\n-/Inserisci il messaggio da cifrare(MAX 128 caratteri)/-");
  printf("-|");
  fgets(sms, size, stdin);
  dim_sms = strlen(sms)-1;

  puts("\n-/Come si vuole procedere?/-");
  puts("1-Inserire manualmente la chiave di codifica");
  puts("2-Far generare automanicamente la chiave di codifica");
  puts("3-Termina il programma");

  do{
    puts("\nInserire la propria scelta:");
    printf("-|");
    risposta = getchar();

    if(risposta == '1'){
      while((risposta = getchar()) != '\n' && risposta != EOF);
      manuale();
    }
    else if(risposta == '2'){
      while((risposta = getchar()) != '\n' && risposta != EOF);
      automatica();
    } else if(risposta == '3') {
      break;
    }
    else {
      while((risposta = getchar()) != '\n' && risposta != EOF);
      puts("\nValore non valido, \nscegliere il numero corrispondente all'opzione desiderata");
    }

  }while(risposta!=1 && risposta!=2);
}
