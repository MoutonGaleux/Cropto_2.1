


/* ************************************************************************************************************ */
	/* **************************************************************************************************** */
/* ************************************************************************************************************ */
	/*


	Cropto -- programme de (dé)chiffrement de fichier (en entier ou, selon le format, uniquement le contenu)


		Copyright (C)  2015   MiG (alias Benoit Nocaudie)


	This file is part of Cropto.

	Cropto is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Cropto is distributed in the hope that it will be useful,
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


#include "CChaine.h"


#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;



//-------------------------------------------------------------------------------------------------------------------------------
			// Intro Cropto GNU/GPL
//-------------------------------------------------------------------------------------------------------------------------------


void About_Cropto()
{

	cout << endl
		 << "******************************"
		 << endl
		 << endl
		 << "\t Bienvenu dans Cropto \n"
		 << " -- programme de (dé)chiffrement de fichier (en entier ou, selon le format, uniquement le contenu) -- \n"
		 << endl
		 << endl
		 << "\t Copyright (C)  2015   MiG (alias Benoit Nocaudie) \n"
		 << endl
		 << " Cropto is free software: you can redistribute it and/or modify \n"
		 << "it under the terms of the GNU General Public License as published by \n"
		 << "the Free Software Foundation, either version 3 of the License, or \n"
		 << "(at your option) any later version. \n"
		 << endl
		 << " Cropto is distributed in the hope that it will be useful, \n"
		 << "but WITHOUT ANY WARRANTY; without even the implied warranty of \n"
		 << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the \n"
		 << "GNU General Public License for more details. \n"
		 << endl
		 << " You should have received a copy of the GNU General Public License \n"
		 << "along with Cropto.  If not, see <http://www.gnu.org/licenses/>. \n"
		 << endl << endl
		 << "\t /!\\ cette version du programme est codé pour les fichiers html \n"
		 << "\t c'est à dire que les balises (entre < >) ne sont pas chiffrées /!\\ \n"
		 << endl
		 << endl
		 << "******************************"
		 << endl;

}



//-------------------------------------------------------------------------------------------------------------------------------
			// Outils
//-------------------------------------------------------------------------------------------------------------------------------


CChaine Get_Path()	/// récupère un path fichier (source/sortie)
{

	CChaine strPath;


	cin >> strPath;


	return strPath;

}


CChaine Get_Key(int nMode, char* strPath)	/// Récupère la clef ;; true : récupe sur fichier / false : récup via console
{

	CChaine strKey;


	if(nMode == 1)
	{

		cout << "Entrez votre clef de chiffrement :"
			 << endl << endl;

		cin >> strKey;

	}
	else if(nMode == 2)
	{

		fstream ifs;
		ifs.open(strPath, ios::in | ios::binary);

		char c;

		while(ifs.read((char*)&c, sizeof(char)))
		{
			strKey += c;
		}

	}
	else if(nMode == 3)
	{

		// TODO : Mode CryptoTxt avec renvoi d'un CChaine déchiffré

	}


	return strKey;

}



//-------------------------------------------------------------------------------------------------------------------------------
			// Menus
//-------------------------------------------------------------------------------------------------------------------------------


int Menu_Key()	/// menu pour choisir le mode d'entrée de la clef ;; 1 : via console / 2 : via fichier / 3 : via fichier chiffré
{

	int nChoice;


	CChaine cChoice;

	while( (cChoice.Get_m_nC() != 2)	// vérifie qu'il n'y a qu'une lettre
				|| ( (cChoice[0] != '1') && (cChoice[0] != '2') && (cChoice[0] != '3')	) )	// vérifie que c'est soit 1, soit 2, soit 3
	{
		cout << endl << "Comment voulez-vous entrer la clef de chiffrement ?"
			 << endl << endl
			 << "\t 1 \t Via la console (entrer au clavier) \n"
			 << "\t   \t    /!\\ seulement des caractères imprimables \n"
			 << "\t 2 \t Via un fichier \n"
			 << "\t 3 \t Via un fichier CryptoTxt \n";

		cin >> cChoice;
	}

	if(cChoice == '1')
	{
		nChoice = 1;
	}
	else if(cChoice == '2')
	{
		nChoice = 2;
	}
	else if(cChoice == '3')
	{
		nChoice = 3;
	}


	return nChoice;

}


bool Menu_Chiffr()	/// menu pour choisir Chiffrement/Déchiffrement ; true : chiffrement / false : déchiffrement
{

	bool bChiffr;


	CChaine cChoice;

	while( (cChoice.Get_m_nC() != 2)	// vérifie qu'il n'y a qu'une lettre
				|| ( (cChoice[0] != '1') && (cChoice[0] != '2')	) )	// vérifie que c'est soit 1, soit 2
	{
		cout << endl << "Voulez-vous chiffrer ou dechiffrer le fichier source ?"
			 << endl << endl
			 << "\t 1 \t Chiffrer \n"
			 << "\t 2 \t Dechiffrer \n";

		cin >> cChoice;
	}

	if(cChoice == '1')
	{
		bChiffr = true;
	}
	else if(cChoice == '2')
	{
		bChiffr = false;
	}


	return bChiffr;

}


int Menu_Mode()	/// menu pour choisir le mode de lecture du fichier déchiffré ;; 1 : via console / 2 : via fichier / 3 : via console et fichier
{

	int nChoice;


	CChaine cChoice;

	while( (cChoice.Get_m_nC() != 2)	// vérifie qu'il n'y a qu'une lettre
				|| ( (cChoice[0] != '1') && (cChoice[0] != '2') && (cChoice[0] != '3')	) )	// vérifie que c'est soit 1, soit 2, soit 3
	{
		cout << endl << "Comment voulez-vous lire le fichier dechiffre ?"
			 << endl << endl
			 << "\t 1 \t Sur la console \n"
			 << "\t 2 \t Sur un fichier \n"
			 << "\t 3 \t Sur les deux \n";

		cin >> cChoice;
	}

	if(cChoice == '1')
	{
		nChoice = 1;
	}
	else if(cChoice == '2')
	{
		nChoice = 2;
	}
	else if(cChoice == '3')
	{
		nChoice = 3;
	}


	return nChoice;

}





//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
			// Main
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------



int main(int argc, char* argv[])
{


	About_Cropto();	// AboutBox de Cropto



	CCroptoHtml App;

	CChaine strBuff;

	CChaine strPath;

	int nChoice;



	cout << endl << endl;




		// Récupération du path du fichier source, et ouverture d'icelui


	cout << "Veuillez entrer le path du fichier source : \n\n";

	strPath = Get_Path();

	App.CCropto_SourceFile_Open(strPath.Get_m_pChar());

	cout << endl << endl;




		// Récupération de la clef


	nChoice = Menu_Key();	// choix du mode de récupération

	cout << endl << endl;

	if(nChoice != 1)	// si pas clef via console
	{
		cout << "Veuillez entrer le path du fichier de la clef :"
			 << endl << endl;

		strPath = Get_Path();	// récupération du path de la clef

		cout << endl << endl;
	}

	strBuff = Get_Key(nChoice, strPath.Get_m_pChar());	// récupération de la clef

	App.CCropto_Set_Key(strBuff.Get_Length(), strBuff.Get_m_pChar());	// transmission de la clef au programme

	cout << endl << endl;




		// Choix Chiffrement/Déchiffrement


	App.CCropto_Set_m_bChiffr(Menu_Chiffr());

	cout << endl << endl;




		// Choix du mode de lecture du déchiffrement


	nChoice = Menu_Mode();	// choix du mode de lecture du fichier déchiffré

	cout << endl << endl;

	if(nChoice != 1)	// si pas clef via console
	{
		cout << "Veuillez entrer le path du fichier de sortie :"
			 << endl << endl;

		strPath = Get_Path();	// récupération du path du fichier source

		App.CCropto_OutputFile_Open(strPath.Get_m_pChar());	// ouverture du fichier de sortie

		cout << endl << endl;
	}



		// Lancement du programme


	App.CCroptoHtml_Crypto(nChoice);

	cout << endl << endl;




	cout << endl << endl;
	system("pause");


	return 0;
}





















