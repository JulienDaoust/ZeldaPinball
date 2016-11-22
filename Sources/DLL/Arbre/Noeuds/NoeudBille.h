///////////////////////////////////////////////////////////////////////////
/// @file NoeudBille.h
/// @author Tommy Sagala
/// @date 2014-09-17
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDBILLE_H__
#define __ARBRE_NOEUDS_NOEUDBILLE_H__


#include "NoeudComposite.h"
#include "NoeudPortail.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"
#include <GL/gl.h>


///////////////////////////////////////////////////////////////////////////
/// @class NoeudBille
/// @brief Classe qui repr�sente un exemple de noeud de l'arbre de rendu.
///
/// @author Tommy Sagala
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////
class NoeudBille : public NoeudComposite
{
public:
	/// Constructeur � partir du type du noeud.
	NoeudBille(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudBille();

	/// Affiche le cube.
	virtual void afficherConcret() const;
	/// Effectue l'animation du cube.
	virtual void animer(float temps);

	/// Accepte le Visiteur
	virtual void accepte(VisiteurAbstrait* Visiteur);

	/// change la vitesse
	void assignerVitesse(double x, double y);

	/// obtenir vitesse en x
	double obtenirVitesseX() const;
	/// obtenir vitesse en y
	double obtenirVitesseY() const;

	/// permet de savoir si la bille est affect�e par les portails
	bool affecterParPortail(NoeudPortail* portail) const;
	/// permet d'activer les interactions avec les portails
	void assignerAffecterParPortail(NoeudPortail* portail);
	/// permet de d�sactiver les interactions avec les portails
	void assignerNonAffecterParPortail(NoeudPortail* portail);

	/// permet d'identifier les collisions
	virtual aidecollision::DetailsCollision NoeudBille::collision(NoeudAbstrait* noeud);

	/// permet de changer la condition du bool�en pour le boost de vitesse
	inline void assignerEffetButoir(bool);
	/// permet de v�rifier la valeur du boost de vitesse
	inline bool estAffectButoir() const;
	/// permet de assigner si la bille est en collision avec le dessu du ressort
	inline void assignerCollisionRessort(bool collisionRessort);
	/// permet de v�rifier si la bille est en collision avec le dessu du ressort
	inline bool collisionRessort() const;
private:
	/// Storage pour le dessin du mod�le
	modele::opengl_storage::OpenGL_Liste liste_;
	/// vitesse en x
	double vitesseX_{ 0 };
	/// vitesse en x
	double vitesseY_{ 0 };
	/// acceleration Y (gravit�)
	double accelerationY_{-9.81}; const
	/// Angle dans le sinus de l'oscillation
	float angle_{ 0 };
	/// determine si labille est affect�e par les portails
	std::list<NoeudPortail*>portailDesactives_;
	/// d�termine si la vitesse de la bile doit �tre acc�l�r� apr�s une collision
	bool affecterButoir_ = false;
	/// vitesse maximaledela bille
	int vitesseMax{ 40 };
	/// d�termine si la bille est en colission avecle dessu du ressort
	bool collisionRessort_ = false;
	/// vitesse de rotation de la bille
	double vitesseAngulaireX_ = 0;
	double vitesseAngulaireY_ = 0;};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudBille::accepte()
///
/// Cette fonction permet au Visiteur de traverse l'arbre
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
inline void NoeudBille::accepte(VisiteurAbstrait* Visiteur)
{
	Visiteur->visite(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudBille::assignerEffetButoir(bool effet)
///
/// Cette fonction permet d'assigner si la bille est acc�l�rer par une collision avec un butoir
///
/// @param effet : l'effet de la collision.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudBille::assignerEffetButoir(bool effet)
{
	affecterButoir_ = effet;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudBille::estAffectButoir() const
///
/// Cette fonction retourne si la bille est acc�l�rer par une collision avec un butoir
///
/// @param effet : aucun
///
/// @return bool�en
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudBille::estAffectButoir() const
{
	return affecterButoir_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudBille::collisionRessort() const
///
/// Cette fonction retourne si la bille est acc�l�rer par une collision avec un butoir
///
/// @return bool�en
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudBille::collisionRessort() const
{
	return collisionRessort_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudBille::assignerCollisionRessort(bool collision)
///
/// Cette fonction assigne si la bille est acc�l�rer par une collision avec un butoir
///
/// @param collision : bool
///
/// @return aucun
///
////////////////////////////////////////////////////////////////////////
inline void NoeudBille::assignerCollisionRessort(bool collision)
{
	collisionRessort_ = collision;
}
#endif // __ARBRE_NOEUDS_NOEUDBILLE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
