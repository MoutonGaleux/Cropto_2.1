


/* ************************************************************************************************************ */
	/* **************************************************************************************************** */
/* ************************************************************************************************************ */
	/*


	CCroptoPng -- Classe fille de CCopto (dé)chiffrant un fichier png, ne modifie que les données des Chunk IDAT (chiffre l'image mais pas ses métadonnées)


		Copyright (C)  2015   MiG (alias Benoit Nocaudie)


	This file is part of Cropto.

	CCroptoPng is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	CCroptoPng is distributed in the hope that it will be useful,
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




#include "CCropto.h"




class CCroptoPng : public CCropto
{

private:

	unsigned int m_unChunkLength;	/// taille du Data du Chunk en cours

	unsigned char m_ucC1, m_ucC2, m_ucC3, m_ucC4;	/// char pour les Chunks Length et Type



public:


//-------------------------------------------------------------------------------------------------------------------------------
		// Constructeurs
//-------------------------------------------------------------------------------------------------------------------------------

	CCroptoPng();
	~CCroptoPng();


//-------------------------------------------------------------------------------------------------------------------------------
		// Initialisation
//-------------------------------------------------------------------------------------------------------------------------------

	int CCroptoPng_Init(int nNbCharKey, char* strKey, bool bChiffr, char* strSourcePath, char* strOutputPath);	/// initialise le CCropto  ;;  0 : Init OK / 1 : erreur ouverture SourceFile / 2 : erreur ouverture OutputFile / 3 : erreur sur les 2



//-------------------------------------------------------------------------------------------------------------------------------
		// Algo Crypto
//-------------------------------------------------------------------------------------------------------------------------------

	void CCroptoPng_Crypto();		/// lance le (dé)chiffrement


	//-------------------------------------------------------------------------------------------------------------------------------
			// Copie MétaDonnées

	void CCroptoPng_Copie_Signature();	/// copie la signature png

	void CCroptoPng_Copie_Chunk_Length();	/// copie la taille du Data du Chunk (et "récupère" sa taille en int)
	bool CCroptoPng_Copie_Chunk_Type();	/// copie le Type du Chunk  ;;  return true si Chunk IDAT (données image)
	void CCroptoPng_Copie_Chunk_Data();	/// copie le Data du Chunk
	void CCroptoPng_Copie_Chunk_CRC();		/// copie le CRC du Chunk


	//-------------------------------------------------------------------------------------------------------------------------------
			// Chiffrement

	void CCroptoPng_Crypto_Chiffre_IDAT();		/// Chiffre et sauve le Data d'un Chunk IDAT

	void CCroptoPng_Crypto_Chiffre();		/// Chiffre et sauve un .png


	//-------------------------------------------------------------------------------------------------------------------------------
			// Déchiffrement

	void CCroptoPng_Crypto_Dechiffre_IDAT();		/// Déchiffre et sauve le Data d'un Chunk IDAT

	void CCroptoPng_Crypto_Dechiffre();		/// Déchiffre et sauve un .png



//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------


};










