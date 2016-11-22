//////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrthoTest.h
/// @author Gabriel Amyot
/// @date 2014-10-08
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "ProjectionOrthoTest.h"
#include "Utilitaire.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(ProjectionOrthoTest);

ProjectionOrthoTest::ProjectionOrthoTest() :ProjectionOrtho(0, 500, 0, 500, 1, 1000, 1, 10000, 1.25, -100, 100, -100, 100)
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModeleTest::setUp()
///
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::setUp()
{
	//maProjectionOrtho = new ProjectionOrtho(0, 500, 0, 500, 1, 1000, 1, 10000, 1.25, -100, 100, -100, 100);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModeleTest::tearDown()
///
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::tearDown()
{
	//delete maProjectionOrtho;
}

/*
////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::selectionSimple()
///
/// Cas de test: s'assuré que le redimentionnement est fait adéquatement
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::testRedimentionnerFenetre()
{
	
	//points  
	glm::ivec2 coinMin(0,0), coinMax(100,100);

	obtenirCoordonneesFenetreVirtuelle(xMinInitial, xMaxInitial, yMinInitial, yMaxInitial);
	
	redimensionnerFenetre(coinMin, coinMax);
	obtenirCoordonneesFenetreVirtuelle(xMinFinal, xMaxFinal, yMinFinal, yMaxFinal);

	CPPUNIT_ASSERT(xMinInitial );
	
}
*/
/*
////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::selectionSimple()
///
/// Cas de test: s'assurer que la trasladation de la fenetre virtuelle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::testTranslader()
{
	obtenirCoordonneesFenetreVirtuelle(xMinInitial, xMaxInitial, yMinInitial, yMaxInitial);
	
	double deplacementX = (std::abs(xMaxInitial) - std::abs(xMinInitial))*0.1;
	double deplacementY = (abs(yMaxInitial) - abs(yMinInitial))*0.1;
	double optionX = 1, optionY = 0;

	translater(optionX,optionY);
	obtenirCoordonneesFenetreVirtuelle(xMinFinal, xMaxFinal, yMinFinal, yMaxFinal);

	std::cout << xMinInitial << xMinFinal << std::endl << deplacementX << std::endl;
	
	CPPUNIT_ASSERT(xMinInitial == xMinFinal - deplacementX*optionX);
	CPPUNIT_ASSERT(xMaxInitial == xMaxFinal - deplacementX*optionX);
	CPPUNIT_ASSERT(yMinInitial == yMinFinal - deplacementY*optionY);
	CPPUNIT_ASSERT(yMaxInitial == yMaxFinal - deplacementY*optionX);

}
*/
////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::testZoomIn()
///
/// Cas de test: vérifier que le zoom in simple fonctionne adéquatement
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::testZoomIn()
{
	obtenirCoordonneesFenetreVirtuelle(xMinInitial, xMaxInitial, yMinInitial, yMaxInitial);
	zoomerIn();
	obtenirCoordonneesFenetreVirtuelle(xMinFinal, xMaxFinal, yMinFinal, yMaxFinal);

	CPPUNIT_ASSERT(xMinInitial <= xMinFinal );
	CPPUNIT_ASSERT(xMaxInitial >= xMaxFinal);
	CPPUNIT_ASSERT(yMinInitial <= yMinFinal) ;
	CPPUNIT_ASSERT(yMaxInitial >= yMaxFinal);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::testZoomOut()
///
/// Cas de test: vérifier que le zoom out simple fonctionne adéquatement
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::testZoomOut()
{
	obtenirCoordonneesFenetreVirtuelle(xMinInitial, xMaxInitial, yMinInitial, yMaxInitial);
	zoomerOut();
	obtenirCoordonneesFenetreVirtuelle(xMinFinal, xMaxFinal, yMinFinal, yMaxFinal);

	CPPUNIT_ASSERT(xMinInitial >= xMinFinal);
	CPPUNIT_ASSERT(xMaxInitial <= xMaxFinal);
	CPPUNIT_ASSERT(yMinInitial >= yMinFinal);
	CPPUNIT_ASSERT(yMaxInitial <= yMaxFinal);
}
/*
////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::selectionSimple()
///
/// Cas de test: vérifier que le zoom in élastique fonctionne adéquatement
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::testZoomInElastique()
{

}
*/


/*
////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::selectionSimple()
///
/// Cas de test: vérifier que le zoom out élastique fonctionne adéquatement
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::testZoomOutElastique()
{
	

}
*/
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////