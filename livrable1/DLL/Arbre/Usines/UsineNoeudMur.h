///////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudMur.h
/// @author Tommy Sagala
/// @date 2014-09-17
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUDMUR_H__
#define __ARBRE_USINES_USINENOEUDMUR_H__


#include "UsineNoeud.h"
#include "NoeudMur.h"


///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudMur
/// @brief Classe qui repr�sente une usine capable de cr�er des noeuds de
///        type NoeudMur.
///
/// @author Tommy Sagala
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////
class UsineNoeudMur : public UsineNoeud
{
public:
   /// Constructeur par param�tres.
   inline UsineNoeudMur(const std::string& nom);

   /// Fonction � surcharger pour la cr�ation d'un noeud.
   inline virtual NoeudAbstrait* creerNoeud() const;


};


////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudMur::UsineNoeudMur(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds cr��s.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudMur::UsineNoeudMur(const std::string& nom)
   : UsineNoeud(nom)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudMur::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cr�� du type produit
/// par cette usine, soit une araign�e.
///
/// @return Le noeud nouvellement cr��.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudMur::creerNoeud() const
{
	return new NoeudMur{ obtenirNom() };
}


#endif // __ARBRE_USINES_USINENOEUDMUR_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
