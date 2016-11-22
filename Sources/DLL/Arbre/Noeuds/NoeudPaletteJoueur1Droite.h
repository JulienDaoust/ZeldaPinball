///////////////-///////////////////////////////////////////////////////////
/// @file NoeudPaletteJoueur1Droite.h
/// @author Tommy Sagala
/// @date 2014-09-17
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NoeudPaletteJoueur1Droite_H__
#define __ARBRE_NOEUDS_NoeudPaletteJoueur1Droite_H__

#include "NoeudAbstrait.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"
#include <GL/gl.h>

///////////////////////////////////////////////////////////////////////////
/// @class NoeudPaletteJoueur1Droite
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////
class NoeudPaletteJoueur1Droite : public NoeudAbstrait
{
public:
   /// Constructeur à partir du type du noeud.
	NoeudPaletteJoueur1Droite(const std::string& typeNoeud);
   /// Destructeur.
	~NoeudPaletteJoueur1Droite();

   /// Affiche le cube.
   virtual void afficherConcret() const;
   /// Effectue l'animation du cube.
   virtual void animer( float temps );

   /// Accepte le Visiteur
   virtual void accepte(VisiteurAbstrait* Visiteur);

   virtual bool estScaleable() const;

   //Change la direction de l'animation
   void setAnimation();

   virtual void calculBoiteEnglobante();
private:
	double angleAnimation = 60;
	bool dansLesAir = false;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudPaletteJoueur1Droite::accepte()
///
/// Cette fonction permet au Visiteur de traverse l'arbre
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void NoeudPaletteJoueur1Droite::accepte(VisiteurAbstrait* Visiteur)
{
	Visiteur->visite(this);
}


#endif // __ARBRE_NOEUDS_NoeudPaletteJoueur1Droite_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
