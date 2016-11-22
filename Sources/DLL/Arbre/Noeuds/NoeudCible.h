///////////////-///////////////////////////////////////////////////////////
/// @file NoeudCible.h
/// @author Tommy Sagala
/// @date 2014-09-17
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDCIBLE_H__
#define __ARBRE_NOEUDS_NOEUDCIBLE_H__

#include "NoeudAbstrait.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"
#include <GL/gl.h>

///////////////////////////////////////////////////////////////////////////
/// @class NoeudCible
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////
class NoeudCible : public NoeudAbstrait
{
public:
   /// Constructeur à partir du type du noeud.
   NoeudCible(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudCible();

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

	//assigne la collision
	void assignerCollision();

	//regarde l'état de la cible
	bool obtenirEtatCible() const;

	/// réinitiliser l'état de l'objet
	virtual void reinitialiserCible();

private:
	///nombre de points
	int nbPoints_ = 10;
	int cibleDisp = 0;
	bool touche_ = false;
	bool etat_ = true;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudCible::accepte()
///
/// Cette fonction permet au Visiteur de traverse l'arbre
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void NoeudCible::accepte(VisiteurAbstrait* Visiteur)
{
	Visiteur->visite(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudCible::assignerPoints(int points);
///
/// Cette fonction permet d'assigner les points au noeud
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void NoeudCible::assignerPoints(int points)
{
	nbPoints_ = points;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline int  NoeudCible::obtenirPoints();
///
/// Cette fonction retourne les points du noeud
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline int NoeudCible::obtenirPoints()
{
	return nbPoints_;
}

#endif // __ARBRE_NOEUDS_NOEUDCIBLE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
