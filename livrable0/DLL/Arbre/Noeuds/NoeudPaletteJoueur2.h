///////////////-///////////////////////////////////////////////////////////
/// @file NoeudPaletteJoueur2.h
/// @author Tommy Sagala
/// @date 2014-09-17
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDPALETTEJOUEUR2_H__
#define __ARBRE_NOEUDS_NOEUDPALETTEJOUEUR2_H__

#include "NoeudAbstrait.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"
#include <GL/gl.h>

///////////////////////////////////////////////////////////////////////////
/// @class NoeudPaletteJoueur2
/// @brief Classe qui repr�sente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////
class NoeudPaletteJoueur2 : public NoeudAbstrait
{
public:
	/// Constructeur � partir du type du noeud.
	NoeudPaletteJoueur2(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudPaletteJoueur2();

	/// Affiche le cube.
	virtual void afficherConcret() const;
	/// Effectue l'animation du cube.
	virtual void animer(float temps);

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
/// @fn inline bool NoeudPaletteJoueur2::accepte()
///
/// Cette fonction permet au visiteur de traverse l'arbre
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void NoeudPaletteJoueur2::accepte(VisiteurAbstrait* visiteur)
{
	visiteur->Visite(this);
}


#endif // __ARBRE_NOEUDS_NOEUDPALETTEJOUEUR2_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
