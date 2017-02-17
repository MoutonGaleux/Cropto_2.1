


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



#pragma once




#include "CCropto.h"




class CCroptoTxt : public CCropto
{

private:

	bool m_bOutputFile;




public:


//-------------------------------------------------------------------------------------------------------------------------------
		// Constructeurs
//-------------------------------------------------------------------------------------------------------------------------------

	CCroptoTxt();
	~CCroptoTxt();


//-------------------------------------------------------------------------------------------------------------------------------
		// Initialisation
//-------------------------------------------------------------------------------------------------------------------------------

	int CCroptoTxt_Init(int nNbCharKey, char* strKey, bool bChiffr, char* strSourcePath, char* strOutputPath = NULL);	/// initialise le CCropto  ;;  0 : Init OK / 1 : erreur ouverture SourceFile / 2 : erreur ouverture OutputFile / 3 : erreur sur les 2



//-------------------------------------------------------------------------------------------------------------------------------
		// Algo Crypto
//-------------------------------------------------------------------------------------------------------------------------------

	void CCroptoTxt_Crypto(int nMode);		/// lance le (dé)chiffrement  ;;  1 : Aff / 2 : Save / 3 : Aff-Save  ;;  true : Chiffrement / false : Déchiffrement


	//-------------------------------------------------------------------------------------------------------------------------------
			// Chiffrement

	void CCroptoTxt_Crypto_Chiffre_Save();		/// Chiffre et sauve
	void CCroptoTxt_Crypto_Chiffre_Aff();		/// Chiffre et Affiche
	void CCroptoTxt_Crypto_Chiffre_AffSave();	/// Chiffre et Affiche et sauve


	//-------------------------------------------------------------------------------------------------------------------------------
			// Déchiffrement

	void CCroptoTxt_Crypto_Dechiffre_Save();		/// Déhiffre et sauve
	void CCroptoTxt_Crypto_Dechiffre_Aff();		/// Déhiffre et Affiche
	void CCroptoTxt_Crypto_Dechiffre_AffSave();	/// Déhiffre et Affiche et sauve



//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------


};












