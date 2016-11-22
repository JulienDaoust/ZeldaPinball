///////////////////////////////////////////////////////////////////////////
/// @file NoeudPlaque.h
/// @author Loïc Sauvageau
/// @date 2014-09-17
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDPLAQUE_H__
#define __ARBRE_NOEUDS_NOEUDPLAQUE_H__


#include "NoeudComposite.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"
#include <GL/gl.h>


///////////////////////////////////////////////////////////////////////////
/// @class NoeudPlaque
/// @brief Classe qui représente un exemple de noeud de l'arbre de rendu.
///
/// @author Loïc Sauvageau
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////
class NoeudPlaque : public NoeudComposite
{
public:
	/// Constructeur à partir du type du noeud.
	NoeudPlaque(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudPlaque();

	/// Affiche le cube.
	virtual void afficherConcret() const;
	/// Effectue l'animation du cube.
	virtual void animer(float temps);
	/// Accepte le visiteur
	virtual void accepte(VisiteurAbstrait* visiteur);


private:
	/// Calcule la Boite englobante du noeud
	virtual void calculBoiteEnglobante();

	virtual BoiteEnglobante obtenirBoiteEnglobante();

	bool estBoiter;

	/// Storage pour le dessin du modèle
	modele::opengl_storage::OpenGL_Liste liste_;

	/// Angle dans le sinus de l'oscillation
	float angle_{ 0 };

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
inline void NoeudPlaque::accepte(VisiteurAbstrait* visiteur)
{
	visiteur->Visite(this);
}


#endif // __ARBRE_NOEUDS_PLAQUE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////