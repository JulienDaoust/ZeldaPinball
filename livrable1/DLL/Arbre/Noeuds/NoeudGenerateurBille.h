///////////////////////////////////////////////////////////////////////////
/// @file NoeudGenerateurBille.h
/// @author Tommy Sagala
/// @date 2014-09-17
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDGENERATEURBILLE_H__
#define __ARBRE_NOEUDS_NOEUDGENERATEURBILLE_H__


#include "NoeudComposite.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"
#include <GL/gl.h>


///////////////////////////////////////////////////////////////////////////
/// @class NoeudGenerateurBille
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Tommy Sagala
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////
class NoeudGenerateurBille : public NoeudComposite
{
public:
   /// Constructeur à partir du type du noeud.
   NoeudGenerateurBille(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudGenerateurBille();

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
/// @fn inline bool NoeudGenerateurBille::accepte()
///
/// Cette fonction permet au Visiteur de traverse l'arbre
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void NoeudGenerateurBille::accepte(VisiteurAbstrait* Visiteur)
{
	Visiteur->visite(this);
}


#endif // __ARBRE_NOEUDS_NOEUDGENERATEURBILLE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
