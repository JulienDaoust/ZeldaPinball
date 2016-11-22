//////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrthoTest.h
/// @author Gabriel Amyot
/// @date 2014-10-08
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_PROJECTIONORTHOTEST_H
#define _TESTS_PROJECTIONORTHOTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "ProjectionOrtho.h"
#include "Vue.h"
#include "FacadeModele.h"


///////////////////////////////////////////////////////////////////////////
/// @class  ProjectionOrthoTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        m�thodes de la classe  ProjectionOrtho
///
/// @author Gabriel Amyot
/// @date 2014-10-08
///////////////////////////////////////////////////////////////////////////
class ProjectionOrthoTest : public CppUnit::TestFixture, vue::ProjectionOrtho
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(ProjectionOrthoTest);
	//CPPUNIT_TEST(testRedimentionnerFenetre);
	//CPPUNIT_TEST(testTranslader);
	CPPUNIT_TEST(testZoomIn);
	CPPUNIT_TEST(testZoomOut);
	//CPPUNIT_TEST(testZoomInElastique);
	//CPPUNIT_TEST(testZoomOutElastique);
	CPPUNIT_TEST_SUITE_END();

public:

	///Constructeur
	ProjectionOrthoTest();

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

	/// Cas de test: s'assur� que le redimentionnement est fait ad�quatement
	//void testRedimentionnerFenetre();

	/// Cas de test: s'assurer que la trasladation de la fenetre virtuelle
	//void testTranslader();

	/// Cas de test: v�rifier que le zoom in simple fonctionne ad�quatement
	void testZoomIn();

	/// Cas de test: v�rifier que le zoom out simple fonctionne ad�quatement
	void testZoomOut();

	/// Cas de test: v�rifier que le zoom in �lastique fonctionne ad�quatement
	//void testZoomInElastique();

	/// Cas de test: v�rifier que le zoom out �lastique fonctionne ad�quatement
	//void testZoomOutElastique();

private:

	double xMinInitial, xMaxInitial, yMinInitial, yMaxInitial;
	double xMinFinal, xMaxFinal, yMinFinal, yMaxFinal;


};

#endif // _TESTS_PROJECTIONORTHOTEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
