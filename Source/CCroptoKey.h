


/* ************************************************************************************************************ */
	/* **************************************************************************************************** */
/* ************************************************************************************************************ */
	/*


	CCroptoKey -- Classe fille de CCopto (dé)chiffrant un contenu et le renvoyant sous forme de CChaine


		Copyright (C)  2015   MiG (alias Benoit Nocaudie)


	This file is part of Cropto.

	CCroptoKey is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	CCroptoKey is distributed in the hope that it will be useful,
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


#include "CChaine.h"




class CCroptoKey : public CCropto
{

private:

	CChaine m_chKey;



public:


//-------------------------------------------------------------------------------------------------------------------------------
		// Constructeurs
//-------------------------------------------------------------------------------------------------------------------------------

	CCroptoKey();
	~CCroptoKey();



//-------------------------------------------------------------------------------------------------------------------------------
		// Algo Crypto
//-------------------------------------------------------------------------------------------------------------------------------

	void CCroptoKey_Crypto(int nMode);		/// lance le (dé)chiffrement  ;;  1 : Aff / 2 : Save / 3 : Aff-Save  ;;  true : Chiffrement / false : Déchiffrement


	//-------------------------------------------------------------------------------------------------------------------------------
			// Chiffrement

	void CCroptoKey_Crypto_Chiffre();		/// Chiffre et sauve


	//-------------------------------------------------------------------------------------------------------------------------------
			// Déchiffrement

	void CCroptoKey_Crypto_Dechiffre();		/// Déhiffre et sauve



//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------


};

















