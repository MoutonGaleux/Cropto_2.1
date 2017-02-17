


/* ************************************************************************************************************ */
	/* **************************************************************************************************** */
/* ************************************************************************************************************ */
	/*


	CCropto -- Classe (mère) offrant des outils pour (dé)chiffrer un fichier


		Copyright (C)  2015   MiG (alias Benoit Nocaudie)


	This file is part of Cropto.

	CCropto is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	CCropto is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Cropto.  If not, see <http://www.gnu.org/licenses/>.



	*/
/* ************************************************************************************************************ */
	/* **************************************************************************************************** */
/* ************************************************************************************************************ */




#include "CCropto.h"






//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
			// Constructeurs
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------



CCropto::CCropto()
: m_nNbCharKey(0)
, m_pstrKey(NULL)

, m_bChiffr(true)

, m_ifs(NULL)	// ??
, m_ofs(NULL)	// ??


, m_cC('\0')
, m_cKey('\0')

, m_nKi(0)
, m_bKeyLeftToRight(true)
{

	m_ifs.clear();
	m_ofs.clear();

}


CCropto::~CCropto()
{

	if(m_pstrKey != NULL)
	{
		delete[] m_pstrKey;
	}
	m_pstrKey = NULL;


	if(m_ifs.is_open())
	{
		m_ifs.close();
	}
	m_ifs.clear();


	if(m_ofs.is_open())
	{
		m_ofs.close();
	}
	m_ofs.clear();

}





//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
			// GetKey
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------



void CCropto::CCropto_Set_Key(int nNbCharKey, char* strKey)
	/// récupère la taille de la clef et ses valeurs
{

	if(m_pstrKey != NULL)
	{
		if(m_nNbCharKey != nNbCharKey)
		{
			delete[] m_pstrKey;
			m_pstrKey = NULL;
		}
	}

	if(m_pstrKey == NULL)
	{
		m_nNbCharKey = nNbCharKey;

		m_pstrKey = new char[m_nNbCharKey];
	}

	for(int i=0; i<m_nNbCharKey; i++)
	{
		m_pstrKey[i] = strKey[i];
	}

}


void CCropto::CCropto_Set_m_bChiffr(bool bChiffr)
	/// récupère le mode de chiffrement ;; true : chiffrement / false : déchiffrement
{

	m_bChiffr = bChiffr;

}





//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
			// Path Fichiers
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------



	//-------------------------------------------------------------------------------------------------------------------------------
				// Fichier Source
	//-------------------------------------------------------------------------------------------------------------------------------


bool CCropto::CCropto_SourceFile_Open(char* strPath)
	/// ouvre le fichier source
{

	if(m_ifs.is_open())	// si déjà ouvert
	{
		m_ifs.close();	// fermeture
		m_ifs.clear();	// et clear
	}


	m_ifs.open(strPath, ios::in | ios::binary);	// ouverture en lecture binaire du fichier source


	return m_ifs.good();	// retourne l'état de l'ouverture

}


bool CCropto::CCropto_SourceFile_Close()
	/// ferme le fichier source
{

	if(m_ifs.is_open())
	{
		m_ifs.close();
	}


	return !m_ifs.is_open();

}



	//-------------------------------------------------------------------------------------------------------------------------------
				// Fichier de sortie
	//-------------------------------------------------------------------------------------------------------------------------------


bool CCropto::CCropto_OutputFile_Open(char* strPath)
	/// ouvre le fichier de sortie
{

	if(m_ofs.is_open())	// si déjà ouvert
	{
		m_ofs.close();	// fermeture
		m_ofs.clear();	// et clear
	}


	m_ofs.open(strPath, ios::out | ios::binary);	// ouverture en écriture binaire du fichier source


	return m_ofs.good();	// retourn l'état de l'ouverture

}


bool CCropto::CCropto_OutputFile_Close()
	/// ferme le fichier de sortie
{

	if(m_ofs.is_open())
	{
		m_ofs.close();
	}


	return !m_ofs.is_open();

}






//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
			// Algo Crypto
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------



void CCropto::CCropto_Crypto_Chiffre()
	/// Chiffre le char en cours et implémente la clef  ::  GetcKey + Chiffre + SetnKey
{

	CCropto_Crypto_GetcKey();

	CCropto_Crypto_Chiffre_char();

	CCropto_Crypto_SetnKey();

}


void CCropto::CCropto_Crypto_Dechiffre()
	/// Déchiffre le char en cours et implémente la clef  ::  GetcKey + Dechiffre + SetnKey
{

	CCropto_Crypto_GetcKey();

	CCropto_Crypto_Dechiffre_char();

	CCropto_Crypto_SetnKey();

}



	//-------------------------------------------------------------------------------------------------------------------------------
				// Implémentations sur la clef
	//-------------------------------------------------------------------------------------------------------------------------------



void CCropto::CCropto_Crypto_GetcKey()
	/// retourne la caractère de la clef modifié par les implémentations
{

	m_cKey = m_pstrKey[m_nKi];

}


void CCropto::CCropto_Crypto_SetnKey()
	/// i compteur sur la clef ; n compteur des utilisations de la clef
{

	if(m_nKi == -1)	// si compteur sur la clef avant le début
	{

		m_bKeyLeftToRight = true;	// indication de lecure gauche->droite

		m_nKi = 0;	// initialisation du compteur sur la clef au début

	}
	else  if(m_nKi == m_nNbCharKey)	// si compteur sur la clef après la fin
	{

		m_bKeyLeftToRight = false;	// indication de lecure droite->gauche

		m_nKi = m_nNbCharKey-1;	// initialisation du compteur sur la clef à la fin

	}
	else
	{

		if(m_bKeyLeftToRight)	// si lecture "aller" de la clef
		{
			m_nKi++;	// incrémentation du compteur sur la clef
		}
		else	// si lectuere "retour" de la clef
		{
			m_nKi--;	// décrémentation du compteur sur la clef
		}

	}

}



	//-------------------------------------------------------------------------------------------------------------------------------
				// Chiffr/Déchiffr char
	//-------------------------------------------------------------------------------------------------------------------------------



void CCropto::CCropto_Crypto_Chiffre_char()
	/// chiffre le char
{

	m_cC += m_cKey;

}


void CCropto::CCropto_Crypto_Dechiffre_char()
	/// déchiffre le char
{

	m_cC -= m_cKey;

}





//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------



























