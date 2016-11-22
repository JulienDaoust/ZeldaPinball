///////////////////////////////////////////////////////////////////////////
/// @file NoeudMur.h
/// @author Tommy Sagala
/// @date 2014-09-17
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDMUR_H__
#define __ARBRE_NOEUDS_NOEUDMUR_H__


#include "NoeudComposite.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"
#include <GL/gl.h>


///////////////////////////////////////////////////////////////////////////
/// @class NoeudMur
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Tommy Sagala
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////
class NoeudMur : public NoeudComposite
{
public:
   /// Constructeur à partir du type du noeud.
   NoeudMur(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudMur();

   /// Affiche le cube.
   virtual void afficherConcret() const;
   /// Effectue l'animation du cube.
   virtual void animer( float temps );
   /// Accepte le Visiteur
	virtual void accepte(VisiteurAbstrait* Visiteur);

private:
   /// Storage pour le dessin du modèle
   modele::opengl_storage::OpenGL_Liste liste_;

   /// Angle dans le sinus de l'oscillation
   float angle_{ 0 };
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudMur::accepte()
///
/// Cette fonction permet au Visiteur de traverse l'arbre
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void NoeudMur::accepte(VisiteurAbstrait* Visiteur)
{
	Visiteur->visite(this);
}


#endif // __ARBRE_NOEUDS_NOEUDMUR_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
