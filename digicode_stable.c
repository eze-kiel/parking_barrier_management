//#include <reg552.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h> //pour sleep(x), utiliser commandes UNIX
#include "../Biblio/types.h"
//#include "../Biblio/mesfonctions.h"
//#include "../Biblio/io_xeva.h"



#define SECRET "9876"
#define TAILLE_PARKING 2      

#define TRUE 1
#define FALSE 0

// VARIABLES
u8 code_index;
u8 digicode[sizeof(SECRET)-1];
u16 nbPlaces = TAILLE_PARKING;
u8 demande_sortie;

// FONCTIONS
u8 secret_size(void);
u8 digit_is_valid(char c);
u8 read_digit(void);
u8 check_code(void);
void debug_digits(void);
u8 check_place(u16 nbPlaces);
void tempo100ms(u16 Nb100ms);
void protocole_ouverture(void);
void protocole_fermeture(void);
void timer(void);

void main (void) 
{
  code_index = 0;

  LCDInit();
  LCDClear();
  LCDDisplay("Fermeture");

  EX0 = 1;
  IT0 = 1;
  EA = 1;


  printf("Place(s) restante(s) : %hu\n", nbPlaces);

  while (TRUE) 
  {
  
    read_digit();

    // RBU
    //debug_digits();

    if ((check_code())) //Si code validé
    {
      if(check_place(nbPlaces)) //Si assez de places
      {
        protocole_ouverture();
        fflush(stdout);

        timer();     

        protocole_fermeture();
        fflush(stdout);       
        
        nbPlaces = nbPlaces - 1;
        printf("Place(s) restante(s) : %hu\n", nbPlaces);
      }
      else
      {
        printf("Pas de place disponible\n");
      }
    }
  }
}

//*******DEF FONC*******//

u8 secret_size(void)  //Donne la taille de SECRET
{
  return (sizeof(SECRET) - 1);
}

u8 digit_is_valid(char c) //TRUE si la saisie est valide, sinon FALSE
{
  if ((c < '0') || (c > '9')) 
  {
    return FALSE;
  }
  else 
  {
    return TRUE;
  }
}

u8 read_digit(void) 
{
  do
  {
    digicode[code_index] = getchar(); //Saisie dans code[]
  }
  while ( !digit_is_valid(digicode[code_index]) ); //Tant que le caract entré est valide

  code_index = (code_index+1) % secret_size(); //incrementer code_index, ou remise à zero quand max

  return TRUE;
}

u8 check_code() //Tester si le code entré est bon
{
  u16 i;

  for(i = 0; i < secret_size(); i++) 
  {
    if (SECRET[i] != digicode[(code_index + i) % secret_size()])
    {
      return FALSE; //Si code faux
    }
  }

  return TRUE; //Si code juste
}

void debug_digits(void) //Afficher digits (phase de debug)
{
  u16 i;
  printf("code_index: %d\n", code_index);

  printf("digits: ");
  for (i=0; i < secret_size(); i++) 
  {
    printf("%c ", digicode[i]);
  }
  printf("\n");
}

u8 check_place(u16 nbPlaces) 
{
  if (nbPlaces == 0)
  {
    return FALSE;
  }
  else
  {
    return TRUE;
  }
}

void tempo100ms(u16 Nb100ms)
{
  u16 Nb1, cpt100ms;
  for(cpt100ms = 0; cpt100ms < Nb100ms; cpt100ms ++)
  {
    for(Nb1 = 0; Nb1 < 48000; Nb1 ++)
    {
    }
  }
}

//    FONCTIONS DE MOUVEMENT DE BARRIERE    //

void protocole_ouverture(void)
{
  LCDClear();

  printf("Ouverture...\n");
  LCDDisplay("Ouverture");

  tempo100ms(10);

  LCDClear();
  LCDDisplay("Ouvert");
  printf("Ouvert\n");
}

void protocole_fermeture(void)
{
  LCDClear();

  printf("Fermeture...\n");
  LCDDisplay("Fermeture");

  tempo100ms(10);

  LCDClear();
  LCDDisplay("Ferme");
  printf("Ferme\n");
}

void timer(void)
{
  u16 temps_restant;

  for (temps_restant = 10; temps_restant !=0; temps_restant--)
  {
    printf("Temps restant: %hu\n", temps_restant);
    sleep(1);
  }
}


//********SPIT********//

void spit_ext0(void) interrupt 0 setting 1
{
  u16 temps_restant;

  protocole_ouverture();

  for (temps_restant = 10; temps_restant !=0; temps_restant--)
  {
    printf("Temps restant: %hu\n", temps_restant);

    u16 Nb1, cpt100ms;
    for(cpt100ms = 0; cpt100ms < 10; cpt100ms ++)
    {
      for(Nb1 = 0; Nb1 < 48000; Nb1 ++)
      {
      }
    }
    
  }
  protocole_fermeture();

  nbPlaces++;

  printf("Place(s) restante(s) : %hu\n", nbPlaces);

  IT0 = 0;
}