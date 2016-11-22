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
///        m�thodes de la classe  FacadeModele
///
/// @author Gabriel Amyot
/// @date 2014-10-08
///////////////////////////////////////////////////////////////////////////
class VisiteurScaleTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(VisiteurScaleTest);
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

	/// Cas de test: s'assur� que le redimentionnement est effetu� correctement
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
