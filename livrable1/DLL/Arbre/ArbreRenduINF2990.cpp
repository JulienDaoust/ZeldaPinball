///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.cpp
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "ArbreRenduINF2990.h"
#include "Usines/UsineNoeudAraignee.h"
#include "Usines/UsineNoeudConeCube.h"
#include "Usines/UsineNoeudPaletteJoueur1.h"
#include "Usines/UsineNoeudPaletteJoueur2.h"
#include "Usines/UsineNoeudButoirTriangulaire.h"
#include "Usines/UsineNoeudButoirCirculaire.h"
#include "Usines/UsineNoeudCible.h"
#include "Usines/UsineNoeudRessort.h"
#include "Usines/UsineNoeudGenerateurBille.h"
#include "Usines/UsineNoeudTrou.h"
#include "Usines/UsineNoeudPortail.h"
#include "Usines/UsineNoeudMur.h"
#include "Usines/UsineNoeudPlaque.h"
#include "EtatOpenGL.h"


/// La chaîne représentant le type des araignées.
const std::string ArbreRenduINF2990::NOM_ARAIGNEE{ "araignee" };
/// La chaîne représentant le type des cones-cubes.
const std::string ArbreRenduINF2990::NOM_CONECUBE{ "conecube" };

const std::string ArbreRenduINF2990::NOM_PALETTE_JOUEUR1{ "paletteJoueur1" };
const std::string ArbreRenduINF2990::NOM_PALETTE_JOUEUR2{ "paletteJoueur2" };
const std::string ArbreRenduINF2990::NOM_BUTOIR_TRIANGULAIRE{ "butoirTriangulaire" };
const std::string ArbreRenduINF2990::NOM_BUTOIR_CIRCULAIRE{ "butoirCirculaire" };
const std::string ArbreRenduINF2990::NOM_CIBLE{ "cible" };
const std::string ArbreRenduINF2990::NOM_RESSORT{ "ressort" };
const std::string ArbreRenduINF2990::NOM_GENERATEUR_BILLE{ "generateurBille" };
const std::string ArbreRenduINF2990::NOM_TROU{ "trou" };
const std::string ArbreRenduINF2990::NOM_PORTAIL{ "portail" };
const std::string ArbreRenduINF2990::NOM_MUR{ "mur" };
const std::string ArbreRenduINF2990::NOM_PLAQUE{ "plaque" };

////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::ArbreRenduINF2990()
///
/// Ce constructeur crée toutes les usines qui seront utilisées par le
/// projet de INF2990et les enregistre auprès de la classe de base.
/// Il crée également la structure de base de l'arbre de rendu, c'est-à-dire
/// avec les noeuds structurants.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::ArbreRenduINF2990()
{
	// Construction des usines
	ajouterUsine(NOM_ARAIGNEE, new UsineNoeudAraignee{ NOM_ARAIGNEE });
	ajouterUsine(NOM_CONECUBE, new UsineNoeudConeCube{ NOM_CONECUBE });
	
	ajouterUsine(NOM_PALETTE_JOUEUR1, new UsineNoeudPaletteJoueur1{ NOM_PALETTE_JOUEUR1 });
	ajouterUsine(NOM_PALETTE_JOUEUR2, new UsineNoeudPaletteJoueur2{ NOM_PALETTE_JOUEUR2 });
	ajouterUsine(NOM_BUTOIR_TRIANGULAIRE, new UsineNoeudButoirTriangulaire{ NOM_BUTOIR_TRIANGULAIRE });
	ajouterUsine(NOM_BUTOIR_CIRCULAIRE, new UsineNoeudButoirCirculaire{ NOM_BUTOIR_CIRCULAIRE });
	ajouterUsine(NOM_CIBLE, new UsineNoeudCible{ NOM_CIBLE });
	ajouterUsine(NOM_RESSORT, new UsineNoeudRessort{ NOM_RESSORT });
	ajouterUsine(NOM_GENERATEUR_BILLE, new UsineNoeudGenerateurBille{ NOM_GENERATEUR_BILLE });
	ajouterUsine(NOM_TROU, new UsineNoeudTrou{ NOM_TROU });
	ajouterUsine(NOM_PORTAIL, new UsineNoeudPortail{ NOM_PORTAIL });
	ajouterUsine(NOM_MUR, new UsineNoeudMur{ NOM_MUR });
	ajouterUsine(NOM_PLAQUE, new UsineNoeudPlaque{ NOM_PLAQUE });
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRenduINF2990::~ArbreRenduINF2990()
///
/// Ce destructeur ne fait rien pour le moment.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::~ArbreRenduINF2990()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::initialiser()
///
/// Cette fonction crée la structure de base de l'arbre de rendu, c'est-à-dire
/// avec les noeuds structurants (pour les objets, les murs, les billes,
/// les parties statiques, etc.)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::initialiser()
{
	// On vide l'arbre
	vider();

	NoeudAbstrait* noeud{ creerNoeud(NOM_PLAQUE) };
	ajouter(noeud);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990::obtenirNoeudSelectionnes()
///
/// Cette fonction parcour l'arbre pour trouver les noeuds selectionnees
///
/// @return un vecteur contenant tou lesnoeuds selectionnes.
///
////////////////////////////////////////////////////////////////////////
std::vector<NoeudAbstrait*> ArbreRenduINF2990::obtenirNoeudSelectionnes()
{
	std::vector<NoeudAbstrait*> avisiter = std::vector<NoeudAbstrait*>();
	std::vector<NoeudAbstrait*> noeudSelectionnes = std::vector<NoeudAbstrait*>();
	avisiter.push_back(this);
	while (!avisiter.empty())
	{
		NoeudAbstrait* noeud = avisiter.back();
		avisiter.pop_back();

		if (noeud->estSelectionne())
		{
			noeudSelectionnes.push_back(noeud);
		}

		for (int i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			avisiter.push_back(noeud->chercher(i));
		}
	}
	return noeudSelectionnes;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
