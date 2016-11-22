///////////////////////////////////////////////////////////////////////////////
/// @file NoeudButoirCirculaire.cpp
/// @author Tommy Sagala
/// @date 2014-09-17
///////////////////////////////////////////////////////////////////////////////
#include "NoeudButoirCirculaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudButoirCirculaire::NoeudButoirCirculaire(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudButoirCirculaire::NoeudButoirCirculaire(const std::string& typeNoeud)
: NoeudAbstrait{ typeNoeud }
{
	/// Charger le modèle 3D
	modele_.charger("media/butoir_circulaire.obj");

	// Création d'une liste d'affichage.  ATTENTION, CECI N'EST PAS UN
	// USAGE CORRECT DES LISTES D'AFFICHAGE, puisque la même liste serait
	// recréée pour chaque instance d'un noeud, alors que la même pourrait
	// être partagée par toutes les instances d'un même type de noeud.
	liste_ = modele::opengl_storage::OpenGL_Liste{ &modele_ };
	liste_.storageCharger();
	calculBoiteEnglobante();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudButoirCirculaire::~NoeudButoirCirculaire()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudButoirCirculaire::~NoeudButoirCirculaire()
{
	liste_.storageRelacher();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudButoirCirculaire::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudButoirCirculaire::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();
	glTranslatef(0, 0, 0);
	//glScalef(20, 20, 20);
	// Rotation autour de l'axe des X.
	glRotatef(90, 1, 0, 0);
	// Affichage du modèle.
	liste_.dessiner();
	glPopMatrix();
	dessinerBoiteEnglobante();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCube::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudButoirCirculaire::animer(float temps)
{
	// Le cube effectue un tour à toutes les 7 secondes sur l'axe des X.
	//angleX_ = fmod(angleX_ + temps / 7.0f * 360.0f, 360.0f);
	// Le cube effectue un tour à toutes les 3 secondes sur l'axe des Y.
	//angleY_ = fmod(angleY_ + temps / 3.0f * 360.0f, 360.0f);
	// Le cube effectue une révolution à toutes les 15 secondes.
	//angleRotation_ = fmod(angleRotation_ + temps / 15.0f * 360.0f, 360.0f);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::calculBoiteEnglobante( glm::dvec3& coinHG, glm::dvec3& coinBG, glm::dvec3& coinHD, glm::dvec3& coinBD )
///
/// Cette fonction calcule la boite englobant un noeud (hitbox)
///
/// @param [in,out] coinHG  : point contenant le coin superieur gauche
/// @param [in,out] coinBG  : point contenant le coin inferieur gauche
/// @param [in,out] coinHD  : point contenant le coin superieur droite
/// @param [in,out] coinBD  : point contenant le coin inferieur droite
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudButoirCirculaire::calculBoiteEnglobante()
{
	if (scale_[0] == 0 && scale_[1] == 0 && scale_[2] == 0)
	{
		scale_[0] = 1;
		scale_[1] = 1;
		scale_[2] = 1;
	}

	utilitaire::BoiteEnglobante boite;
	boite = utilitaire::calculerBoiteEnglobante(modele_);
	double longueur = abs(boite.coinMax[0] - boite.coinMin[0]) * scale_[0];
	double hauteur = abs(boite.coinMax[2] - boite.coinMin[2]) * scale_[2];
	boiteEnglobante.coinHG = { longueur / 2 * -1, hauteur / 2, 0 };
	boiteEnglobante.coinBG = { longueur / 2 * -1, hauteur / 2 * -1, 0 };
	boiteEnglobante.coinHD = { longueur / 2, hauteur / 2, 0 };
	boiteEnglobante.coinBD = { longueur / 2, hauteur / 2 * -1, 0 };
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
