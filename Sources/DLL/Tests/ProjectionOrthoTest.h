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
///        méthodes de la classe  ProjectionOrtho
///
/// @author Gabriel Amyot
/// @date 2014-10-08
///////////////////////////////////////////////////////////////////////////
class ProjectionOrthoTest : public CppUnit::TestFixture, vue::ProjectionOrtho
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
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
	// Méthodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement à effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement à effectuer pour 'finaliser' cette suite de tests
	void tearDown();


	// =================================================================
	// Définissez ici les différents cas de tests...
	// =================================================================

	/// Cas de test: s'assuré que le redimentionnement est fait adéquatement
	//void testRedimentionnerFenetre();

	/// Cas de test: s'assurer que la trasladation de la fenetre virtuelle
	//void testTranslader();

	/// Cas de test: vérifier que le zoom in simple fonctionne adéquatement
	void testZoomIn();

	/// Cas de test: vérifier que le zoom out simple fonctionne adéquatement
	void testZoomOut();

	/// Cas de test: vérifier que le zoom in élastique fonctionne adéquatement
	//void testZoomInElastique();

	/// Cas de test: vérifier que le zoom out élastique fonctionne adéquatement
	//void testZoomOutElastique();

private:

	double xMinInitial, xMaxInitial, yMinInitial, yMaxInitial;
	double xMinFinal, xMaxFinal, yMinFinal, yMaxFinal;


};

#endif // _TESTS_PROJECTIONORTHOTEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
