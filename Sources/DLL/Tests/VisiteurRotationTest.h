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
///        méthodes de la classe  FacadeModele
///
/// @author Gabriel Amyot
/// @date 2014-10-08
///////////////////////////////////////////////////////////////////////////
class VisiteurRotationTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(VisiteurRotationTest);
	CPPUNIT_TEST(testVisit);
	CPPUNIT_TEST(testRevert);
	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// Méthodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement à effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement à effectuer pour 'finaliser' cette suite de tests
	void tearDown();


	// =================================================================
	// Définissez ici les différents cas de tests...
	// =================================================================

	/// Cas de test: s'assuré que ltranslation est effetué correctement
	void testVisit();

	/// Cas de test: s'assurer que, si un objet est déplacer en dehor de
	///	la zone de jeux, le déplacement seras annulé
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
