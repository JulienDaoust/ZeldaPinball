///////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudPaletteJoueur2.h
/// @author Tommy Sagala
/// @date 2014-09-17
/// @version 1.0
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDPALETTEJOUEUR2_H__
#define __ARBRE_USINES_USINENOEUDPALETTEJOUEUR2_H__

#include "UsineNoeud.h"
#include "NoeudPaletteJoueur2.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudPaletteJoueur2
/// @brief Classe qui représente une usine capable de créer des noeuds de
///        type NoeudPalette.
///
/// @author Tommy Sagala
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////
class UsineNoeudPaletteJoueur2 : public UsineNoeud
{
public:
	/// Constructeur par paramètres.
	inline UsineNoeudPaletteJoueur2(const std::string& nom);

	/// Fonction à surcharger pour la création d'un noeud.
	inline virtual NoeudAbstrait* creerNoeud() const;


};


////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudPalette::UsineNoeudPalette(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds créés.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudPaletteJoueur2::UsineNoeudPaletteJoueur2(const std::string& nom)
: UsineNoeud(nom)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudPalette::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement créé du type produit
/// par cette usine, soit une araignée.
///
/// @return Le noeud nouvellement créé.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudPaletteJoueur2::creerNoeud() const
{
	return new NoeudPaletteJoueur2{ obtenirNom() };
}


#endif // __ARBRE_USINES_USINENOEUDPALETTE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
