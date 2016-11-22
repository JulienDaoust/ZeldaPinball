//////////////////////////////////////////////////////////////////////////////
/// @file VisiteurTranslationTest.h
/// @author Gabriel Amyot
/// @date 2014-10-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "VisiteurTranslationTest.h"
#include "Utilitaire.h"



// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(VisiteurTranslationTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurTranslationTest::setUp()
///
///	créé 2 noeuds
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurTranslationTest::setUp()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurTranslationTest::tearDown()
///
/// désalouer les 2 noeuds 
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurTranslationTest::tearDown()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurTranslationTest::testVisit()
///
/// Cas de test: s'assuré que ltranslation est effetué correctement
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurTranslationTest::testVisit()
{

	noeud1 = new NoeudAbstrait{ ArbreRenduINF2990::NOM_CIBLE };
	std::vector<NoeudAbstrait*> noeudSelectionnes;
	noeudSelectionnes.push_back(noeud1);
	monVisiteur = new VisiteurTranslation(noeudSelectionnes);
	glm::dvec3 mouvement(5.0, 10.0, 15.0);
	monVisiteur->visiteAll(mouvement);

	CPPUNIT_ASSERT(noeud1->obtenirPositionRelative() == mouvement);

	delete monVisiteur;

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurTranslationTest::testRevert()
///
/// Cas de test: s'assurer que, si un objet est déplacer en dehor de
///	la zone de jeux, le déplacement seras annulé
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurTranslationTest::testRevert()
{
	//Position Initial
	glm::dvec3 positionInit(0.0,0.0,0.0)  ;
	//Deplacement
	glm::dvec3 mouvement(1.0, 0.0, 0.0);

	noeud1 = new NoeudAbstrait{ ArbreRenduINF2990::NOM_CIBLE };
	std::vector<NoeudAbstrait*> noeudSelectionnes;
	noeudSelectionnes.push_back(noeud1);
	monVisiteur = new VisiteurTranslation(noeudSelectionnes);
	
	monVisiteur->visiteAll(mouvement);
	monVisiteur->revert();

	CPPUNIT_ASSERT(noeud1->obtenirPositionRelative() == positionInit);

	delete monVisiteur;

}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////