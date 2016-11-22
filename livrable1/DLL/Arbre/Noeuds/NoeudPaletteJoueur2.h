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
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////
class NoeudPaletteJoueur2 : public NoeudAbstrait
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudPaletteJoueur2(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudPaletteJoueur2();

	/// Affiche le cube.
	virtual void afficherConcret() const;
	/// Effectue l'animation du cube.
	virtual void animer(float temps);

	/// Accepte le Visiteur
	virtual void accepte(VisiteurAbstrait* Visiteur);
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudPaletteJoueur2::accepte()
///
/// Cette fonction permet au Visiteur de traverse l'arbre
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void NoeudPaletteJoueur2::accepte(VisiteurAbstrait* Visiteur)
{
	Visiteur->visite(this);
}


#endif // __ARBRE_NOEUDS_NOEUDPALETTEJOUEUR2_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
