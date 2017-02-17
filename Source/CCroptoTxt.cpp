


/* ************************************************************************************************************ */
	/* **************************************************************************************************** */
/* ************************************************************************************************************ */
	/*


	CCroptoTxt -- Classe fille de CCopto (dé)chiffrant un fichier en entier


		Copyright (C)  2015   MiG (alias Benoit Nocaudie)


	This file is part of Cropto.

	CCroptoTxt is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	CCroptoTxt is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Cropto.  If not, see <http://www.gnu.org/licenses/>.



	*/
/* ************************************************************************************************************ */
	/* **************************************************************************************************** */
/* ************************************************************************************************************ */




#include "CCroptoTxt.h"



#include <iostream>

using namespace std;






//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
			// Constructeurs
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------



CCroptoTxt::CCroptoTxt()
: m_bOutputFile(false)
{
}


CCroptoTxt::~CCroptoTxt()
{
}






//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
			// Initialisation
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------



int CCroptoTxt::CCroptoTxt_Init(int nNbCharKey, char* strKey, bool bChiffr, char* strSourcePath, char* strOutputPath)
		/// initialise le CCropto  ;;  0 : Init OK / 1 : erreur ouverture SourceFile / 2 : erreur ouverture OutputFile / 3 : erreur sur les 2
{

	int nEtat = 0;


	CCropto_Set_Key(nNbCharKey, strKey);	// initialisation de la clef

	CCropto_Set_m_bChiffr(bChiffr);	// initialisation du mode chiffre/déchiffre

	if(!(CCropto_SourceFile_Open(strSourcePath)))	// ouverture du fichier Source
	{
		nEtat += 1;
	}

	if(strOutputPath != NULL)
	{
		m_bOutputFile = true;

		if(!(CCropto_OutputFile_Open(strOutputPath)))	// ouverture du fichier de sortie
		{
			nEtat += 2;
		}
	}


	return nEtat;

}






//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
			// Algo Crypto
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------



void CCroptoTxt::CCroptoTxt_Crypto(int nMode)
	/// lance le (dé)chiffrement  ;;  1 : Aff / 2 : Save / 3 : Aff-Save  ;;  true : Chiffrement / false : Déchiffrement
{

	if(nMode == 1)	// aff
	{

		if(m_bChiffr)	// chiffrement
		{
			CCroptoTxt_Crypto_Chiffre_Aff();
		}
		else	// déchiffrement
		{
			CCroptoTxt_Crypto_Dechiffre_Aff();
		}

	}

	if(m_bOutputFile)
	{

		if(nMode == 2)	// save
		{

			if(m_bChiffr)	// chiffrement
			{
				CCroptoTxt_Crypto_Chiffre_Save();
			}
			else	// déchiffrement
			{
				CCroptoTxt_Crypto_Dechiffre_Save();
			}

		}
		else if(nMode == 3)	// aff-save
		{

			if(m_bChiffr)	// chiffrement
			{
				CCroptoTxt_Crypto_Chiffre_AffSave();
			}
			else	// déchiffrement
			{
				CCroptoTxt_Crypto_Dechiffre_AffSave();
			}

		}

	}

}



	//-------------------------------------------------------------------------------------------------------------------------------
				// Chiffrement
	//-------------------------------------------------------------------------------------------------------------------------------



void CCroptoTxt::CCroptoTxt_Crypto_Chiffre_Aff()
	/// Chiffre et Affiche
{

	while(m_ifs.read((char*)&m_cC, sizeof(char)))	// lit le char en cours du txt (tant qu'il y en as)
	{

		CCropto_Crypto_Chiffre();	// Chiffre le char en cours de la source


		cout << m_cC;	// aff

	}

}


void CCroptoTxt::CCroptoTxt_Crypto_Chiffre_Save()
	/// Chiffre et sauve
{

	while(m_ifs.read((char*)&m_cC, sizeof(char)))	// lit le char en cours du txt (tant qu'il y en as)
	{

		CCropto_Crypto_Chiffre();	// Chiffre le char en cours de la source


		m_ofs.write((char*)&m_cC, sizeof(char));	// save

	}

}


void CCroptoTxt::CCroptoTxt_Crypto_Chiffre_AffSave()
	/// Chiffre et Affiche et sauve
{

	while(m_ifs.read((char*)&m_cC, sizeof(char)))	// lit le char en cours du txt (tant qu'il y en as)
	{

		CCropto_Crypto_Chiffre();	// Chiffre le char en cours de la source


		m_ofs.write((char*)&m_cC, sizeof(char));	// save
		cout << m_cC;	// aff

	}

}



	//-------------------------------------------------------------------------------------------------------------------------------
				// Déchiffrement
	//-------------------------------------------------------------------------------------------------------------------------------



void CCroptoTxt::CCroptoTxt_Crypto_Dechiffre_Aff()
	/// Déhiffre et Affiche
{

	while(m_ifs.read((char*)&m_cC, sizeof(char)))	// lit le char en cours du txt (tant qu'il y en as)
	{

		CCropto_Crypto_Dechiffre();	// Chiffre le char en cours de la source


		cout << m_cC;	// aff

	}

}


void CCroptoTxt::CCroptoTxt_Crypto_Dechiffre_Save()
	/// Déhiffre et sauve
{

	while(m_ifs.read((char*)&m_cC, sizeof(char)))	// lit le char en cours du txt (tant qu'il y en as)
	{

		CCropto_Crypto_Dechiffre();	// Chiffre le char en cours de la source


		m_ofs.write((char*)&m_cC, sizeof(char));	// save

	}

}


void CCroptoTxt::CCroptoTxt_Crypto_Dechiffre_AffSave()
	/// Déhiffre et Affiche et sauve
{

	while(m_ifs.read((char*)&m_cC, sizeof(char)))	// lit le char en cours du txt (tant qu'il y en as)
	{

		CCropto_Crypto_Dechiffre();	// Chiffre le char en cours de la source


		m_ofs.write((char*)&m_cC, sizeof(char));	// save
		cout << m_cC;	// aff

	}

}





//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
















