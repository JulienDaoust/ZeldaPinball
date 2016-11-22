///////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudButoirTriangulaireGauche.h
/// @author Tommy Sagala
/// @date 2014-09-17
/// @version 1.0
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_UsineNoeudButoirTriangulaireGauche_H__
#define __ARBRE_USINES_UsineNoeudButoirTriangulaireGauche_H__

#include "UsineNoeud.h"
#include "NoeudButoirTriangulaireGauche.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudButoirTriangulaireGauche
/// @brief Classe qui repr�sente une usine capable de cr�er des noeuds de
///        type NoeudButoirTriangulaire.
///
/// @author Tommy Sagala
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////
class UsineNoeudButoirTriangulaireGauche : public UsineNoeud
{
public:
   /// Constructeur par param�tres.
   inline UsineNoeudButoirTriangulaireGauche(const std::string& nom);

   /// Fonction � surcharger pour la cr�ation d'un noeud.
   inline virtual NoeudAbstrait* creerNoeud() const;


};


////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudButoirTriangulaireGauche::UsineNoeudButoirTriangulaireGauche(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds cr��s.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudButoirTriangulaireGauche::UsineNoeudButoirTriangulaireGauche(const std::string& nom)
   : UsineNoeud(nom)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudButoirTriangulaireGauche::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cr�� du type produit
/// par cette usine, soit une araign�e.
///
/// @return Le noeud nouvellement cr��.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudButoirTriangulaireGauche::creerNoeud() const
{
	return new NoeudButoirTriangulaireGauche{ obtenirNom() };
}


#endif // __ARBRE_USINES_UsineNoeudButoirTriangulaireGauche_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
