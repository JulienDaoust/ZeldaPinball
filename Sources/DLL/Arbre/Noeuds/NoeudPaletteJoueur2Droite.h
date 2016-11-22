///////////////-///////////////////////////////////////////////////////////
/// @file NoeudPaletteJoueur2Droite.h
/// @author Tommy Sagala
/// @date 2014-09-17
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NoeudPaletteJoueur2Droite_H__
#define __ARBRE_NOEUDS_NoeudPaletteJoueur2Droite_H__

#include "NoeudAbstrait.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"
#include <GL/gl.h>

///////////////////////////////////////////////////////////////////////////
/// @class NoeudPaletteJoueur2Droite
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////
class NoeudPaletteJoueur2Droite : public NoeudAbstrait
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudPaletteJoueur2Droite(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudPaletteJoueur2Droite();

	/// Affiche le cube.
	virtual void afficherConcret() const;
	/// Effectue l'animation du cube.
	virtual void animer(float temps);

	/// Accepte le Visiteur
	virtual void accepte(VisiteurAbstrait* Visiteur);

	virtual bool estScaleable() const;

	virtual void calculBoiteEnglobante();

	//Inverse le sens de l'animation
	void setAnimation();
private:
	double angleAnimation = 60;
	bool dansLesAir = false;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudPaletteJoueur2Droite::accepte()
///
/// Cette fonction permet au Visiteur de traverse l'arbre
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void NoeudPaletteJoueur2Droite::accepte(VisiteurAbstrait* Visiteur)
{
	Visiteur->visite(this);
}


#endif // __ARBRE_NOEUDS_NoeudPaletteJoueur2Droite_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
