#include <Arduino.h>

int clk =12;
int data =2;
int clk_enable =11;
int bp_gauche = 5;
int bp_droit = 6;
int bp_haut = 4;
int bp_bas = 3;
int etat_bp_gauche=0;
int etat_bp_droit=0;
int etat_bp_haut=0;
int etat_bp_bas=0;
int tempo_bouton_gauche=0;
int tempo_bouton_droit=0;
int tempo_bouton_haut=0;
int tempo_bouton_bas=0;
int ligne =0;
int colonne =0;
int data_pomme =1;
int delay_pomme =0;



#define gauche 1
#define droit 2
#define haut 3
#define bas 4
#define monte 5
#define descent 6
int valeur_bouton =0;
void lecture_boutons();
void deplacement_point();
void chenillard_1_Led();
void affichage();
void affichage_matrice();

 boolean Matrice_Data[5][5]={
  0,0,0,0,0,
  0,0,0,0,0,
  0,0,0,0,0,
  0,0,0,0,0,
  0,0,0,0,0,
 };
 boolean Etages_Data[5]={
   0,0,0,0,0,
 };
void setup() {
  pinMode(clk,OUTPUT); 
  pinMode(data,OUTPUT);
  pinMode(clk_enable,OUTPUT);
  pinMode(bp_gauche,INPUT_PULLUP);
  pinMode(bp_droit,INPUT_PULLUP);
  pinMode(bp_bas,INPUT_PULLUP);
  pinMode(bp_haut,INPUT_PULLUP);
  digitalWrite(clk_enable,LOW);

  for (int i=0;i<32;i++)//reset
  {
      digitalWrite(data,LOW);
      digitalWrite(clk, HIGH);
      digitalWrite(clk_enable, LOW);
      delay(1);
      digitalWrite(clk, LOW);
      digitalWrite(clk_enable, HIGH);
      delay(1);
  }

}
void loop() 
{
  
 
 lecture_boutons();
 deplacement_point();
 


 
}
 

void deplacement_point()
{

  //bouton bas
  if (etat_bp_bas == 0 && tempo_bouton_bas==0)
  {
    tempo_bouton_bas=1;
    
  }
  if(etat_bp_bas == 1 && tempo_bouton_bas==1)
  {
    tempo_bouton_bas=0;
    Matrice_Data[ligne][colonne]= 0;
    
    if (ligne>0)
    {
      ligne= ligne-1;
    }
    else
    {
      ligne= 4;
    }
    
  }

  //bouton haut
  if (etat_bp_haut == 0 && tempo_bouton_haut==0)
  {
    tempo_bouton_haut=1;
    
  }
  if(etat_bp_haut == 1 && tempo_bouton_haut==1)
  {
    tempo_bouton_haut=0;
    Matrice_Data[ligne][colonne]= 0;
    
    if (ligne<4)
    {
      ligne= ligne+1;
    }
    else
    {
      ligne= 0;
    }
    
  }
  //bouton gauche
  if (etat_bp_gauche == 0 && tempo_bouton_gauche==0)
  {
    tempo_bouton_gauche=1;
    
  }
  if(etat_bp_gauche == 1 && tempo_bouton_gauche==1)
  {
    tempo_bouton_gauche=0;
    Matrice_Data[ligne][colonne]= 0;

    if (colonne>0)
    {
      colonne= colonne-1;
    }
    else
    {
      colonne= 4;
    }
    
  }
  //bouton droit
  if (etat_bp_droit == 0 && tempo_bouton_droit==0)
  {
    tempo_bouton_droit=1;
    
  }
  if(etat_bp_droit == 1 && tempo_bouton_droit==1)
  {
    tempo_bouton_droit=0;
    Matrice_Data[ligne][colonne]= 0;
    if (colonne<4)
    {
      colonne= colonne+1;
    }
    else
    {
      colonne= 0;
    }
    
  }
    if(delay_pomme > 1000)
    {
      delay_pomme=0;
      if (data_pomme ==0)
      {
        data_pomme=1;
      }
      else
      {
         data_pomme=0;
      }
      
      
    }
    

    Matrice_Data[ligne][colonne]= data_pomme;
 
    
    for (int i=0;i<=7;i++)//les 7 premier bits à 0 
    {
        digitalWrite(data,HIGH);
        digitalWrite(clk, HIGH);
        delay(1);
        digitalWrite(clk, LOW);
        delay(1);
    }
    
    
    for (int ligne=4;ligne>=0;ligne--)
    {
      for (int colonne=4;colonne>=0;colonne--)
      {
        digitalWrite(data,Matrice_Data[ligne][colonne]);
        digitalWrite(clk, HIGH);
        delay(1);
        digitalWrite(clk, LOW);
        delay(1);
        
      }
      
    }
    digitalWrite(clk_enable, HIGH);
    delay(1);
    digitalWrite(clk_enable, LOW);
    delay(1);
    delay_pomme =delay_pomme+1;
    
    
  
}
void lecture_boutons()
{
  etat_bp_bas =digitalRead(bp_bas);
  etat_bp_haut =digitalRead(bp_haut);
  etat_bp_droit =digitalRead(bp_droit);
  etat_bp_gauche =digitalRead(bp_gauche);
}



void affichage()
{
   // digitalWrite(clk, HIGH);
    digitalWrite(clk_enable, LOW);
    delay(1);
   // digitalWrite(clk, LOW);
    digitalWrite(clk_enable, HIGH);
    delay(1);
}















void chenillard_1_Led()
{
 for (int i=0;i<5;i++)
 {
   for (int c=0;c<5;c++)
 {
   Matrice_Data[i][c]= 1;
   digitalWrite(data,Matrice_Data[i][c]);
   digitalWrite(clk, HIGH);
   delay(100);
   digitalWrite(clk, LOW);
   delay(100);
   Matrice_Data[i][c]= 0;
 }
 }
}



void affichage_matrice()
{
  

    for (int i=0;i<=7;i++)//les 7 premier bits à 0 
    {
        digitalWrite(data,HIGH);
        digitalWrite(clk, HIGH);
        delay(1);
        digitalWrite(clk, LOW);
        delay(1);
    }

    for (int ligne=4;ligne>=0;ligne--)
    {
      for (int colonne=4;colonne>=0;colonne--)
      {
        digitalWrite(data,Matrice_Data[ligne][colonne]);
        digitalWrite(clk, HIGH);
        digitalWrite(clk_enable, LOW);
        delay(1);
        digitalWrite(clk, LOW);
        digitalWrite(clk_enable, HIGH);
        delay(1);
      }
      
    }
    
   
 
  
}
