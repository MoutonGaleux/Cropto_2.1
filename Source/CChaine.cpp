


/* ************************************************************************************************************ */
	/* **************************************************************************************************** */
/* ************************************************************************************************************ */
	/*


	CChaine -- Classe gérant les chaînes de caractère : transformation, incrémentation, affichage...


		Copyright (C)  2011,2012,2015   MiG (alias Benoit Nocaudie)


	This file is part of Cropto.

	CChaine is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	CChaine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Cropto.  If not, see <http://www.gnu.org/licenses/>.



	*/
/* ************************************************************************************************************ */
	/* **************************************************************************************************** */
/* ************************************************************************************************************ */



#include "CChaine.h"

#include <cmath>



//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
			// Constructeurs
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------


CChaine::CChaine()
: m_nC(0)
, m_pChar(NULL)
{
}

//-------------------------------------------------------------------------------------------------------------------------------
				// "Chaine"

CChaine::CChaine(char c)
: m_nC(2)
, m_pChar(NULL)
{
	m_pChar = new char[m_nC];

	m_pChar[0] = c;
	m_pChar[1] = '\0';
}

CChaine::CChaine(char* pChar)
: m_nC(0)
, m_pChar(NULL)
{
	if(pChar != NULL)
	{
		m_nC = strlen(pChar)+1;

		m_pChar = new char [m_nC];
		strncpy(m_pChar, pChar, m_nC);
	}
}

//-------------------------------------------------------------------------------------------------------------------------------
				// "Nombres"

CChaine::CChaine(int n)
: m_nC(0)
, m_pChar(NULL)
{
	CChaine cBuff;

	// Récupération de la "puissance 0 maximale" de l'int
	int n10 = 1;
	while( (int)(n / n10) != 0)
	{
		n10 *= 10;
	}
	n10 /= 10;

	// Ajout au Buffer des différent chiffres contenus dans l'int (par "puissance 10" décroissante)
	while(n > 0)
	{	// Ajout du chiffre au Buffer
		cBuff += (char)((n / n10) + 48);
		// "Suppression" du chiffre à l'int
		n -= ((n / n10) * n10);
		n10 /= 10;	// passe à la puissance 10 inférieure
	}

	*this = cBuff;
}

CChaine::CChaine(double d, int nPrecision)
: m_nC(0)
, m_pChar(NULL)
{
	CChaine cBuff;

	// Récupération de la "puissance 0 maximale" de l'int
	double d10 = 1;
	while( ((int)(d / d10)) != 0)
	{
		d10 *= 10;
	}
	d10 /= 10;

		// Ajout au Buffer des différent chiffres contenus dans l'int (par "puissance 10" décroissante)
	while(d > 1)
	{
		// Ajout du chiffre au Buffer
		cBuff += (char)(( (int)(d / d10) ) + 48);
		// "Suppression" du chiffre à l'int
		d -= ( ((int)(d / d10) ) * d10);
		d10 /= 10;	// passe à la puissance 10 inférieure
	}

	cBuff += '.';

		// 'intage" des décimales
	for(int i=0; i<nPrecision; i++)
	{
		d *= 10;
		d10 *= 10;
	}

		// Arrondi
	if( (d-(int)d) >= 0.5 )
		d += 1.;

		// récupe du "Nombre décimal"
	for(int i=0; i<nPrecision; i++)
	{
		// Ajout du chiffre au Buffer
		cBuff += (char)(( (int)(d / d10) ) + 48);
		// "Suppression" du chiffre à l'int
		d -= ( ((int)(d / d10) ) * d10);
		d10 /= 10;	// passe à la puissance 10 inférieure
	}

	*this = cBuff;
}

//-------------------------------------------------------------------------------------------------------------------------------
				// "Booleen"

CChaine::CChaine(bool b, bool bBinaire)
: m_nC(0)
, m_pChar(NULL)
{
	if(b)
	{
		if(bBinaire)
		{
			*this = CChaine('1');
		}
		else
		{
			*this = CChaine("true");
		}
	}
	else
	{
		if(bBinaire)
		{
			*this = CChaine('0');
		}
		else
		{
			*this = CChaine("false");
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------------------
				// CChaine

CChaine::CChaine(const CChaine & C)
: m_nC(C.m_nC)
, m_pChar(NULL)
{
	if(C.m_pChar != NULL)
	{
		m_pChar = new char [strlen(C.m_pChar)+1];
		strncpy(m_pChar, C.m_pChar, strlen(C.m_pChar)+1);
	}
}

CChaine CChaine::operator= (const CChaine & C)
{
	if(m_pChar == NULL)
	{
		if(C.m_pChar != NULL)
		{
			m_nC = C.m_nC;

			m_pChar = new char [m_nC];
			strncpy(m_pChar, C.m_pChar, m_nC);
		}
		// else ==> rien
	}
	else	// m_pChar != NULL
	{
		if(C.m_pChar == NULL)
		{
			m_nC = 0;

			delete [] m_pChar;
			m_pChar = NULL;
		}
		else	// C.m_pChar != NULL
		{
			if(m_nC != C.m_nC)
			{
				m_nC = C.m_nC;

				delete [] m_pChar;
				m_pChar = new char [m_nC];
			}

			strncpy(m_pChar, C.m_pChar, m_nC);
		}
	}

	return *this;
}

CChaine::~CChaine()
{
	if(m_pChar != NULL)
		delete [] m_pChar;
}



//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
			// Opérateurs
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------
			// Addition
//-------------------------------------------------------------------------------------------------------------------------------

CChaine CChaine::operator+ (CChaine C)
{
	return *this += C;
}

//-------------------------------------------------------------------------------------------------------------------------------
				// "Chaine"

CChaine operator+ (char c, CChaine C)
{
	return CChaine(c) += C;
}

CChaine operator+ (CChaine C, char c)
{
	return C += c;
}

CChaine operator+ (char* pchar, CChaine C)
{
	return CChaine(pchar) += C;
}

CChaine operator+ (CChaine C, char* pchar)
{
	return C += pchar;
}

//-------------------------------------------------------------------------------------------------------------------------------
				// "Nombre"

CChaine operator+ (int n, CChaine C)
{
	return CChaine(n) += C;
}

CChaine operator+ (CChaine C, int n)
{
	return C += n;
}

CChaine operator+ (double d, CChaine C)
{
	return CChaine(d) += C;
}

CChaine operator+ (CChaine C, double d)
{
	return C += d;
}

//-------------------------------------------------------------------------------------------------------------------------------
				// "Booleen"

CChaine operator+ (bool bBinaire, CChaine C)
{
	return CChaine(bBinaire) += C;
}

CChaine operator+ (CChaine C, bool bBinaire)
{
	return C += bBinaire;
}


//-------------------------------------------------------------------------------------------------------------------------------
			// Ajout (à la fin de la chaine)
//-------------------------------------------------------------------------------------------------------------------------------

CChaine CChaine::operator+= (CChaine C)
{
	CChaine cBuff;

	if(*this == CChaine())
	{
		cBuff = C;
	}
	else if(C == CChaine())
	{
		cBuff = *this;
	}
	else
	{
		char* pBuff = new char[m_nC + C.m_nC -1];

		for(int i=0; i<m_nC-1; i++)
			pBuff[i] = this->m_pChar[i];

		for(int i=0; i<C.m_nC-1; i++)
			pBuff[m_nC-1 + i] = C.m_pChar[i];

		pBuff[m_nC + C.m_nC -2] = '\0';

		cBuff = CChaine(pBuff);
	}

	*this = cBuff;

	return *this;
}

//-------------------------------------------------------------------------------------------------------------------------------
				// "Chaine"

CChaine CChaine::operator+= (char c)
{
	return *this += CChaine(c);
}

CChaine CChaine::operator+= (char* pChar)
{
	return *this += CChaine(pChar);
}

//-------------------------------------------------------------------------------------------------------------------------------
				// "Nombre"

CChaine CChaine::operator+= (int n)
{
	return *this += CChaine(n);
}

CChaine CChaine::operator+= (double d)
{
	return *this += CChaine(d);
}

//-------------------------------------------------------------------------------------------------------------------------------
				// "Booleen"

CChaine CChaine::operator+= (bool bBinaire)
{
	return *this += CChaine(bBinaire);
}


//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
				// Booleen
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------
			// Egalité
//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
				// chaines

bool operator== (CChaine C1, CChaine C2)
{
	bool bEqual = false;

	if(C1.m_nC == C2.m_nC)
	{
		if( (C1.m_pChar == NULL) && (C2.m_pChar == NULL) )
		{
			bEqual = true;
		}
		else if( (C1.m_pChar != NULL) && (C2.m_pChar != NULL) )
		{
			if(strcmp(C1.m_pChar,C2.m_pChar) == 0)
				bEqual = true;
		}
	}

	return bEqual;
}

bool operator== (CChaine C, char c)
{
	bool bEqual = false;

	if(C.m_nC == 2)
	{
		if(C.m_pChar[0] == c)
		{
			bEqual = true;
		}
	}

	return bEqual;
}

bool operator== (char c, CChaine C)
{
	bool bEqual = false;

	if(C.m_nC == 2)
	{
		if(C.m_pChar[0] == c)
		{
			bEqual = true;
		}
	}

	return bEqual;
}

bool operator== (CChaine C, char* pchar)
{
	bool bEqual = false;

	if(C == CChaine(pchar))
	{
		bEqual = true;
	}

	return bEqual;
}

bool operator== (char* pchar, CChaine C)
{
	bool bEqual = false;

	if(C == CChaine(pchar))
	{
		bEqual = true;
	}

	return bEqual;
}

//-------------------------------------------------------------------------------------------------------------------------------
				// nombres

bool operator== (CChaine C, int n)
{
	bool bEqual = false;

	if(C == CChaine(n))
	{
		bEqual = true;
	}

	return bEqual;
}

bool operator== (int n, CChaine C)
{
	bool bEqual = false;

	if(C == CChaine(n))
	{
		bEqual = true;
	}

	return bEqual;
}

bool operator== (CChaine C, double d)
{
	bool bEqual = false;

	if(C == CChaine(d))
	{
		bEqual = true;
	}

	return bEqual;
}

bool operator== (double d, CChaine C)
{
	bool bEqual = false;

	if(C == CChaine(d))
	{
		bEqual = true;
	}

	return bEqual;
}

//-------------------------------------------------------------------------------------------------------------------------------
				// bool

bool operator== (CChaine C, bool b)
{
	bool bEqual = false;

	if(b)
	{
		if(C == "1")
		{
			bEqual = true;
		}
		else if(C == "true")
		{
			bEqual = true;
		}
	}
	else
	{
		if(C == "0")
		{
			bEqual = true;
		}
		else if(C == "false")
		{
			bEqual = true;
		}
	}

	return bEqual;
}

bool operator== (bool b, CChaine C)
{
	bool bEqual = false;

	if(b)
	{
		if(C == "1")
		{
			bEqual = true;
		}
		else if(C == "true")
		{
			bEqual = true;
		}
	}
	else
	{
		if(C == "0")
		{
			bEqual = true;
		}
		else if(C == "false")
		{
			bEqual = true;
		}
	}

	return bEqual;
}


//-------------------------------------------------------------------------------------------------------------------------------
			// Différence
//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
				// chaines

bool operator!= (CChaine C1, CChaine C2)
{
	bool bInEqual = false;

	if(C1.m_nC == C2.m_nC)
	{
		if(strcmp(C1.m_pChar,C2.m_pChar) != 0)
			bInEqual = true;
	}

	return bInEqual;
}

bool operator!= (CChaine C, char c)
{
	bool bInEqual = false;

	if(C.m_nC != 2)
	{
		if(C.m_pChar[0] != c)
		{
			bInEqual = true;
		}
	}

	return bInEqual;
}

bool operator!= (char c, CChaine C)
{
	bool bInEqual = false;

	if(C.m_nC != 2)
	{
		if(C.m_pChar[0] != c)
		{
			bInEqual = true;
		}
	}

	return bInEqual;
}

bool operator!= (CChaine C, char* pchar)
{
	bool bInEqual = false;

	if(C != CChaine(pchar))
	{
		bInEqual = true;
	}

	return bInEqual;
}

bool operator!= (char* pchar, CChaine C)
{
	bool bInEqual = false;

	if(C != CChaine(pchar))
	{
		bInEqual = true;
	}

	return bInEqual;
}

//-------------------------------------------------------------------------------------------------------------------------------
				// nombres

bool operator!= (CChaine C, int n)
{
	bool bInEqual = false;

	if(C != CChaine(n))
	{
		bInEqual = true;
	}

	return bInEqual;
}

bool operator!= (int n, CChaine C)
{
	bool bInEqual = false;

	if(C != CChaine(n))
	{
		bInEqual = true;
	}

	return bInEqual;
}

bool operator!= (CChaine C, double d)
{
	bool bInEqual = false;

	if(C != CChaine(d))
	{
		bInEqual = true;
	}

	return bInEqual;
}

bool operator!= (double d, CChaine C)
{
	bool bInEqual = false;

	if(C != CChaine(d))
	{
		bInEqual = true;
	}

	return bInEqual;
}

//-------------------------------------------------------------------------------------------------------------------------------
				// bool

bool operator!= (CChaine C, bool b)
{
	bool bInEqual = true;

	if(C == b)
	{
		bInEqual = false;
	}

	return bInEqual;
}

bool operator!= (bool b, CChaine C)
{
	bool bInEqual = true;

	if(C == b)
	{
		bInEqual = false;
	}

	return bInEqual;
}


//-------------------------------------------------------------------------------------------------------------------------------
			// Comparaison
//-------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------
				// inf

bool operator< (CChaine C, int n)
{
	bool bInf = false;

	if(Int(C) < n)
	{
		bInf = true;
	}

	return bInf;
}

bool operator< (int n, CChaine C)
{
	bool bInf = false;

	if(Int(C) < n)
	{
		bInf = true;
	}

	return bInf;
}

bool operator< (CChaine C, double d)
{
	bool bInf = false;

	if(Double(C) < d)
	{
		bInf = true;
	}

	return bInf;
}

bool operator< (double d, CChaine C)
{
	bool bInf = false;

	if(Double(C) < d)
	{
		bInf = true;
	}

	return bInf;
}

//-------------------------------------------------------------------------------------------------------------------------------
				// inf egal

bool operator<= (CChaine C, int n)
{
	bool bInfEq = false;

	if(Int(C) <= n)
	{
		bInfEq = true;
	}

	return bInfEq;
}

bool operator<= (int n, CChaine C)
{
	bool bInfEq = false;

	if(Int(C) <= n)
	{
		bInfEq = true;
	}

	return bInfEq;
}

bool operator<= (CChaine C, double d)
{
	bool bInfEq = false;

	if(Double(C) <= d)
	{
		bInfEq = true;
	}

	return bInfEq;
}

bool operator<= (double d, CChaine C)
{
	bool bInfEq = false;

	if(Double(C) <= d)
	{
		bInfEq = true;
	}

	return bInfEq;
}

//-------------------------------------------------------------------------------------------------------------------------------
				// sup

bool operator> (CChaine C, int n)
{
	bool bSup = false;

	if(Int(C) > n)
	{
		bSup = true;
	}

	return bSup;
}

bool operator> (int n, CChaine C)
{
	bool bSup = false;

	if(Int(C) > n)
	{
		bSup = true;
	}

	return bSup;
}

bool operator> (CChaine C, double d)
{
	bool bSup = false;

	if(Double(C) > d)
	{
		bSup = true;
	}

	return bSup;
}

bool operator> (double d, CChaine C)
{
	bool bSup = false;

	if(Double(C) > d)
	{
		bSup = true;
	}

	return bSup;
}

//-------------------------------------------------------------------------------------------------------------------------------
				// sup egal

bool operator>= (CChaine C, int n)
{
	bool bSupEq = false;

	if(Int(C) >= n)
	{
		bSupEq = true;
	}

	return bSupEq;
}

bool operator>= (int n, CChaine C)
{
	bool bSupEq = false;

	if(Int(C) >= n)
	{
		bSupEq = true;
	}

	return bSupEq;
}

bool operator>= (CChaine C, double d)
{
	bool bSupEq = false;

	if(Double(C) >= d)
	{
		bSupEq = true;
	}

	return bSupEq;
}

bool operator>= (double d, CChaine C)
{
	bool bSupEq = false;

	if(Double(C) >= d)
	{
		bSupEq = true;
	}

	return bSupEq;
}




//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
			// manipulation
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------
			// Find
//-------------------------------------------------------------------------------------------------------------------------------


int CChaine::Find(CChaine C)
{
	int i = -1;

	return i;
}

int CChaine::Find(char c)
{
	int i = -1;

	for(int j=0; j<m_nC; j++)
	{
		if(m_pChar[j] == c)
		{
			i = j;
		}
	}

	return i;
}

int CChaine::Find(char* pchar)
{
	int i = -1;

	return i;
}


//-------------------------------------------------------------------------------------------------------------------------------
			// Get/Set
//-------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------
				// insert à

char CChaine::GetAt(int i)
{
	return m_pChar[i];
}

void CChaine::SetAt(int i, CChaine C)
{
}

void CChaine::SetAt(int i, char c)
{
	m_pChar[i] = c;
}

void CChaine::SetAt(int i, char* pchar)
{
}

//-------------------------------------------------------------------------------------------------------------------------------
				// insert depuis

CChaine CChaine::GetFrom(int i)
{
	char* pBuff = new char[m_nC-i];

	for(int j=0; j<m_nC-i; j++)
	{
		pBuff[j] = m_pChar[j+i];
	}

	return CChaine(pBuff);
}

void CChaine::SetFrom(int i, CChaine C)
{
}

void CChaine::SetFrom(int i, char c)
{
}

void CChaine::SetFrom(int i, char* pchar)
{
}

//-------------------------------------------------------------------------------------------------------------------------------
				// insert entre

CChaine CChaine::GetFromTo(int i, int n)
{
	char* pBuff;

	return CChaine(pBuff);
}

void CChaine::SetFromTo(int i, int n, CChaine C)
{
}

void CChaine::SetFromTo(int i, int n, char c)
{
}

void CChaine::SetFromTo(int i, int n, char* pchar)
{
}

//-------------------------------------------------------------------------------------------------------------------------------
				// insert jusqu'à

CChaine CChaine::GetTo(int n)
{
	char* pBuff;

	return CChaine(pBuff);
}

void CChaine::SetTo(int n, CChaine C)
{
}

void CChaine::SetTo(int n, char c)
{
}

void CChaine::SetTo(int n, char* pchar)
{
}



//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
			// Transformation
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------
			// Int
//-------------------------------------------------------------------------------------------------------------------------------

CChaine Int(int n)
{
	return CChaine(n);
}

int Int(CChaine C)
{
	int n = 0;

	int strLength = C.Get_Length();
	int n10 = 1;
		// récupère tout les "caractères" de la chaine en partant de la fin
	for(int i=strLength; i>0; i--)
	{
			// si il s'agit d'un chiffre
		if( (C[i-1] >=48) && (C[i-1] <= 57) )
		{
				// tranforme le caractère en cour en entier puis l'ajoute à n en le "mettant" à la bonne puissance de 10
			n += (((int)C[i-1] - 48) * n10);
				// passe à la puissance 10 supérieure
			n10 *= 10;
		}
		else
		{
			return 69;
		}
	}

	return n;
}


//-------------------------------------------------------------------------------------------------------------------------------
			// Double
//-------------------------------------------------------------------------------------------------------------------------------

CChaine Double(double d)
{
	return CChaine(d);
}

double Double(CChaine C)
{
	double d = 69.69;

	CChaine CEntiere;
	int nEntiere;
	CChaine CDecimal;
	double nDecimal;

		// "récupération" du séparateur décimal
	int point = C.Find('.');
	if(point == -1)
	{
		point = C.Find(',');
	}

		// récupération de la partie entière et de la partie décimale;
	for(int i=0; i<C.m_nC; i++)
	{
		if(i < point)
		{
			CEntiere += C.m_pChar[i];
		}
		else if(i > point)
		{
			CDecimal += C.m_pChar[i];
		}
	}

		// transformation en double
	d = Int(CEntiere) + ( Int(CDecimal) / pow(10., (C.m_nC-point-2)) );

		// arrondi de la dernière décimale
	if(Int(CChaine(C.m_pChar[C.m_nC-2])) > 5)
	{
//		d += 0.000000000000001;		// n'a pas d'effet convenable sur la perte de donnée de la dernière décimale
	}

	return d;
}


//-------------------------------------------------------------------------------------------------------------------------------
			// Bool
//-------------------------------------------------------------------------------------------------------------------------------

CChaine Bool(bool bBinaire)
{
	CChaine cBuff;

	if(bBinaire == 0)
		cBuff = CChaine("false");
	else
		cBuff = CChaine("true");

	return cBuff;
}

bool Bool(CChaine C)
{
	bool b;

	if(C == "true")
	{
		b = true;
	}
	else if(C == "false")
	{
		b = false;
	}
	else if( (C < 0.) || (C > 0.) )
	{
		b = true;
	}
	else if(C == 0.)
	{
		b = false;
	}

	return b;
}



//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
		// accès en lecture
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------


int CChaine::Get_m_nC()
{
	return m_nC;
}

	// retourne la chaine de caractère
char* CChaine::Get_m_pChar()
{
	return m_pChar;
}

	// retourne le nombre de lettre de la chaine
int CChaine::Get_Length()
{
	return (m_nC - 1);
}

	// retourne le caractère "i+1" de la chaine
char CChaine::operator[] (int i)
{
	return m_pChar[i];
}



//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
			// Flux
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------


ostream& operator<< (ostream& aff, CChaine & C)
{
	if(C.m_pChar != NULL)
		aff << C.m_pChar;

	return aff;
}

istream& operator>> (istream& in, CChaine & C)
{
	char pBuf[2048];
	in.getline(pBuf, 2048);

	CChaine Ch(pBuf);		//
	C = Ch;					//	<==>	C = CChaine(pBuf);

	return in;
}



//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
			// Load/Save
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------
			// txt
//-------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------
			// .rtf
//-------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------
			// Binaire
//-------------------------------------------------------------------------------------------------------------------------------

int CChaine::Write(fstream& fs)
{
	int nWrite = 1;

	char cBuff;

		// récupération du nombre de char
	if(!(fs.write((char*)&m_nC, sizeof(int))))
	{
		nWrite = -1;
	}

		// récupération de la chaine
	for(int i=0; i<m_nC-1; i++)
	{
		cBuff = m_pChar[i];
		if(cBuff == '\0')
		{
			return -2;
		}
		if(!(fs.write((char*)&cBuff, sizeof(char))))
		{
			return -1;
		}
	}

		// récupération du caractère de fin de chaine
	cBuff = m_pChar[m_nC-1];
	if(cBuff != '\0')
	{
		return -3;
	}
	if(!(fs.write((char*)&cBuff, sizeof(char))))
	{
		return -1;
	}


	return nWrite;
}

int CChaine::Read(fstream& fs)
{
	int nRead = 1;

	char cBuff;

		// récupération du nombre de char
	if(!(fs.read((char*)&m_nC, sizeof(int))))
	{
		nRead = -1;
	}

	if(m_nC == 0)
	{
		m_pChar = NULL;
	}
	else if(m_nC > 0)
	{
		m_pChar = new char[m_nC];

			// récupération de la chaine
		for(int i=0; i<m_nC-1; i++)
		{
			if(!(fs.read((char*)&cBuff, sizeof(char))))
			{
				return -1;
			}
			else if(cBuff == '\0')
			{
				return -2;
			}
			else
			{
				m_pChar[i] = cBuff;
			}
		}

			// récupération du caractère de fin de chaine
		if(!(fs.read((char*)&cBuff, sizeof(char))))
		{
			return -1;
		}
		else if(cBuff != '\0')
		{
			return -3;
		}
		else
		{
			m_pChar[m_nC-1] = cBuff;
		}
	}
	else
	{
		nRead = -4;
	}


	return nRead;
}



//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------



