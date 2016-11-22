///////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudRessort.h
/// @author Tommy Sagala
/// @date 2014-09-17
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDRESSORT_H__
#define __ARBRE_USINES_USINENOEUDRESSORT_H__


#include "UsineNoeud.h"
#include "NoeudRessort.h"


///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudRessort
/// @brief Classe qui représente une usine capable de créer des noeuds de
///        type NoeudRessort.
///
/// @author Tommy Sagala
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////
class UsineNoeudRessort : public UsineNoeud
{
public:
   /// Constructeur par paramètres.
   inline UsineNoeudRessort(const std::string& nom);

   /// Fonction à surcharger pour la création d'un noeud.
   inline virtual NoeudAbstrait* creerNoeud() const;


};


////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudRessort::UsineNoeudRessort(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds créés.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudRessort::UsineNoeudRessort(const std::string& nom)
   : UsineNoeud(nom)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudRessort::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement créé du type produit
/// par cette usine, soit une araignée.
///
/// @return Le noeud nouvellement créé.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudRessort::creerNoeud() const
{
	return new NoeudRessort{ obtenirNom() };
}


#endif // __ARBRE_USINES_USINENOEUDRESSORT_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
