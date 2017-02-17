


/* ************************************************************************************************************ */
	/* **************************************************************************************************** */
/* ************************************************************************************************************ */
	/*


	CCroptoHtml -- Classe fille de CCopto (dé)chiffrant un fichier html, mais laissant les balises intactes


		Copyright (C)  2015   MiG (alias Benoit Nocaudie)


	This file is part of Cropto.

	CCroptoHtml is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	CCroptoHtml is distributed in the hope that it will be useful,
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




class CCroptoHtml : public CCropto
{

private:

	CChaine m_chBalise;

	bool m_bOutputFile;



public:


//-------------------------------------------------------------------------------------------------------------------------------
		// Constructeurs
//-------------------------------------------------------------------------------------------------------------------------------

	CCroptoHtml();
	~CCroptoHtml();


//-------------------------------------------------------------------------------------------------------------------------------
		// Initialisation
//-------------------------------------------------------------------------------------------------------------------------------

	int CCroptoHtml_Init(int nNbCharKey, char* strKey, bool bChiffr, char* strSourcePath, char* strOutputPath = NULL);	/// initialise le CCropto  ;;  0 : Init OK / 1 : erreur ouverture SourceFile / 2 : erreur ouverture OutputFile / 3 : erreur sur les 2



//-------------------------------------------------------------------------------------------------------------------------------
		// Algo Crypto
//-------------------------------------------------------------------------------------------------------------------------------

	void CCroptoHtml_Crypto(int nMode);		/// lance le (dé)chiffrement  ;;  1 : Aff / 2 : Save / 3 : Aff-Save  ;;  true : Chiffrement / false : Déchiffrement


	//-------------------------------------------------------------------------------------------------------------------------------
			// Détection de Balise

	bool CCroptoHtml_Crypto_IsBalise();		/// test si balise ou juste '<' et enregistre dans un CChaine


				// Copie de la Balise

	void CCroptoHtml_Crypto_Balise_Copie_Save();	/// copie la Balise  ;!;  set aussi les compteurs clef
	void CCroptoHtml_Crypto_Balise_Copie_Aff();		/// copie la Balise  ;!;  set aussi les compteurs clef
	void CCroptoHtml_Crypto_Balise_Copie_AffSave();	/// copie la Balise  ;!;  set aussi les compteurs clef


				// Chiffrement du contenu commençant par '<'

	void CCroptoHtml_Crypto_Balise_Chiffre_Save();		/// chiffre la fausse Balise
	void CCroptoHtml_Crypto_Balise_Chiffre_Aff();		/// chiffre la fausse Balise
	void CCroptoHtml_Crypto_Balise_Chiffre_AffSave();	/// chiffre la fausse Balise


				// Déchiffrement du contenu commençant par '<'

	void CCroptoHtml_Crypto_Balise_Dechiffre_Save();	/// déchiffre la fausse Balise
	void CCroptoHtml_Crypto_Balise_Dechiffre_Aff();		/// déchiffre la fausse Balise
	void CCroptoHtml_Crypto_Balise_Dechiffre_AffSave();	/// déchiffre la fausse Balise


	//-------------------------------------------------------------------------------------------------------------------------------
			// Chiffrement

	void CCroptoHtml_Crypto_Chiffre_Save();		/// Chiffre et sauve
	void CCroptoHtml_Crypto_Chiffre_Aff();		/// Chiffre et Affiche
	void CCroptoHtml_Crypto_Chiffre_AffSave();	/// Chiffre et Affiche et sauve


	//-------------------------------------------------------------------------------------------------------------------------------
			// Déchiffrement

	void CCroptoHtml_Crypto_Dechiffre_Save();		/// Déhiffre et sauve
	void CCroptoHtml_Crypto_Dechiffre_Aff();		/// Déhiffre et Affiche
	void CCroptoHtml_Crypto_Dechiffre_AffSave();	/// Déhiffre et Affiche et sauve



//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------


};












