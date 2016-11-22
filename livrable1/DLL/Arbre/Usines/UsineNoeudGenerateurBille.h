///////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudGenerateurBille.h
/// @author Tommy Sagala
/// @date 2014-09-17
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDGENERATEURBILLE_H__
#define __ARBRE_USINES_USINENOEUDGENERATEURBILLE_H__


#include "UsineNoeud.h"
#include "NoeudGenerateurBille.h"


///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudGenerateurBille
/// @brief Classe qui représente une usine capable de créer des noeuds de
///        type NoeudGenerateurBille.
///
/// @author Tommy Sagala
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////
class UsineNoeudGenerateurBille : public UsineNoeud
{
public:
   /// Constructeur par paramètres.
   inline UsineNoeudGenerateurBille(const std::string& nom);

   /// Fonction à surcharger pour la création d'un noeud.
   inline virtual NoeudAbstrait* creerNoeud() const;


};


////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudGenerateurBille::UsineNoeudGenerateurBille(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds créés.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudGenerateurBille::UsineNoeudGenerateurBille(const std::string& nom)
   : UsineNoeud(nom)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudGenerateurBille::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement créé du type produit
/// par cette usine, soit une araignée.
///
/// @return Le noeud nouvellement créé.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudGenerateurBille::creerNoeud() const
{
	return new NoeudGenerateurBille{ obtenirNom() };
}


#endif // __ARBRE_USINES_USINENOEUDGENERATEURBILLE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
