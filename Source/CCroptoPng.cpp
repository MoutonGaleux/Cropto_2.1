


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





#include "CCroptoPng.h"






//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
			// Constructeurs
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------



CCroptoPng::CCroptoPng()
: m_unChunkLength(0)

, m_ucC1('\0')
, m_ucC2('\0')
, m_ucC3('\0')
, m_ucC4('\0')
{
}


CCroptoPng::~CCroptoPng()
{
}






//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
			// Initialisation
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------



int CCroptoPng::CCroptoPng_Init(int nNbCharKey, char* strKey, bool bChiffr, char* strSourcePath, char* strOutputPath)
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



void CCroptoPng::CCroptoPng_Crypto()
	/// lance le (dé)chiffrement
{

		// Lancement du (dé)chiffrement

	if(m_bChiffr)	// chiffrement
	{

		CCroptoPng_Crypto_Chiffre();

	}
	else	// déchiffrement
	{

		CCroptoPng_Crypto_Dechiffre();

	}

}




	//-------------------------------------------------------------------------------------------------------------------------------
				// Copie des MétaDonnées
	//-------------------------------------------------------------------------------------------------------------------------------



void CCroptoPng::CCroptoPng_Copie_Signature()
	/// copie la signature png
{

	for(int i=0; i<8; i++)
	{

		m_ifs.read((char*)&m_cC, sizeof(char));	// lecture de la signature png de la source
		m_ofs.write((char*)&m_cC, sizeof(char));	// copie de la signature png dans le fichier de sortie

	}

}


void CCroptoPng::CCroptoPng_Copie_Chunk_Length()
	/// copie la taille du Data du Chunk (et "récupère" sa taille en int)
{

	m_ifs.read((char*)&m_ucC1, sizeof(char));	// lecture du 1° char de Taille du Data du Chunk en cours de la source
	m_ofs.write((char*)&m_ucC1, sizeof(char));	// copie du 1° char de Taille du Data du Chunk dans le fichier de sortie

	m_ifs.read((char*)&m_ucC2, sizeof(char));	// lecture du 2°
	m_ofs.write((char*)&m_ucC2, sizeof(char));	// copie du 2°

	m_ifs.read((char*)&m_ucC3, sizeof(char));	// lecture du 3°
	m_ofs.write((char*)&m_ucC4, sizeof(char));	// copie du 3°

	m_ifs.read((char*)&m_ucC4, sizeof(char));	// lecture du 4°
	m_ofs.write((char*)&m_ucC4, sizeof(char));	// copie du 4°


	m_unChunkLength = (m_ucC1 * 16777216) + (m_ucC2 * 65536) + (m_ucC3 * 256) + m_ucC4;		// (char[4]) c1,c2,c3,c4 -> (int) c1*((2^8)^3) + c2*((2^8)^2) + c3*((2^8)^1) + c4*((2^8)^0)

}


bool CCroptoPng::CCroptoPng_Copie_Chunk_Type()
	/// copie le Type du Chunk
{

	bool bIDAT = false;


	m_ifs.read((char*)&m_ucC1, sizeof(char));	// lecture du 1° char du Type du Chunk en cours de la source
	m_ofs.write((char*)&m_ucC1, sizeof(char));	// copie du 1° char du Type du Chunk dans le fichier de sortie

	m_ifs.read((char*)&m_ucC2, sizeof(char));	// lecture du 2°
	m_ofs.write((char*)&m_ucC2, sizeof(char));	// copie du 2°

	m_ifs.read((char*)&m_ucC3, sizeof(char));	// lecture du 3°
	m_ofs.write((char*)&m_ucC3, sizeof(char));	// copie du 3°

	m_ifs.read((char*)&m_ucC4, sizeof(char));	// lecture du 4°
	m_ofs.write((char*)&m_ucC4, sizeof(char));	// copie du 4°


	if( (m_ucC1 == 73) && (m_ucC2 == 68) && (m_ucC3 == 65) && (m_ucC4 == 84) )	// 'I' 'D' 'A' 'T'
	{
		bIDAT = true;
	}


	return bIDAT;

}


void CCroptoPng::CCroptoPng_Copie_Chunk_Data()
	/// Chiffre et sauve le Data d'un Chunk IDAT
{

	for(unsigned int i=0; i<m_unChunkLength; i++)
	{

		m_ifs.read((char*)&m_cC, sizeof(char));	// lecture du char en cours de la source
		m_ofs.write((char*)&m_cC, sizeof(char));	// copie

	}

}


void CCroptoPng::CCroptoPng_Copie_Chunk_CRC()
	/// copie le CRC du Chunk
{

	for(int i=0; i<4; i++)
	{

		m_ifs.read((char*)&m_cC, sizeof(char));	// lecture du CRC du Chunk en cours de la source
		m_ofs.write((char*)&m_cC, sizeof(char));	// copie du CRC du Chunk en cours dans le fichier de sortie

	}

}



	//-------------------------------------------------------------------------------------------------------------------------------
				// Chiffrement
	//-------------------------------------------------------------------------------------------------------------------------------


void CCroptoPng::CCroptoPng_Crypto_Chiffre_IDAT()
	/// Chiffre et sauve le Data d'un Chunk IDAT
{

	for(unsigned int i=0; i<m_unChunkLength; i++)
	{

		m_ifs.read((char*)&m_cC, sizeof(char));	// lecture du char en cours de la source


		CCropto_Crypto_Chiffre();	// Chiffre le char en cours de la source


		m_ofs.write((char*)&m_cC, sizeof(char));	// save

	}

}


void CCroptoPng::CCroptoPng_Crypto_Chiffre()
	/// Chiffre et sauve un .png
{

		// copie de la signature PNG

	CCroptoPng_Copie_Signature();



	bool bIDAT = false;	// bool pour chunk IDAT


	while(m_ifs.good())	// lit les chunks du .png tant qu'il y en a
	{

			// copie du Length (et récupération de m_unChunkLength)

		CCroptoPng_Copie_Chunk_Length();


			// copie du type

		bIDAT = CCroptoPng_Copie_Chunk_Type();


			// chiffrement du Data du Chunk

		if(bIDAT)	// si Chunk IDAT
		{

			CCroptoPng_Crypto_Chiffre_IDAT();	// Chiffre et sauve les Data du Chunk en cours

		}
		else	// si autre que IDAT
		{

			CCroptoPng_Copie_Chunk_Data();	// Copie les Data du Chunk en cours

		}


			// copie du CRC du Chunk

		CCroptoPng_Copie_Chunk_CRC();

	}

}



	//-------------------------------------------------------------------------------------------------------------------------------
				// Déchiffrement
	//-------------------------------------------------------------------------------------------------------------------------------


void CCroptoPng::CCroptoPng_Crypto_Dechiffre_IDAT()
	/// Chiffre et sauve le Data d'un Chunk IDAT
{

	for(unsigned int i=0; i<m_unChunkLength; i++)
	{

		m_ifs.read((char*)&m_cC, sizeof(char));	// lecture du char en cours de la source


		CCropto_Crypto_Dechiffre();	// Chiffre le char en cours de la source


		m_ofs.write((char*)&m_cC, sizeof(char));	// save

	}

}


void CCroptoPng::CCroptoPng_Crypto_Dechiffre()
	/// Déchiffre et sauve un .png
{

		// copie de la signature PNG

	CCroptoPng_Copie_Signature();


	bool bIDAT = false;	// bool pour chunk IDAT

	while(m_ifs.good())	// lit les chunks du .png tant qu'il y en a
	{

			// copie du Length (et récupération de m_unChunkLength)

		CCroptoPng_Copie_Chunk_Length();


			// copie du type

		bIDAT = CCroptoPng_Copie_Chunk_Type();


			// chiffrement du Data du Chunk

		if(bIDAT)	// si Chunk IDAT
		{

			CCroptoPng_Crypto_Dechiffre_IDAT();	// Chiffre et sauve les Data du Chunk en cours

		}
		else	// si autre que IDAT
		{

			CCroptoPng_Copie_Chunk_Data();	// Copie les Data du Chunk en cours

		}


			// copie du CRC du Chunk

		CCroptoPng_Copie_Chunk_CRC();

	}

}



//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------






























