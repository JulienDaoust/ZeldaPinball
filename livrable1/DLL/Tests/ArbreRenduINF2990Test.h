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
///        m�thodes de la classe  FacadeModele
///
/// @author Gabriel Amyot
/// @date 2014-10-08
///////////////////////////////////////////////////////////////////////////
class ArbreRenduInf2990Test : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(ArbreRenduInf2990Test);
	CPPUNIT_TEST(testInitialiser);
	CPPUNIT_TEST(testObtenirNoeudSelectionnes);
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

	/// Cas de test: s'assur� que l'arbre se vide
	void testInitialiser();

	/// Cas de test: s'assurer que les noeud s�l�ctionn�s sont trouv�
	void testObtenirNoeudSelectionnes();



private:
	///Noeuds
	ArbreRendu arbre;
};

#endif // _TESTS_ARBRERENDUINF2990TEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
