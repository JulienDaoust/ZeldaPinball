////////////////////////////////////////////////////////////////////////////////////
/// @file NoeudAbstraitTest.cpp
/// @author Julien Gascon-Samson
/// @date 2011-07-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "NoeudAbstraitTest.h"
#include "Utilitaire.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(NoeudAbstraitTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::setUp()
///
/// Effectue l'initialisation pr�alable � l'ex�cution de l'ensemble des
/// cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets doivent �tre construits, il est conseill� de le
/// faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstraitTest::setUp()
{
	noeud = new NoeudConeCube{ ArbreRenduINF2990::NOM_CONECUBE };
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::tearDown()
///
/// Effectue les op�rations de finalisation n�cessaires suite � l'ex�cution
/// de l'ensemble des cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets ont �t� allou�s � l'initialisation, ils doivent �tre
/// d�sallou�s, et il est conseill� de le faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstraitTest::tearDown()
{
	delete noeud;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::testPositionRelative()
///
/// Cas de test: �criture/lecture de la position relative
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstraitTest::testPositionRelative()
{
	noeud->assignerPositionRelative(glm::dvec3{ 2.2, 3.3, 4.4 });

	glm::dvec3 vecteur{ noeud->obtenirPositionRelative() };

	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[0] - 2.2));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[1] - 3.3));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[2] - 4.4));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::testType()
///
/// Cas de test: type de noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstraitTest::testType()
{
	CPPUNIT_ASSERT(noeud->obtenirType() == ArbreRenduINF2990::NOM_CONECUBE);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::testEtat()
///
/// Cas de test: d�finition/obtention de l'�tat (bool�ens) du noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstraitTest::testEtat()
{
	// R�gler tous les �tats (bool�ens) � faux
	noeud->assignerAffiche(false);
	noeud->assignerEstEnregistrable(false);

	// V�rifier que la valeur attribu�e est fausse
	CPPUNIT_ASSERT(noeud->estAffiche() == false);
	CPPUNIT_ASSERT(noeud->estEnregistrable() == false);

	// R�gler tous les �tats (bool�ens) � true
	noeud->assignerAffiche(true);
	noeud->assignerEstEnregistrable(true);

	// V�rifier que la valeur attribu�e est fausse
	CPPUNIT_ASSERT(noeud->estAffiche() == true);
	CPPUNIT_ASSERT(noeud->estEnregistrable() == true);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::testSelection()
///
/// Cas de test: d�finition/obtention des �tats de s�lection du noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstraitTest::testSelection()
{
	// Cas 1 : non s�lectionnable, non s�lectionn�
	noeud->assignerEstSelectionnable(false);
	noeud->assignerSelection(false);
	CPPUNIT_ASSERT(noeud->estSelectionnable() == false);
	CPPUNIT_ASSERT(noeud->estSelectionne() == false);

	// Cas 2 : non s�lectionnable, s�lectionn�
	noeud->assignerEstSelectionnable(false);
	noeud->assignerSelection(true);
	CPPUNIT_ASSERT(noeud->estSelectionnable() == false);
	CPPUNIT_ASSERT(noeud->estSelectionne() == false);

	// Cas 3 : s�lectionnable, non s�lectionn�
	noeud->assignerEstSelectionnable(true);
	noeud->assignerSelection(false);
	CPPUNIT_ASSERT(noeud->estSelectionnable() == true);
	CPPUNIT_ASSERT(noeud->estSelectionne() == false);

	// Cas 4 : non s�lectionnable, s�lectionn�
	noeud->assignerEstSelectionnable(true);
	noeud->assignerSelection(true);
	CPPUNIT_ASSERT(noeud->estSelectionnable() == true);
	CPPUNIT_ASSERT(noeud->estSelectionne() == true);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::testEnfants()
///
/// Cas de test: s'assurer que le noeud abstrait n'a pas d'enfant
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstraitTest::testEnfants()
{
	CPPUNIT_ASSERT(noeud->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeud->calculerProfondeur() == 1);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::testAjout()
///
/// Cas de test: s'assurer qu'il est impossible d'ajouter un enfant
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstraitTest::testAjout()
{
	// Essaie d'ajouter un noeud
	NoeudAbstrait* nouveauNoeud{ new NoeudConeCube{ ArbreRenduINF2990::NOM_CONECUBE } };
	bool ajout{ noeud->ajouter(nouveauNoeud) };

	// L'ajout devrait avoir �chou� puisqu'il s'agit d'un noeud abstrait...
	CPPUNIT_ASSERT(ajout == false);

	// Assurons-nous que le noeud ne poss�de pas d'enfant...
	CPPUNIT_ASSERT(noeud->obtenirNombreEnfants() == 0);

	// Nettoyage
	delete nouveauNoeud;
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
