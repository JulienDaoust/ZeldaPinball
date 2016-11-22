///////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudPaletteJoueur2Gauche.h
/// @author Tommy Sagala
/// @date 2014-09-17
/// @version 1.0
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDPALETTEJOUEUR2GAUCHE_H__
#define __ARBRE_USINES_USINENOEUDPALETTEJOUEUR2GAUCHE_H__

#include "UsineNoeud.h"
#include "NoeudPaletteJoueur2Gauche.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudPaletteJoueur2Gauche
/// @brief Classe qui repr�sente une usine capable de cr�er des noeuds de
///        type NoeudPalette.
///
/// @author Tommy Sagala
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////
class UsineNoeudPaletteJoueur2Gauche : public UsineNoeud
{
public:
	/// Constructeur par param�tres.
	inline UsineNoeudPaletteJoueur2Gauche(const std::string& nom);

	/// Fonction � surcharger pour la cr�ation d'un noeud.
	inline virtual NoeudAbstrait* creerNoeud() const;

};


////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudPalette::UsineNoeudPalette(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds cr��s.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudPaletteJoueur2Gauche::UsineNoeudPaletteJoueur2Gauche(const std::string& nom)
	: UsineNoeud(nom)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudPalette::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cr�� du type produit
/// par cette usine, soit une araign�e.
///
/// @return Le noeud nouvellement cr��.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudPaletteJoueur2Gauche::creerNoeud() const
{
	return new NoeudPaletteJoueur2Gauche{ obtenirNom() };
}


#endif // __ARBRE_USINES_USINENOEUDPALETTEJOUEUR2GAUCHE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
