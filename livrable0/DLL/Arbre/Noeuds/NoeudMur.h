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
   /// Accepte le visiteur
	virtual void accepte(VisiteurAbstrait* visiteur);
	/// méthode pour assigner des points aux cliques.
	void assigner(glm::dvec3 point1, glm::dvec3 point2);

private:
   /// Storage pour le dessin du modèle
   modele::opengl_storage::OpenGL_Liste liste_;

   /// Angle dans le sinus de l'oscillation
   float angle_{ 0 };
   glm::dvec3 point1_;
   glm::dvec3 point2_;

};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudMur::accepte()
///
/// Cette fonction permet au visiteur de traverse l'arbre
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void NoeudMur::accepte(VisiteurAbstrait* visiteur)
{
	visiteur->Visite(this);
}


#endif // __ARBRE_NOEUDS_NOEUDMUR_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
