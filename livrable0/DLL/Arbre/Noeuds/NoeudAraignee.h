///////////////////////////////////////////////////////////////////////////
/// @file NoeudAraignee.h
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDARAIGNEE_H__
#define __ARBRE_NOEUDS_NOEUDARAIGNEE_H__


#include "NoeudComposite.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"
#include <GL/gl.h>


///////////////////////////////////////////////////////////////////////////
/// @class NoeudAraignee
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2011-05-19
///////////////////////////////////////////////////////////////////////////
class NoeudAraignee : public NoeudComposite
{
public:
   /// Constructeur à partir du type du noeud.
   NoeudAraignee(const std::string& typeNoeud);
   /// Destructeur.
   ~NoeudAraignee();

   /// Affiche le cube.
   virtual void afficherConcret() const;
   /// Effectue l'animation du cube.
   virtual void animer( float temps );

   /// Accepte le visiteur
	virtual void accepte(VisiteurAbstrait* visiteur);


private:
   /// Storage pour le dessin du modèle
   modele::opengl_storage::OpenGL_Liste liste_;

   /// Angle dans le sinus de l'oscillation
   float angle_{ 0 };

};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAraignee::accepte()
///
/// Cette fonction permet au visiteur de traverse l'arbre
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAraignee::accepte(VisiteurAbstrait* visiteur)
{
	visiteur->Visite(this);
}


#endif // __ARBRE_NOEUDS_NOEUDARAIGNEE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
