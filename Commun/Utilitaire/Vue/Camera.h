////////////////////////////////////////////////////////////////////////////////////
/// @file Camera.h
/// @author DGI
/// @date 2006-12-15
/// @version 1.0 
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_CAMERA_H__
#define __UTILITAIRE_CAMERA_H__

#include "glm/glm.hpp"

namespace vue {


	///////////////////////////////////////////////////////////////////////////
	/// @class Camera
	/// @brief Classe repr�sentant une cam�ra dans le monde en 3D.
	///
	/// Cette camera encapsule les diff�rentes op�rations qu'il est possible 
	/// de faire pour d�placer le point de vue de l'observateur � l'int�rieur
	/// de la sc�ne en 3D.
	///
	/// @author Martin Bisson
	/// @date 2006-12-15
	///////////////////////////////////////////////////////////////////////////
	class Camera
	{
	public:
		/// Constructeur � partir des coordonn�es cart�siennes.
		Camera(const glm::dvec3& position,
			const glm::dvec3& pointVise,
			const glm::dvec3& directionHautCamera,
			const glm::dvec3& directionHautMonde);

		/// Destructeur virtuel vide.
		virtual ~Camera() {}

		/// Assigner la position de la cam�ra.
		inline void assignerPosition(const glm::dvec3& position);
		/// Assigner le point vis� de la cam�ra.
		inline void assignerPointVise(const glm::dvec3& pointVise);
		/// Assigner la direction du haut de la cam�ra.
		inline void assignerDirectionHaut(const glm::dvec3& directionHaut);


		/// Obtenir la position de la cam�ra.
		inline const glm::dvec3& obtenirPosition() const;
		/// Obtenir le point vis� de la cam�ra.
		inline const glm::dvec3& obtenirPointVise() const;
		/// Obtenir la direction du haut de la cam�ra.
		inline const glm::dvec3& obtenirDirectionHaut() const;

		/// D�placement dans le plan perpendiculaire � la direction vis�e.
		void deplacerXY(double deplacementX, double deplacementY);
		/// D�placement dans l'axe de la direction vis�e.
		void deplacerZ(double deplacement, bool bougePointVise);
		/// Rotation de la cam�ra autour de sa position.
		void tournerXY(double rotationX, double rotationY, bool empecheInversion = true);
		/// Rotation de la position de la cam�ra autour de son point de vis�.
		void orbiterXY(double rotationX, double rotationY, bool empecheInversion = true);



		/// Positionner la cam�ra (appel � gluLookAt).
		void positionner() const;

	private:
		/// La position de la cam�ra.
		glm::dvec3 position_;
		/// La position du point vis� par la cam�ra.
		glm::dvec3 pointVise_;
		/// La direction du haut de la cam�ra.
		glm::dvec3 directionHaut_;
		/// La direction du haut du monde de la cam�ra.
		const glm::dvec3 directionHautMonde_;

		double lastPosX_;
		double lastPosY_;

	};




	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline void Camera::assignerPosition(const glm::dvec3& position)
	///
	/// Cette fonction permet d'assigner la position de la cam�ra.
	///
	/// @param[in] position : La nouvelle position de la cam�ra.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	inline void Camera::assignerPosition(const glm::dvec3& position)
	{
		position_ = position;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline void Camera::assignerPointVise(const glm::dvec3& pointVise)
	///
	/// Cette fonction permet d'assigner le point de vis� de la cam�ra.
	///
	/// @param[in] pointVise : Le nouveau point de vis� de la cam�ra.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	inline void Camera::assignerPointVise(const glm::dvec3& pointVise)
	{
		pointVise_ = pointVise;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline void Camera::assignerDirectionHaut(const glm::dvec3& directionHaut)
	///
	/// Cette fonction permet d'assigner la direction du haut de la cam�ra.
	///
	/// @param[in] directionHaut : La nouvelle direction du haut de la cam�ra.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	inline void Camera::assignerDirectionHaut(const glm::dvec3& directionHaut)
	{
		directionHaut_ = directionHaut;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline const glm::dvec3& Camera::obtenirPosition() const
	///
	/// Cette fonction permet d'obtenir la position de la cam�ra.
	///
	/// @return La position de la cam�ra.
	///
	////////////////////////////////////////////////////////////////////////
	inline const glm::dvec3& Camera::obtenirPosition() const
	{
		return position_;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline const glm::dvec3& Camera::obtenirPointVise() const
	///
	/// Cette fonction permet d'obtenir le point de vis� de la cam�ra.
	///
	/// @return Le point de vis� de la cam�ra.
	///
	////////////////////////////////////////////////////////////////////////
	inline const glm::dvec3& Camera::obtenirPointVise() const
	{
		return pointVise_;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline const glm::dvec3& Camera::obtenirDirectionHaut() const
	///
	/// Cette fonction permet d'obtenir la direction du haut de la cam�ra.
	///
	/// @return La direction du haut de la cam�ra.
	///
	////////////////////////////////////////////////////////////////////////
	inline const glm::dvec3& Camera::obtenirDirectionHaut() const
	{
		return directionHaut_;
	}


} // Fin de l'espace de nom vue.


#endif // __UTILITAIRE_CAMERA_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
