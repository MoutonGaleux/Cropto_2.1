


/* ************************************************************************************************************ */
	/* **************************************************************************************************** */
/* ************************************************************************************************************ */
	/*


	CCroptoBmp -- Classe fille de CCopto (dé)chiffrant un fichier bmp, mais laissant le header intact


		Copyright (C)  2015   MiG (alias Benoit Nocaudie)


	This file is part of Cropto.

	CCroptoBmp is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	CCroptoBmp is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Cropto.  If not, see <http://www.gnu.org/licenses/>.



	*/
/* ************************************************************************************************************ */
	/* **************************************************************************************************** */
/* ************************************************************************************************************ */




#include "CCroptoBmp.h"






//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
			// Constructeurs
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------



CCroptoBmp::CCroptoBmp()
{
}


CCroptoBmp::~CCroptoBmp()
{
}






//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
			// Initialisation
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------



int CCroptoBmp::CCroptoBmp_Init(int nNbCharKey, char* strKey, bool bChiffr, char* strSourcePath, char* strOutputPath)
	/// initialise le CCropto  ;;  0 : Init OK / 1 : erreur ouverture SourceFile / 2 : erreur ouverture OutputFile / 3 : erreur sur les 2
{

	int nEtat = 0;


	CCropto_Set_Key(nNbCharKey, strKey);	// initialisation de la clef

	CCropto_Set_m_bChiffr(bChiffr);	// initialisation du mode chiffre/déchiffre

	if(!(CCropto_SourceFile_Open(strSourcePath)))	// ouverture du fichier Source
	{
		nEtat += 1;
	}

	if(!(CCropto_OutputFile_Open(strOutputPath)))	// ouverture du fichier de sortie
	{
		nEtat += 2;
	}


	return nEtat;

}






//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
			// Algo Crypto
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------



void CCroptoBmp::CCroptoBmp_Crypto()
	/// lance le (dé)chiffrement
{

	if(m_bChiffr)	// chiffrement
	{

		CCroptoBmp_Crypto_Chiffre();

	}
	else	// déchiffrement
	{

		CCroptoBmp_Crypto_Dechiffre();

	}

}



	//-------------------------------------------------------------------------------------------------------------------------------
				// Copie MétaDonnées
	//-------------------------------------------------------------------------------------------------------------------------------



void CCroptoBmp::CCroptoBmp_Copie_Header()
	/// copie le header d'un .bmp
{

	int nOffset;

	m_ifs.seekg(10, ios_base::beg);	// décalage vers la taille de l'offset

	m_ifs.read((char*)&nOffset, sizeof(int));	// récupération de l'offset de l'image

	m_ifs.seekg(0, ios_base::beg);	// retour au début du fichier



	for(int i=0; i<nOffset; i++)	// parcours du header
	{

		m_ifs.read((char*)&m_cC, sizeof(char));	// lecture de chaque char de la source
		m_ofs.write((char*)&m_cC, sizeof(char));	// écriture de ces char dans le fichier de sortie

	}

}



	//-------------------------------------------------------------------------------------------------------------------------------
				// Chiffrement/Déchiffrement
	//-------------------------------------------------------------------------------------------------------------------------------



void CCroptoBmp::CCroptoBmp_Crypto_Chiffre()
	/// Chiffre et sauve
{

	CCroptoBmp_Copie_Header();	// copie du header


	while(m_ifs.read((char*)&m_cC, sizeof(char)))	// lit le char en cours du txt (tant qu'il y en as)
	{

		CCropto_Crypto_Chiffre();	// Chiffre le char en cours de la source


		m_ofs.write((char*)&m_cC, sizeof(char));	// save

	}

}


void CCroptoBmp::CCroptoBmp_Crypto_Dechiffre()
	/// Déchiffre et sauve
{

	CCroptoBmp_Copie_Header();	// copie du header


	while(m_ifs.read((char*)&m_cC, sizeof(char)))	// lit le char en cours du txt (tant qu'il y en as)
	{

		CCropto_Crypto_Dechiffre();	// Chiffre le char en cours de la source


		m_ofs.write((char*)&m_cC, sizeof(char));	// save

	}

}



//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------





















