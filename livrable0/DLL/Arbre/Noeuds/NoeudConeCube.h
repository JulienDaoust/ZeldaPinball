///////////////////////////////////////////////////////////////////////////
/// @file NoeudConeCube.h
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDCONECUBE_H__
#define __ARBRE_NOEUDS_NOEUDCONECUBE_H__


#include "NoeudAbstrait.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"
#include <GL/gl.h>


///////////////////////////////////////////////////////////////////////////
/// @class NoeudConeCube
/// @brief Classe qui repr�sente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudConeCube : public NoeudAbstrait
{
public:
   /// Constructeur � partir du type du noeud.
   NoeudConeCube(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudConeCube();

   /// Affiche le cube.
   virtual void afficherConcret() const;
   /// Effectue l'animation du cube.
   virtual void animer( float temps );

   /// Accepte le visiteur
   virtual void accepte(VisiteurAbstrait* visiteur);


private:
   /// Storage pour le dessin du mod�le
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
/// @fn inline bool NoeudConeCube::visit()
///
/// Cette fonction permet au visiteur de traverse l'arbre
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void NoeudConeCube::accepte(VisiteurAbstrait* visiteur)
{
	visiteur->Visite(this);
}

#endif // __ARBRE_NOEUDS_NOEUDCONECUBE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
