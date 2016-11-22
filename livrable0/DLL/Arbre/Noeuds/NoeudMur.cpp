///////////////////////////////////////////////////////////////////////////////
/// @file NoeudMur.cpp
/// @author Tommy Sagala
/// @date 2014-09-17
/// @version 1.0
///////////////////////////////////////////////////////////////////////////////
#include "NoeudMur.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>
#include <iostream>


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMur::NoeudMur(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMur::NoeudMur(const std::string& typeNoeud)
: NoeudComposite{ typeNoeud }
{
	/// Charger le modèle 3D
	modele_.charger("media/cube.obj");

	// Création d'une liste d'affichage.  ATTENTION, CECI N'EST PAS UN
	// USAGE CORRECT DES LISTES D'AFFICHAGE, puisque la même liste serait
	// recréée pour chaque instance d'un noeud, alors que la même pourrait
	// être partagée par toutes les instances d'un même type de noeud.
	liste_ = modele::opengl_storage::OpenGL_Liste{ &modele_ };
	liste_.storageCharger();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMur::~NoeudMur()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMur::~NoeudMur()
{
	liste_.storageRelacher();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMur::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMur::afficherConcret() const
{
	// Appel à la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();

	// Sauvegarde de la matrice.
	glPushMatrix();
	
	float distance = std::sqrt(((point1_.x - point2_.x)*(point1_.x - point2_.x)) + ((point1_.y - point2_.y)*(point1_.y - point2_.y))); 
	float point1x = point1_.x;
	float point2x = point2_.x;
	float point1y = point1_.y;
	float point2y = point2_.y;
	float radian1 = (point2y - point1y);
	float radian2 = (point2x - point1x);
	float radian = radian1 / radian2;

	//std::cout << "point1 x:" << point1_.x << "point1 y:" << point1_.y << "               point2 x:" << point2_.x << "point2 y:" << point2_.y << std::endl;
	//std::cout << "radian1: " << radian1 << std::endl;
	//std::cout << "radian2: " << radian2 << std::endl;
	//std::cout << "radian: " << radian << std::endl;
	//std::cout << "angleRadian: " << angle << std::endl;
	//std::cout << "angleDeg: " << angleDeg << std::endl;

	float angle = std::atan(radian);
	float angleDeg = ((angle*180) / 3.141592);
	glRotatef(angleDeg, 0, 0, 1);
	glTranslatef(distance/2.0, 0, 0);
	glScalef(distance, 1.0, 1.0);

	//glTranslatef(d2, 0.0, 0.0);
	// Révolution autour du centre.
	//glRotatef(angleRotation_, 0, 0, 1);
	// Translation.
	//glTranslatef(40, 0, 0);
	// Rotation autour de l'axe des X.
	//glRotatef(angleX_, 1, 0, 0);
	// Rotation autour de l'axe des Y.
	//glRotatef(angleY_, 0, 1, 0);
	// Recentrage du cube.
	//glTranslatef(0, 0, -10);
	// Affichage du modèle.
	liste_.dessiner();
	// Restauration de la matrice.
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
void NoeudMur::animer(float temps)
{
	// Appel à la version de la classe de base pour l'animation des enfants.
	NoeudComposite::animer(temps);

	// L'araignée oscille selon une période de 4 secondes.
	angle_ = fmod(angle_ + temps / 4.0f * 360.0f, 360.0f);
	positionRelative_[0] = 5 * cos(utilitaire::DEG_TO_RAD(angle_));
	positionRelative_[1] = 40 * sin(utilitaire::DEG_TO_RAD(angle_));
}

void NoeudMur::assigner(glm::dvec3 point1, glm::dvec3 point2)
{
	point1_ = point1;
	point2_ = point2;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
