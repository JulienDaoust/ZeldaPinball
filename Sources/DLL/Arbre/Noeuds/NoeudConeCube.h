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
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudConeCube : public NoeudAbstrait
{
public:
   /// Constructeur à partir du type du noeud.
   NoeudConeCube(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudConeCube();

   /// Affiche le cube.
   virtual void afficherConcret() const;
   /// Effectue l'animation du cube.
   virtual void animer( float temps );

   /// Accepte le Visiteur
   virtual void accepte(VisiteurAbstrait* Visiteur);
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudConeCube::visit()
///
/// Cette fonction permet au Visiteur de traverse l'arbre
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void NoeudConeCube::accepte(VisiteurAbstrait* Visiteur)
{
	Visiteur->visite(this);
}

#endif // __ARBRE_NOEUDS_NOEUDCONECUBE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
