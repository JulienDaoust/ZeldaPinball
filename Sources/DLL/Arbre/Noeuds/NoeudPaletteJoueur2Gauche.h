///////////////-///////////////////////////////////////////////////////////
/// @file NoeudPaletteJoueur2Gauche.h
/// @author Tommy Sagala
/// @date 2014-09-17
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NoeudPaletteJoueur2Gauche_H__
#define __ARBRE_NOEUDS_NoeudPaletteJoueur2Gauche_H__

#include "NoeudAbstrait.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"
#include <GL/gl.h>

///////////////////////////////////////////////////////////////////////////
/// @class NoeudPaletteJoueur2Gauche
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Julien Gascon-Samson
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////
class NoeudPaletteJoueur2Gauche : public NoeudAbstrait
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudPaletteJoueur2Gauche(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudPaletteJoueur2Gauche();

	/// Affiche le cube.
	virtual void afficherConcret() const;
	/// Effectue l'animation du cube.
	virtual void animer(float temps);

	/// Accepte le Visiteur
	virtual void accepte(VisiteurAbstrait* Visiteur);

	virtual bool estScaleable() const;
	//Inverse le sens de l'animation
	void setAnimation();

	virtual void calculBoiteEnglobante();
private:
	double angleAnimation = 0;
	bool dansLesAir = false;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudPaletteJoueur2Gauche::accepte()
///
/// Cette fonction permet au Visiteur de traverse l'arbre
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void NoeudPaletteJoueur2Gauche::accepte(VisiteurAbstrait* Visiteur)
{
	Visiteur->visite(this);
}


#endif // __ARBRE_NOEUDS_NoeudPaletteJoueur2Gauche_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
