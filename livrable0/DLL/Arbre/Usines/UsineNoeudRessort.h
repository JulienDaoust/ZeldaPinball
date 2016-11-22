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
/// @brief Classe qui repr�sente une usine capable de cr�er des noeuds de
///        type NoeudRessort.
///
/// @author Tommy Sagala
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////
class UsineNoeudRessort : public UsineNoeud
{
public:
   /// Constructeur par param�tres.
   inline UsineNoeudRessort(const std::string& nom);

   /// Fonction � surcharger pour la cr�ation d'un noeud.
   inline virtual NoeudAbstrait* creerNoeud() const;


};


////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudRessort::UsineNoeudRessort(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds cr��s.
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
/// Cette fonction retourne un noeud nouvellement cr�� du type produit
/// par cette usine, soit une araign�e.
///
/// @return Le noeud nouvellement cr��.
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
