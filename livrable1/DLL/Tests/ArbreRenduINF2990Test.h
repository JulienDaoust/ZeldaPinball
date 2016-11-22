//////////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduInf2990Test.h
/// @author Gabriel Amyot
/// @date 2014-10-08
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_ARBRERENDUINF2990TEST_H
#define _TESTS_ARBRERENDUINF2990TEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "ArbreRenduINF2990.h"

///////////////////////////////////////////////////////////////////////////
/// @class  ArbreRenduInf2990Test
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe  FacadeModele
///
/// @author Gabriel Amyot
/// @date 2014-10-08
///////////////////////////////////////////////////////////////////////////
class ArbreRenduInf2990Test : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(ArbreRenduInf2990Test);
	CPPUNIT_TEST(testInitialiser);
	CPPUNIT_TEST(testObtenirNoeudSelectionnes);
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

	/// Cas de test: s'assuré que l'arbre se vide
	void testInitialiser();

	/// Cas de test: s'assurer que les noeud séléctionnés sont trouvé
	void testObtenirNoeudSelectionnes();



private:
	///Noeuds
	ArbreRendu arbre;
};

#endif // _TESTS_ARBRERENDUINF2990TEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
