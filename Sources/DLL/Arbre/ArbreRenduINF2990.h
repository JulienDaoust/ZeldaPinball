///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.h
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_ARBRERENDUINF2990_H__
#define __ARBRE_ARBRERENDUINF2990_H__


#include "ArbreRendu.h"
#include "noeudAbstrait.h"
#include "noeudPortail.h"

#include <map>
#include <string>


///////////////////////////////////////////////////////////////////////////
/// @class ArbreRenduINF2990
/// @brief Classe qui représente l'arbre de rendu spécifique au projet de
///        INF2990.
///
///        Cette classe s'occupe de configurer les usines des noeuds qui
///        seront utilisés par le projet.
///
/// @author Martin Bisson
/// @date 2007-03-23
///////////////////////////////////////////////////////////////////////////
class ArbreRenduINF2990 : public ArbreRendu
{
public:
   /// Constructeur par défaut.
   ArbreRenduINF2990();
   /// Destructeur.
   virtual ~ArbreRenduINF2990();

   /// Initialise l'arbre de rendu à son état initial.
   void initialiser();
   /// retourne lesnoeuds selectionnés
   std::vector<NoeudAbstrait*> obtenirNoeudSelectionnes();
   /// Retourne les palettes gauche du joueur 1
   std::vector<NoeudAbstrait*> obtenirNoeudPaletteGJ1();
   /// Retourne les palettes droite du joueur 1
   std::vector<NoeudAbstrait*> obtenirNoeudPaletteDJ1();
   /// Retourne les palettes gauche du joueur 1
   std::vector<NoeudAbstrait*> obtenirNoeudPaletteGJ2();
   /// Retourne les palettes droite du joueur 2
   std::vector<NoeudAbstrait*> obtenirNoeudPaletteDJ2();
   /// Retourne les ressorts
   std::vector<NoeudAbstrait*> obtenirNoeudRessort();
   /// Retourne les generateurs de billes
   std::vector<NoeudAbstrait*> obtenirNoeudGenerateurBille();
   /// Retourne les billes
   std::vector<NoeudAbstrait*> obtenirNoeudBille();
   /// Retourne les generateurs de billes
   std::vector<NoeudAbstrait*> obtenirNoeudPortail();
   /// Permet de parcourir l'arbre pour obtenir le deuxieme portail d'une paire
   NoeudPortail* obtenirNoeudFrere(NoeudPortail* portail);

   /// Permet d'obtenir les points pour passer a la prochaine campagne
   inline int obtenirPointsCampagne();
   /// Permet d'obtenir les points pour avoir une bille gratuite
   inline int obtenirPointsBille();
   /// Permet d'obtenir la difficulté
   inline int obtenirDifficulte();
   /// Retourne les points dun certain type de collision
   inline int obtenirPointsCollision(std::string objet);

   /// Permet d'assigner les points pour passer a la prochaine campagne
   inline void assignerPointsCampagne(int points);
   /// Permet d'assigner les points pour avoir une bille gratuite
   inline  void assignerPointsBille(int points);
   /// Permet d'assigner les points d'un butoir circulaire
   inline  void assignerPointsButoirCir(int points);
   /// Permet d'assigner les points d'un butoir triangulaire
   inline  void assignerPointsButoirTri(int points);
   /// Permet d'assigner les points d'une cible
   inline  void assignerPointsCible(int points);
   /// Permet d'assigner la difficulte dun niveau
   inline  void assignerDifficulte(int points);
   /// Permet d'obtenir les points d'un butoir circulaire
   inline int obtenirPointsButoirCir();
   /// Permet d'obtenir les points d'un butoir triangulaire
   inline int obtenirPointsButoirTri();
   /// Permet d'obtenir les points d'une cible
   inline int obtenirPointsCible();

	/// La chaîne représentant le type des araignées.
   static const std::string NOM_ARAIGNEE;
	/// La chaîne représentant le type des cones-cubes.
   static const std::string NOM_CONECUBE;

   static const std::string NOM_PALETTE_JOUEUR1_GAUCHE;
   static const std::string NOM_PALETTE_JOUEUR1_DROITE;
   static const std::string NOM_PALETTE_JOUEUR2_GAUCHE;
   static const std::string NOM_PALETTE_JOUEUR2_DROITE;
   static const std::string NOM_PLAQUE;
   static const std::string NOM_BUTOIR_TRIANGULAIRE_GAUCHE;
   static const std::string NOM_BUTOIR_TRIANGULAIRE_DROIT;
   static const std::string NOM_BUTOIR_CIRCULAIRE;
   static const std::string NOM_CIBLE;
   static const std::string NOM_RESSORT;
   static const std::string NOM_GENERATEUR_BILLE;
   static const std::string NOM_TROU;
   static const std::string NOM_PORTAIL;
   static const std::string NOM_MUR;
   static const std::string NOM_BILLE;

private:
	/// Points nécessaires pour passer a la campagne suivante
	int pointsCampagne = 10000;

	/// Points nécessaires pour obtenir une bille gratuite
	int pointsBille = 10000;

	/// Points assignés aux butoirs circulaires
	int pointsButoirCirculaire = 100;

	/// Points assignés aux butoirs triangulaires
	int pointsButoirTriangulaire = 100;

	/// Points assignés aux cibles
	int pointsCible = 100;

	/// Niveau de difficulté
	int difficulte = 0;

};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline int ArbreRenduINF2990::obtenirPointsCampagne()
///
/// Cette fonction retourne le nombre de points requis pour passer a la campagne suivante
///
/// @return le nombre de points requis pour passer a la campagne suivante
///
////////////////////////////////////////////////////////////////////////
inline int ArbreRenduINF2990::obtenirPointsCampagne()
{
	return pointsCampagne;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline int ArbreRenduINF2990::obtenirPointsBille()
///
/// Cette fonction retourne le nombre de points requis pour avoir une bille gratuite
///
/// @return le nombre de points requis pour avoir une bille gratuite
///
////////////////////////////////////////////////////////////////////////
inline int ArbreRenduINF2990::obtenirPointsBille()
{
	return pointsBille;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline int ArbreRenduINF2990::obtenirPointsButoirCir()
///
/// Cette fonction retourne le nombre de points d'un butoir circulaire
///
/// @return le nombre de points
///
////////////////////////////////////////////////////////////////////////
inline int ArbreRenduINF2990::obtenirPointsCollision(std::string objet)
{
	if (objet == ArbreRenduINF2990::NOM_BUTOIR_CIRCULAIRE)
		return pointsButoirCirculaire;
	if (objet == ArbreRenduINF2990::NOM_BUTOIR_TRIANGULAIRE_DROIT)
		return pointsButoirTriangulaire;
	if (objet == ArbreRenduINF2990::NOM_BUTOIR_TRIANGULAIRE_GAUCHE)
		return pointsButoirTriangulaire;
	if (objet == ArbreRenduINF2990::NOM_CIBLE)
		return pointsCible;
	return 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline int ArbreRenduINF2990::obtenirDifficulté()
///
/// Cette fonction retourne la difficulté
///
/// @return La difficulte
///
////////////////////////////////////////////////////////////////////////
inline int ArbreRenduINF2990::obtenirDifficulte()
{
	return difficulte;
}



////////////////////////////////////////////////////////////////////////
///
/// @fn inline void ArbreRenduINF2990::obtenirPointsButoirCir()
///
/// Cette fonction permet d'obtenir le nombre de points d'un butoir circulaire
///
/// @return pointsButoirCirculaire
///
////////////////////////////////////////////////////////////////////////
inline int ArbreRenduINF2990::obtenirPointsButoirCir()
{
	return pointsButoirCirculaire;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void ArbreRenduINF2990::obtenirPointsButoirTri(int point)
///
/// Cette fonction permet d'obtenir le nombre de points d'un butoir triangulaire
///
/// @return pointsButoirTriangulaire
///
////////////////////////////////////////////////////////////////////////
inline int ArbreRenduINF2990::obtenirPointsButoirTri()
{
	return pointsButoirTriangulaire;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void ArbreRenduINF2990::obtenirPointsCible()
///
/// Cette fonction permet d'obtenir le nombre de points d'une cible
///
/// @return pointsCible
///
////////////////////////////////////////////////////////////////////////
inline int ArbreRenduINF2990::obtenirPointsCible()
{
	return pointsCible;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void ArbreRenduINF2990::assignerPointsButoirCir(int points)
///
/// Cette fonction assigner le nombre de points d'un butoire circulaire
///
/// @return pointsCible
///
////////////////////////////////////////////////////////////////////////
inline void ArbreRenduINF2990::assignerPointsButoirCir(int points)
{
	pointsButoirCirculaire = points;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void ArbreRenduINF2990::assignerPointsButoirCir(int points)
///
/// Cette fonction d'assigner le nombre de points d'un butoir triangulaire
///
/// @return none
///
////////////////////////////////////////////////////////////////////////
inline void ArbreRenduINF2990::assignerPointsButoirTri(int points)
{
	pointsButoirTriangulaire = points;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void ArbreRenduINF2990::assignerPointsCible(int points)
///
/// Cette fonction d'assigner le nombre de points d'une cible
///
/// @return none
///
////////////////////////////////////////////////////////////////////////
inline void ArbreRenduINF2990::assignerPointsCible(int points)
{
	pointsCible = points;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void ArbreRenduINF2990::assignerPointsCampagne(int points)
///
/// Cette fonction d'assigner le nombre de points pour passer au niveau
///
/// suivant d'une campagne
///
/// @return none
///
////////////////////////////////////////////////////////////////////////
inline void ArbreRenduINF2990::assignerPointsCampagne(int points)
{
	pointsCampagne = points;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void ArbreRenduINF2990::assignerPointsBille(int points)
///
/// Cette fonction d'assigner le nombre de points pour obtenir une
///
/// bille supplementaire
///
/// @return none
///
////////////////////////////////////////////////////////////////////////
inline void ArbreRenduINF2990::assignerPointsBille(int points)
{
	pointsBille = points;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn inline void ArbreRenduINF2990::assignerDifficulte(int points)
///
/// Cette fonction d'assigner la difficulte d'un niveau
///
/// @return none
///
////////////////////////////////////////////////////////////////////////
inline void ArbreRenduINF2990::assignerDifficulte(int points)
{
	difficulte = points;
}
#endif // __ARBRE_ARBRERENDUINF2990_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
