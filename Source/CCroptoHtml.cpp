


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




#include "CCroptoHtml.h"


#include <iostream>






//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
			// Constructeurs
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------



CCroptoHtml::CCroptoHtml()
: m_chBalise()

, m_bOutputFile(false)
{
}


CCroptoHtml::~CCroptoHtml()
{
}






//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
			// Initialisation
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------



int CCroptoHtml::CCroptoHtml_Init(int nNbCharKey, char* strKey, bool bChiffr, char* strSourcePath, char* strOutputPath)
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



void CCroptoHtml::CCroptoHtml_Crypto(int nMode)
	/// lance le (dé)chiffrement  ;;  1 : Aff / 2 : Save / 3 : Aff-Save  ;;  true : Chiffrement / false : Déchiffrement
{

	if(nMode == 1)	// aff
	{

		if(m_bChiffr)	// chiffrement
		{
			CCroptoHtml_Crypto_Chiffre_Aff();
		}
		else	// déchiffrement
		{
			CCroptoHtml_Crypto_Dechiffre_Aff();
		}

	}
	else if(nMode == 2)	// save
	{

		if(m_bChiffr)	// chiffrement
		{
			CCroptoHtml_Crypto_Chiffre_Save();
		}
		else	// déchiffrement
		{
			CCroptoHtml_Crypto_Dechiffre_Save();
		}

	}
	else if(nMode == 3)	// aff-save
	{

		if(m_bChiffr)	// chiffrement
		{
			CCroptoHtml_Crypto_Chiffre_AffSave();
		}
		else	// déchiffrement
		{
			CCroptoHtml_Crypto_Dechiffre_AffSave();
		}

	}

}



	//-------------------------------------------------------------------------------------------------------------------------------
				// Détection de Balise
	//-------------------------------------------------------------------------------------------------------------------------------


bool CCroptoHtml::CCroptoHtml_Crypto_IsBalise()
	/// test si balise ou juste '<' et enregistre dans un CChaine
{

	bool bBalise = false;


	m_chBalise = CChaine(m_cC);	// initialisation de m_chBalise avec '<'


	bool bContinue = true;

	while(bContinue)
	{

		bContinue = m_ifs.read((char*)&m_cC, sizeof(char));	// lecture du char (et état de la lecture dans bContinue)


		if(m_cC == '<')	// si fausse balise
		{

			m_ifs.seekg(-1, ios_base::cur);	// remet m_ifs sur le '<' qui vient d'apparaitre

			bContinue = false;

		}
		else	// si autre char que '<'
		{

			m_chBalise += m_cC;	// on l'ajoute au CChaine


			if(m_cC == '>')	// si Balise
			{
				bContinue = false;

				bBalise = true;	// on le dit
			}

		}

	}


	return bBalise;

}



		//-------------------------------------------------------------------------------------------------------------------------------
					// Copie de la Balise


void CCroptoHtml::CCroptoHtml_Crypto_Balise_Copie_Save()
	/// copie la Balise  ;!;  set aussi les compteurs clef
{

	int nC = m_chBalise.Get_Length();

	for(int i=0; i<nC; i++)	// parcours de m_chBalise
	{
		m_cC = m_chBalise[i];

		CCropto_Crypto_SetnKey();	// implémentation des compteurs des clefs

		m_ofs.write((char*)&m_cC, sizeof(char));	// save du char de m_chBalise
	}

}


void CCroptoHtml::CCroptoHtml_Crypto_Balise_Copie_Aff()
	/// copie la Balise  ;!;  set aussi les compteurs clef
{

	int nC = m_chBalise.Get_Length();

	for(int i=0; i<nC; i++)
	{
		m_cC = m_chBalise[i];

		CCropto_Crypto_SetnKey();	// implémentation des compteurs des clefs

		cout << m_cC;	// aff
	}

}


void CCroptoHtml::CCroptoHtml_Crypto_Balise_Copie_AffSave()
	/// copie la Balise  ;!;  set aussi les compteurs clef
{

	int nC = m_chBalise.Get_Length();

	for(int i=0; i<nC; i++)
	{
		m_cC = m_chBalise[i];

		CCropto_Crypto_SetnKey();	// implémentation des compteurs des clefs

		m_ofs.write((char*)&m_cC, sizeof(char));	// save
		cout << m_cC;	// aff
	}

}



		//-------------------------------------------------------------------------------------------------------------------------------
					// Chiffrement du contenu commençant par '<'


void CCroptoHtml::CCroptoHtml_Crypto_Balise_Chiffre_Save()
	/// chiffre la fausse Balise
{

	int nC = m_chBalise.Get_Length();

	for(int i=0; i<nC; i++)
	{
		m_cC = m_chBalise[i];

		CCropto_Crypto_Chiffre();	// Chiffre le char en cours de la source

		m_ofs.write((char*)&m_cC, sizeof(char));	// save
	}

}


void CCroptoHtml::CCroptoHtml_Crypto_Balise_Chiffre_Aff()
	/// chiffre la fausse Balise
{

	int nC = m_chBalise.Get_Length();

	for(int i=0; i<nC; i++)
	{
		m_cC = m_chBalise[i];

		CCropto_Crypto_Chiffre();	// Chiffre le char en cours de la source

		cout << m_cC;	// aff
	}

}


void CCroptoHtml::CCroptoHtml_Crypto_Balise_Chiffre_AffSave()
	/// chiffre la fausse Balise
{

	int nC = m_chBalise.Get_Length();

	for(int i=0; i<nC; i++)
	{
		m_cC = m_chBalise[i];

		CCropto_Crypto_Chiffre();	// Chiffre le char en cours de la source

		m_ofs.write((char*)&m_cC, sizeof(char));	// save
		cout << m_cC;	// aff
	}

}



		//-------------------------------------------------------------------------------------------------------------------------------
					// Déchiffrement du contenu commençant par '<'


void CCroptoHtml::CCroptoHtml_Crypto_Balise_Dechiffre_Save()
	/// déchiffre la fausse Balise
{

	int nC = m_chBalise.Get_Length();

	for(int i=0; i<nC; i++)
	{
		m_cC = m_chBalise[i];

		CCropto_Crypto_Dechiffre();	// Chiffre le char en cours de la source

		m_ofs.write((char*)&m_cC, sizeof(char));	// save
	}

}


void CCroptoHtml::CCroptoHtml_Crypto_Balise_Dechiffre_Aff()
	/// déchiffre la fausse Balise
{

	int nC = m_chBalise.Get_Length();

	for(int i=0; i<nC; i++)
	{
		m_cC = m_chBalise[i];

		CCropto_Crypto_Dechiffre();	// Chiffre le char en cours de la source

		cout << m_cC;	// aff
	}

}


void CCroptoHtml::CCroptoHtml_Crypto_Balise_Dechiffre_AffSave()
	/// déchiffre la fausse Balise
{

	int nC = m_chBalise.Get_Length();

	for(int i=0; i<nC; i++)
	{
		m_cC = m_chBalise[i];

		CCropto_Crypto_Dechiffre();	// Chiffre le char en cours de la source

		m_ofs.write((char*)&m_cC, sizeof(char));	// save
		cout << m_cC;	// aff
	}

}





	//-------------------------------------------------------------------------------------------------------------------------------
				// Chiffrement
	//-------------------------------------------------------------------------------------------------------------------------------



void CCroptoHtml::CCroptoHtml_Crypto_Chiffre_Save()
	/// Chiffre et sauve
{

	while(m_ifs.read((char*)&m_cC, sizeof(char)))	// lit le char en cours du txt (tant qu'il y en as)
	{

		if(m_cC == '<')	// si début de Balise
		{

			if(CCroptoHtml_Crypto_IsBalise())	// si c'est une balise
			{

				CCroptoHtml_Crypto_Balise_Copie_Save();	// copie de la Balise (et implémente les compteurs sur la clef

			}
			else	// si c'était juste un '<' perdu
			{

				CCroptoHtml_Crypto_Balise_Chiffre_Save();	// chiffre la fausse balise

			}

		}
		else	// si char lambda
		{

			CCropto_Crypto_Chiffre();	// Chiffre le char en cours de la source

			m_ofs.write((char*)&m_cC, sizeof(char));	// save
		}

	}

}


void CCroptoHtml::CCroptoHtml_Crypto_Chiffre_Aff()
	/// Chiffre et Affiche
{

	while(m_ifs.read((char*)&m_cC, sizeof(char)))	// lit le char en cours du txt (tant qu'il y en as)
	{

		if(m_cC == '<')	// si début de Balise
		{

			if(CCroptoHtml_Crypto_IsBalise())	// si c'est une balise
			{

				CCroptoHtml_Crypto_Balise_Copie_Aff();	// copie de la Balise (et implémente les compteurs sur la clef

			}
			else	// si c'était juste un '<' perdu
			{

				CCroptoHtml_Crypto_Balise_Chiffre_Aff();	// chiffre la fausse balise

			}

		}
		else	// si char lambda
		{

			CCropto_Crypto_Chiffre();	// Chiffre le char en cours de la source

			cout << m_cC;	// aff

		}

	}

}


void CCroptoHtml::CCroptoHtml_Crypto_Chiffre_AffSave()
	/// Chiffre et Affiche et sauve
{

	while(m_ifs.read((char*)&m_cC, sizeof(char)))	// lit le char en cours du txt (tant qu'il y en as)
	{

		if(m_cC == '<')	// si début de Balise
		{

			if(CCroptoHtml_Crypto_IsBalise())	// si c'est une balise
			{

				CCroptoHtml_Crypto_Balise_Copie_AffSave();	// copie de la Balise (et implémente les compteurs sur la clef

			}
			else	// si c'était juste un '<' perdu
			{

				CCroptoHtml_Crypto_Balise_Chiffre_AffSave();	// chiffre la fausse balise

			}

		}
		else	// si char lambda
		{

			CCropto_Crypto_Chiffre();	// Chiffre le char en cours de la source

			m_ofs.write((char*)&m_cC, sizeof(char));	// save
			cout << m_cC;	// aff

		}

	}

}



	//-------------------------------------------------------------------------------------------------------------------------------
				// Déchiffrement
	//-------------------------------------------------------------------------------------------------------------------------------



void CCroptoHtml::CCroptoHtml_Crypto_Dechiffre_Save()
	/// Déhiffre et sauve
{

	while(m_ifs.read((char*)&m_cC, sizeof(char)))	// lit le char en cours du txt (tant qu'il y en as)
	{

		if(m_cC == '<')	// si début de Balise
		{

			if(CCroptoHtml_Crypto_IsBalise())	// si c'est une balise
			{

				CCroptoHtml_Crypto_Balise_Copie_Save();	// copie de la Balise (et implémente les compteurs sur la clef

			}
			else	// si c'était juste un '<' perdu
			{

				CCroptoHtml_Crypto_Balise_Dechiffre_Save();	// chiffre la fausse balise

			}

		}
		else	// si char lambda
		{

			CCropto_Crypto_Dechiffre();	// Chiffre le char en cours de la source

			m_ofs.write((char*)&m_cC, sizeof(char));	// save

		}

	}

}


void CCroptoHtml::CCroptoHtml_Crypto_Dechiffre_Aff()
	/// Déhiffre et Affiche
{

	while(m_ifs.read((char*)&m_cC, sizeof(char)))	// lit le char en cours du txt (tant qu'il y en as)
	{

		if(m_cC == '<')	// si début de Balise
		{

			if(CCroptoHtml_Crypto_IsBalise())	// si c'est une balise
			{

				CCroptoHtml_Crypto_Balise_Copie_Aff();	// copie de la Balise (et implémente les compteurs sur la clef

			}
			else	// si c'était juste un '<' perdu
			{

				CCroptoHtml_Crypto_Balise_Dechiffre_Aff();	// chiffre la fausse balise

			}

		}
		else	// si char lambda
		{

			CCropto_Crypto_Dechiffre();	// Chiffre le char en cours de la source

			cout << m_cC;	// aff

		}

	}

}


void CCroptoHtml::CCroptoHtml_Crypto_Dechiffre_AffSave()
	/// Déhiffre et Affiche et sauve
{

	while(m_ifs.read((char*)&m_cC, sizeof(char)))	// lit le char en cours du txt (tant qu'il y en as)
	{

		if(m_cC == '<')	// si début de Balise
		{

			if(CCroptoHtml_Crypto_IsBalise())	// si c'est une balise
			{

				CCroptoHtml_Crypto_Balise_Copie_AffSave();	// copie de la Balise (et implémente les compteurs sur la clef

			}
			else	// si c'était juste un '<' perdu
			{

				CCroptoHtml_Crypto_Balise_Dechiffre_AffSave();	// chiffre la fausse balise

			}

		}
		else	// si char lambda
		{

			CCropto_Crypto_Dechiffre();	// Chiffre le char en cours de la source

			m_ofs.write((char*)&m_cC, sizeof(char));	// save
			cout << m_cC;	// aff

		}

	}

}





//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------






















