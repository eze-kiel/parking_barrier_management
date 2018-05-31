<<<<<<< HEAD:digicode_stable.c
//#include <reg552.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h> //pour sleep(x)
#include "../Biblio/types.h"
//#include "../Biblio/mesfonctions.h"


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

void main (void) 
{
  code_index = 0;
/*
  EX0 = 0;
  IT0 = 1;
  EA = 1;
*/

  printf("Place(s) restante(s) : %hu\n", nbPlaces);

  while (TRUE) 
  {
  
    read_digit();

    // REMOVE BEFORE USE
    //debug_digits();

    if ((check_code())) 
    {
      if(check_place(nbPlaces))
      {
        protocole_ouverture();
        //REMPLACER PAR tempo100ms       
        sleep(3);
        protocole_fermeture();       
        
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

  code_index = (code_index+1) % secret_size(); //incrementer code incrementerdex, ou remise à zero quand max

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
  printf("Ouverture...\n");
  sleep(1);
  printf("Ouvert\n");
}

void protocole_fermeture(void)
{
  printf("Fermeture...\n");
  sleep(1);
  printf("Fermé\n");
}


//********SPIT********//
/*
void spit_ext0(void) interrupt 0 setting 1
{
  demande_sortie++;
  printf("\nOUVERTURE!\n"); 
  tempo100ms(10);
    printf("FERMETURE\n");
    nbPlaces = nbPlaces + 1;
    printf("\nPlace(s) restante(s) : %hu\n", nbPlaces);
    demande_sortie = 0;
}

*/
=======
#include <reg552.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//#include <unistd.h>
#include "../Biblio/types.h"
#include "../Biblio/mesfonctions.h"
#include "../Biblio/io_xeva.h"


#define SECRET "9876"
#define TAILLE_PARKING 2

#define TRUE 1
#define FALSE 0

u8 code_index;
u8 digicode[sizeof(SECRET)-1];
u8 nbPlaces = TAILLE_PARKING;
u8 demande_sortie;


u8 secret_size(void);
u8 digit_is_valid(char c);
u8 read_digit(void);
u8 check_code(void);
void debug_digits(void);
u8 check_place(u16 nbPlaces);
void tempo100ms(u16 Nb100ms);
void sortie(void);
u8 Appui_P32(void);
//u16 protocole_entree (u16 nbPlaces);

u8 Places_restantes[1];

void main (void) 
{
  code_index = 0;
  
  EX0 = 0;
  IT0 = 1;
  EA = 1;

  LCDInit();

  
  //REMOVE BEFORE USE
  //printf("sizeof: %ld\n", sizeof(SECRET) - 1);

  printf("Place(s) restante(s) : %hu\n", nbPlaces);

  //REMOVE BEFORE USE
  //printf("%s\n", SECRET); 

  while (TRUE) 
  {
  
    read_digit();
    
    if((P3 & 0x04)==0)
    {
      sortie();
    }

    // REMOVE BEFORE USE
    // debug_digits();

    if ((check_code())) 
    {
      if(check_place(nbPlaces))
      {
         LCDClear();
      LCDDisplay("Ouverture");
      tempo100ms(10);
      
      LCDClear();
      LCDDisplay("Ouvert");
        // AJOUTER LIGNE DESSOUS LA TEMPO
        tempo100ms(10);
        
      LCDClear();
        LCDDisplay("Fermeture");
        
        tempo100ms(10);

        nbPlaces = nbPlaces - 1;
  
      //Places_restantes[0] = nbPlaces;
          nbPlaces = (char) nbPlaces;
        LCDClear();
        LCDDisplay(&nbPlaces);
        tempo100ms(10);
      
      }
      else
      {

      }

    }

  }
}

//*******FUNC DEF*******//

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
  while ((!digit_is_valid(digicode[code_index]))||((P3 & 0x04)==0)); //Tant que le caract entré est valide

  code_index = (code_index+1) % secret_size(); //incrementer code index, ou remise à zero quand max

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

void sortie(void)
{
  printf("walou\n");

}

u8 Appui_P32(void)
{
  if((P3 & 0x04)==0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
/*
u16 protocole_entree (u16 nbPlaces)
{
  LCDClear();
  LCDDisplay(LCD_ouverture);
        
  tempo100ms(10);
        
  LCDClear();
  LCDDisplay(LCD_fermeture);

  nbPlaces = nbPlaces - 1;
  
  Places_restantes[0] = nbPlaces;
        
  LCDClear();
  LCDDisplay(Places_restantes);
}*/

//********SPIT********//
/*
void spit_ext0(void) interrupt 0 setting 1
{
  demande_sortie++;
  printf("\nOUVERTURE!\n"); 
  tempo100ms(10);
    printf("FERMETURE\n");
    nbPlaces = nbPlaces + 1;
    printf("\nPlace(s) restante(s) : %hu\n", nbPlaces);
    demande_sortie = 0;
}

*/
>>>>>>> 13e4b33f0c57ec5b612f6a558c2bdd121cab2634:digicode.c
