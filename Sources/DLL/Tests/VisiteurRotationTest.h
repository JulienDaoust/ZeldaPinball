//////////////////////////////////////////////////////////////////////////////
/// @file VisiteurRotationTest.h
/// @author Gabriel Amyot
/// @date 2014-10-08
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_VISITEURROTATIONTTEST_H
#define _TESTS_VISITEURROTATIONTTEST_H

#include <cppunit/extensions/HelperMacros.h>


#include "ArbreRenduINF2990.h"
#include "Visiteurs/VisiteurRotation.h"

///////////////////////////////////////////////////////////////////////////
/// @class  VisiteurRotationTestTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        m�thodes de la classe  FacadeModele
///
/// @author Gabriel Amyot
/// @date 2014-10-08
///////////////////////////////////////////////////////////////////////////
class VisiteurRotationTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(VisiteurRotationTest);
	CPPUNIT_TEST(testVisit);
	CPPUNIT_TEST(testRevert);
	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// M�thodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement � effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement � effectuer pour 'finaliser' cette suite de tests
	void tearDown();


	// =================================================================
	// D�finissez ici les diff�rents cas de tests...
	// =================================================================

	/// Cas de test: s'assur� que ltranslation est effetu� correctement
	void testVisit();

	/// Cas de test: s'assurer que, si un objet est d�placer en dehor de
	///	la zone de jeux, le d�placement seras annul�
	void testRevert();



private:
	///Noeuds
	NoeudAbstrait* noeud1, noeud2;
	VisiteurRotation * monVisiteur;
};

#endif // _TESTS_VISITEURROTATIONTTEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
