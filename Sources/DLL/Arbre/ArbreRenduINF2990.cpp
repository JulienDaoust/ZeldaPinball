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
#include "Usines/UsineNoeudBille.h"
#include "Usines/UsineNoeudConeCube.h"
#include "Usines/UsineNoeudPaletteJoueur1Gauche.h"
#include "Usines/UsineNoeudPaletteJoueur1Droite.h"
#include "Usines/UsineNoeudPaletteJoueur2Gauche.h"
#include "Usines/UsineNoeudPaletteJoueur2Droite.h"
#include "Usines/UsineNoeudButoirTriangulaireGauche.h"
#include "Usines/UsineNoeudButoirTriangulaireDroit.h"
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

const std::string ArbreRenduINF2990::NOM_PALETTE_JOUEUR1_GAUCHE{ "paletteJoueur1Gauche" };
const std::string ArbreRenduINF2990::NOM_PALETTE_JOUEUR1_DROITE{ "paletteJoueur1Droite" };
const std::string ArbreRenduINF2990::NOM_PALETTE_JOUEUR2_GAUCHE{ "paletteJoueur2Gauche" };
const std::string ArbreRenduINF2990::NOM_PALETTE_JOUEUR2_DROITE{ "paletteJoueur2Droite" };
const std::string ArbreRenduINF2990::NOM_BUTOIR_TRIANGULAIRE_GAUCHE{ "butoirTriangulaireGauche" };
const std::string ArbreRenduINF2990::NOM_BUTOIR_TRIANGULAIRE_DROIT{ "butoirTriangulaireDroit" };
const std::string ArbreRenduINF2990::NOM_BUTOIR_CIRCULAIRE{ "butoirCirculaire" };
const std::string ArbreRenduINF2990::NOM_CIBLE{ "cible" };
const std::string ArbreRenduINF2990::NOM_RESSORT{ "ressort" };
const std::string ArbreRenduINF2990::NOM_GENERATEUR_BILLE{ "generateurBille" };
const std::string ArbreRenduINF2990::NOM_TROU{ "trou" };
const std::string ArbreRenduINF2990::NOM_PORTAIL{ "portail" };
const std::string ArbreRenduINF2990::NOM_MUR{ "mur" };
const std::string ArbreRenduINF2990::NOM_PLAQUE{ "plaque" };
const std::string ArbreRenduINF2990::NOM_BILLE{ "bille" };


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
	
	ajouterUsine(NOM_PALETTE_JOUEUR1_GAUCHE, new UsineNoeudPaletteJoueur1Gauche{ NOM_PALETTE_JOUEUR1_GAUCHE });
	ajouterUsine(NOM_PALETTE_JOUEUR1_DROITE, new UsineNoeudPaletteJoueur1Droite{ NOM_PALETTE_JOUEUR1_DROITE });
	ajouterUsine(NOM_PALETTE_JOUEUR2_GAUCHE, new UsineNoeudPaletteJoueur2Gauche{ NOM_PALETTE_JOUEUR2_GAUCHE });
	ajouterUsine(NOM_PALETTE_JOUEUR2_DROITE, new UsineNoeudPaletteJoueur2Droite{ NOM_PALETTE_JOUEUR2_DROITE });
	ajouterUsine(NOM_BUTOIR_TRIANGULAIRE_GAUCHE, new UsineNoeudButoirTriangulaireGauche{ NOM_BUTOIR_TRIANGULAIRE_GAUCHE });
	ajouterUsine(NOM_BUTOIR_TRIANGULAIRE_DROIT, new UsineNoeudButoirTriangulaireDroit{ NOM_BUTOIR_TRIANGULAIRE_DROIT });
	ajouterUsine(NOM_BUTOIR_CIRCULAIRE, new UsineNoeudButoirCirculaire{ NOM_BUTOIR_CIRCULAIRE });
	ajouterUsine(NOM_CIBLE, new UsineNoeudCible{ NOM_CIBLE });
	ajouterUsine(NOM_RESSORT, new UsineNoeudRessort{ NOM_RESSORT });
	ajouterUsine(NOM_GENERATEUR_BILLE, new UsineNoeudGenerateurBille{ NOM_GENERATEUR_BILLE });
	ajouterUsine(NOM_TROU, new UsineNoeudTrou{ NOM_TROU });
	ajouterUsine(NOM_PORTAIL, new UsineNoeudPortail{ NOM_PORTAIL });
	ajouterUsine(NOM_MUR, new UsineNoeudMur{ NOM_MUR });
	ajouterUsine(NOM_PLAQUE, new UsineNoeudPlaque{ NOM_PLAQUE });
	ajouterUsine(NOM_BILLE, new UsineNoeudBille{ NOM_BILLE });
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
/// @fn std::vector<NoeudAbstrait*> ArbreRenduINF2990::obtenirNoeudSelectionnes()
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

		for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			avisiter.push_back(noeud->chercher(i));
		}
	}
	return noeudSelectionnes;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::vector<NoeudAbstrait*> ArbreRenduINF2990::obtenirNoeudPaletteGJ1()
///
/// Cette fonction parcour l'arbre pour trouver les palettes gauche du joueur 1
///
/// @return un vecteur contenant tous les noeuds de type palette gauche du joueur 1.
///
////////////////////////////////////////////////////////////////////////
std::vector<NoeudAbstrait*> ArbreRenduINF2990::obtenirNoeudPaletteGJ1()
{
	std::vector<NoeudAbstrait*> avisiter = std::vector<NoeudAbstrait*>();
	std::vector<NoeudAbstrait*> noeudSelectionnes = std::vector<NoeudAbstrait*>();
	avisiter.push_back(this);
	while (!avisiter.empty())
	{
		NoeudAbstrait* noeud = avisiter.back();
		avisiter.pop_back();

		if (noeud->obtenirType() == "paletteJoueur1Gauche")
		{
			noeudSelectionnes.push_back(noeud);
		}

		for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			avisiter.push_back(noeud->chercher(i));
		}
	}
	return noeudSelectionnes;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::vector<NoeudAbstrait*> ArbreRenduINF2990::obtenirNoeudPaletteDJ1()
///
/// Cette fonction parcour l'arbre pour trouver les palettes droite du joueur 1
///
/// @return un vecteur contenant tous les noeuds de type palette droite du joueur 1.
///
////////////////////////////////////////////////////////////////////////
std::vector<NoeudAbstrait*> ArbreRenduINF2990::obtenirNoeudPaletteDJ1()
{
	std::vector<NoeudAbstrait*> avisiter = std::vector<NoeudAbstrait*>();
	std::vector<NoeudAbstrait*> noeudSelectionnes = std::vector<NoeudAbstrait*>();
	avisiter.push_back(this);
	while (!avisiter.empty())
	{
		NoeudAbstrait* noeud = avisiter.back();
		avisiter.pop_back();

		if (noeud->obtenirType() == "paletteJoueur1Droite")
		{
			noeudSelectionnes.push_back(noeud);
		}

		for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			avisiter.push_back(noeud->chercher(i));
		}
	}
	return noeudSelectionnes;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::vector<NoeudAbstrait*> ArbreRenduINF2990::obtenirNoeudPaletteGJ2()
///
/// Cette fonction parcour l'arbre pour trouver les palettes gauche du joueur 2
///
/// @return un vecteur contenant tous les noeuds de type palette gauche du joueur 2.
///
////////////////////////////////////////////////////////////////////////
std::vector<NoeudAbstrait*> ArbreRenduINF2990::obtenirNoeudPaletteGJ2()
{
	std::vector<NoeudAbstrait*> avisiter = std::vector<NoeudAbstrait*>();
	std::vector<NoeudAbstrait*> noeudSelectionnes = std::vector<NoeudAbstrait*>();
	avisiter.push_back(this);
	while (!avisiter.empty())
	{
		NoeudAbstrait* noeud = avisiter.back();
		avisiter.pop_back();

		if (noeud->obtenirType() == "paletteJoueur2Gauche")
		{
			noeudSelectionnes.push_back(noeud);
		}

		for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			avisiter.push_back(noeud->chercher(i));
		}
	}
	return noeudSelectionnes;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::vector<NoeudAbstrait*> ArbreRenduINF2990::obtenirNoeudPaletteDJ2()
///
/// Cette fonction parcour l'arbre pour trouver les palettes droite du joueur 2
///
/// @return un vecteur contenant tous les noeuds de type palette droite du joueur 2.
///
////////////////////////////////////////////////////////////////////////
std::vector<NoeudAbstrait*> ArbreRenduINF2990::obtenirNoeudPaletteDJ2()
{
	std::vector<NoeudAbstrait*> avisiter = std::vector<NoeudAbstrait*>();
	std::vector<NoeudAbstrait*> noeudSelectionnes = std::vector<NoeudAbstrait*>();
	avisiter.push_back(this);
	while (!avisiter.empty())
	{
		NoeudAbstrait* noeud = avisiter.back();
		avisiter.pop_back();

		if (noeud->obtenirType() == "paletteJoueur2Droite")
		{
			noeudSelectionnes.push_back(noeud);
		}

		for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			avisiter.push_back(noeud->chercher(i));
		}
	}
	return noeudSelectionnes;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::vector<NoeudAbstrait*> ArbreRenduINF2990::obtenirNoeudRessort()
///
/// Cette fonction parcour l'arbre pour trouver les ressorts
///
/// @return un vecteur contenant tous les noeuds de type palette ressort.
///
////////////////////////////////////////////////////////////////////////
std::vector<NoeudAbstrait*> ArbreRenduINF2990::obtenirNoeudRessort()
{
	std::vector<NoeudAbstrait*> avisiter = std::vector<NoeudAbstrait*>();
	std::vector<NoeudAbstrait*> noeudSelectionnes = std::vector<NoeudAbstrait*>();
	avisiter.push_back(this);
	while (!avisiter.empty())
	{
		NoeudAbstrait* noeud = avisiter.back();
		avisiter.pop_back();

		if (noeud->obtenirType() == ArbreRenduINF2990::NOM_RESSORT)
		{
			noeudSelectionnes.push_back(noeud);
		}

		for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			avisiter.push_back(noeud->chercher(i));
		}
	}
	return noeudSelectionnes;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::vector<NoeudAbstrait*> ArbreRenduINF2990::obtenirNoeudPortail()
///
/// Cette fonction parcour l'arbre pour trouver les portails
///
/// @return un vecteur contenant tous les noeuds de type palette portail.
///
////////////////////////////////////////////////////////////////////////
std::vector<NoeudAbstrait*> ArbreRenduINF2990::obtenirNoeudPortail()
{
	std::vector<NoeudAbstrait*> avisiter = std::vector<NoeudAbstrait*>();
	std::vector<NoeudAbstrait*> noeudSelectionnes = std::vector<NoeudAbstrait*>();
	avisiter.push_back(this);
	while (!avisiter.empty())
	{
		NoeudAbstrait* noeud = avisiter.back();
		avisiter.pop_back();

		if (noeud->obtenirType() == ArbreRenduINF2990::NOM_PORTAIL)
		{
			noeudSelectionnes.push_back(noeud);
		}

		for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			avisiter.push_back(noeud->chercher(i));
		}
	}
	return noeudSelectionnes;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::vector<NoeudAbstrait*> ArbreRenduINF2990::obtenirNoeudGenerateur()
///
/// Cette fonction parcour l'arbre pour trouver les generateurs
///
/// @return un vecteur contenant tous les noeuds de type generateurbille.
///
////////////////////////////////////////////////////////////////////////
std::vector<NoeudAbstrait*> ArbreRenduINF2990::obtenirNoeudGenerateurBille()
{
	std::vector<NoeudAbstrait*> avisiter = std::vector<NoeudAbstrait*>();
	std::vector<NoeudAbstrait*> noeudSelectionnes = std::vector<NoeudAbstrait*>();
	avisiter.push_back(this);
	while (!avisiter.empty())
	{
		NoeudAbstrait* noeud = avisiter.back();
		avisiter.pop_back();

		if (noeud->obtenirType() == ArbreRenduINF2990::NOM_GENERATEUR_BILLE)
		{
			noeudSelectionnes.push_back(noeud);
		}

		for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			avisiter.push_back(noeud->chercher(i));
		}
	}
	return noeudSelectionnes;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::vector<NoeudAbstrait*> ArbreRenduINF2990::obtenirNoeudBille()
///
/// Cette fonction parcour l'arbre pour trouver les billes
///
/// @return un vecteur contenant tous les noeuds de type bille.
///
////////////////////////////////////////////////////////////////////////
std::vector<NoeudAbstrait*> ArbreRenduINF2990::obtenirNoeudBille()
{
	std::vector<NoeudAbstrait*> avisiter = std::vector<NoeudAbstrait*>();
	std::vector<NoeudAbstrait*> noeudSelectionnes = std::vector<NoeudAbstrait*>();
	avisiter.push_back(this);
	while (!avisiter.empty())
	{
		NoeudAbstrait* noeud = avisiter.back();
		avisiter.pop_back();

		if (noeud->obtenirType() == ArbreRenduINF2990::NOM_BILLE)
		{
			noeudSelectionnes.push_back(noeud);
		}

		for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			avisiter.push_back(noeud->chercher(i));
		}
	}
	return noeudSelectionnes;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPortail* ArbreRenduINF2990::obtenirNoeudFrere(NoeudPortail* portail)
///
/// Cette fonction parcour l'arbre pour trouver le portail associer au portail recu en parametre
///
/// @param[in] NoeudPortail* portail : portail associer
///
/// @return un vecteur contenant tous les noeuds de type palette droite du joueur 2.
///
////////////////////////////////////////////////////////////////////////
NoeudPortail* ArbreRenduINF2990::obtenirNoeudFrere(NoeudPortail* portail)
{
	std::vector<NoeudAbstrait*> avisiter = std::vector<NoeudAbstrait*>();
	avisiter.push_back(this);
	while (!avisiter.empty())
	{
		NoeudAbstrait* noeud = avisiter.back();
		avisiter.pop_back();

		if (noeud->obtenirType() == NOM_PORTAIL && ((NoeudPortail*)noeud)->obtenirId() == portail->obtenirId())
		{
			if (portail->obtenirPositionRelative() != noeud->obtenirPositionRelative())
			{
				return (NoeudPortail*)noeud;
			}

		}

		for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			avisiter.push_back(noeud->chercher(i));
		}
	}
	return nullptr;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
