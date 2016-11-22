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
   /// Accepte le visiteur
	virtual void accepte(VisiteurAbstrait* visiteur);


private:
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
/// @fn inline bool NoeudButoirTriangulaire::accepte()
///
/// Cette fonction permet au visiteur de traverse l'arbre
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void NoeudButoirTriangulaire::accepte(VisiteurAbstrait* visiteur)
{
	visiteur->Visite(this);
}


#endif // __ARBRE_NOEUDS_NOEUDBUTOIRTRIANGULAIRE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
