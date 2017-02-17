


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



#pragma once




#include "CCropto.h"




class CCroptoBmp : public CCropto
{

public:


//-------------------------------------------------------------------------------------------------------------------------------
		// Constructeurs
//-------------------------------------------------------------------------------------------------------------------------------

	CCroptoBmp();
	~CCroptoBmp();


//-------------------------------------------------------------------------------------------------------------------------------
		// Initialisation
//-------------------------------------------------------------------------------------------------------------------------------

	int CCroptoBmp_Init(int nNbCharKey, char* strKey, bool bChiffr, char* strSourcePath, char* strOutputPath);	/// initialise le CCropto  ;;  0 : Init OK / 1 : erreur ouverture SourceFile / 2 : erreur ouverture OutputFile / 3 : erreur sur les 2



//-------------------------------------------------------------------------------------------------------------------------------
		// Algo Crypto
//-------------------------------------------------------------------------------------------------------------------------------

	void CCroptoBmp_Crypto();		/// lance le (dé)chiffrement


	//-------------------------------------------------------------------------------------------------------------------------------
			// Copie MétaDonnées

	void CCroptoBmp_Copie_Header();	/// copie le header d'un .bmp


	//-------------------------------------------------------------------------------------------------------------------------------
			// Chiffrement/Déchiffrement

	void CCroptoBmp_Crypto_Chiffre();		/// Chiffre et sauve un .bmp

	void CCroptoBmp_Crypto_Dechiffre();		/// Déchiffre et sauve un .bmp



//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------


};

















