///////////////-///////////////////////////////////////////////////////////
/// @file NoeudButoirTriangulaireGauche.h
/// @author Tommy Sagala
/// @date 2014-09-17
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NoeudButoirTriangulaireGauche_H__
#define __ARBRE_NOEUDS_NoeudButoirTriangulaireGauche_H__

#include "NoeudAbstrait.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"
#include <GL/gl.h>

///////////////////////////////////////////////////////////////////////////
/// @class NoeudButoirTriangulaireGauche
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////
class NoeudButoirTriangulaireGauche : public NoeudAbstrait
{
public:
   /// Constructeur à partir du type du noeud.
   NoeudButoirTriangulaireGauche(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudButoirTriangulaireGauche();

   /// Affiche le cube.
   virtual void afficherConcret() const;
   /// Effectue l'animation du cube.
   virtual void animer( float temps );
   /// Accepte le Visiteur
	virtual void accepte(VisiteurAbstrait* Visiteur);

	/// Assigne le nombre de points
	virtual void assignerPoints(int points);

	/// Retourne le nombre de points
	virtual int obtenirPoints();

	/// Calcule la Boite englobante du noeud
	virtual void calculBoiteEnglobante();

	/// permet d'identifier les collisions
	virtual aidecollision::DetailsCollision collision(NoeudAbstrait* noeud);

private:
	///nombre de points
	int nbPoints_ = 10;

};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudButoirTriangulaireGauche::accepte()
///
/// Cette fonction permet au Visiteur de traverse l'arbre
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void NoeudButoirTriangulaireGauche::accepte(VisiteurAbstrait* Visiteur)
{
	Visiteur->visite(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudButoirTriangulaireGauche::assignerPoints(int points);
///
/// Cette fonction permet d'assigner les points au noeud
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void NoeudButoirTriangulaireGauche::assignerPoints(int points)
{
	nbPoints_ = points;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline int  NoeudButoirTriangulaireGauche::obtenirPoints();
///
/// Cette fonction retourne les points du noeud
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline int NoeudButoirTriangulaireGauche::obtenirPoints()
{
	return nbPoints_;
}

#endif // __ARBRE_NOEUDS_NoeudButoirTriangulaireGauche_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
