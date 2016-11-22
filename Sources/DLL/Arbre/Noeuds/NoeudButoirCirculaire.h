///////////////-///////////////////////////////////////////////////////////
/// @file NoeudButoirCirculaire.h
/// @author Tommy Sagala
/// @date 2014-09-17
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDBUTOIRCIRCULAIRE_H__
#define __ARBRE_NOEUDS_NOEUDBUTOIRCIRCULAIRE_H__

#include "NoeudAbstrait.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"
#include <GL/gl.h>

///////////////////////////////////////////////////////////////////////////
/// @class NoeudButoirCirculaire
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////
class NoeudButoirCirculaire : public NoeudAbstrait
{
public:
   /// Constructeur à partir du type du noeud.
   NoeudButoirCirculaire(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudButoirCirculaire();

   /// Affiche le cube.
   virtual void afficherConcret() const;
   /// Effectue l'animation du cube.
   virtual void animer( float temps );

   /// Assigne le nombre de points
   virtual void assignerPoints(int points);

   /// Retourne le nombre de points
   virtual int obtenirPoints();

   /// Accepte le Visiteur
	virtual void accepte(VisiteurAbstrait* Visiteur);

	// Assigne la collision
	void assignerCollision();

	/// permet d'identifier les collisions
	virtual aidecollision::DetailsCollision collision(NoeudAbstrait* noeud);

private:
	double hitScaling_{ 1.2 };
	double scalingTime_{ 0.5 };
	double multiplicateurScale_{1.0};
	int nbPoints_ = 10;
	bool touche_ = false;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudButoirCirculaire::accepte()
///
/// Cette fonction permet au Visiteur de traverse l'arbre
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void NoeudButoirCirculaire::accepte(VisiteurAbstrait* Visiteur)
{
	Visiteur->visite(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void assignerPoints(int points);
///
/// Cette fonction permet d'assigner les points au noeud
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void NoeudButoirCirculaire::assignerPoints(int points)
{
	nbPoints_ = points;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline int obtenirPoints();
///
/// Cette fonction retourne les points du noeud
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline int NoeudButoirCirculaire::obtenirPoints()
{
	return nbPoints_;
}


#endif // __ARBRE_NOEUDS_NOEUDBUTOIRCIRCULAIRE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
