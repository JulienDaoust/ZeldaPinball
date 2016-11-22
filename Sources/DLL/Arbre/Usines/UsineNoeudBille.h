///////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudBille.h
/// @author Tommy Sagala
/// @date 2014-09-17
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDBILLE_H__
#define __ARBRE_USINES_USINENOEUDBILLE_H__


#include "UsineNoeud.h"
#include "NoeudBille.h"


///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudBille
/// @brief Classe qui repr�sente une usine capable de cr�er des noeuds de
///        type NoeudBille.
///
/// @author Tommy Sagala
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////
class UsineNoeudBille : public UsineNoeud
{
public:
	/// Constructeur par param�tres.
	inline UsineNoeudBille(const std::string& nom);

	/// Fonction � surcharger pour la cr�ation d'un noeud.
	inline virtual NoeudAbstrait* creerNoeud() const;


};


////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudBille::UsineNoeudBille(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds cr��s.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudBille::UsineNoeudBille(const std::string& nom)
	: UsineNoeud(nom)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudBille::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cr�� du type produit
/// par cette usine, soit une araign�e.
///
/// @return Le noeud nouvellement cr��.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudBille::creerNoeud() const
{
	return new NoeudBille{ obtenirNom() };
}


#endif // __ARBRE_USINES_USINENOEUDBILLE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
