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

   /// Accepte le visiteur
	virtual void accepte(VisiteurAbstrait* visiteur);


private:
	/// Calcule la Boite englobante du noeud
	virtual void calculBoiteEnglobante();

   /// Storage pour le dessin du modèle
   modele::opengl_storage::OpenGL_Liste liste_;

   /// Angle selon l'axe des X.
   float angleX_{ 0.f };
   /// Angle selon l'axe des Y.
   float angleY_{ 0.f };
   /// Angle de rotation.
   float angleRotation_{ 0.f };

};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudButoirCirculaire::accepte()
///
/// Cette fonction permet au visiteur de traverse l'arbre
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void NoeudButoirCirculaire::accepte(VisiteurAbstrait* visiteur)
{
	visiteur->Visite(this);
}

#endif // __ARBRE_NOEUDS_NOEUDBUTOIRCIRCULAIRE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
