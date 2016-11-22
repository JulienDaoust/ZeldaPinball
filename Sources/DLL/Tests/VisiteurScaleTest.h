//////////////////////////////////////////////////////////////////////////////
/// @file VisiteurScaleTest.h
/// @author Gabriel Amyot
/// @date 2014-10-08
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_VISITEURSCALETEST_H
#define _TESTS_VISITEURSCALETEST_H

#include <cppunit/extensions/HelperMacros.h>


#include "ArbreRenduINF2990.h"
#include "Visiteurs/VisiteurScale.h"

///////////////////////////////////////////////////////////////////////////
/// @class  VisiteurScaleTestTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe  FacadeModele
///
/// @author Gabriel Amyot
/// @date 2014-10-08
///////////////////////////////////////////////////////////////////////////
class VisiteurScaleTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(VisiteurScaleTest);
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

	/// Cas de test: s'assuré que le redimentionnement est effetué correctement
	void testVisit();

	/// Cas de test: 
	void testRevert();



private:
	///Noeuds
	NoeudAbstrait* noeud1, noeud2;
	VisiteurScale * monVisiteur;
};

#endif // _TESTS_VISITEURSCALETEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
