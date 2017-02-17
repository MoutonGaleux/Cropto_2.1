


/* ************************************************************************************************************ */
	/* **************************************************************************************************** */
/* ************************************************************************************************************ */
	/*


	CChaine -- Classe gérant les chaînes de caractère : transformation, incrémentation, affichage...


		Copyright (C)  2011,2012,2015   MiG (alias Benoit Nocaudie)


	This file is part of Cropto.

	CChaine is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	CChaine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Cropto.  If not, see <http://www.gnu.org/licenses/>.



	*/
/* ************************************************************************************************************ */
	/* **************************************************************************************************** */
/* ************************************************************************************************************ */




#pragma once

#include <stdio.h>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;


class CChaine
{

private:
	unsigned int m_nC;	// nombre de char + '\0'
	char* m_pChar;	// caractère de fin de chaine : \0


public:
//-------------------------------------------------------------------------------------------------------------------------------
		// Constructeurs
//-------------------------------------------------------------------------------------------------------------------------------
	CChaine();

			// "Chaines"
	CChaine(char c);
	CChaine(char* pChar);

			// "Nombres"
	CChaine(int n);
	CChaine(double d, int nPrecision = 15);	// nPrecision : nb de chiffres après la virgule (Max 16)

			// "Booleen"
	CChaine(bool b, bool bBinaire = true);	// bBinaire : true->0 ou 1; false->"true" ou "false"

			// CChaine
	CChaine(const CChaine & C);
	CChaine operator= (const CChaine & C);

	~CChaine();


//-------------------------------------------------------------------------------------------------------------------------------
		// opérateurs
//-------------------------------------------------------------------------------------------------------------------------------
			// addition
	CChaine operator+ (CChaine C);

				// "Chaine"
	friend CChaine operator+ (char c, CChaine C);
	friend CChaine operator+ (CChaine C, char c);

	friend CChaine operator+ (char* pchar, CChaine C);
	friend CChaine operator+ (CChaine C, char* pchar);

				// "Nombre"
	friend CChaine operator+ (int n, CChaine C);
	friend CChaine operator+ (CChaine C, int n);

	friend CChaine operator+ (double d, CChaine C);
	friend CChaine operator+ (CChaine C, double d);

				// "Booleen"
	friend CChaine operator+ (bool bBinaire, CChaine C);
	friend CChaine operator+ (CChaine C, bool bBinaire);


			// Ajout (à la fin de la chaine°
	CChaine operator+= (CChaine C);

				// "Chaine"
	CChaine operator+= (char c);
	CChaine operator+= (char* pChar);

				// "Nombre"
	CChaine operator+= (int n);
	CChaine operator+= (double d);

				// "Booleen"
	CChaine operator+= (bool bBinaire);


			// Booleen

				// Egalité
	friend bool operator== (CChaine C1, CChaine C2);
					// chaines
	friend bool operator== (CChaine C, char c);
	friend bool operator== (char c, CChaine C);
	friend bool operator== (CChaine C, char* pchar);
	friend bool operator== (char* pchar, CChaine C);
					// nombres
	friend bool operator== (CChaine C, int n);
	friend bool operator== (int n, CChaine C);
	friend bool operator== (CChaine C, double d);
	friend bool operator== (double d, CChaine C);
					// bool
	friend bool operator== (CChaine C, bool b);
	friend bool operator== (bool b, CChaine C);

				// Différence
	friend bool operator!= (CChaine C1, CChaine C2);
					// chaines
	friend bool operator!= (CChaine C, char c);
	friend bool operator!= (char c, CChaine C);
	friend bool operator!= (CChaine C, char* pchar);
	friend bool operator!= (char* pchar, CChaine C);
					// nombres
	friend bool operator!= (CChaine C, int n);
	friend bool operator!= (int n, CChaine C);
	friend bool operator!= (CChaine C, double d);
	friend bool operator!= (double d, CChaine C);
					// bool
	friend bool operator!= (CChaine C, bool b);
	friend bool operator!= (bool b, CChaine C);

				// Comparaison
					// inf
	friend bool operator< (CChaine C, int n);
	friend bool operator< (int n, CChaine C);
	friend bool operator< (CChaine C, double d);
	friend bool operator< (double d, CChaine C);
					// inf egal
	friend bool operator<= (CChaine C, int n);
	friend bool operator<= (int n, CChaine C);
	friend bool operator<= (CChaine C, double d);
	friend bool operator<= (double d, CChaine C);
					// sup
	friend bool operator> (CChaine C, int n);
	friend bool operator> (int n, CChaine C);
	friend bool operator> (CChaine C, double d);
	friend bool operator> (double d, CChaine C);
					// sup egal
	friend bool operator>= (CChaine C, int n);
	friend bool operator>= (int n, CChaine C);
	friend bool operator>= (CChaine C, double d);
	friend bool operator>= (double d, CChaine C);


//-------------------------------------------------------------------------------------------------------------------------------
		// manipulation
//-------------------------------------------------------------------------------------------------------------------------------

			// Find
	int Find(CChaine C);
	int Find(char c);
	int Find(char* pchar);

			// Get/Set
				// insert à
	char GetAt(int i);

	void SetAt(int i, CChaine C);
	void SetAt(int i, char c);
	void SetAt(int i, char* pchar);

				// insert depuis
	CChaine GetFrom(int i);

	void SetFrom(int i, CChaine C);
	void SetFrom(int i, char c);
	void SetFrom(int i, char* pchar);

				// insert entre
	CChaine GetFromTo(int i, int n);

	void SetFromTo(int i, int n, CChaine C);
	void SetFromTo(int i, int n, char c);
	void SetFromTo(int i, int n, char* pchar);

				// insert jusqu'à
	CChaine GetTo(int n);

	void SetTo(int n, CChaine C);
	void SetTo(int n, char c);
	void SetTo(int n, char* pchar);


//-------------------------------------------------------------------------------------------------------------------------------
		// Transformation
//-------------------------------------------------------------------------------------------------------------------------------
			// int
	friend CChaine Int(int n);
	friend int Int(CChaine C);	// 69->"erreur"

			// double
	friend CChaine Double(double d);
	friend double Double(CChaine C);	// 69.69->"erreur"

			// bool
	friend CChaine Bool(bool bBinaire);
	friend bool Bool(CChaine C);	// true->"erreur


//-------------------------------------------------------------------------------------------------------------------------------
		// accès en lecture
//-------------------------------------------------------------------------------------------------------------------------------
	int Get_m_nC();		// retourne le nombre de lettre de la chaine + '\0'
	char* Get_m_pChar();	// retourne la chaine de caractère
	int Get_Length();	// retourne le nombre de lettre de la chaine
	char operator[] (int i);	// retourne le caractère "i+1" de la chaine


//-------------------------------------------------------------------------------------------------------------------------------
		// Flux
//-------------------------------------------------------------------------------------------------------------------------------
	friend ostream& operator<< (ostream&, CChaine & C);
	friend istream& operator>> (istream&, CChaine & C);


//-------------------------------------------------------------------------------------------------------------------------------
		// Load/Save
//-------------------------------------------------------------------------------------------------------------------------------
			// .txt
			// .rtf
			// Binaire
	int Write(fstream& fs);	// 1->OK, -1->erreur écriture, -2->fin de chaine atteint trop tôt, -3->fin de chaine non atteinte
	int Read(fstream& fs);	// 1->OK, -1->erreur lecture, -2->fin de chaine atteint trop tôt, -3->fin de chaine non atteinte, -4->nombre de char négatif



//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------


};



