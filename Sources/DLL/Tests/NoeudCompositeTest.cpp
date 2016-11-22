//////////////////////////////////////////////////////////////////////////////
/// @file NoeudCompositeTest.h
/// @author Gabriel Amyot
/// @date 2014-10-08
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "NoeudCompositeTest.h"
#include "Utilitaire.h"



// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(NoeudCompositeTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::setUp()
///
///	créé un noeud composite plaque, un noeud cible et un noeud trou
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::setUp()
{
	noeudComposite = new ArbreRenduINF2990();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::tearDown()
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::tearDown()
{
	delete noeudComposite;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testChercher()
///
/// Cas de test: la recherche par le type retourne un enfant valide
/// 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testChercher()
{
	NoeudAbstrait* noeudFils = new NoeudAbstrait{ ArbreRenduINF2990::NOM_CIBLE };
	noeudComposite->ajouter(noeudFils);
	CPPUNIT_ASSERT(noeudComposite->chercher(ArbreRenduINF2990::NOM_CIBLE) == noeudFils);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testAjouter()
///
/// Cas de test: il est possible d'ajouter un noeud enfant
/// 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testAjouter()
{
	NoeudAbstrait* noeudfils1 = new NoeudAbstrait{ ArbreRenduINF2990::NOM_CIBLE };
	NoeudAbstrait* noeudfils2 = new NoeudAbstrait{ ArbreRenduINF2990::NOM_TROU};

	noeudComposite->ajouter(noeudfils1);
	noeudComposite->ajouter(noeudfils2);
	noeudComposite->chercher(ArbreRenduINF2990::NOM_TROU);
	CPPUNIT_ASSERT(noeudComposite->chercher(ArbreRenduINF2990::NOM_TROU) == noeudfils2);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testEffacer()
///
/// Cas de test: s'assurer que l'éffacementun d'enfant fonctionne correctement
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testEffacer()
{

	NoeudAbstrait* noeudFils2 = new NoeudAbstrait{ ArbreRenduINF2990::NOM_TROU };

	noeudComposite->effacer(noeudFils2);

	CPPUNIT_ASSERT(noeudComposite->chercher(ArbreRenduINF2990::NOM_TROU) == nullptr);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testSelectionExiste()
///
// Cas de test: s'assurer que l'itentification d'une selection est fontionel
/// 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testSelectionExiste()
{
	NoeudAbstrait* noeudFils1 = new NoeudAbstrait{ ArbreRenduINF2990::NOM_CIBLE };

	noeudComposite->ajouter(noeudFils1);
	
	noeudFils1->inverserSelection();
	CPPUNIT_ASSERT(noeudComposite->selectionExiste());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testSelectionnerTout()
///
/// Cas de test: il est possible de selectionner tous les enfants
/// 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testSelectionnerTout()
{

	NoeudAbstrait* noeudFils1 = new NoeudAbstrait{ ArbreRenduINF2990::NOM_CIBLE };
	NoeudAbstrait* noeudFils2 = new NoeudAbstrait{ ArbreRenduINF2990::NOM_TROU };

	noeudComposite->ajouter(noeudFils1);
	noeudComposite->ajouter(noeudFils2);

	noeudComposite->selectionnerTout();

	CPPUNIT_ASSERT(noeudComposite->chercher(ArbreRenduINF2990::NOM_TROU)->estSelectionne()
		&& noeudComposite->chercher(ArbreRenduINF2990::NOM_CIBLE)->estSelectionne());
}



///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////