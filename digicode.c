//#include <reg552.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "../Biblio/types.h"


#define SECRET "9876"
#define TAILLE_PARKING 2

#define TRUE 1
#define FALSE 0

u8 code[sizeof(SECRET)-1];
u8  code_index;
u16 nbPlaces = TAILLE_PARKING;

u8 secret_size(void);
u8 digit_is_valid(char c);
u8 read_digit(void);
u8 check_code(void);
void debug_digits(void);
u8 check_place(u16 nbPlaces);
void tempo100ms(u16 Nb100ms);

void main (void) 
{
  code_index = 0;

  //REMOVE BEFORE USE
  //printf("sizeof: %ld\n", sizeof(SECRET) - 1);

  printf("Place(s) restante(s) : %hu\n", nbPlaces);

  //REMOVE BEFORE USE
  //printf("%s\n", SECRET); 

  while (TRUE) 
  {
    read_digit();

    // REMOVE BEFORE USE
    // debug_digits();

    if ((check_code())) 
    {
      if(check_place(nbPlaces))
      {
        printf("OUVERTURE!\n");
        fflush(stdout);
        tempo100ms(100);
        printf("FERMETURE\n");
        nbPlaces = nbPlaces - 1;
        printf("Place(s) restante(s) : %hu\n", nbPlaces);
        fflush(stdout);
      }
      else
      {
        printf("Place(s) restante(s) : %hu\n", nbPlaces);
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
    code[code_index] = getchar(); //Saisie dans code[]
  }
  while ( !digit_is_valid(code[code_index]) ); //Tant que le caract entré est valide

  code_index = (code_index+1) % secret_size(); //incrementer code index, ou remise à zero quand max

  return TRUE;
}

u8 check_code() //Tester si le code entré est bon
{
  u16 i;

  for(i = 0; i < secret_size(); i++) 
  {
    if (SECRET[i] != code[(code_index + i) % secret_size()])
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
    printf("%c ", code[i]);
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

//********SPIT********//

/*void spit_ext0(void) interrupt 0 setting 1
{
  printf("OUVERTURE!\n");
  fflush(stdout);
  tempo100ms(100);
  printf("FERMETURE\n");
  nbPlaces = nbPlaces + 1;
}*/