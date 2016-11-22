//////////////////////////////////////////////////////////////////////////////
/// @file NoeudCompositeTest.h
/// @author Gabriel Amyot
/// @date 2014-10-08
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_NOEUDCOMPOSITETEST_H
#define _TESTS_NOEUDCOMPOSITETEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "NoeudComposite.h"
#include "ArbreRenduINF2990.h"
#include "NoeudCible.h"
#include "NoeudPlaque.h"
#include "NoeudTrou.h"



///////////////////////////////////////////////////////////////////////////
/// @class  FacadeModeleTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe  NoeudComposite
///
/// @author Gabriel Amyot
/// @date 2014-10-08
///////////////////////////////////////////////////////////////////////////
class NoeudCompositeTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(NoeudCompositeTest);
	CPPUNIT_TEST(testChercher);
	CPPUNIT_TEST(testAjouter);
	CPPUNIT_TEST(testEffacer);
	CPPUNIT_TEST(testSelectionExiste);
	CPPUNIT_TEST(testSelectionnerTout);
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

	/// Cas de test: la recherche par le type retourne un enfant valide
	void testChercher();

	/// Cas de test: il est possible d'ajouter un noeud enfant
	void testAjouter();

	/// Cas de test: s'assurer que l'enlèvement d'un enfant fonctionne correctement
	void testEffacer();

	// Cas de test: s'assurer que l'itentication d'une selection est fontionel
	void testSelectionExiste();

	/// Cas de test: il est possible de selectionner tous les enfants
	void testSelectionnerTout();

	


private:
	///Noeuds
	ArbreRenduINF2990* noeudComposite;

};

#endif // _TESTS_NOEUDCOMPOSITETEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
