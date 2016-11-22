///////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudButoirCirculaire.h
/// @author Tommy Sagala
/// @date 2014-09-17
/// @version 1.0
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDBUTOIRCIRCULAIRE_H__
#define __ARBRE_USINES_USINENOEUDBUTOIRCIRCULAIRE_H__

#include "UsineNoeud.h"
#include "NoeudButoirCirculaire.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudButoirCirculaire
/// @brief Classe qui représente une usine capable de créer des noeuds de
///        type NoeudButoirCirculaire.
///
/// @author Tommy Sagala
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////
class UsineNoeudButoirCirculaire : public UsineNoeud
{
public:
   /// Constructeur par paramètres.
   inline UsineNoeudButoirCirculaire(const std::string& nom);

   /// Fonction à surcharger pour la création d'un noeud.
   inline virtual NoeudAbstrait* creerNoeud() const;


};


////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudButoirCirculaire::UsineNoeudButoirCirculaire(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds créés.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudButoirCirculaire::UsineNoeudButoirCirculaire(const std::string& nom)
   : UsineNoeud(nom)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudButoirCirculaire::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement créé du type produit
/// par cette usine, soit une araignée.
///
/// @return Le noeud nouvellement créé.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudButoirCirculaire::creerNoeud() const
{
	return new NoeudButoirCirculaire{ obtenirNom() };
}


#endif // __ARBRE_USINES_USINENOEUDBUTOIRCIRCULAIRE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
