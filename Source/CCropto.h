


/* ************************************************************************************************************ */
	/* **************************************************************************************************** */
/* ************************************************************************************************************ */
	/*


	CCropto -- Classe (m�re) offrant des outils pour (d�)chiffrer un fichier


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



#pragma once



#include <fstream>

using namespace std;



class CCropto
{

protected:	// obligatoire pour l'h�ritage : private l'est aussi pour les classes filles :'(


	int m_nNbCharKey;	/// nombre de char dans la clef
	char* m_pstrKey;		/// valeurs de la clef

	bool m_bChiffr;	/// true : Chiffrement ; false : D�chiffrement

	ifstream m_ifs;		/// flux du fichier � (d�)chiffrer
	ofstream m_ofs;		/// flux du fichier de sorti


	char m_cC;		/// char en cours des donn�es



private:


	char m_cKey;	/// char en cours de la clef

	int m_nKi;	/// compteur sur la clef
	bool m_bKeyLeftToRight;	/// indicateur sur la lecture de la clef  ;; true : de 0 � m_nNbCharKey-1 / false : de m_nNbCharKey-1 � 0



public:


//-------------------------------------------------------------------------------------------------------------------------------
		// Constructeurs
//-------------------------------------------------------------------------------------------------------------------------------

	CCropto();
	~CCropto();



//-------------------------------------------------------------------------------------------------------------------------------
		// GetKey
//-------------------------------------------------------------------------------------------------------------------------------

	void CCropto_Set_Key(int nNbCharKey, char* strKey);	/// r�cup�re la taille de la clef et ses valeurs

	void CCropto_Set_m_bChiffr(bool bChiffr);	/// r�cup�re le mode de chiffrement ;; true : chiffrement / false : d�chiffrement



//-------------------------------------------------------------------------------------------------------------------------------
		// Open/Close Fichiers
//-------------------------------------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------------------------------------
			// Fichier Source

	bool CCropto_SourceFile_Open(char* strPath);	/// ouvre le fichier source
	bool CCropto_SourceFile_Close();	/// ferme le fichier source


	//-------------------------------------------------------------------------------------------------------------------------------
			// Fichier de sortie

	bool CCropto_OutputFile_Open(char* strPath);	/// ouvre le fichier de sortie
	bool CCropto_OutputFile_Close();	/// ferme le fichier de sortie



//-------------------------------------------------------------------------------------------------------------------------------
		// Algo Crypto
//-------------------------------------------------------------------------------------------------------------------------------

	void CCropto_Crypto_Chiffre();		/// Chiffre le char en cours et impl�mente la clef  ::  GetcKey + Chiffre + SetnKey

	void CCropto_Crypto_Dechiffre();	/// D�chiffre le char en cours et impl�mente la clef  ::  GetcKey + Dechiffre + SetnKey


	//-------------------------------------------------------------------------------------------------------------------------------
			// Impl�mentations sur la clef

	void CCropto_Crypto_GetcKey();	/// retourne m_cKey modifi� par les impl�mentations

	void CCropto_Crypto_SetnKey();		/// impl�mentation de la clef  ::  m_nKi compteur sur la clef ; m_nKn compteur des utilisations de la clef


	//-------------------------------------------------------------------------------------------------------------------------------
			// Chiffr/D�chiffr char

	void CCropto_Crypto_Chiffre_char();	 /// chiffre m_cC avec m_cKey

	void CCropto_Crypto_Dechiffre_char();	/// d�chiffre m_cC avec m_cKey



//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------


};










