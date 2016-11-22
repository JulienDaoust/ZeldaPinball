//////////////////////////////////////////////////////////////////////////////
/// @file VisiteurScaleTest.h
/// @author Gabriel Amyot
/// @date 2014-10-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "VisiteurScaleTest.h"
#include "Utilitaire.h"



// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(VisiteurScaleTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurScaleTest::setUp()
///
///	créé 2 noeuds
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurScaleTest::setUp()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurScaleTest::tearDown()
///
/// désalouer les 2 noeuds 
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurScaleTest::tearDown()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurScaleTest::testVisit()
///
/// Cas de test: s'assuré que ltranslation est effetué correctement
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurScaleTest::testVisit()
{
	glm::dvec3 centre(0.0, 0.0, 0.0);
	noeud1 = new NoeudAbstrait{ ArbreRenduINF2990::NOM_CIBLE };
	std::vector<NoeudAbstrait*> noeudSelectionnes;
	noeudSelectionnes.push_back(noeud1);
	monVisiteur = new VisiteurScale(centre, noeudSelectionnes);
	glm::dvec3 grossissement(0.0, 1., 0.);
	monVisiteur->visiteAll(grossissement);

	//CPPUNIT_ASSERT(noeud1-> == grossissement);

	delete monVisiteur;

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurScaleTest::testRevert()
///
/// Cas de test: s'assurer que, si un objet est déplacer en dehor de
///	la zone de jeux, le déplacement seras annulé
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurScaleTest::testRevert()
{
	//glm::dvec3 centre(0.0, 0.0, 0.0);
	//noeud1 = new NoeudAbstrait{ ArbreRenduINF2990::NOM_CIBLE };
	//std::vector<NoeudAbstrait*> noeudSelectionnes;
	//noeudSelectionnes.push_back(noeud1);
	//monVisiteur = new VisiteurRotation(centre, noeudSelectionnes);
	//glm::dvec3 rotation(1.0, 0., 0.);
	//monVisiteur->visiteAll(rotation);
	//monVisiteur->revert();
	//// le revert consiste a 1% de diminution
	//CPPUNIT_ASSERT(noeud1->obtenirAngleRotation() == 0.99*rotation[0]);

	//delete monVisiteur;

}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////