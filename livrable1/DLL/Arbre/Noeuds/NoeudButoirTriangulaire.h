///////////////-///////////////////////////////////////////////////////////
/// @file NoeudButoirTriangulaire.h
/// @author Tommy Sagala
/// @date 2014-09-17
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDBUTOIRTRIANGULAIRE_H__
#define __ARBRE_NOEUDS_NOEUDBUTOIRTRIANGULAIRE_H__

#include "NoeudAbstrait.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"
#include <GL/gl.h>

///////////////////////////////////////////////////////////////////////////
/// @class NoeudButoirTriangulaire
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////
class NoeudButoirTriangulaire : public NoeudAbstrait
{
public:
   /// Constructeur à partir du type du noeud.
   NoeudButoirTriangulaire(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudButoirTriangulaire();

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

private:
	///nombre de points
	int nbPoints_ = 10;

};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudButoirTriangulaire::accepte()
///
/// Cette fonction permet au Visiteur de traverse l'arbre
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void NoeudButoirTriangulaire::accepte(VisiteurAbstrait* Visiteur)
{
	Visiteur->visite(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudButoirTriangulaire::assignerPoints(int points);
///
/// Cette fonction permet d'assigner les points au noeud
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void NoeudButoirTriangulaire::assignerPoints(int points)
{
	nbPoints_ = points;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline int  NoeudButoirTriangulaire::obtenirPoints();
///
/// Cette fonction retourne les points du noeud
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline int NoeudButoirTriangulaire::obtenirPoints()
{
	return nbPoints_;
}

#endif // __ARBRE_NOEUDS_NOEUDBUTOIRTRIANGULAIRE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
